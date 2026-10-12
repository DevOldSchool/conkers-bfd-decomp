/* Raw-DEFLATE driver for the bounded-lookahead encoder. */
#include <stdlib.h>
#include "tailor.h"
#include "gzip.h"
uch inbuf[INBUFSIZ + INBUF_EXTRA];
uch outbuf[OUTBUFSIZ + OUTBUF_EXTRA];
ush d_buf[DIST_BUFSIZE];
uch window[2L * WSIZE];
ush prev[65536];
unsigned outcnt;
long bytes_in;
int level, method = DEFLATED;

void error(char *message) {
    fprintf(stderr, "bounded-deflate: %s\n", message);
    exit(2);
}
int file_read(char *buffer, unsigned size) {
    size_t n = fread(buffer, 1, size, stdin);
    if (ferror(stdin)) error("input read failed");
    bytes_in += n;
    return (int)n;
}
void flush_outbuf(void) {
    if (outcnt && fwrite(outbuf, 1, outcnt, stdout) != outcnt)
        error("output write failed");
    outcnt = 0;
}
int main(int argc, char **argv) {
    ush attr = 0, flags = 0;
    if (argc != 2 || (strcmp(argv[1], "6") && strcmp(argv[1], "9")))
        error("expected level 6 or 9");
    level = atoi(argv[1]);
    bi_init(1);
    ct_init(&attr, &method);
    lm_init(level, &flags);
    (void)deflate();
    flush_outbuf();
    if (fflush(stdout)) error("output flush failed");
    return 0;
}
