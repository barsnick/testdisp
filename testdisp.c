/* testdisp-1.4
 * Copyright (c) 1999-2023 Moritz Barsnick <barsnick@gmx.net>
 *
 * A program to check whether an X11 server is available and allows access
 * from the user calling it. It checks either the display specified in the
 * argument or, if not available, in the environment variable $DISPLAY.
 *
 * Success or failure messages are sent to standard error.
 *
 * -----
 *
 * Usage:
 *
 * prompt> testdisp  # $DISPLAY has to be set to the server being tested
 *
 * or
 *
 * prompt> testdisp <display>
 * e.g.
 * prompt> testdisp remotehost:0.0
 *
 * Return level (exit code):
 *   0 if display could be opened
 *   1 if display could not be opened
 *   2 if wrong number of arguments was given
 *
 * -----
 *
 * Compilation:
 * prompt> gcc -Wall -o testdisp testdisp.c -lX11
 * or
 * prompt> gcc -Wall -o testdisp testdisp.c -lX11 -lsocket
 * on Solaris,
 * or similar.
 *
 * -----
 *
 * Common usage:
 *
 * First and foremost in your mailcap (e.g. ~/.mailcap), to differentiate
 * when you have an X11 display and when not. Note that many programs
 * use mailcap, and you may not want all of them to have this behavior!
 * No more trying to start a PDF viewer from your terminal.
 *
 * You'll need some lines like these in ~/.mailcap:
 * image/gif; xv %s; test=testdisp 2>/dev/null; description=GIF image; nametemplate=%s.gif
 * image/gif; zgv %s; needsterminal; description=GIF image; nametemplate=%s.gif
 *
 * Note the "test=" parameter in the first line using this X11 application
 * testdisp! See RFC 1524: http://www.faqs.org/rfcs/rfc1524.html
 *
 * In my ~/.urlview (for the program "urlview"), I have this statement:
 * COMMAND URL=%s; if testdisp 2>/dev/null; then xw3m "$URL"; else w3m "$URL"; fi
 *
 * Author: Moritz Barsnick <barsnick@gmx.net>
 *
 * Revision history:
 *   0.x	1999-05		various attemps and fiddles :)
 *   1.0	1999-06-03	first fully working and C-syntactically
 *      			correct version
 *   1.1	2000-01-21	added comments
 *   1.2	2001-01-29	updated comments and copyright
 *   1.3	2001-07-26	added more comments and usage info; added
 *				progname in messages; ready for public
 *				release
 *   1.4	2023-01-01	updated comments and copyright
 *
 * License: GPL
 */

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

char *display;
Display *hDisplay;

int main(int argc, char **argv) {
  if (argc > 2) {
    fprintf( stderr, "%s: Too many arguments\n", argv[0] );
    exit(2);
  }
  
  if (argc == 2) {
    display = argv[1];
  }
  else {
    display = (char *)getenv("DISPLAY");
  }

  if (!display) {
    fprintf(stderr, "No display argument given and no DISPLAY environment variable set\n");
    exit(2);
  }

  hDisplay = XOpenDisplay(display);
  if (!hDisplay) {
    fprintf(stderr, "Could not open display '%s'\n", display);
    exit(1);
  }
  else {
    fprintf(stderr, "Successfully opened display '%s'\n", display);
    exit(0);
  }
}
