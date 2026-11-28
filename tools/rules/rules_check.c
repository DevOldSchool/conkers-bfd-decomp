/* SPDX-License-Identifier: MIT */
/*
 * rules_check.c -- read-only code-rule checker for the decompiled C sources.
 *
 * Every live C function definition in src/ is a byte-matched function: the
 * project keeps unmatched functions as GLOBAL_ASM and parks unfinished bodies
 * in `#if 0` blocks whose comment names CONKER_DEFERRED_CANDIDATE, which this
 * tool skips.
 * Each matched function is graded against the [match] rules of the project's
 * code-rule profile (docs/code-rules.md):
 *
 *   R1   the same type name with conflicting definitions in two files
 *   R2   a global declared `extern` outside a header and used by the function
 *   R4   fixed-offset access: a constant added to a byte-pointer cast, or a
 *        dereference cast of a byte pointer plus a constant
 *   R17  fake code: `volatile` without a `volatile:` evidence note, empty
 *        if/else blocks, bare `;` statements, `do { } while (0)` in a body,
 *        self-assignment, `+ 0` and `* 1`
 *   R18  inline assembly
 *
 * A function with any [match] finding is MATCH-PENDING; the rest are matched
 * under the rules.  Advisory findings (placeholder names R7, missing header
 * comments R33, braceless bodies R35, file-scope prototypes R25, `#if 0`
 * outside the parking form R37, padding members R27) never block a match.
 *
 * The tool never edits files.  It lexes C without preprocessing, so it is a
 * conservative filter, not a compiler: macros are not expanded.
 *
 * Usage: rules_check [--findings] [--advisory] [--pending] [--strict-padding]
 *                    [--fail-on-pending] [--max-lines N] [--list-globals] [path...]
 * Paths are files or directories; the default is `include src`, and include/
 * is always read.  Only .c and .h files are read.  Headers contribute
 * declarations and types; functions are graded only in .c files.  R1 compares
 * only the files read, so a run over part of src/ can miss a conflicting
 * copy.  The exit status is 0 unless an I/O error
 * occurs, or --fail-on-pending is given and a function is MATCH-PENDING.
 */

#include <ctype.h>
#include <dirent.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define PARKING_MARKER "CONKER_DEFERRED_CANDIDATE"
#define VOLATILE_NOTE  "volatile:"

enum {
    TOK_IDENT,
    TOK_NUM,
    TOK_PUNCT,
    TOK_STR,
    TOK_CHAR,
    TOK_COMMENT,
    TOK_PP
};

/* rule identifiers, in report order */
enum {
    RULE_R1,
    RULE_R2,
    RULE_R4,
    RULE_R17,
    RULE_R18,
    NUM_MATCH_RULES,
    RULE_R7 = NUM_MATCH_RULES,
    RULE_R25,
    RULE_R27,
    RULE_R33,
    RULE_R35,
    RULE_R37,
    NUM_RULES
};

static const char *const ruleNames[NUM_RULES] = {
    "R1", "R2", "R4", "R17", "R18", "R7", "R25", "R27", "R33", "R35", "R37"
};

static const char *const ruleTitles[NUM_RULES] = {
    "same type name with conflicting definitions",
    "global declared extern outside a header",
    "fixed-offset access through a byte pointer",
    "fake code",
    "inline assembly",
    "placeholder names",
    "prototype outside a header",
    "padding member (name it unk_<HEX>)",
    "function without a header comment",
    "body without braces",
    "#if 0 outside the parking form"
};

typedef struct token_s {
    int   kind;
    int   line;
    char *text;
} token_t;

typedef struct finding_s {
    int   rule;
    int   line;
    char *message;
} finding_t;

typedef struct function_s {
    char      *name;
    int        line;
    int        bodyStart;           /* token index of the opening brace */
    int        bodyEnd;             /* token index of the closing brace */
    int        paramStart;          /* token index of the opening parenthesis */
    finding_t *findings;
    int        numFindings;
    int        maxFindings;
    unsigned   matchRules;          /* bit per [match] rule that fired */
    unsigned   advisoryRules;       /* bit per advisory rule that fired */
} function_t;

typedef struct name_list_s {
    char **names;
    int   *lines;
    int    count;
    int    max;
} name_list_t;

typedef struct unit_s {
    char        *path;
    int          isHeader;
    token_t     *tokens;
    int          numTokens;
    int          maxTokens;
    function_t  *functions;
    int          numFunctions;
    int          maxFunctions;
    name_list_t  externs;           /* globals declared extern at any scope */
    name_list_t  prototypes;        /* file-scope prototypes */
    name_list_t  volatileMembers;   /* struct members declared volatile */
    name_list_t  padMembers;        /* struct members named pad* */
    name_list_t  disabledBlocks;    /* `#if 0` blocks outside the parking form */
    name_list_t  defines;           /* macros the file defines in read regions */
    name_list_t  includes;          /* basenames of the "..." headers it includes */
    name_list_t  volatileOwners;    /* the type name each volatileMembers entry belongs to */
    int         *ppDepth;           /* --list-globals: #if nesting before each token */
} unit_t;

typedef struct type_def_s {
    char *name;
    char *body;
    int   unit;
    int   line;
} type_def_t;

static unit_t     *units;
static int         numUnits;
static int         maxUnits;
static type_def_t *typeDefs;
static int         numTypeDefs;
static int         maxTypeDefs;

static int optFindings;
static int optAdvisory;
static int optPending;
static int optStrictPadding;
static int optFailOnPending;
static int optMaxLines = -1;
static int optListGlobals;

/*
================
Error
================
*/
static void Error( const char *fmt, ... ) {
    va_list args;

    va_start( args, fmt );
    fprintf( stderr, "rules_check: " );
    vfprintf( stderr, fmt, args );
    fprintf( stderr, "\n" );
    va_end( args );
    exit( 2 );
}

/*
================
Grow

Ensures room for one more element in a growable array.
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
static char *CopyString( const char *start, size_t length ) {
    char *copy;

    copy = malloc( length + 1 );
    if ( !copy ) {
        Error( "out of memory" );
    }
    memcpy( copy, start, length );
    copy[length] = '\0';
    return copy;
}

/*
================
FormatString
================
*/
static char *FormatString( const char *fmt, ... ) {
    char    buffer[512];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buffer, sizeof( buffer ), fmt, args );
    va_end( args );
    return CopyString( buffer, strlen( buffer ) );
}

/*
================
NameList_Add
================
*/
static void NameList_Add( name_list_t *list, const char *name, int line ) {
    list->names = Grow( list->names, list->count, &list->max, sizeof( *list->names ) );
    list->lines = realloc( list->lines, (size_t)list->max * sizeof( *list->lines ) );
    if ( !list->lines ) {
        Error( "out of memory" );
    }
    list->names[list->count] = CopyString( name, strlen( name ) );
    list->lines[list->count] = line;
    list->count++;
}

/*
================
NameList_Find

Returns the index of name in the list, or -1.
================
*/
static int NameList_Find( const name_list_t *list, const char *name ) {
    int i;

    for ( i = 0; i < list->count; i++ ) {
        if ( !strcmp( list->names[i], name ) ) {
            return i;
        }
    }
    return -1;
}

/*
================
NameList_Remove

Removes every entry with the given name.
================
*/
static void NameList_Remove( name_list_t *list, const char *name ) {
    int i;
    int kept = 0;

    for ( i = 0; i < list->count; i++ ) {
        if ( !strcmp( list->names[i], name ) ) {
            free( list->names[i] );
            continue;
        }
        list->names[kept] = list->names[i];
        list->lines[kept] = list->lines[i];
        kept++;
    }
    list->count = kept;
}

/*
===============================================================================

LEXER

===============================================================================
*/

/*
================
AddToken
================
*/
static void AddToken( unit_t *unit, int kind, int line, const char *start, size_t length ) {
    token_t *token;

    unit->tokens = Grow( unit->tokens, unit->numTokens, &unit->maxTokens, sizeof( *unit->tokens ) );
    token = &unit->tokens[unit->numTokens++];
    token->kind = kind;
    token->line = line;
    token->text = CopyString( start, length );
}

/*
================
DirectiveIs

True when a preprocessor line (starting at '#') is the given directive.
================
*/
static int DirectiveIs( const char *text, const char *directive ) {
    size_t length;

    text++;
    while ( *text == ' ' || *text == '\t' ) {
        text++;
    }
    length = strlen( directive );
    return !strncmp( text, directive, length ) && !isalnum( (unsigned char)text[length] )
        && text[length] != '_';
}

/*
================
IsDisabledIf

True for `#if 0`.
================
*/
static int IsDisabledIf( const char *text ) {
    if ( !DirectiveIs( text, "if" ) ) {
        return 0;
    }
    text = strstr( text, "if" ) + 2;
    while ( *text == ' ' || *text == '\t' ) {
        text++;
    }
    return text[0] == '0' && !isalnum( (unsigned char)text[1] );
}

/*
================
MacroName

Copies the identifier after a directive (`#define NAME`, `#ifdef NAME`).
================
*/
static int MacroName( const char *text, const char *directive, char *name, size_t size ) {
    const char *p = strstr( text, directive );
    size_t      length = 0;

    if ( !p ) {
        return 0;
    }
    for ( p += strlen( directive ); *p == ' ' || *p == '\t'; p++ ) {
    }
    while ( ( isalnum( (unsigned char)p[length] ) || p[length] == '_' ) && length + 1 < size ) {
        name[length] = p[length];
        length++;
    }
    name[length] = '\0';
    return length > 0;
}

/*
================
IsDefined

True for the macros the US build defines (Makefile CFLAGS), those the file
has defined and not #undef'd so far, and those of the include/ headers it
has included, followed transitively.  SDK headers (lib/ultralib) are not
read, so their macros count as undefined.
================
*/
static int HeaderDefines( const char *header, const char *name, int depth ) {
    int u;
    int i;

    if ( depth > 16 ) {
        return 0;
    }
    for ( u = 0; u < numUnits; u++ ) {
        const unit_t *unit = &units[u];
        const char   *base = strrchr( unit->path, '/' );

        if ( !unit->isHeader || strcmp( base ? base + 1 : unit->path, header ) ) {
            continue;
        }
        if ( NameList_Find( &unit->defines, name ) >= 0 ) {
            return 1;
        }
        for ( i = 0; i < unit->includes.count; i++ ) {
            if ( HeaderDefines( unit->includes.names[i], name, depth + 1 ) ) {
                return 1;
            }
        }
    }
    return 0;
}

static int IsDefined( const unit_t *unit, const char *name ) {
    // keep in sync with CFLAGS and PROFILE_CFLAGS_us in the Makefile
    static const char *const buildDefines[] = { "_LANGUAGE_C", "_FINALROM", "_MIPS_SZLONG", "PROFILE_US", NULL };
    int i;

    for ( i = 0; buildDefines[i]; i++ ) {
        if ( !strcmp( buildDefines[i], name ) ) {
            return 1;
        }
    }
    if ( NameList_Find( &unit->defines, name ) >= 0 ) {
        return 1;
    }
    for ( i = 0; i < unit->includes.count; i++ ) {
        if ( HeaderDefines( unit->includes.names[i], name, 0 ) ) {
            return 1;
        }
    }
    return 0;
}

/*
================
EvaluateCondition

The value of an #if, #elif, #ifdef or #ifndef line: 0 and 1, `defined X`,
`!defined X` and a bare macro name are evaluated; anything else counts as
true, so exactly one branch of every chain is read.
================
*/
static int EvaluateCondition( const unit_t *unit, const char *text ) {
    char        name[256];
    const char *p;
    int         negate = 0;

    if ( DirectiveIs( text, "ifdef" ) ) {
        return MacroName( text, "ifdef", name, sizeof( name ) ) && IsDefined( unit, name );
    }
    if ( DirectiveIs( text, "ifndef" ) ) {
        return !( MacroName( text, "ifndef", name, sizeof( name ) ) && IsDefined( unit, name ) );
    }
    p = strstr( text, DirectiveIs( text, "elif" ) ? "elif" : "if" ) + ( DirectiveIs( text, "elif" ) ? 4 : 2 );
    while ( *p == ' ' || *p == '\t' ) {
        p++;
    }
    if ( *p == '!' ) {
        negate = 1;
        for ( p++; *p == ' ' || *p == '\t'; p++ ) {
        }
    }
    if ( isdigit( (unsigned char)*p ) ) {
        const char *end = p;

        while ( isalnum( (unsigned char)*end ) ) {
            end++;
        }
        if ( *end && !isspace( (unsigned char)*end ) && *end != '/' ) {
            return 1;               // an expression, not a lone number
        }
        return negate ^ ( strtol( p, NULL, 0 ) != 0 );
    }
    if ( !strncmp( p, "defined", 7 ) && !isalnum( (unsigned char)p[7] ) && p[7] != '_' ) {
        size_t length = 0;

        for ( p += 7; *p == ' ' || *p == '\t' || *p == '('; p++ ) {
        }
        while ( ( isalnum( (unsigned char)p[length] ) || p[length] == '_' ) && length + 1 < sizeof( name ) ) {
            name[length] = p[length];
            length++;
        }
        name[length] = '\0';
        p += length;
        while ( *p == ' ' || *p == '\t' || *p == ')' ) {
            p++;
        }
        if ( *p && *p != '/' ) {
            return 1;               // `defined X && ...`: not evaluated
        }
        return negate ^ IsDefined( unit, name );
    }
    if ( isalpha( (unsigned char)*p ) || *p == '_' ) {
        size_t length = 0;

        while ( ( isalnum( (unsigned char)p[length] ) || p[length] == '_' ) && length + 1 < sizeof( name ) ) {
            name[length] = p[length];
            length++;
        }
        name[length] = '\0';
        for ( p += length; *p == ' ' || *p == '\t'; p++ ) {
        }
        if ( *p && *p != '/' ) {
            return 1;
        }
        return negate ^ IsDefined( unit, name );
    }
    return 1;
}

/*
================
Lex

Splits a file into tokens.  Comments are kept as tokens; preprocessor lines
become single TOK_PP tokens.  Conditional blocks are evaluated so that exactly
one branch of each chain is read (EvaluateCondition); the conditional
directives of read regions are kept as tokens.  `#if 0` blocks that are not in
the project's parking form are recorded for R37.
================
*/
#define MAX_CONDITIONS 64
#define ACTIVE         ( numConditions == 0 || conditions[numConditions - 1].active )

typedef struct condition_s {
    int parentActive;               /* the enclosing region is read */
    int active;                     /* this branch is read */
    int taken;                      /* some branch of this chain was chosen */
} condition_t;

static void Lex( unit_t *unit, const char *source ) {
    condition_t conditions[MAX_CONDITIONS];
    int         numConditions = 0;
    const char *p;
    const char *start;
    int         line;
    int         atLineStart;

    p = source;
    line = 1;
    atLineStart = 1;
    while ( *p ) {
        if ( *p == '\n' ) {
            line++;
            p++;
            atLineStart = 1;
            continue;
        }
        if ( isspace( (unsigned char)*p ) ) {
            p++;
            continue;
        }

        // preprocessor line, with continuations
        if ( *p == '#' && atLineStart ) {
            char *text;
            int   startLine;

            start = p;
            startLine = line;
            while ( *p && *p != '\n' ) {
                if ( *p == '\\' && p[1] == '\n' ) {
                    line++;
                    p += 2;
                    continue;
                }
                if ( *p == '\\' && p[1] == '\r' && p[2] == '\n' ) {
                    line++;
                    p += 3;
                    continue;
                }
                p++;
            }
            text = CopyString( start, (size_t)( p - start ) );
            if ( DirectiveIs( text, "if" ) || DirectiveIs( text, "ifdef" ) || DirectiveIs( text, "ifndef" ) ) {
                int parent = ACTIVE;
                int value = parent ? EvaluateCondition( unit, text ) : 0;

                if ( numConditions == MAX_CONDITIONS ) {
                    Error( "%s:%d: #if nesting too deep", unit->path, startLine );
                }
                if ( parent && IsDisabledIf( text ) && !strstr( text, PARKING_MARKER ) ) {
                    NameList_Add( &unit->disabledBlocks, "#if 0", startLine );
                }
                conditions[numConditions].parentActive = parent;
                conditions[numConditions].active = parent && value;
                conditions[numConditions].taken = value;
                numConditions++;
                if ( parent ) {
                    AddToken( unit, TOK_PP, startLine, text, strlen( text ) );
                }
            } else if ( DirectiveIs( text, "elif" ) || DirectiveIs( text, "else" ) ) {
                condition_t *top = numConditions ? &conditions[numConditions - 1] : NULL;

                if ( top ) {
                    if ( top->taken ) {
                        top->active = 0;
                    } else {
                        int value = DirectiveIs( text, "else" ) ? 1
                            : top->parentActive ? EvaluateCondition( unit, text ) : 0;

                        top->active = top->parentActive && value;
                        top->taken = value;
                    }
                    if ( top->parentActive ) {
                        AddToken( unit, TOK_PP, startLine, text, strlen( text ) );
                    }
                }
            } else if ( DirectiveIs( text, "endif" ) ) {
                if ( numConditions ) {
                    numConditions--;
                    if ( conditions[numConditions].parentActive ) {
                        AddToken( unit, TOK_PP, startLine, text, strlen( text ) );
                    }
                }
            } else if ( ACTIVE ) {
                char name[256];

                if ( DirectiveIs( text, "define" ) ) {
                    if ( MacroName( text, "define", name, sizeof( name ) ) ) {
                        NameList_Add( &unit->defines, name, startLine );
                    }
                } else if ( DirectiveIs( text, "undef" ) ) {
                    if ( MacroName( text, "undef", name, sizeof( name ) ) ) {
                        NameList_Remove( &unit->defines, name );
                    }
                } else if ( DirectiveIs( text, "include" ) ) {
                    // `#include "x.h"`: the header's macros count from here on
                    const char *quote = strchr( text, '"' );
                    const char *end = quote ? strchr( quote + 1, '"' ) : NULL;

                    if ( end ) {
                        const char *base = quote + 1;
                        const char *p;

                        for ( p = quote + 1; p < end; p++ ) {
                            if ( *p == '/' ) {
                                base = p + 1;
                            }
                        }
                        if ( end > base && (size_t)( end - base ) < sizeof( name ) ) {
                            memcpy( name, base, (size_t)( end - base ) );
                            name[end - base] = '\0';
                            NameList_Add( &unit->includes, name, startLine );
                        }
                    }
                }
                AddToken( unit, TOK_PP, startLine, text, strlen( text ) );
            }
            free( text );
            continue;
        }
        atLineStart = 0;
        if ( !ACTIVE ) {
            // inside a dropped block: only track lines and comments' newlines
            if ( p[0] == '/' && p[1] == '*' ) {
                p += 2;
                while ( *p && !( p[0] == '*' && p[1] == '/' ) ) {
                    if ( *p == '\n' ) {
                        line++;
                    }
                    p++;
                }
                if ( *p ) {
                    p += 2;
                }
                continue;
            }
            if ( p[0] == '/' && p[1] == '/' ) {
                while ( *p && *p != '\n' ) {
                    p++;
                }
                continue;
            }
            p++;
            continue;
        }

        start = p;
        if ( p[0] == '/' && p[1] == '*' ) {
            int startLine = line;

            p += 2;
            while ( *p && !( p[0] == '*' && p[1] == '/' ) ) {
                if ( *p == '\n' ) {
                    line++;
                }
                p++;
            }
            if ( *p ) {
                p += 2;
            }
            AddToken( unit, TOK_COMMENT, startLine, start, (size_t)( p - start ) );
            continue;
        }
        if ( p[0] == '/' && p[1] == '/' ) {
            while ( *p && *p != '\n' ) {
                p++;
            }
            AddToken( unit, TOK_COMMENT, line, start, (size_t)( p - start ) );
            continue;
        }
        if ( *p == '"' || *p == '\'' ) {
            char quote = *p++;

            while ( *p && *p != quote && *p != '\n' ) {
                if ( *p == '\\' && p[1] ) {
                    p++;
                }
                p++;
            }
            if ( *p == quote ) {
                p++;
            }
            AddToken( unit, quote == '"' ? TOK_STR : TOK_CHAR, line, start, (size_t)( p - start ) );
            continue;
        }
        if ( isalpha( (unsigned char)*p ) || *p == '_' ) {
            while ( isalnum( (unsigned char)*p ) || *p == '_' ) {
                p++;
            }
            AddToken( unit, TOK_IDENT, line, start, (size_t)( p - start ) );
            continue;
        }
        if ( isdigit( (unsigned char)*p ) || ( *p == '.' && isdigit( (unsigned char)p[1] ) ) ) {
            while ( isalnum( (unsigned char)*p ) || *p == '.' || *p == '_'
                || ( ( *p == '+' || *p == '-' ) && ( p[-1] == 'e' || p[-1] == 'E' )
                    && !( start[0] == '0' && ( start[1] == 'x' || start[1] == 'X' ) ) ) ) {
                p++;
            }
            AddToken( unit, TOK_NUM, line, start, (size_t)( p - start ) );
            continue;
        }

        // punctuators: longest match first
        {
            static const char *const multi[] = {
                "<<=", ">>=", "...", "->", "++", "--", "<<", ">>", "<=", ">=", "==", "!=",
                "&&", "||", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", NULL
            };
            int i;

            for ( i = 0; multi[i]; i++ ) {
                size_t length = strlen( multi[i] );

                if ( !strncmp( p, multi[i], length ) ) {
                    break;
                }
            }
            if ( multi[i] ) {
                size_t length = strlen( multi[i] );

                AddToken( unit, TOK_PUNCT, line, p, length );
                p += length;
            } else {
                AddToken( unit, TOK_PUNCT, line, p, 1 );
                p++;
            }
        }
    }
}

/*
===============================================================================

TOKEN HELPERS

===============================================================================
*/

/*
================
Is
================
*/
static int Is( const token_t *token, const char *text ) {
    return token->kind != TOK_COMMENT && token->kind != TOK_PP && !strcmp( token->text, text );
}

/*
================
IsCode

True for tokens that take part in C syntax.
================
*/
static int IsCode( const token_t *token ) {
    return token->kind != TOK_COMMENT && token->kind != TOK_PP;
}

/*
================
NextCode

Index of the next syntax token after i, or the token count.
================
*/
static int NextCode( const unit_t *unit, int i ) {
    for ( i++; i < unit->numTokens; i++ ) {
        if ( IsCode( &unit->tokens[i] ) ) {
            return i;
        }
    }
    return unit->numTokens;
}

/*
================
PrevCode

Index of the previous syntax token before i, or -1.
================
*/
static int PrevCode( const unit_t *unit, int i ) {
    for ( i--; i >= 0; i-- ) {
        if ( IsCode( &unit->tokens[i] ) ) {
            return i;
        }
    }
    return -1;
}

/*
================
MatchClose

Given the index of an opening bracket, returns the index of its closing
bracket, or the token count when unbalanced.
================
*/
static int MatchClose( const unit_t *unit, int open ) {
    const char *openText;
    const char *closeText;
    int         depth;
    int         i;

    openText = unit->tokens[open].text;
    closeText = !strcmp( openText, "(" ) ? ")" : !strcmp( openText, "[" ) ? "]" : "}";
    depth = 0;
    for ( i = open; i < unit->numTokens; i++ ) {
        if ( !IsCode( &unit->tokens[i] ) ) {
            continue;
        }
        if ( !strcmp( unit->tokens[i].text, openText ) ) {
            depth++;
        } else if ( !strcmp( unit->tokens[i].text, closeText ) ) {
            if ( --depth == 0 ) {
                return i;
            }
        }
    }
    return unit->numTokens;
}

/*
================
MatchOpen

Given the index of a closing parenthesis, returns its opening one, or -1.
================
*/
static int MatchOpen( const unit_t *unit, int close ) {
    int depth;
    int i;

    depth = 0;
    for ( i = close; i >= 0; i-- ) {
        if ( !IsCode( &unit->tokens[i] ) ) {
            continue;
        }
        if ( !strcmp( unit->tokens[i].text, ")" ) ) {
            depth++;
        } else if ( !strcmp( unit->tokens[i].text, "(" ) ) {
            if ( --depth == 0 ) {
                return i;
            }
        }
    }
    return -1;
}

/*
================
IsByteType

True for the identifiers that name a byte type.
================
*/
static int IsByteType( const char *text ) {
    return !strcmp( text, "u8" ) || !strcmp( text, "s8" ) || !strcmp( text, "char" );
}

/*
================
IsZeroLiteral
================
*/
static int IsZeroLiteral( const char *text ) {
    return !strcmp( text, "0" ) || !strcmp( text, "0x0" ) || !strcmp( text, "0X0" );
}

/*
================
IsOperandEnd

True when a token can end an operand, so a following `+` or `*` is binary.
================
*/
static int IsOperandEnd( const token_t *token ) {
    if ( token->kind == TOK_IDENT ) {
        return strcmp( token->text, "return" ) && strcmp( token->text, "case" )
            && strcmp( token->text, "sizeof" );
    }
    return token->kind == TOK_NUM || token->kind == TOK_CHAR || Is( token, ")" ) || Is( token, "]" );
}

/*
================
LineHasNote

True when a comment on the given line contains the note text.
================
*/
static int LineHasNote( const unit_t *unit, int line, const char *note ) {
    int i;

    for ( i = 0; i < unit->numTokens; i++ ) {
        const token_t *token = &unit->tokens[i];

        if ( token->kind == TOK_COMMENT && token->line == line && strstr( token->text, note ) ) {
            return 1;
        }
    }
    return 0;
}

/*
================
IsPlaceholder

True for the placeholder names of the naming ruling (docs/code-rules.md,
Naming): `func_`, `D_`, `B_`, `jtbl_` and the m2c names `temp_`, `var_`,
`phi_`, `spXX`, `argN`, plus legacy `unkXX` members.  `unk_<HEX>` is the
ruling's name for an unknown member, not a placeholder.
================
*/
static int IsPlaceholder( const char *name ) {
    static const char *const prefixes[] = {
        "func_", "D_", "B_", "jtbl_", "temp_", "var_", "phi_", "sp", "arg", "unk", NULL
    };
    const char *rest;
    int         i;

    for ( i = 0; prefixes[i]; i++ ) {
        size_t length = strlen( prefixes[i] );

        if ( strncmp( name, prefixes[i], length ) ) {
            continue;
        }
        rest = name + length;
        if ( !strcmp( prefixes[i], "sp" ) || !strcmp( prefixes[i], "arg" ) || !strcmp( prefixes[i], "unk" ) ) {
            // spXX stack slots, argN parameters and legacy unkXX members: the remainder is hex
            if ( !*rest ) {
                return 0;
            }
            while ( isxdigit( (unsigned char)*rest ) ) {
                rest++;
            }
            return *rest == '\0';
        }
        return 1;
    }
    return 0;
}

/*
===============================================================================

DECLARATION PASS

===============================================================================
*/

/*
================
AddTypeDef
================
*/
static void AddTypeDef( const char *name, const char *body, int unitIndex, int line ) {
    type_def_t *def;

    typeDefs = Grow( typeDefs, numTypeDefs, &maxTypeDefs, sizeof( *typeDefs ) );
    def = &typeDefs[numTypeDefs++];
    def->name = CopyString( name, strlen( name ) );
    def->body = CopyString( body, strlen( body ) );
    def->unit = unitIndex;
    def->line = line;
}

/*
================
JoinTokens

Normalized text of the code tokens from first to last, inclusive.
================
*/
static char *JoinTokens( const unit_t *unit, int first, int last ) {
    size_t length;
    char  *text;
    int    i;

    length = 1;
    for ( i = first; i <= last; i++ ) {
        if ( IsCode( &unit->tokens[i] ) ) {
            length += strlen( unit->tokens[i].text ) + 1;
        }
    }
    text = malloc( length );
    if ( !text ) {
        Error( "out of memory" );
    }
    text[0] = '\0';
    for ( i = first; i <= last; i++ ) {
        if ( IsCode( &unit->tokens[i] ) ) {
            strcat( text, unit->tokens[i].text );
            strcat( text, " " );
        }
    }
    return text;
}

/*
================
ScanAggregateBody

Records volatile and padding members of a struct or union body.
================
*/
static void ScanAggregateBody( unit_t *unit, int open, int close, const name_list_t *owners ) {
    int memberStart;
    int i;

    memberStart = NextCode( unit, open );
    for ( i = memberStart; i < close; i = NextCode( unit, i ) ) {
        const token_t *token = &unit->tokens[i];

        if ( Is( token, "{" ) ) {
            int inner = MatchClose( unit, i );

            ScanAggregateBody( unit, i, inner, owners );
            i = inner;
            continue;
        }
        if ( !Is( token, ";" ) ) {
            continue;
        }

        // one member declaration spans memberStart .. i
        {
            int isVolatile = 0;
            int j;

            for ( j = memberStart; j < i; j = NextCode( unit, j ) ) {
                if ( Is( &unit->tokens[j], "volatile" ) ) {
                    isVolatile = 1;
                }
                if ( Is( &unit->tokens[j], "{" ) ) {
                    j = MatchClose( unit, j );
                }
            }
            for ( j = memberStart; j < i; j = NextCode( unit, j ) ) {
                const token_t *name = &unit->tokens[j];
                int            next = NextCode( unit, j );

                if ( Is( name, "{" ) ) {
                    j = MatchClose( unit, j );
                    continue;
                }
                if ( name->kind != TOK_IDENT || next >= unit->numTokens ) {
                    continue;
                }
                if ( !Is( &unit->tokens[next], ";" ) && !Is( &unit->tokens[next], "[" )
                    && !Is( &unit->tokens[next], "," ) && !Is( &unit->tokens[next], ":" ) ) {
                    continue;
                }
                if ( isVolatile && !LineHasNote( unit, name->line, VOLATILE_NOTE ) ) {
                    int k;

                    // one entry per type name the member can be reached through
                    for ( k = 0; k < owners->count; k++ ) {
                        NameList_Add( &unit->volatileMembers, name->text, name->line );
                        NameList_Add( &unit->volatileOwners, owners->names[k], name->line );
                    }
                }
                if ( !strncmp( name->text, "pad", 3 ) || !strncmp( name->text, "_pad", 4 ) ) {
                    NameList_Add( &unit->padMembers, name->text, name->line );
                }
            }
        }
        memberStart = NextCode( unit, i );
    }
}

/*
================
RecordAggregate

Records a struct/union/enum definition whose body spans open .. close.
The type names are the tag before the body and, for a typedef, the
declarators after it.
================
*/
static void RecordAggregate( unit_t *unit, int unitIndex, int keyword, int open, int close ) {
    name_list_t owners;
    char       *body;
    int         tag;
    int         i;

    memset( &owners, 0, sizeof( owners ) );
    body = JoinTokens( unit, open, close );
    tag = NextCode( unit, keyword );
    if ( tag < open && unit->tokens[tag].kind == TOK_IDENT ) {
        AddTypeDef( unit->tokens[tag].text, body, unitIndex, unit->tokens[tag].line );
        NameList_Add( &owners, unit->tokens[tag].text, unit->tokens[tag].line );
    }
    i = PrevCode( unit, keyword );
    if ( i >= 0 && Is( &unit->tokens[i], "typedef" ) ) {
        for ( i = NextCode( unit, close ); i < unit->numTokens && !Is( &unit->tokens[i], ";" );
            i = NextCode( unit, i ) ) {
            if ( unit->tokens[i].kind == TOK_IDENT ) {
                AddTypeDef( unit->tokens[i].text, body, unitIndex, unit->tokens[i].line );
                NameList_Add( &owners, unit->tokens[i].text, unit->tokens[i].line );
            }
        }
    }
    if ( !Is( &unit->tokens[keyword], "enum" ) ) {
        ScanAggregateBody( unit, open, close, &owners );
    }
    for ( i = 0; i < owners.count; i++ ) {
        free( owners.names[i] );
    }
    free( owners.names );
    free( owners.lines );
    free( body );
}

/*
================
RecordExternNames

Records the variable names an `extern` declaration (first .. last) declares.
Function prototypes are skipped; function-pointer variables are recorded.
================
*/
static void RecordExternNames( const unit_t *unit, int first, int last, name_list_t *names ) {
    int i;

    for ( i = first; i <= last; i = NextCode( unit, i ) ) {
        const token_t *token = &unit->tokens[i];
        int            next;

        if ( Is( token, "{" ) ) {
            i = MatchClose( unit, i );
            continue;
        }
        if ( token->kind != TOK_IDENT ) {
            continue;
        }
        next = NextCode( unit, i );
        if ( next > last + 1 || next >= unit->numTokens ) {
            continue;
        }
        if ( Is( &unit->tokens[next], ")" ) ) {
            // `(*name)(...)`: a function-pointer variable
            int prev = PrevCode( unit, i );

            if ( prev >= 0 && Is( &unit->tokens[prev], "*" ) ) {
                NameList_Add( names, token->text, token->line );
            }
            continue;
        }
        if ( Is( &unit->tokens[next], "[" ) || Is( &unit->tokens[next], ";" )
            || Is( &unit->tokens[next], "," ) || Is( &unit->tokens[next], "=" ) ) {
            NameList_Add( names, token->text, token->line );
        }
    }
}

/*
================
IsPrototype

True when the declaration first .. last declares a function (a name followed
directly by a parameter list).
================
*/
static int IsPrototype( const unit_t *unit, int first, int last, const char **name ) {
    int i;

    for ( i = first; i <= last; i = NextCode( unit, i ) ) {
        int next = NextCode( unit, i );

        if ( unit->tokens[i].kind == TOK_IDENT && next <= last && Is( &unit->tokens[next], "(" ) ) {
            int prev = PrevCode( unit, i );

            int after = NextCode( unit, next );

            if ( prev >= 0 && Is( &unit->tokens[prev], "(" ) ) {
                return 0;           // (name)(...) is a function-pointer variable
            }
            if ( after <= last && Is( &unit->tokens[after], "*" ) ) {
                return 0;           // type (*name)(...) is a function-pointer variable
            }
            *name = unit->tokens[i].text;
            return 1;
        }
        if ( Is( &unit->tokens[i], "(" ) ) {
            return 0;
        }
        if ( Is( &unit->tokens[i], "{" ) ) {
            i = MatchClose( unit, i );      // an aggregate body: its members are not prototypes
        }
    }
    return 0;
}

/*
================
AddFunction
================
*/
static void AddFunction( unit_t *unit, int nameIndex, int paramStart, int open, int close ) {
    function_t *func;

    unit->functions = Grow( unit->functions, unit->numFunctions, &unit->maxFunctions,
        sizeof( *unit->functions ) );
    func = &unit->functions[unit->numFunctions++];
    memset( func, 0, sizeof( *func ) );
    func->name = unit->tokens[nameIndex].text;
    func->line = unit->tokens[nameIndex].line;
    func->paramStart = paramStart;
    func->bodyStart = open;
    func->bodyEnd = close;
}

/*
===============================================================================

GLOBAL LISTING (--list-globals)

One tab-separated row per declaration, for tools that edit declarations:

  E  path  first-line  last-line  scope  clean  conditional  name  declaration  comment
  D  path  line  static  name  declaration
  T  path  type-name
  P  path  function-name
  M  path  macro-name

E rows are `extern` variable declarations (scope `file` or `block`).  `clean`
is 1 when the declaration's lines hold nothing else but an optional trailing
comment, `conditional` when it sits inside an #if.  The declaration is the
normalized token text without `extern` and the final ';'.  D rows are
file-scope variable definitions, T rows the type names a file defines, P rows
functions it declares or defines, M rows the identifiers a macro definition
names (the macro and its replacement).

===============================================================================
*/

/*
================
ComputeConditionalDepth
================
*/
static void ComputeConditionalDepth( unit_t *unit ) {
    int depth = 0;
    int i;

    unit->ppDepth = calloc( (size_t)unit->numTokens + 1, sizeof( *unit->ppDepth ) );
    if ( !unit->ppDepth ) {
        Error( "out of memory" );
    }
    for ( i = 0; i < unit->numTokens; i++ ) {
        const token_t *token = &unit->tokens[i];

        unit->ppDepth[i] = depth;
        if ( token->kind != TOK_PP ) {
            continue;
        }
        if ( DirectiveIs( token->text, "if" ) || DirectiveIs( token->text, "ifdef" )
            || DirectiveIs( token->text, "ifndef" ) ) {
            depth++;
        } else if ( DirectiveIs( token->text, "endif" ) && depth > 0 ) {
            depth--;
        }
    }
}

/*
================
TokenEndLine

The line a token ends on (comments may span lines).
================
*/
static int TokenEndLine( const token_t *token ) {
    const char *p;
    int         line = token->line;

    for ( p = token->text; *p; p++ ) {
        if ( *p == '\n' ) {
            line++;
        }
    }
    return line;
}

/*
================
PrintField

Prints a field with tabs and newlines flattened to spaces.
================
*/
static void PrintField( const char *text ) {
    const char *p;

    putchar( '\t' );
    for ( p = text; *p; p++ ) {
        putchar( *p == '\t' || *p == '\n' || *p == '\r' ? ' ' : *p );
    }
}

/*
================
ListExtern

Prints the E rows for the extern declaration first .. semicolon: one row per
declarator, each with the shared specifiers, so `extern f32 a, b;` gives
`f32 a` and `f32 b`.
================
*/
static void ListExtern( const unit_t *unit, int first, int semicolon, const char *scope ) {
    const char *comment = "";
    int         firstLine = unit->tokens[first].line;
    int         lastLine = unit->tokens[semicolon].line;
    int         clean = 1;
    int         specifierEnd;           /* first token of the first declarator */
    int         pieceStart;
    int         i;

    // the declaration's lines must hold nothing else but a trailing comment
    for ( i = 0; i < unit->numTokens; i++ ) {
        const token_t *token = &unit->tokens[i];

        if ( TokenEndLine( token ) < firstLine || token->line > lastLine ) {
            continue;
        }
        if ( i >= first && i <= semicolon && token->kind != TOK_COMMENT ) {
            continue;
        }
        if ( token->kind == TOK_COMMENT && i > semicolon && token->line == lastLine
            && TokenEndLine( token ) == lastLine && !comment[0] ) {
            comment = token->text;
            continue;
        }
        clean = 0;
    }

    // specifiers run up to the first '*', '(' or the identifier that names the variable
    specifierEnd = NextCode( unit, first );
    for ( i = specifierEnd; i < semicolon; i = NextCode( unit, i ) ) {
        int next;

        if ( Is( &unit->tokens[i], "{" ) ) {
            i = MatchClose( unit, i );      // an aggregate body is part of the specifiers
            continue;
        }
        next = NextCode( unit, i );
        if ( Is( &unit->tokens[i], "*" ) || Is( &unit->tokens[i], "(" ) ) {
            break;
        }
        if ( unit->tokens[i].kind == TOK_IDENT && ( Is( &unit->tokens[next], "[" ) || Is( &unit->tokens[next], ";" )
            || Is( &unit->tokens[next], "," ) ) ) {
            break;
        }
    }
    specifierEnd = i;

    pieceStart = specifierEnd;
    for ( i = specifierEnd; i <= semicolon; i = NextCode( unit, i ) ) {
        int   pieceEnd;
        int   name;
        int   k;
        char *specifiers;
        char *declarator;

        if ( Is( &unit->tokens[i], "(" ) || Is( &unit->tokens[i], "[" ) || Is( &unit->tokens[i], "{" ) ) {
            i = MatchClose( unit, i );
            continue;
        }
        if ( !Is( &unit->tokens[i], "," ) && !Is( &unit->tokens[i], ";" ) ) {
            continue;
        }
        pieceEnd = PrevCode( unit, i );

        // the declarator's name: the last identifier before '[' or the end, or inside '(*name)'
        name = -1;
        for ( k = pieceStart; k <= pieceEnd; k = NextCode( unit, k ) ) {
            int next = NextCode( unit, k );

            if ( unit->tokens[k].kind != TOK_IDENT ) {
                continue;
            }
            if ( next > pieceEnd || Is( &unit->tokens[next], "[" ) || Is( &unit->tokens[next], ")" ) ) {
                name = k;
                break;
            }
        }
        specifiers = specifierEnd > NextCode( unit, first )
            ? JoinTokens( unit, NextCode( unit, first ), PrevCode( unit, specifierEnd ) ) : CopyString( "", 0 );
        declarator = JoinTokens( unit, pieceStart, pieceEnd );
        if ( declarator[0] ) {
            declarator[strlen( declarator ) - 1] = '\0';
        }
        printf( "E\t%s\t%d\t%d\t%s\t%d\t%d", unit->path, firstLine, lastLine, scope, clean,
            unit->ppDepth[first] > ( unit->isHeader ? 1 : 0 ) );
        PrintField( name >= 0 ? unit->tokens[name].text : "" );
        putchar( '\t' );
        fputs( specifiers, stdout );
        fputs( declarator, stdout );
        PrintField( comment );
        putchar( '\n' );
        free( specifiers );
        free( declarator );
        pieceStart = NextCode( unit, i );
    }
}

/*
================
ListDefinition

Prints the D row for a file-scope variable definition first .. last, if the
declaration defines a variable.
================
*/
static void ListDefinition( const unit_t *unit, int first, int last ) {
    int isStatic = 0;
    int i;

    for ( i = first; i <= last; i = NextCode( unit, i ) ) {
        const token_t *token = &unit->tokens[i];
        int            next = NextCode( unit, i );

        if ( Is( token, "static" ) ) {
            isStatic = 1;
            continue;
        }
        if ( Is( token, "{" ) || Is( token, "=" ) ) {
            return;                 // an aggregate body or initializer before any name
        }
        if ( token->kind != TOK_IDENT || next > last + 1 ) {
            continue;
        }
        if ( i > first && ( Is( &unit->tokens[PrevCode( unit, i )], "struct" )
            || Is( &unit->tokens[PrevCode( unit, i )], "union" ) || Is( &unit->tokens[PrevCode( unit, i )], "enum" ) ) ) {
            continue;               // a tag, not a variable (`struct Foo;`)
        }
        if ( Is( &unit->tokens[next], "=" ) || Is( &unit->tokens[next], "[" ) || Is( &unit->tokens[next], ";" )
            || Is( &unit->tokens[next], "," )
            || ( Is( &unit->tokens[next], ")" ) && Is( &unit->tokens[PrevCode( unit, i )], "*" ) ) ) {
            int   end = i;
            char *declaration;
            int   start = first;

            // the declarator runs to the initializer or the end of the declaration
            while ( end < last && !Is( &unit->tokens[NextCode( unit, end )], "=" )
                && !Is( &unit->tokens[NextCode( unit, end )], ";" ) && !Is( &unit->tokens[NextCode( unit, end )], "," ) ) {
                end = NextCode( unit, end );
            }
            while ( start < i && ( Is( &unit->tokens[start], "static" ) || Is( &unit->tokens[start], "extern" ) ) ) {
                start = NextCode( unit, start );
            }
            declaration = JoinTokens( unit, start, end );
            if ( declaration[0] ) {
                declaration[strlen( declaration ) - 1] = '\0';
            }
            printf( "D\t%s\t%d\t%d", unit->path, token->line, isStatic );
            PrintField( token->text );
            PrintField( declaration );
            putchar( '\n' );
            free( declaration );
            return;
        }
    }
}

/*
================
ParseTopLevel

Walks the file-scope declarations: records function definitions, aggregates,
extern globals and prototypes.
================
*/
static void ParseTopLevel( unit_t *unit, int unitIndex ) {
    int declStart;
    int i;

    declStart = NextCode( unit, -1 );
    for ( i = declStart; i < unit->numTokens; i = NextCode( unit, i ) ) {
        token_t *token = &unit->tokens[i];

        if ( Is( token, "struct" ) || Is( token, "union" ) || Is( token, "enum" ) ) {
            int next = NextCode( unit, i );

            if ( next < unit->numTokens && unit->tokens[next].kind == TOK_IDENT ) {
                next = NextCode( unit, next );
            }
            if ( next < unit->numTokens && Is( &unit->tokens[next], "{" ) ) {
                int close = MatchClose( unit, next );

                RecordAggregate( unit, unitIndex, i, next, close );
                i = close;
            }
            continue;
        }
        if ( Is( token, "=" ) ) {
            // initializer: skip to the end of the declaration
            for ( i = NextCode( unit, i ); i < unit->numTokens && !Is( &unit->tokens[i], ";" );
                i = NextCode( unit, i ) ) {
                if ( Is( &unit->tokens[i], "{" ) || Is( &unit->tokens[i], "(" ) ) {
                    i = MatchClose( unit, i );
                }
            }
        }
        if ( i >= unit->numTokens ) {
            break;
        }
        token = &unit->tokens[i];
        if ( Is( token, "{" ) ) {
            int prev = PrevCode( unit, i );
            int close = MatchClose( unit, i );

            if ( prev >= 0 && Is( &unit->tokens[prev], ")" ) ) {
                int open = MatchOpen( unit, prev );
                int nameIndex = PrevCode( unit, open );

                // a K&R parameter list would sit between ')' and '{'; IDO code here has none
                if ( nameIndex >= 0 && unit->tokens[nameIndex].kind == TOK_IDENT ) {
                    AddFunction( unit, nameIndex, open, i, close );
                }
            }
            i = close;
            declStart = NextCode( unit, i );
            continue;
        }
        if ( Is( token, ";" ) ) {
            const char *name;
            int         last = PrevCode( unit, i );

            if ( declStart <= last ) {
                if ( Is( &unit->tokens[declStart], "extern" ) && !IsPrototype( unit, declStart, last, &name ) ) {
                    if ( optListGlobals ) {
                        ListExtern( unit, declStart, i, "file" );
                    }
                    RecordExternNames( unit, declStart, i, &unit->externs );
                } else if ( !Is( &unit->tokens[declStart], "typedef" )
                    && IsPrototype( unit, declStart, last, &name ) ) {
                    NameList_Add( &unit->prototypes, name, unit->tokens[declStart].line );
                } else if ( optListGlobals && Is( &unit->tokens[declStart], "typedef" ) ) {
                    int k;

                    // the declared type names: identifiers before ';' or ','
                    for ( k = declStart; k <= last; k = NextCode( unit, k ) ) {
                        int next = NextCode( unit, k );

                        if ( Is( &unit->tokens[k], "{" ) ) {
                            k = MatchClose( unit, k );
                            continue;
                        }
                        if ( unit->tokens[k].kind == TOK_IDENT && next <= i
                            && ( Is( &unit->tokens[next], ";" ) || Is( &unit->tokens[next], "," )
                                || Is( &unit->tokens[next], "[" ) ) ) {
                            printf( "T\t%s\t%s\n", unit->path, unit->tokens[k].text );
                        }
                    }
                } else if ( optListGlobals ) {
                    ListDefinition( unit, declStart, last );
                }
            }
            declStart = NextCode( unit, i );
        }
    }
}

/*
===============================================================================

FUNCTION CHECKS

===============================================================================
*/

/*
================
AddFinding
================
*/
static void AddFinding( function_t *func, int rule, int line, char *message ) {
    func->findings = Grow( func->findings, func->numFindings, &func->maxFindings, sizeof( *func->findings ) );
    func->findings[func->numFindings].rule = rule;
    func->findings[func->numFindings].line = line;
    func->findings[func->numFindings].message = message;
    func->numFindings++;
    if ( rule < NUM_MATCH_RULES ) {
        func->matchRules |= 1u << rule;
    } else {
        func->advisoryRules |= 1u << ( rule - NUM_MATCH_RULES );
    }
}

/*
================
OperandEnd

Given the first token of a postfix operand (an identifier with member,
index and call suffixes, or a parenthesized group), returns its last token.
Returns -1 when no operand starts at i.
================
*/
static int OperandEnd( const unit_t *unit, int i, int limit ) {
    if ( i >= limit ) {
        return -1;
    }
    if ( Is( &unit->tokens[i], "(" ) ) {
        i = MatchClose( unit, i );
    } else if ( unit->tokens[i].kind != TOK_IDENT ) {
        return -1;
    }
    for ( ;; ) {
        int next = NextCode( unit, i );

        if ( next >= limit ) {
            return i;
        }
        if ( Is( &unit->tokens[next], "->" ) || Is( &unit->tokens[next], "." ) ) {
            int member = NextCode( unit, next );

            if ( member >= limit || unit->tokens[member].kind != TOK_IDENT ) {
                return i;
            }
            i = member;
        } else if ( Is( &unit->tokens[next], "[" ) || Is( &unit->tokens[next], "(" ) ) {
            i = MatchClose( unit, next );
        } else {
            return i;
        }
    }
}

/*
================
CastEnd

When tokens at i form a pointer cast `( type * )`, returns the index of the
closing parenthesis and sets *isByte when the cast is to a byte pointer
(exactly one level of indirection to u8/s8/char).  Returns -1 otherwise.
================
*/
static int CastEnd( const unit_t *unit, int i, int limit, int *isByte, int *isVolatile ) {
    int stars = 0;
    int byteType = 0;
    int typeWords = 0;
    int j;

    if ( !Is( &unit->tokens[i], "(" ) ) {
        return -1;
    }
    *isVolatile = 0;
    for ( j = NextCode( unit, i ); j < limit; j = NextCode( unit, j ) ) {
        const token_t *token = &unit->tokens[j];

        if ( Is( token, ")" ) ) {
            if ( stars == 0 || typeWords == 0 ) {
                return -1;
            }
            *isByte = byteType && stars == 1;
            return j;
        }
        if ( Is( token, "*" ) ) {
            stars++;
            continue;
        }
        if ( token->kind != TOK_IDENT || stars ) {
            if ( !( token->kind == TOK_IDENT && ( Is( token, "const" ) || Is( token, "volatile" ) ) ) ) {
                return -1;
            }
        }
        if ( Is( token, "volatile" ) ) {
            *isVolatile = 1;
            continue;
        }
        if ( Is( token, "const" ) || Is( token, "unsigned" ) || Is( token, "signed" )
            || Is( token, "struct" ) || Is( token, "union" ) ) {
            continue;
        }
        if ( IsByteType( token->text ) ) {
            byteType = 1;
        }
        typeWords++;
        if ( typeWords > 1 ) {
            return -1;
        }
    }
    return -1;
}

/*
================
IsConstantOffset

True when tokens at i are `+ <integer>` or `- <integer>`.
================
*/
static int IsConstantOffset( const unit_t *unit, int i, int limit ) {
    const char *text;
    int         number;

    if ( i >= limit || ( !Is( &unit->tokens[i], "+" ) && !Is( &unit->tokens[i], "-" ) ) ) {
        return 0;
    }
    number = NextCode( unit, i );
    if ( number >= limit || unit->tokens[number].kind != TOK_NUM ) {
        return 0;
    }
    text = unit->tokens[number].text;
    if ( text[0] == '0' && ( text[1] == 'x' || text[1] == 'X' ) ) {
        return 1;
    }
    return !strpbrk( text, ".eEfF" );
}

/*
================
IsCastOperandGroup

True when the token at close is the ')' of a group that is the operand of a
pointer cast, as in `*(T *)(p + 0)`.  A zero offset there is a member at
offset 0, which R4 reports; it is not a separate `+ 0`.
================
*/
static int IsCastOperandGroup( const unit_t *unit, int close ) {
    int open;
    int before;

    if ( close >= unit->numTokens || !Is( &unit->tokens[close], ")" ) ) {
        return 0;
    }
    open = MatchOpen( unit, close );
    before = PrevCode( unit, open );
    if ( before < 0 || !Is( &unit->tokens[before], ")" ) ) {
        return 0;
    }
    before = PrevCode( unit, before );
    return before >= 0 && Is( &unit->tokens[before], "*" );
}

/*
================
IsStrideIndex

True when the operand ending at i is a product (`k * 3`), so a following
`+ 0` is the first of a run of element offsets (`k * 3 + 0`, `k * 3 + 1`).
================
*/
static int IsStrideIndex( const unit_t *unit, int i ) {
    int before;

    if ( unit->tokens[i].kind != TOK_IDENT && unit->tokens[i].kind != TOK_NUM ) {
        return 0;
    }
    before = PrevCode( unit, i );
    return before >= 0 && Is( &unit->tokens[before], "*" );
}

/*
================
IsKseg1Address

True for an 8-digit hex literal in the uncached KSEG1 range (0xA0000000 to
0xBFFFFFFF), which addresses hardware or uncached memory.
================
*/
static int IsKseg1Address( const char *text ) {
    if ( strlen( text ) < 10 || text[0] != '0' || ( text[1] != 'x' && text[1] != 'X' ) ) {
        return 0;
    }
    return text[2] == 'A' || text[2] == 'a' || text[2] == 'B' || text[2] == 'b';
}

/*
================
CollectBytePointers

Names of the function's parameters and locals declared as byte pointers
(`u8 *name`).
================
*/
static void CollectBytePointers( const unit_t *unit, const function_t *func, name_list_t *names ) {
    int i;

    for ( i = func->paramStart; i < func->bodyEnd; i = NextCode( unit, i ) ) {
        int star;
        int name;
        int prev;

        if ( unit->tokens[i].kind != TOK_IDENT || !IsByteType( unit->tokens[i].text ) ) {
            continue;
        }
        prev = PrevCode( unit, i );
        if ( prev >= 0 && Is( &unit->tokens[prev], "(" ) ) {
            // `(u8 *name` only in a parameter list; `(u8 *)` is a cast
            star = NextCode( unit, i );
            name = NextCode( unit, star );
            if ( name < func->bodyEnd && Is( &unit->tokens[star], "*" )
                && unit->tokens[name].kind == TOK_IDENT && i < func->bodyStart ) {
                NameList_Add( names, unit->tokens[name].text, unit->tokens[name].line );
            }
            continue;
        }
        star = NextCode( unit, i );
        name = NextCode( unit, star );
        if ( name < func->bodyEnd && Is( &unit->tokens[star], "*" ) && unit->tokens[name].kind == TOK_IDENT ) {
            NameList_Add( names, unit->tokens[name].text, unit->tokens[name].line );
        }
    }
}

static const char *DeclaredType( const unit_t *unit, const function_t *func, const char *name, int before,
    int *isArray, int *isPointer );

/*
================
ScalarSize

The size in bytes of a base arithmetic type (`types.h` aliases and C
keywords), or 0 for anything else.
================
*/
static int ScalarSize( const char *type ) {
    static const struct {
        const char *name;
        int         size;
    } scalars[] = {
        { "s8", 1 }, { "u8", 1 }, { "char", 1 },
        { "s16", 2 }, { "u16", 2 }, { "short", 2 },
        { "s32", 4 }, { "u32", 4 }, { "f32", 4 }, { "int", 4 }, { "long", 4 }, { "float", 4 },
        { "unsigned", 4 }, { "signed", 4 },
        { "s64", 8 }, { "u64", 8 }, { "f64", 8 }, { "double", 8 },
        { NULL, 0 }
    };
    int i;

    for ( i = 0; type && scalars[i].name; i++ ) {
        if ( !strcmp( scalars[i].name, type ) ) {
            return scalars[i].size;
        }
    }
    return 0;
}

/*
================
WithinScalar

True for a byte offset `number` (a TOK_NUM) inside a scalar of `size`
bytes: a byte view of the scalar itself, not of a struct behind it.
================
*/
static int WithinScalar( const token_t *number, int size ) {
    long value;

    if ( size <= 0 || number->kind != TOK_NUM || strpbrk( number->text, ".fF" ) ) {
        return 0;
    }
    value = strtol( number->text, NULL, 0 );
    return value >= 0 && value < size;
}

/*
================
CheckOffsetAccess

R4: `(u8 *)x + N` (also `(u8 *)&x + N`), `((u8 *)x)[N]`, and
`*(T *)(p + N)` / `(T *)(p + N)` where p is a byte pointer.
================
*/
static void CheckOffsetAccess( const unit_t *unit, function_t *func ) {
    name_list_t bytePointers;
    int         i;

    memset( &bytePointers, 0, sizeof( bytePointers ) );
    CollectBytePointers( unit, func, &bytePointers );
    for ( i = func->bodyStart; i < func->bodyEnd; i = NextCode( unit, i ) ) {
        int isByte = 0;
        int isVolatile = 0;
        int castClose;
        int operand;
        int operandEnd;
        int after;
        int scalarSize;

        castClose = CastEnd( unit, i, func->bodyEnd, &isByte, &isVolatile );
        if ( castClose < 0 ) {
            continue;
        }
        operand = NextCode( unit, castClose );
        // `(u8 *)&D_x + 4`: the operand may take its address
        operandEnd = operand < func->bodyEnd && Is( &unit->tokens[operand], "&" )
            ? OperandEnd( unit, NextCode( unit, operand ), func->bodyEnd )
            : OperandEnd( unit, operand, func->bodyEnd );
        if ( operandEnd < 0 ) {
            continue;
        }

        // `&x` of a plain (non-pointer, non-array) scalar: offsets inside it are a
        // byte view of the scalar (`((u8 *)&word)[3]`), with no struct behind it
        scalarSize = 0;
        if ( Is( &unit->tokens[operand], "&" ) && operandEnd == NextCode( unit, operand ) ) {
            int isArray = 0;
            int isPointer = 0;
            int size = ScalarSize( DeclaredType( unit, func, unit->tokens[operandEnd].text, operandEnd,
                &isArray, &isPointer ) );

            scalarSize = isArray || isPointer ? 0 : size;
        }
        after = NextCode( unit, operandEnd );
        if ( isByte && IsConstantOffset( unit, after, func->bodyEnd ) ) {
            if ( Is( &unit->tokens[after], "+" ) && WithinScalar( &unit->tokens[NextCode( unit, after )], scalarSize ) ) {
                continue;
            }
            AddFinding( func, RULE_R4, unit->tokens[i].line,
                FormatString( "byte-pointer cast plus constant offset" ) );
            continue;
        }

        // ((u8 *)p)[N]: a byte-pointer cast indexed by a constant
        if ( isByte && after < func->bodyEnd && Is( &unit->tokens[after], ")" ) ) {
            int open = MatchOpen( unit, after );
            int index = NextCode( unit, after );
            int number = NextCode( unit, index );
            int close = NextCode( unit, number );

            if ( open == PrevCode( unit, i ) && close < func->bodyEnd && Is( &unit->tokens[index], "[" )
                && unit->tokens[number].kind == TOK_NUM && Is( &unit->tokens[close], "]" ) ) {
                if ( WithinScalar( &unit->tokens[number], scalarSize ) ) {
                    continue;
                }
                AddFinding( func, RULE_R4, unit->tokens[i].line,
                    FormatString( "byte-pointer cast indexed by a constant offset" ) );
                continue;
            }
        }

        // (T *)(p + N) with p a byte pointer
        if ( Is( &unit->tokens[operand], "(" ) ) {
            int inner = NextCode( unit, operand );
            int innerEnd = OperandEnd( unit, inner, operandEnd );

            if ( innerEnd >= 0 && innerEnd == inner && unit->tokens[inner].kind == TOK_IDENT
                && NameList_Find( &bytePointers, unit->tokens[inner].text ) >= 0
                && IsConstantOffset( unit, NextCode( unit, innerEnd ), operandEnd ) ) {
                AddFinding( func, RULE_R4, unit->tokens[i].line,
                    FormatString( "cast of byte pointer '%s' plus constant offset", unit->tokens[inner].text ) );
            }
        }
    }
    free( bytePointers.names );
    free( bytePointers.lines );
}

/*
================
EnclosingCastClose

When the token at i lies inside a pointer cast `( ... )`, returns the index
of the cast's closing parenthesis; otherwise -1.
================
*/
static int EnclosingCastClose( const unit_t *unit, const function_t *func, int i ) {
    int depth = 0;
    int k;

    for ( k = PrevCode( unit, i ); k >= func->paramStart; k = PrevCode( unit, k ) ) {
        if ( Is( &unit->tokens[k], ")" ) ) {
            depth++;
        } else if ( Is( &unit->tokens[k], "(" ) ) {
            if ( depth == 0 ) {
                int isByte = 0;
                int isVolatile = 0;
                int close = CastEnd( unit, k, func->bodyEnd, &isByte, &isVolatile );

                return close > i ? close : -1;
            }
            depth--;
        } else if ( depth == 0 && ( Is( &unit->tokens[k], ";" ) || Is( &unit->tokens[k], "{" )
            || Is( &unit->tokens[k], "}" ) ) ) {
            return -1;
        }
    }
    return -1;
}

/*
================
DeclaredType

The type name in the nearest declaration of `name` before token `before`:
locals and parameters first, then file scope.  Returns NULL when none is
found.  `Foo *name`, `struct Foo name[4]` and `Foo name =` all give "Foo".
*isArray and *isPointer, when given, say whether the declarator is an array
or a pointer.

Only a real declaration counts: the type token must start a declaration
(follow `;`, `{`, `}`, `(`, `,` or the start of the file, past storage
classes and qualifiers), so statements such as `else p = b;` or
`return a;` are not taken for declarations of `p` or `a`.
================
*/
static int IsStatementKeyword( const char *text ) {
    static const char *const keywords[] = {
        "return", "else", "case", "goto", "sizeof", "do", "if", "while", "for", "switch", "default", "break",
        "continue", NULL
    };
    int i;

    for ( i = 0; keywords[i]; i++ ) {
        if ( !strcmp( keywords[i], text ) ) {
            return 1;
        }
    }
    return 0;
}

static int IsDeclarationPrefix( const char *text ) {
    static const char *const prefixes[] = {
        "struct", "union", "enum", "const", "volatile", "static", "extern", "register", "unsigned", "signed", NULL
    };
    int i;

    for ( i = 0; prefixes[i]; i++ ) {
        if ( !strcmp( prefixes[i], text ) ) {
            return 1;
        }
    }
    return 0;
}

static const char *DeclaredType( const unit_t *unit, const function_t *func, const char *name, int before,
    int *isArray, int *isPointer ) {
    int pass;

    if ( isArray ) {
        *isArray = 0;
    }
    if ( isPointer ) {
        *isPointer = 0;
    }
    for ( pass = 0; pass < 2; pass++ ) {
        int first = pass == 0 ? func->paramStart : 0;
        int last = pass == 0 ? before : func->paramStart;
        int found = -1;
        int foundType = -1;
        int foundPointer = 0;
        int k;

        for ( k = first; k < last; k = NextCode( unit, k ) ) {
            int prev;
            int next;
            int type;
            int start;
            int pointer = 0;

            if ( unit->tokens[k].kind != TOK_IDENT || strcmp( unit->tokens[k].text, name ) ) {
                continue;
            }
            prev = PrevCode( unit, k );
            next = NextCode( unit, k );
            if ( prev < 0 || next >= unit->numTokens ) {
                continue;
            }
            if ( !( Is( &unit->tokens[prev], "*" ) || unit->tokens[prev].kind == TOK_IDENT )
                || IsStatementKeyword( unit->tokens[prev].text ) ) {
                continue;
            }
            if ( !( Is( &unit->tokens[next], ";" ) || Is( &unit->tokens[next], "," ) || Is( &unit->tokens[next], "=" )
                || Is( &unit->tokens[next], ")" ) || Is( &unit->tokens[next], "[" ) ) ) {
                continue;
            }

            // the type token, past pointers and qualifiers
            for ( type = prev; type >= 0 && ( Is( &unit->tokens[type], "*" ) || Is( &unit->tokens[type], "const" )
                || Is( &unit->tokens[type], "volatile" ) ); type = PrevCode( unit, type ) ) {
                pointer |= Is( &unit->tokens[type], "*" );
            }
            if ( type < 0 || unit->tokens[type].kind != TOK_IDENT || IsStatementKeyword( unit->tokens[type].text ) ) {
                continue;
            }

            // ... which must start a declaration
            for ( start = PrevCode( unit, type ); start >= 0 && unit->tokens[start].kind == TOK_IDENT
                && IsDeclarationPrefix( unit->tokens[start].text ); start = PrevCode( unit, start ) ) {
            }
            if ( start >= 0 && !Is( &unit->tokens[start], ";" ) && !Is( &unit->tokens[start], "{" )
                && !Is( &unit->tokens[start], "}" ) && !Is( &unit->tokens[start], "(" ) && !Is( &unit->tokens[start], "," ) ) {
                continue;
            }
            found = k;
            foundType = type;
            foundPointer = pointer;
        }
        if ( found >= 0 ) {
            if ( isArray ) {
                *isArray = Is( &unit->tokens[NextCode( unit, found )], "[" );
            }
            if ( isPointer ) {
                *isPointer = foundPointer;
            }
            return unit->tokens[foundType].text;
        }
    }
    return NULL;
}

/*
================
BaseTypeName

The struct type of the expression before the `->` or `.` at `access`:
a variable (`p->m`), an indexed variable (`p[i].m`) or a cast
(`((Foo *)p)->m`).  Returns NULL for anything else.
================
*/
static const char *BaseTypeName( const unit_t *unit, const function_t *func, int access ) {
    int prev = PrevCode( unit, access );
    int before;

    if ( prev < 0 ) {
        return NULL;
    }
    if ( Is( &unit->tokens[prev], "]" ) ) {
        int depth = 0;
        int k;

        for ( k = prev; k >= 0; k = PrevCode( unit, k ) ) {
            if ( Is( &unit->tokens[k], "]" ) ) {
                depth++;
            } else if ( Is( &unit->tokens[k], "[" ) && --depth == 0 ) {
                break;
            }
        }
        if ( k < 0 ) {
            return NULL;
        }
        prev = PrevCode( unit, k );
        if ( prev < 0 ) {
            return NULL;
        }
    }
    if ( unit->tokens[prev].kind == TOK_IDENT ) {
        before = PrevCode( unit, prev );
        if ( before >= 0 && ( Is( &unit->tokens[before], "->" ) || Is( &unit->tokens[before], "." ) ) ) {
            return NULL;            // a member chain: its type is not tracked
        }
        return DeclaredType( unit, func, unit->tokens[prev].text, prev, NULL, NULL );
    }
    if ( Is( &unit->tokens[prev], ")" ) ) {
        int open = MatchOpen( unit, prev );
        int cast = open >= 0 ? NextCode( unit, open ) : -1;
        int isByte = 0;
        int isVolatile = 0;
        int k;

        if ( cast < 0 || CastEnd( unit, cast, prev, &isByte, &isVolatile ) < 0 ) {
            return NULL;
        }
        for ( k = NextCode( unit, cast ); !Is( &unit->tokens[k], ")" ); k = NextCode( unit, k ) ) {
            if ( unit->tokens[k].kind == TOK_IDENT && !Is( &unit->tokens[k], "const" ) && !Is( &unit->tokens[k], "volatile" )
                && !Is( &unit->tokens[k], "struct" ) && !Is( &unit->tokens[k], "union" ) ) {
                return unit->tokens[k].text;
            }
        }
    }
    return NULL;
}

/*
================
CheckVolatile

R17: `volatile` in a body without a `volatile:` note, except casts of a
literal address (hardware registers); uses of volatile members without a note.
================
*/
static void CheckVolatile( const unit_t *unit, function_t *func ) {
    int i;

    // parameters too: `volatile` on a parameter is a carrier like any local
    for ( i = func->paramStart; i < func->bodyEnd; i = NextCode( unit, i ) ) {
        const token_t *token = &unit->tokens[i];

        if ( Is( token, "volatile" ) ) {
            int j = EnclosingCastClose( unit, func, i );
            int hardware = 0;

            // only a cast `( volatile T * ) 0xA4...` addresses a hardware register
            if ( j > i ) {
                int next = NextCode( unit, j );

                while ( next < func->bodyEnd && Is( &unit->tokens[next], "(" ) ) {
                    next = NextCode( unit, next );
                }
                if ( next < func->bodyEnd && ( unit->tokens[next].kind == TOK_NUM
                    || ( unit->tokens[next].kind == TOK_IDENT && !strncmp( unit->tokens[next].text, "PHYS_TO_K", 9 ) ) ) ) {
                    hardware = 1;
                }

                // `(volatile T *)(address | 0xA0000000)`: an uncached KSEG1 access
                next = NextCode( unit, j );
                if ( next < func->bodyEnd && Is( &unit->tokens[next], "(" ) ) {
                    int close = MatchClose( unit, next );
                    int k;

                    for ( k = next; k < close; k = NextCode( unit, k ) ) {
                        if ( unit->tokens[k].kind == TOK_NUM && IsKseg1Address( unit->tokens[k].text ) ) {
                            hardware = 1;
                        }
                    }
                }
            }
            if ( !hardware && !LineHasNote( unit, token->line, VOLATILE_NOTE ) ) {
                AddFinding( func, RULE_R17, token->line, FormatString( "volatile without a 'volatile:' evidence note" ) );
            }
            continue;
        }
        if ( ( Is( token, "->" ) || Is( token, "." ) ) && unit->volatileMembers.count && i >= func->bodyStart ) {
            int         member = NextCode( unit, i );
            const char *owner;
            int         k;

            if ( member >= func->bodyEnd || unit->tokens[member].kind != TOK_IDENT ) {
                continue;
            }
            // through the struct that declares the volatile member; when the base's
            // type cannot be resolved (`(*pp)->m`, `a->b->m`, `f()->m`), by member name
            owner = BaseTypeName( unit, func, i );
            for ( k = 0; k < unit->volatileMembers.count; k++ ) {
                if ( strcmp( unit->volatileMembers.names[k], unit->tokens[member].text ) ) {
                    continue;
                }
                if ( owner && strcmp( unit->volatileOwners.names[k], owner ) ) {
                    continue;
                }
                AddFinding( func, RULE_R17, unit->tokens[member].line,
                    FormatString( "uses volatile member '%s.%s' declared without a 'volatile:' note%s",
                        unit->volatileOwners.names[k], unit->tokens[member].text,
                        owner ? "" : " (base type not resolved; matched by member name)" ) );
                break;
            }
        }
    }
}

/*
================
CheckStatements

R17 statement forms (empty if/else blocks, bare `;`, `do { } while (0)`,
self-assignment, `+ 0`, `* 1`), R18 assembly, R35 braceless bodies and
R2 block-scope externs.
================
*/
static void CheckStatements( unit_t *unit, function_t *func ) {
    int  i;
    int  statementStart;
    int *initializerClose;
    int  depth;

    // closing braces of initializer and aggregate bodies, which a ';' may follow
    initializerClose = calloc( (size_t)unit->numTokens, sizeof( *initializerClose ) );
    if ( !initializerClose ) {
        Error( "out of memory" );
    }
    for ( i = NextCode( unit, func->bodyStart ); i < func->bodyEnd; i = NextCode( unit, i ) ) {
        if ( Is( &unit->tokens[i], "{" ) ) {
            int prev = PrevCode( unit, i );
            int prevPrev = PrevCode( unit, prev );

            if ( Is( &unit->tokens[prev], "=" ) || Is( &unit->tokens[prev], "," )
                || ( Is( &unit->tokens[prev], "{" ) && !Is( &unit->tokens[prevPrev], ")" )
                    && !Is( &unit->tokens[prevPrev], "else" ) && !Is( &unit->tokens[prevPrev], "do" )
                    && !Is( &unit->tokens[prevPrev], ";" ) && !Is( &unit->tokens[prevPrev], "{" )
                    && !Is( &unit->tokens[prevPrev], "}" ) && !Is( &unit->tokens[prevPrev], ":" ) )
                || Is( &unit->tokens[prev], "struct" ) || Is( &unit->tokens[prev], "union" )
                || Is( &unit->tokens[prev], "enum" )
                || ( unit->tokens[prev].kind == TOK_IDENT && prevPrev >= 0
                    && ( Is( &unit->tokens[prevPrev], "struct" ) || Is( &unit->tokens[prevPrev], "union" )
                        || Is( &unit->tokens[prevPrev], "enum" ) ) ) ) {
                initializerClose[MatchClose( unit, i )] = 1;
            }
            if ( Is( &unit->tokens[prev], "struct" ) || Is( &unit->tokens[prev], "union" )
                || ( unit->tokens[prev].kind == TOK_IDENT && prevPrev >= 0
                    && ( Is( &unit->tokens[prevPrev], "struct" ) || Is( &unit->tokens[prevPrev], "union" ) ) ) ) {
                int keyword = Is( &unit->tokens[prev], "struct" ) || Is( &unit->tokens[prev], "union" ) ? prev : prevPrev;
                int close = MatchClose( unit, i );

                RecordAggregate( unit, (int)( unit - units ), keyword, i, close );
            }
        }
    }

    statementStart = NextCode( unit, func->bodyStart );
    depth = 0;
    for ( i = NextCode( unit, func->bodyStart ); i < func->bodyEnd; i = NextCode( unit, i ) ) {
        const token_t *token = &unit->tokens[i];
        int            prev = PrevCode( unit, i );
        int            next = NextCode( unit, i );

        if ( Is( token, "(" ) ) {
            depth++;
        } else if ( Is( token, ")" ) ) {
            depth--;
        }

        if ( Is( token, "asm" ) || Is( token, "__asm" ) || Is( token, "__asm__" ) ) {
            AddFinding( func, RULE_R18, token->line, FormatString( "inline assembly" ) );
        }

        // block-scope extern
        if ( Is( token, "extern" ) && depth == 0 ) {
            int end = i;
            const char *name;

            while ( end < func->bodyEnd && !Is( &unit->tokens[end], ";" ) ) {
                end = NextCode( unit, end );
            }
            if ( IsPrototype( unit, i, PrevCode( unit, end ), &name ) ) {
                AddFinding( func, RULE_R25, token->line, FormatString( "block-scope prototype of '%s'", name ) );
                if ( optListGlobals ) {
                    printf( "P\t%s\t%s\n", unit->path, name );
                }
            } else {
                name_list_t names;
                int         k;

                if ( optListGlobals ) {
                    ListExtern( unit, i, end, "block" );
                }
                // block scope: the declaration belongs to this function only
                memset( &names, 0, sizeof( names ) );
                RecordExternNames( unit, i, end, &names );
                for ( k = 0; k < names.count; k++ ) {
                    AddFinding( func, RULE_R2, token->line,
                        FormatString( "block-scope extern '%s'", names.names[k] ) );
                    free( names.names[k] );
                }
                free( names.names );
                free( names.lines );
            }
        }

        // empty if/else blocks
        if ( Is( token, "{" ) && next < func->bodyEnd && Is( &unit->tokens[next], "}" ) ) {
            if ( Is( &unit->tokens[prev], "else" ) ) {
                AddFinding( func, RULE_R17, token->line, FormatString( "empty else block" ) );
            } else if ( Is( &unit->tokens[prev], ")" ) ) {
                int open = MatchOpen( unit, prev );
                int keyword = PrevCode( unit, open );

                if ( keyword >= 0 && Is( &unit->tokens[keyword], "if" ) ) {
                    AddFinding( func, RULE_R17, token->line, FormatString( "empty if block" ) );
                }
            }
        }

        // bare ';' statements
        if ( Is( token, ";" ) && depth == 0 && prev >= 0 ) {
            const token_t *before = &unit->tokens[prev];

            if ( Is( before, "{" ) || Is( before, ";" ) || ( Is( before, "}" ) && !initializerClose[prev] ) ) {
                AddFinding( func, RULE_R17, token->line, FormatString( "bare ';' statement" ) );
            } else if ( Is( before, ")" ) ) {
                int open = MatchOpen( unit, prev );
                int keyword = PrevCode( unit, open );

                if ( keyword >= 0 && Is( &unit->tokens[keyword], "if" ) ) {
                    AddFinding( func, RULE_R17, token->line, FormatString( "empty if statement" ) );
                }
            } else if ( Is( before, "else" ) ) {
                AddFinding( func, RULE_R17, token->line, FormatString( "empty else statement" ) );
            }
        }

        // do { } while ( 0 )
        if ( Is( token, "while" ) && Is( &unit->tokens[prev], "}" ) && next < func->bodyEnd
            && Is( &unit->tokens[next], "(" ) ) {
            int value = NextCode( unit, next );
            int close = NextCode( unit, value );

            if ( close < func->bodyEnd && IsZeroLiteral( unit->tokens[value].text ) && Is( &unit->tokens[close], ")" ) ) {
                AddFinding( func, RULE_R17, token->line, FormatString( "do { } while ( 0 ) in a function body" ) );
            }
        }

        // + 0 and * 1
        if ( ( Is( token, "+" ) || Is( token, "-" ) || Is( token, "*" ) ) && prev >= 0
            && IsOperandEnd( &unit->tokens[prev] ) && next < func->bodyEnd
            && unit->tokens[next].kind == TOK_NUM ) {
            int follow = NextCode( unit, next );
            int bounded = follow >= func->bodyEnd || !( Is( &unit->tokens[follow], "*" )
                || Is( &unit->tokens[follow], "/" ) || Is( &unit->tokens[follow], "%" )
                || Is( &unit->tokens[follow], "[" ) );

            if ( bounded && !Is( token, "*" ) && IsZeroLiteral( unit->tokens[next].text )
                && !IsCastOperandGroup( unit, follow ) && !IsStrideIndex( unit, prev ) ) {
                AddFinding( func, RULE_R17, token->line, FormatString( "'%s 0'", token->text ) );
            } else if ( bounded && Is( token, "*" ) && !strcmp( unit->tokens[next].text, "1" ) ) {
                AddFinding( func, RULE_R17, token->line, FormatString( "'* 1'" ) );
            }
        }

        // braceless bodies
        if ( ( Is( token, "if" ) || Is( token, "while" ) || Is( token, "for" ) ) && next < func->bodyEnd
            && Is( &unit->tokens[next], "(" ) ) {
            int close = MatchClose( unit, next );
            int body = NextCode( unit, close );

            if ( body < func->bodyEnd && !Is( &unit->tokens[body], "{" ) && !Is( &unit->tokens[body], ";" ) ) {
                AddFinding( func, RULE_R35, token->line, FormatString( "'%s' body without braces", token->text ) );
            }
        }
        if ( Is( token, "else" ) && next < func->bodyEnd && !Is( &unit->tokens[next], "{" )
            && !Is( &unit->tokens[next], "if" ) ) {
            AddFinding( func, RULE_R35, token->line, FormatString( "'else' body without braces" ) );
        }

        // statement boundaries and self-assignment
        if ( Is( token, ";" ) || Is( token, "{" ) || Is( token, "}" ) ) {
            if ( Is( token, ";" ) && depth == 0 ) {
                int eq = -1;
                int count = 0;
                int k;

                for ( k = statementStart; k < i; k = NextCode( unit, k ) ) {
                    if ( Is( &unit->tokens[k], "=" ) ) {
                        eq = k;
                        count++;
                    }
                }
                if ( count == 1 && eq > statementStart ) {
                    char *left = JoinTokens( unit, statementStart, PrevCode( unit, eq ) );
                    char *right = JoinTokens( unit, NextCode( unit, eq ), PrevCode( unit, i ) );

                    if ( !strcmp( left, right ) ) {
                        AddFinding( func, RULE_R17, token->line, FormatString( "self-assignment" ) );
                    }
                    free( left );
                    free( right );
                }
            }
            if ( depth == 0 ) {
                statementStart = next;
            }
        } else if ( Is( token, ":" ) && depth == 0 ) {
            statementStart = next;
        } else if ( Is( token, ")" ) && depth == 0 ) {
            // after `if ( ... )` the statement starts again
            int open = MatchOpen( unit, i );
            int keyword = PrevCode( unit, open );

            if ( keyword >= 0 && ( Is( &unit->tokens[keyword], "if" ) || Is( &unit->tokens[keyword], "while" )
                || Is( &unit->tokens[keyword], "for" ) || Is( &unit->tokens[keyword], "switch" ) ) ) {
                statementStart = next;
            }
        } else if ( Is( token, "else" ) || Is( token, "do" ) ) {
            statementStart = next;
        }
    }
    free( initializerClose );
}

/*
================
CheckExternUses

R2: a function that uses a global this unit declares `extern`.
================
*/
static void CheckExternUses( const unit_t *unit, function_t *func ) {
    char *reported;
    int   i;

    if ( !unit->externs.count ) {
        return;
    }
    reported = calloc( (size_t)unit->externs.count, 1 );
    if ( !reported ) {
        Error( "out of memory" );
    }
    for ( i = func->bodyStart; i < func->bodyEnd; i = NextCode( unit, i ) ) {
        int index;
        int prev;

        if ( unit->tokens[i].kind != TOK_IDENT ) {
            continue;
        }
        prev = PrevCode( unit, i );
        if ( prev >= 0 && ( Is( &unit->tokens[prev], "->" ) || Is( &unit->tokens[prev], "." ) ) ) {
            continue;
        }
        index = NameList_Find( &unit->externs, unit->tokens[i].text );
        if ( index >= 0 && !reported[index] && unit->externs.lines[index] < unit->tokens[func->bodyStart].line ) {
            reported[index] = 1;
            AddFinding( func, RULE_R2, unit->tokens[i].line,
                FormatString( "uses '%s', declared extern in this unit (line %d), not in a header",
                    unit->tokens[i].text, unit->externs.lines[index] ) );
        }
    }
    free( reported );
}

/*
================
CheckTypeCopies

R1: a function that names a type this unit defines differently from
another file.
================
*/
static void CheckTypeCopies( const unit_t *unit, function_t *func, const name_list_t *conflictNames ) {
    char *reported;
    int   i;

    if ( !conflictNames->count ) {
        return;
    }
    reported = calloc( (size_t)conflictNames->count, 1 );
    if ( !reported ) {
        Error( "out of memory" );
    }
    for ( i = func->paramStart; i < func->bodyEnd; i = NextCode( unit, i ) ) {
        int index;

        if ( unit->tokens[i].kind != TOK_IDENT ) {
            continue;
        }
        index = NameList_Find( conflictNames, unit->tokens[i].text );
        if ( index >= 0 && !reported[index] ) {
            reported[index] = 1;
            AddFinding( func, RULE_R1, unit->tokens[i].line,
                FormatString( "type '%s' is defined differently in another file", unit->tokens[i].text ) );
        }
    }
    free( reported );
}

/*
================
CheckAdvisory

R7 placeholder names, R33 header comments, R27 padding members.
================
*/
static void CheckAdvisory( unit_t *unit, function_t *func ) {
    int i;
    int start;
    int placeholders = 0;

    for ( i = func->paramStart; i < func->bodyEnd; i = NextCode( unit, i ) ) {
        if ( unit->tokens[i].kind == TOK_IDENT && IsPlaceholder( unit->tokens[i].text ) ) {
            placeholders++;
        }
    }
    if ( IsPlaceholder( func->name ) || placeholders ) {
        AddFinding( func, RULE_R7, func->line,
            FormatString( "%s%d placeholder identifier use(s)", IsPlaceholder( func->name ) ? "placeholder function name; " : "",
                placeholders ) );
    }

    // the header comment sits directly above the declaration's first token
    start = func->paramStart;
    for ( ;; ) {
        int prev = PrevCode( unit, start );

        if ( prev < 0 || Is( &unit->tokens[prev], ";" ) || Is( &unit->tokens[prev], "}" ) ) {
            break;
        }
        start = prev;
    }
    if ( start == 0 || unit->tokens[start - 1].kind != TOK_COMMENT ) {
        AddFinding( func, RULE_R33, func->line, FormatString( "no header comment" ) );
    }

    for ( i = func->bodyStart; i < func->bodyEnd && unit->padMembers.count; i = NextCode( unit, i ) ) {
        int prev = PrevCode( unit, i );

        if ( unit->tokens[i].kind == TOK_IDENT && prev >= 0
            && ( Is( &unit->tokens[prev], "->" ) || Is( &unit->tokens[prev], "." ) )
            && NameList_Find( &unit->padMembers, unit->tokens[i].text ) >= 0 ) {
            AddFinding( func, optStrictPadding ? RULE_R17 : RULE_R27, unit->tokens[i].line,
                FormatString( "uses padding member '%s' (name it unk_<HEX>: uppercase hex, no 0x)", unit->tokens[i].text ) );
        }
    }
}

/*
===============================================================================

DRIVER

===============================================================================
*/

/*
================
HasSuffix
================
*/
static int HasSuffix( const char *path, const char *suffix ) {
    size_t pathLength = strlen( path );
    size_t suffixLength = strlen( suffix );

    return pathLength >= suffixLength && !strcmp( path + pathLength - suffixLength, suffix );
}

/*
================
LoadUnit
================
*/
static void LoadUnit( const char *path ) {
    FILE   *file;
    long    size;
    char   *source;
    unit_t *unit;

    file = fopen( path, "rb" );
    if ( !file ) {
        Error( "cannot open %s", path );
    }
    fseek( file, 0, SEEK_END );
    size = ftell( file );
    fseek( file, 0, SEEK_SET );
    source = malloc( (size_t)size + 1 );
    if ( !source ) {
        Error( "out of memory" );
    }
    if ( fread( source, 1, (size_t)size, file ) != (size_t)size ) {
        Error( "cannot read %s", path );
    }
    source[size] = '\0';
    fclose( file );

    units = Grow( units, numUnits, &maxUnits, sizeof( *units ) );
    unit = &units[numUnits++];
    memset( unit, 0, sizeof( *unit ) );
    unit->path = CopyString( path, strlen( path ) );
    unit->isHeader = HasSuffix( path, ".h" );
    Lex( unit, source );
    free( source );
}

/*
================
ComparePaths
================
*/
static int ComparePaths( const void *a, const void *b ) {
    return strcmp( *(char *const *)a, *(char *const *)b );
}

/*
================
LoadPath

Loads a file, or every .c and .h file under a directory, in sorted order.
================
*/
static void LoadPath( const char *path ) {
    struct stat    info;
    DIR           *dir;
    struct dirent *entry;
    char         **children = NULL;
    int            numChildren = 0;
    int            maxChildren = 0;
    int            i;

    if ( stat( path, &info ) != 0 ) {
        Error( "cannot stat %s", path );
    }
    if ( !S_ISDIR( info.st_mode ) ) {
        if ( HasSuffix( path, ".c" ) || HasSuffix( path, ".h" ) ) {
            LoadUnit( path );
        }
        return;
    }
    dir = opendir( path );
    if ( !dir ) {
        Error( "cannot open directory %s", path );
    }
    while ( ( entry = readdir( dir ) ) != NULL ) {
        if ( entry->d_name[0] == '.' ) {
            continue;
        }
        children = Grow( children, numChildren, &maxChildren, sizeof( *children ) );
        children[numChildren++] = FormatString( "%s/%s", path, entry->d_name );
    }
    closedir( dir );
    qsort( children, (size_t)numChildren, sizeof( *children ), ComparePaths );
    for ( i = 0; i < numChildren; i++ ) {
        LoadPath( children[i] );
        free( children[i] );
    }
    free( children );
}

/*
================
CompareTypeDefs

Orders type definitions by name, then by file.
================
*/
static int CompareTypeDefs( const void *a, const void *b ) {
    const type_def_t *defA = &typeDefs[*(const int *)a];
    const type_def_t *defB = &typeDefs[*(const int *)b];
    int               order = strcmp( defA->name, defB->name );

    return order ? order : defA->unit - defB->unit;
}

/*
================
PrintFinding
================
*/
static int printedLines;

static void PrintFinding( const unit_t *unit, const function_t *func, const finding_t *finding ) {
    if ( optMaxLines >= 0 && printedLines >= optMaxLines ) {
        return;
    }
    printf( "%s:%d: %s: %s [%s] %s\n", unit->path, finding->line, func->name, ruleNames[finding->rule],
        finding->rule < NUM_MATCH_RULES ? "match" : "advisory", finding->message );
    printedLines++;
}

/*
================
main
================
*/
int main( int argc, char **argv ) {
    static const char *const defaultPaths[] = { "include", "src", NULL };
    name_list_t *conflictNames;
    int         *order;
    int   numPaths = 0;
    int   loadedInclude = 0;
    int   functions = 0;
    int   pending = 0;
    int   ruleFunctions[NUM_RULES];
    int   ruleFindings[NUM_RULES];
    int   disabledBlocks = 0;
    int   prototypeUnits = 0;
    int   prototypes = 0;
    int   i;
    int   u;

    memset( ruleFunctions, 0, sizeof( ruleFunctions ) );
    memset( ruleFindings, 0, sizeof( ruleFindings ) );
    for ( i = 1; i < argc; i++ ) {
        if ( !strcmp( argv[i], "--findings" ) ) {
            optFindings = 1;
        } else if ( !strcmp( argv[i], "--advisory" ) ) {
            optFindings = 1;
            optAdvisory = 1;
        } else if ( !strcmp( argv[i], "--pending" ) ) {
            optPending = 1;
        } else if ( !strcmp( argv[i], "--strict-padding" ) ) {
            optStrictPadding = 1;
        } else if ( !strcmp( argv[i], "--list-globals" ) ) {
            optListGlobals = 1;
        } else if ( !strcmp( argv[i], "--fail-on-pending" ) ) {
            optFailOnPending = 1;
        } else if ( !strcmp( argv[i], "--max-lines" ) && i + 1 < argc ) {
            optMaxLines = atoi( argv[++i] );
        } else if ( !strcmp( argv[i], "--help" ) || !strcmp( argv[i], "-h" ) ) {
            printf( "usage: rules_check [--findings] [--advisory] [--pending] [--strict-padding]\n"
                    "                   [--fail-on-pending] [--max-lines N] [path...]\n" );
            return 0;
        } else if ( argv[i][0] == '-' ) {
            Error( "unknown option %s", argv[i] );
        } else {
            numPaths++;
            if ( !strncmp( argv[i], "include", 7 ) || !strncmp( argv[i], "./include", 9 ) ) {
                loadedInclude = 1;
            }
        }
    }

    // include/ is read first: shared types, and the macros #if conditions may test
    if ( !numPaths ) {
        for ( i = 0; defaultPaths[i]; i++ ) {
            LoadPath( defaultPaths[i] );
        }
    } else {
        struct stat info;
        int         pass;

        if ( !loadedInclude && stat( "include", &info ) == 0 && S_ISDIR( info.st_mode ) ) {
            LoadPath( "include" );
        }
        for ( pass = 0; pass < 2; pass++ ) {
            for ( i = 1; i < argc; i++ ) {
                int isInclude = !strncmp( argv[i], "include", 7 ) || !strncmp( argv[i], "./include", 9 );

                if ( argv[i][0] == '-' ) {
                    if ( !strcmp( argv[i], "--max-lines" ) ) {
                        i++;
                    }
                    continue;
                }
                if ( isInclude == ( pass == 0 ) ) {
                    LoadPath( argv[i] );
                }
            }
        }
    }

    for ( u = 0; u < numUnits; u++ ) {
        if ( optListGlobals ) {
            ComputeConditionalDepth( &units[u] );
        }
        ParseTopLevel( &units[u], u );
    }

    // statement checks also record block-scope aggregates for R1
    for ( u = 0; u < numUnits; u++ ) {
        if ( units[u].isHeader ) {
            continue;
        }
        for ( i = 0; i < units[u].numFunctions; i++ ) {
            CheckStatements( &units[u], &units[u].functions[i] );
        }
    }

    if ( optListGlobals ) {
        // aggregate type names (struct tags and typedefs with bodies)
        for ( i = 0; i < numTypeDefs; i++ ) {
            printf( "T\t%s\t%s\n", units[typeDefs[i].unit].path, typeDefs[i].name );
        }

        // function names (prototypes and definitions) and macro names
        for ( u = 0; u < numUnits; u++ ) {
            const unit_t *unit = &units[u];

            for ( i = 0; i < unit->prototypes.count; i++ ) {
                printf( "P\t%s\t%s\n", unit->path, unit->prototypes.names[i] );
            }
            for ( i = 0; i < unit->numFunctions; i++ ) {
                printf( "P\t%s\t%s\n", unit->path, unit->functions[i].name );
            }
            for ( i = 0; i < unit->numTokens; i++ ) {
                const char *p = unit->tokens[i].text;
                const char *start;

                if ( unit->tokens[i].kind != TOK_PP || !DirectiveIs( p, "define" ) ) {
                    continue;
                }
                // the macro's name and every identifier in its replacement
                p = strstr( p, "define" ) + 6;
                while ( *p ) {
                    if ( !isalpha( (unsigned char)*p ) && *p != '_' ) {
                        p++;
                        continue;
                    }
                    for ( start = p; isalnum( (unsigned char)*p ) || *p == '_'; p++ ) {
                    }
                    printf( "M\t%s\t%.*s\n", unit->path, (int)( p - start ), start );
                }
            }
        }
        return 0;
    }

    // R1: the same type name with different bodies in different files
    conflictNames = calloc( (size_t)numUnits, sizeof( *conflictNames ) );
    order = malloc( ( (size_t)numTypeDefs + 1 ) * sizeof( *order ) );
    if ( !conflictNames || !order ) {
        Error( "out of memory" );
    }
    for ( i = 0; i < numTypeDefs; i++ ) {
        order[i] = i;
    }
    qsort( order, (size_t)numTypeDefs, sizeof( *order ), CompareTypeDefs );
    for ( i = 0; i < numTypeDefs; ) {
        int end;
        int differs = 0;
        int j;

        for ( end = i + 1; end < numTypeDefs && !strcmp( typeDefs[order[end]].name, typeDefs[order[i]].name ); end++ ) {
            if ( strcmp( typeDefs[order[end]].body, typeDefs[order[i]].body ) ) {
                differs = 1;
            }
        }
        if ( differs ) {
            for ( j = i; j < end; j++ ) {
                const type_def_t *def = &typeDefs[order[j]];
                int               k;

                // only definitions whose body differs from one in another file
                for ( k = i; k < end; k++ ) {
                    const type_def_t *other = &typeDefs[order[k]];

                    if ( other->unit != def->unit && strcmp( other->body, def->body ) ) {
                        if ( NameList_Find( &conflictNames[def->unit], def->name ) < 0 ) {
                            NameList_Add( &conflictNames[def->unit], def->name, def->line );
                        }
                        break;
                    }
                }
            }
        }
        i = end;
    }
    free( order );

    for ( u = 0; u < numUnits; u++ ) {
        unit_t *unit = &units[u];
        int     definedHere;

        if ( unit->isHeader ) {
            continue;
        }
        disabledBlocks += unit->disabledBlocks.count;
        definedHere = 0;
        for ( i = 0; i < unit->prototypes.count; i++ ) {
            int f;
            int local = 0;

            for ( f = 0; f < unit->numFunctions; f++ ) {
                if ( !strcmp( unit->functions[f].name, unit->prototypes.names[i] ) ) {
                    local = 1;
                }
            }
            if ( !local ) {
                prototypes++;
                definedHere = 1;
            }
        }
        prototypeUnits += definedHere;
        if ( optAdvisory ) {
            for ( i = 0; i < unit->disabledBlocks.count; i++ ) {
                if ( optMaxLines < 0 || printedLines < optMaxLines ) {
                    printf( "%s:%d: (unit): R37 [advisory] #if 0 outside the %s parking form\n", unit->path,
                        unit->disabledBlocks.lines[i], PARKING_MARKER );
                    printedLines++;
                }
            }
        }

        for ( i = 0; i < unit->numFunctions; i++ ) {
            function_t *func = &unit->functions[i];
            int         f;
            int         r;

            CheckOffsetAccess( unit, func );
            CheckVolatile( unit, func );
            CheckExternUses( unit, func );
            CheckTypeCopies( unit, func, &conflictNames[u] );
            CheckAdvisory( unit, func );

            functions++;
            if ( func->matchRules ) {
                pending++;
            }
            for ( r = 0; r < NUM_RULES; r++ ) {
                unsigned bit = r < NUM_MATCH_RULES ? ( func->matchRules >> r ) & 1
                    : ( func->advisoryRules >> ( r - NUM_MATCH_RULES ) ) & 1;

                ruleFunctions[r] += bit;
            }
            for ( f = 0; f < func->numFindings; f++ ) {
                ruleFindings[func->findings[f].rule]++;
                if ( optFindings && ( func->findings[f].rule < NUM_MATCH_RULES || optAdvisory ) ) {
                    PrintFinding( unit, func, &func->findings[f] );
                }
            }
            if ( optPending && func->matchRules && ( optMaxLines < 0 || printedLines < optMaxLines ) ) {
                printf( "MATCH-PENDING %s %s:", func->name, unit->path );
                for ( r = 0; r < NUM_MATCH_RULES; r++ ) {
                    if ( func->matchRules & ( 1u << r ) ) {
                        printf( " %s", ruleNames[r] );
                    }
                }
                printf( "\n" );
                printedLines++;
            }
        }
    }

    printf( "functions with C bodies (bytes matched): %d\n", functions );
    printf( "matched under the rules:                 %d\n", functions - pending );
    printf( "MATCH-PENDING:                           %d\n", pending );
    printf( "\n[match] rules              functions  findings\n" );
    for ( i = 0; i < NUM_MATCH_RULES; i++ ) {
        printf( "  %-4s %-48s %6d %9d\n", ruleNames[i], ruleTitles[i], ruleFunctions[i], ruleFindings[i] );
    }
    if ( optStrictPadding ) {
        printf( "  (padding members counted under R17: --strict-padding)\n" );
    }
    printf( "\nadvisory rules             functions  findings\n" );
    for ( i = NUM_MATCH_RULES; i < NUM_RULES; i++ ) {
        if ( i == RULE_R25 ) {
            printf( "  %-4s %-48s %6d %9d  (+%d file-scope prototypes in %d units)\n", ruleNames[i], ruleTitles[i],
                ruleFunctions[i], ruleFindings[i], prototypes, prototypeUnits );
        } else if ( i == RULE_R37 ) {
            printf( "  %-4s %-48s %6s %9d\n", ruleNames[i], ruleTitles[i], "-", disabledBlocks );
        } else {
            printf( "  %-4s %-48s %6d %9d\n", ruleNames[i], ruleTitles[i], ruleFunctions[i], ruleFindings[i] );
        }
    }
    return optFailOnPending && pending ? 1 : 0;
}
