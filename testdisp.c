/* testdisp-1.1
 * © 1999-2000 Moritz Barsnick <barsnick@gmx.net>
 *
 * A program to check whether the X11 server specified in the
 *   environment variable DISPLAY actually allows access from the
 *   user calling it.
 *
 * Usage:
 * # testdisp  ($DISPLAY has to be set to the server being tested)
 * # testdisp <display>
 * e.g.
 * # testdisp remotehost:0.0
 *
 * Return level (exit code):
 *   0 if display could be opened
 *   1 if display could not be opened
 *   2 if wrong number of arguments was given
 *
 * Compililation:
 * # gcc -Wall -o testdisp testdisp.c -lX11 -lsocket
 * or similar
 *
 * Author: Moritz Barsnick <barsnick@gmx.net>
 *
 * Revision history:
 *   0.x	1999-05		various tries and fiddles :)
 *   1.0	1999-06-03	first fully working and C-syntactically
 *      			correct version
 *   1.1	2000-01-21	added comments
 *
 * License: GPL

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

char * display;
Display * hDisplay;

int main( int argc, char **argv )
{
  if ( argc > 2 )
  {
    fprintf( stderr, "Too many arguments\n" );
    exit(2);
  }
  
  if ( argc == 2 )
  {
    display = argv[1];
  }
  else
  {
    display = (char *)getenv( "DISPLAY" );
  }

  hDisplay = XOpenDisplay( display );
  if ( !hDisplay )
  {
    fprintf( stderr, "Could not open display '%s'\n", display );
            exit(1);
  }
  else
  {
    fprintf( stderr, "Successfully opened display '%s'\n", display );
            exit(0);
  }
}
