/* SPDX-License-Identifier: MIT */
/*
 * hoist_externs.c -- move unit-local `extern` globals into one shared header.
 *
 * Code rule R2 (docs/code-rules.md): each global is declared `extern` once, in
 * a header, and defined in its owning unit.  This tool reads the declaration
 * listing that `rules_check --list-globals` prints and moves every global
 * that can move safely into the header (include/globals.h by default):
 *
 *   - every unit that declares it uses the same declaration text, except
 *     that an unbounded array (`D_X[]`) agrees with one bounded form
 *     (`D_X[4]`), which the header then uses;
 *   - every type the declaration names is available to the header
 *     (the SDK base types, include/types.h, include/game_vec.h);
 *   - no unit defines it `static`, and a C definition, if any, agrees with
 *     the declaration apart from array bounds;
 *   - no other header declares it, and no declaration sits inside an #if;
 *   - no macro names it (as the macro or in its replacement), and no unit
 *     declares it as a function.
 *
 * Moved declarations are removed from their units, which gain
 * `#include "globals.h"`.  Units that define storage of their own (file-scope
 * variables or static locals) are left alone: IDO's layout of a unit's own
 * storage can shift when the unit sees thousands more declarations, which
 * the ROM build caught in src/done/main/init_34E0.c.  A line that also declares a global that cannot
 * move keeps that global, one declaration per line.  Declarations that
 * cannot move stay where they are and are reported with the reason.
 *
 * Declarations carry no code, so moving one cannot change what the compiler
 * emits for a function; the byte gates still verify every application.
 *
 * Usage: hoist_externs [--apply] [--header include/globals.h] listing.tsv
 * Without --apply the tool only reports.  Run from the repository root.
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELDS 10

typedef struct extern_row_s {
    char *path;
    int   firstLine;
    int   lastLine;
    int   block;                /* block-scope declaration */
    int   clean;
    int   conditional;
    char *name;
    char *declaration;          /* normalized tokens, space separated */
    char *comment;
    int   moves;                /* set when the global moves to the header */
} extern_row_t;

typedef struct definition_row_s {
    char *path;
    int   isStatic;
    char *name;
    char *declaration;
} definition_row_t;

typedef struct global_s {
    char       *name;
    const char *declaration;
    const char *comment;
    const char *owner;          /* defining unit, or NULL */
    const char *reason;         /* why it stays, or NULL when it moves */
    int         inHeader;       /* already declared in the target header */
    int         usesVec;        /* names a type from game_vec.h */
} global_t;

static extern_row_t     *externRows;
static int               numExternRows;
static int               maxExternRows;
static definition_row_t *definitionRows;
static int               numDefinitionRows;
static int               maxDefinitionRows;
static char            **headerTypes;      /* types the target header can name */
static int               numHeaderTypes;
static int               maxHeaderTypes;
static char            **vecTypes;         /* the subset from include/game_vec.h */
static int               numVecTypes;
static int               maxVecTypes;
static char            **functionNames;    /* names declared or defined as functions */
static int               numFunctionNames;
static int               maxFunctionNames;
static char            **macroNames;       /* names defined as macros */
static int               numMacroNames;
static int               maxMacroNames;
static global_t         *globals;
static int               numGlobals;
static int               maxGlobals;

static const char *headerPath = "include/globals.h";

static const char *const baseTypes[] = {
    "const", "volatile", "unsigned", "signed", "char", "short", "int", "long", "float", "double", "void",
    "struct", "union",
    "u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "f32", "f64",
    "vu8", "vs8", "vu16", "vs16", "vu32", "vs32", "vu64", "vs64",
    NULL
};

/*
================
Error
================
*/
static void Error( const char *fmt, ... ) {
    va_list args;

    va_start( args, fmt );
    fprintf( stderr, "hoist_externs: " );
    vfprintf( stderr, fmt, args );
    fprintf( stderr, "\n" );
    va_end( args );
    exit( 2 );
}

/*
================
Grow
================
*/
static void *Grow( void *array, int count, int *max, size_t elementSize ) {
    if ( count < *max ) {
        return array;
    }
    *max = *max ? *max * 2 : 64;
    array = realloc( array, (size_t)*max * elementSize );
    if ( !array ) {
        Error( "out of memory" );
    }
    return array;
}

/*
================
CopyString
================
*/
static char *CopyString( const char *text ) {
    size_t length = strlen( text );
    char  *copy = malloc( length + 1 );

    if ( !copy ) {
        Error( "out of memory" );
    }
    memcpy( copy, text, length + 1 );
    return copy;
}

/*
================
AddName
================
*/
static void AddName( char ***names, int *count, int *max, const char *name ) {
    *names = Grow( *names, *count, max, sizeof( **names ) );
    ( *names )[( *count )++] = CopyString( name );
}

/*
================
HasName
================
*/
static int HasName( char *const *names, int count, const char *name ) {
    int i;

    for ( i = 0; i < count; i++ ) {
        if ( !strcmp( names[i], name ) ) {
            return 1;
        }
    }
    return 0;
}

/*
================
ReadFile

Returns the whole file, or NULL when it cannot be opened.
================
*/
static char *ReadFile( const char *path ) {
    FILE *file;
    long  size;
    char *text;

    file = fopen( path, "rb" );
    if ( !file ) {
        return NULL;
    }
    fseek( file, 0, SEEK_END );
    size = ftell( file );
    fseek( file, 0, SEEK_SET );
    text = malloc( (size_t)size + 1 );
    if ( !text ) {
        Error( "out of memory" );
    }
    if ( fread( text, 1, (size_t)size, file ) != (size_t)size ) {
        Error( "cannot read %s", path );
    }
    text[size] = '\0';
    fclose( file );
    return text;
}

/*
================
WriteFile
================
*/
static void WriteFile( const char *path, const char *text ) {
    FILE *file = fopen( path, "wb" );

    if ( !file ) {
        Error( "cannot write %s", path );
    }
    fputs( text, file );
    fclose( file );
}

/*
===============================================================================

LISTING

===============================================================================
*/

/*
================
SplitFields

Splits a tab-separated line in place.  Returns the field count.
================
*/
static int SplitFields( char *line, char **fields ) {
    int count = 0;

    fields[count++] = line;
    for ( ; *line; line++ ) {
        if ( *line == '\t' && count < MAX_FIELDS ) {
            *line = '\0';
            fields[count++] = line + 1;
        } else if ( *line == '\n' || *line == '\r' ) {
            *line = '\0';
            break;
        }
    }
    return count;
}

/*
================
LoadListing
================
*/
static void LoadListing( const char *path ) {
    char *text;
    char *line;

    text = ReadFile( path );
    if ( !text ) {
        Error( "cannot open %s", path );
    }
    for ( line = text; *line; ) {
        char *next = strchr( line, '\n' );
        char *fields[MAX_FIELDS];
        int   count;

        if ( next ) {
            *next++ = '\0';
        } else {
            next = line + strlen( line );
        }
        count = SplitFields( line, fields );
        if ( !strcmp( fields[0], "E" ) && count >= 10 ) {
            extern_row_t *row;

            externRows = Grow( externRows, numExternRows, &maxExternRows, sizeof( *externRows ) );
            row = &externRows[numExternRows++];
            row->path = CopyString( fields[1] );
            row->firstLine = atoi( fields[2] );
            row->lastLine = atoi( fields[3] );
            row->block = !strcmp( fields[4], "block" );
            row->clean = atoi( fields[5] );
            row->conditional = atoi( fields[6] );
            row->name = CopyString( fields[7] );
            row->declaration = CopyString( fields[8] );
            row->comment = CopyString( fields[9] );
            row->moves = 0;
        } else if ( !strcmp( fields[0], "D" ) && count >= 6 ) {
            definition_row_t *row;

            definitionRows = Grow( definitionRows, numDefinitionRows, &maxDefinitionRows, sizeof( *definitionRows ) );
            row = &definitionRows[numDefinitionRows++];
            row->path = CopyString( fields[1] );
            row->isStatic = atoi( fields[3] );
            row->name = CopyString( fields[4] );
            row->declaration = CopyString( fields[5] );
        } else if ( !strcmp( fields[0], "P" ) && count >= 3 ) {
            AddName( &functionNames, &numFunctionNames, &maxFunctionNames, fields[2] );
        } else if ( !strcmp( fields[0], "M" ) && count >= 3 ) {
            AddName( &macroNames, &numMacroNames, &maxMacroNames, fields[2] );
        } else if ( !strcmp( fields[0], "T" ) && count >= 3 ) {
            if ( !strcmp( fields[1], "include/types.h" ) ) {
                AddName( &headerTypes, &numHeaderTypes, &maxHeaderTypes, fields[2] );
            } else if ( !strcmp( fields[1], "include/game_vec.h" ) ) {
                AddName( &headerTypes, &numHeaderTypes, &maxHeaderTypes, fields[2] );
                AddName( &vecTypes, &numVecTypes, &maxVecTypes, fields[2] );
            }
        }
        line = next;
    }
    free( text );
}

/*
===============================================================================

DECISIONS

===============================================================================
*/

/*
================
IsWord
================
*/
static int IsWord( const char *token ) {
    return isalnum( (unsigned char)token[0] ) || token[0] == '_';
}

/*
================
CheckTypes

True when every identifier in the declaration, other than the global's own
name, is a type the header can name.  Sets *usesVec for game_vec.h types.
================
*/
static int CheckTypes( const char *declaration, const char *name, int *usesVec ) {
    char *copy = CopyString( declaration );
    char *token;
    int   ok = 1;

    *usesVec = 0;
    for ( token = strtok( copy, " " ); token; token = strtok( NULL, " " ) ) {
        int i;
        int known = 0;

        if ( !IsWord( token ) || isdigit( (unsigned char)token[0] ) || !strcmp( token, name ) ) {
            continue;
        }
        for ( i = 0; baseTypes[i]; i++ ) {
            if ( !strcmp( baseTypes[i], token ) ) {
                known = 1;
            }
        }
        if ( !known && HasName( headerTypes, numHeaderTypes, token ) ) {
            known = 1;
            if ( HasName( vecTypes, numVecTypes, token ) ) {
                *usesVec = 1;
            }
        }
        if ( !known ) {
            ok = 0;
        }
    }
    free( copy );
    return ok;
}

/*
================
WithoutBounds

The declaration with array bounds removed (`s32 D_X [ 4 ]` -> `s32 D_X [ ]`).
================
*/
static char *WithoutBounds( const char *declaration ) {
    char       *result = CopyString( declaration );
    const char *open = strchr( declaration, '[' );
    const char *close = open ? strchr( open, ']' ) : NULL;

    // only the outermost bound: `[ 2 ] [ 4 ]` and `[ ] [ 4 ]` agree, `[ ] [ 8 ]` does not
    if ( close ) {
        sprintf( result + ( open - declaration ), "[ ]%s", close + 1 );
    }
    return result;
}

/*
================
FindGlobal
================
*/
static global_t *FindGlobal( const char *name ) {
    int i;

    for ( i = 0; i < numGlobals; i++ ) {
        if ( !strcmp( globals[i].name, name ) ) {
            return &globals[i];
        }
    }
    return NULL;
}

/*
================
IsTargetHeader
================
*/
static int IsTargetHeader( const char *path ) {
    return !strcmp( path, headerPath );
}

/*
================
IsHeader
================
*/
static int IsHeader( const char *path ) {
    size_t length = strlen( path );

    return length > 2 && !strcmp( path + length - 2, ".h" );
}

/*
================
CompareGlobals

Owner groups first (by owning unit), then unowned data; by name within.
================
*/
static int CompareGlobals( const void *a, const void *b ) {
    const global_t *globalA = a;
    const global_t *globalB = b;

    if ( !globalA->owner != !globalB->owner ) {
        return globalA->owner ? -1 : 1;
    }
    if ( globalA->owner && strcmp( globalA->owner, globalB->owner ) ) {
        return strcmp( globalA->owner, globalB->owner );
    }
    return strcmp( globalA->name, globalB->name );
}

/*
================
DefinesStorage

True when a unit defines variables of its own: a file-scope definition, or
a `static` local.  Such units keep their extern declarations and do not
include the shared header: IDO lays out a unit's own storage in an order
that can shift when the unit sees thousands more declarations.
================
*/
static char **storageUnits;
static int    numStorageUnits;
static int    maxStorageUnits;
static char **checkedUnits;
static int    numCheckedUnits;
static int    maxCheckedUnits;

static int DefinesStorage( const char *path ) {
    char       *text;
    const char *line;
    int         i;

    if ( HasName( checkedUnits, numCheckedUnits, path ) ) {
        return HasName( storageUnits, numStorageUnits, path );
    }
    AddName( &checkedUnits, &numCheckedUnits, &maxCheckedUnits, path );
    for ( i = 0; i < numDefinitionRows; i++ ) {
        if ( !strcmp( definitionRows[i].path, path ) ) {
            AddName( &storageUnits, &numStorageUnits, &maxStorageUnits, path );
            return 1;
        }
    }
    text = ReadFile( path );
    if ( !text ) {
        return 0;
    }
    // a static local is an indented `static`; file-scope statics are definition rows
    for ( line = text; line; line = strchr( line, '\n' ) ) {
        const char *p;

        if ( *line == '\n' ) {
            line++;
        }
        for ( p = line; *p == ' ' || *p == '\t'; p++ ) {
        }
        if ( p > line && !strncmp( p, "static", 6 ) && isspace( (unsigned char)p[6] ) ) {
            AddName( &storageUnits, &numStorageUnits, &maxStorageUnits, path );
            free( text );
            return 1;
        }
    }
    free( text );
    return 0;
}

/*
================
Decide

Builds the global table and marks which globals move.
================
*/
static void Decide( void ) {
    int i;
    int j;

    for ( i = 0; i < numExternRows; i++ ) {
        extern_row_t *row = &externRows[i];
        global_t     *global;

        if ( !row->name[0] ) {
            continue;
        }
        global = FindGlobal( row->name );
        if ( !global ) {
            globals = Grow( globals, numGlobals, &maxGlobals, sizeof( *globals ) );
            global = &globals[numGlobals++];
            memset( global, 0, sizeof( *global ) );
            global->name = row->name;
        }
        if ( IsTargetHeader( row->path ) ) {
            global->inHeader = 1;
            global->declaration = row->declaration;
            global->comment = row->comment;
        }
    }

    for ( i = 0; i < numGlobals; i++ ) {
        global_t *global = &globals[i];

        for ( j = 0; j < numExternRows && !global->reason; j++ ) {
            extern_row_t *row = &externRows[j];

            if ( strcmp( row->name, global->name ) || IsTargetHeader( row->path ) ) {
                continue;
            }
            if ( IsHeader( row->path ) ) {
                global->reason = "declared in another header";
            } else if ( row->conditional ) {
                global->reason = "declared inside #if";
            } else if ( !global->declaration ) {
                global->declaration = row->declaration;
                global->comment = row->comment;
            } else if ( strcmp( global->declaration, row->declaration ) ) {
                // declarations that differ only in the outer array bound agree; the header takes the bound
                char *current = WithoutBounds( global->declaration );
                char *other = WithoutBounds( row->declaration );
                int   currentBounded = strcmp( current, global->declaration ) != 0;
                int   otherBounded = strcmp( other, row->declaration ) != 0;

                if ( strcmp( current, other ) || ( currentBounded && otherBounded ) ) {
                    global->reason = "declared with different types";
                } else if ( otherBounded ) {
                    global->declaration = row->declaration;
                }
                free( current );
                free( other );
            }
            if ( global->comment && !global->comment[0] && row->comment[0] ) {
                global->comment = row->comment;
            }
        }
        if ( !global->reason && HasName( macroNames, numMacroNames, global->name ) ) {
            global->reason = "aliased by a macro";
        }
        if ( !global->reason && HasName( functionNames, numFunctionNames, global->name ) ) {
            global->reason = "also declared as a function";
        }
        if ( !global->reason && !CheckTypes( global->declaration, global->name, &global->usesVec ) ) {
            global->reason = "names a type the header cannot see";
        }
        for ( j = 0; j < numDefinitionRows && !global->reason; j++ ) {
            definition_row_t *def = &definitionRows[j];
            char             *defText;
            char             *declText;

            if ( strcmp( def->name, global->name ) ) {
                continue;
            }
            if ( def->isStatic ) {
                global->reason = "a unit defines it static";
                continue;
            }
            defText = WithoutBounds( def->declaration );
            declText = WithoutBounds( global->declaration );
            if ( strcmp( defText, declText ) ) {
                global->reason = "its definition has a different type";
            } else {
                global->owner = def->path;
            }
            free( defText );
            free( declText );
        }
    }

    for ( i = 0; i < numExternRows; i++ ) {
        global_t *global = externRows[i].name[0] ? FindGlobal( externRows[i].name ) : NULL;

        externRows[i].moves = global && !global->reason && !IsHeader( externRows[i].path )
            && !DefinesStorage( externRows[i].path );
    }
}

/*
===============================================================================

EDITING

===============================================================================
*/

typedef struct line_s {
    char *text;                 /* without the line ending */
    int   removed;
} line_t;

/*
================
Pretty

Formats normalized declaration tokens as source: `const u8 * D_X [ ]`
becomes `const u8 *D_X[]`.
================
*/
static char *Pretty( const char *declaration ) {
    char       *result = malloc( strlen( declaration ) + 1 );
    char       *copy = CopyString( declaration );
    char       *out = result;
    const char *previous = NULL;
    char       *token;

    if ( !result ) {
        Error( "out of memory" );
    }
    for ( token = strtok( copy, " " ); token; token = strtok( NULL, " " ) ) {
        if ( previous && ( ( IsWord( previous ) && ( IsWord( token ) || !strcmp( token, "*" ) || !strcmp( token, "(" ) ) )
            || !strcmp( previous, "," ) ) ) {
            *out++ = ' ';
        }
        strcpy( out, token );
        out += strlen( token );
        previous = token;
    }
    *out = '\0';
    free( copy );
    return result;
}

/*
================
SplitLines

Splits text into lines; sets *crlf when the file uses CRLF endings.
================
*/
static line_t *SplitLines( char *text, int *count, int *crlf ) {
    line_t *lines = NULL;
    int     max = 0;
    char   *p = text;

    *count = 0;
    *crlf = strstr( text, "\r\n" ) != NULL;
    while ( *p ) {
        char *end = strchr( p, '\n' );
        char *next;

        if ( end ) {
            next = end + 1;
            if ( end > p && end[-1] == '\r' ) {
                end--;
            }
            *end = '\0';
        } else {
            next = p + strlen( p );
        }
        lines = Grow( lines, *count, &max, sizeof( *lines ) );
        lines[*count].text = p;
        lines[*count].removed = 0;
        ( *count )++;
        p = next;
    }
    return lines;
}

/*
================
IsBlank
================
*/
static int IsBlank( const char *text ) {
    for ( ; *text; text++ ) {
        if ( !isspace( (unsigned char)*text ) ) {
            return 0;
        }
    }
    return 1;
}

/*
================
EditUnit

Removes the moved declarations from one unit and adds the include.
Returns the number of declarations removed.
================
*/
static int EditUnit( const char *path, int apply ) {
    char       *text;
    line_t     *lines;
    char      **extra;              /* replacement lines, indexed by line */
    int         count;
    int         crlf;
    int         removed = 0;
    int         lastInclude = -1;
    int         hasInclude = 0;
    int         i;
    int         j;
    const char *newline;
    size_t      size;
    char       *out;
    char       *p;

    text = ReadFile( path );
    if ( !text ) {
        Error( "cannot open %s", path );
    }
    lines = SplitLines( text, &count, &crlf );
    newline = crlf ? "\r\n" : "\n";
    extra = calloc( (size_t)count + 1, sizeof( *extra ) );
    if ( !extra ) {
        Error( "out of memory" );
    }

    // each declaration statement (a line range) is removed when all its globals move
    for ( i = 0; i < numExternRows; i++ ) {
        extern_row_t *row = &externRows[i];
        int           anyMoves = 0;
        int           allMove = 1;
        int           clean = 1;
        size_t        keepSize = 1;
        char         *keep;
        const char   *indent;
        int           indentLength;

        if ( strcmp( row->path, path ) || ( i > 0 && !strcmp( externRows[i - 1].path, path )
            && externRows[i - 1].firstLine == row->firstLine ) ) {
            continue;               // not this unit, or not the first row of its statement
        }
        for ( j = i; j < numExternRows && !strcmp( externRows[j].path, path )
            && externRows[j].firstLine == row->firstLine; j++ ) {
            anyMoves |= externRows[j].moves;
            allMove &= externRows[j].moves;
            clean &= externRows[j].clean;
            keepSize += strlen( externRows[j].declaration ) + strlen( externRows[j].comment ) + 64;
        }
        if ( !anyMoves || !clean || row->firstLine < 1 || row->lastLine > count ) {
            continue;
        }
        for ( j = row->firstLine; j <= row->lastLine; j++ ) {
            lines[j - 1].removed = 1;
        }
        if ( allMove ) {
            continue;
        }

        // keep the globals that stay, one declaration per line, with the line's indent
        indent = lines[row->firstLine - 1].text;
        indentLength = (int)strspn( indent, " \t" );
        keep = malloc( keepSize + (size_t)indentLength * 16 );
        if ( !keep ) {
            Error( "out of memory" );
        }
        keep[0] = '\0';
        for ( j = i; j < numExternRows && !strcmp( externRows[j].path, path )
            && externRows[j].firstLine == row->firstLine; j++ ) {
            char *declaration;

            if ( externRows[j].moves ) {
                continue;
            }
            declaration = Pretty( externRows[j].declaration );
            if ( keep[0] ) {
                strcat( keep, newline );
            }
            strncat( keep, indent, (size_t)indentLength );
            strcat( keep, "extern " );
            strcat( keep, declaration );
            strcat( keep, ";" );
            if ( externRows[j].comment[0] ) {
                strcat( keep, " " );
                strcat( keep, externRows[j].comment );
            }
            free( declaration );
        }
        extra[row->firstLine - 1] = keep;
    }
    for ( i = 0; i < numExternRows; i++ ) {
        if ( !strcmp( externRows[i].path, path ) && externRows[i].moves && lines[externRows[i].firstLine - 1].removed ) {
            removed++;
        }
    }
    if ( !removed ) {
        free( extra );
        free( lines );
        free( text );
        return 0;
    }

    // drop blank lines that a removal left doubled, or left at the top of a block
    for ( i = 0; i < count; i++ ) {
        int before;
        int after;

        if ( !lines[i].removed || extra[i] || ( i + 1 < count && lines[i + 1].removed ) ) {
            continue;
        }
        // i ends a removed run: find the kept neighbours
        for ( before = i; before >= 0 && lines[before].removed && !extra[before]; before-- ) {
        }
        after = i + 1;
        if ( after < count && IsBlank( lines[after].text ) && !extra[after]
            && ( before < 0 || IsBlank( lines[before].text ) || lines[before].text[strlen( lines[before].text ) - 1] == '{' ) ) {
            lines[after].removed = 1;
        }
    }

    // the include goes after the last #include of the leading include block
    for ( i = 0; i < count; i++ ) {
        const char *line = lines[i].text;

        if ( !strncmp( line, "#include", 8 ) ) {
            lastInclude = i;
            if ( strstr( line, "\"globals.h\"" ) ) {
                hasInclude = 1;
            }
            continue;
        }
        if ( !IsBlank( line ) && line[0] != '#' ) {
            break;
        }
    }
    if ( lastInclude < 0 ) {
        Error( "%s has no #include block to extend", path );
    }

    size = strlen( path ) + 64;
    for ( i = 0; i < count; i++ ) {
        size += strlen( lines[i].text ) + 2 + ( extra[i] ? strlen( extra[i] ) + 2 : 0 );
    }
    out = malloc( size );
    if ( !out ) {
        Error( "out of memory" );
    }
    p = out;
    for ( i = 0; i < count; i++ ) {
        if ( extra[i] ) {
            p += sprintf( p, "%s%s", extra[i], newline );
        }
        if ( !lines[i].removed ) {
            p += sprintf( p, "%s%s", lines[i].text, newline );
        }
        if ( i == lastInclude && !hasInclude ) {
            p += sprintf( p, "#include \"globals.h\"%s", newline );
        }
    }
    *p = '\0';
    if ( apply ) {
        WriteFile( path, out );
    }
    for ( i = 0; i < count; i++ ) {
        free( extra[i] );
    }
    free( out );
    free( extra );
    free( lines );
    free( text );
    return removed;
}

/*
================
WriteHeader
================
*/
static int WriteHeader( int apply ) {
    FILE       *file;
    global_t  **moved;
    int         numMoved = 0;
    int         usesVec = 0;
    const char *group = "";
    int         i;

    qsort( globals, (size_t)numGlobals, sizeof( *globals ), CompareGlobals );
    moved = malloc( ( (size_t)numGlobals + 1 ) * sizeof( *moved ) );
    if ( !moved ) {
        Error( "out of memory" );
    }
    for ( i = 0; i < numGlobals; i++ ) {
        // a global the header already declares stays there even when a unit now disagrees
        if ( !globals[i].reason || globals[i].inHeader ) {
            moved[numMoved++] = &globals[i];
            usesVec |= globals[i].usesVec;
        }
    }
    if ( !apply ) {
        free( moved );
        return numMoved;
    }
    file = fopen( headerPath, "wb" );
    if ( !file ) {
        Error( "cannot write %s", headerPath );
    }
    fprintf( file, "#ifndef CONKER_GLOBALS_H\n#define CONKER_GLOBALS_H\n\n#include \"types.h\"\n" );
    if ( usesVec ) {
        fprintf( file, "#include \"game_vec.h\"\n" );
    }
    fprintf( file,
        "\n"
        "/*\n"
        " * Globals that matched C uses, each declared once (docs/code-rules.md, R2).\n"
        " * Globals a C unit defines are grouped under that unit; the rest live in\n"
        " * data that no C unit owns yet. Sorted by name within each group.\n"
        " * Maintained by ./conker hoist-externs.\n"
        " */\n" );
    for ( i = 0; i < numMoved; i++ ) {
        const char *owner = moved[i]->owner ? moved[i]->owner : "";
        char       *declaration = Pretty( moved[i]->declaration );

        if ( i == 0 || strcmp( owner, group ) ) {
            group = owner;
            fprintf( file, "\n/* %s */\n", owner[0] ? owner : "data not yet owned by a C unit" );
        }
        fprintf( file, "extern %s;", declaration );
        if ( moved[i]->comment && moved[i]->comment[0] ) {
            fprintf( file, " %s", moved[i]->comment );
        }
        fprintf( file, "\n" );
        free( declaration );
    }
    fprintf( file, "\n#endif\n" );
    fclose( file );
    free( moved );
    return numMoved;
}

/*
================
main
================
*/
int main( int argc, char **argv ) {
    const char **paths = NULL;
    const char  *listing = NULL;
    int          numPaths = 0;
    int          maxPaths = 0;
    int          apply = 0;
    int          sites = 0;
    int          units = 0;
    int          moved;
    int          i;

    for ( i = 1; i < argc; i++ ) {
        if ( !strcmp( argv[i], "--apply" ) ) {
            apply = 1;
        } else if ( !strcmp( argv[i], "--header" ) && i + 1 < argc ) {
            headerPath = argv[++i];
        } else if ( argv[i][0] == '-' ) {
            Error( "usage: hoist_externs [--apply] [--header include/globals.h] listing.tsv" );
        } else {
            listing = argv[i];
        }
    }
    if ( !listing ) {
        Error( "usage: hoist_externs [--apply] [--header include/globals.h] listing.tsv" );
    }
    LoadListing( listing );
    Decide();

    // units with at least one moved declaration, in listing order
    for ( i = 0; i < numExternRows; i++ ) {
        int j;
        int seen = 0;

        if ( !externRows[i].moves ) {
            continue;
        }
        for ( j = 0; j < numPaths; j++ ) {
            if ( !strcmp( paths[j], externRows[i].path ) ) {
                seen = 1;
            }
        }
        if ( !seen ) {
            paths = Grow( paths, numPaths, &maxPaths, sizeof( *paths ) );
            paths[numPaths++] = externRows[i].path;
        }
    }
    for ( i = 0; i < numPaths; i++ ) {
        int removed = EditUnit( paths[i], apply );

        sites += removed;
        units += removed > 0;
    }
    moved = WriteHeader( apply );

    printf( "%s: %d globals declared in %s; %d declarations removed from %d units\n",
        apply ? "applied" : "dry run", moved, headerPath, sites, units );
    printf( "  left alone: %d units that define their own storage\n", numStorageUnits );
    {
        static const char *const reasons[] = {
            "declared with different types", "names a type the header cannot see", "a unit defines it static",
            "its definition has a different type", "declared in another header", "declared inside #if",
            "aliased by a macro", "also declared as a function", NULL
        };
        int r;

        for ( r = 0; reasons[r]; r++ ) {
            int count = 0;

            for ( i = 0; i < numGlobals; i++ ) {
                if ( globals[i].reason && !strcmp( globals[i].reason, reasons[r] ) ) {
                    count++;
                }
            }
            printf( "  stays: %-40s %5d globals\n", reasons[r], count );
        }
    }
    return 0;
}
