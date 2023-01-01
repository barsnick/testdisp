/* testdisp-1.4
 * Copyright (c) 1999-2023 Moritz Barsnick <barsnick@gmx.net>
 *
 * A program to check whether an X11 server is available and allows access
 * from the user calling it.
 *
 * License: GPLv3
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
