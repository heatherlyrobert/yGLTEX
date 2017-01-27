/*============================----beg-of-source---============================*/
#ifndef YGLTEX
#define YGLTEX loaded


/*===[[ HEADERS ]]========================================*/
/*---(ansi-c standard)-------------------*/
#include    <stdio.h>        /* CLIBC   standard input/output                 */
#include    <stdlib.h>       /* CLIBC   standard general purpose              */
#include    <string.h>       /* CLIBC   standard string handling              */
/*---(X11 standard)----------------------*/
#include    <X11/X.h>        /* X11     standard overall file                 */
#include    <X11/Xlib.h>     /* X11     standard C API                        */
/*---(opengl standard)-------------------*/
#include    <GL/gl.h>        /* OPENGL  standard primary header               */
#include    <GL/glx.h>       /* OPENGL  standard X11 integration              */
/*---(heatherly made)--------------------*/
#include    <yURG.h>         /* CUSTOM  heatherly urgent processing           */
#include    <yLOG.h>         /* CUSTOM  heatherly program logging             */
#include    <ySTR.h>         /* CUSTOM  heatherly string handling             */
/*---(special)---------------------------*/
#include    <png.h>          /* OTHER   PNG image library                     */




GLuint      yGLTEX_png2tex       (const char *a_name);
char        yGLTEX_scr2png       (const char *a_name, int a_width, int a_height);


#endif

/*============================----end-of-source---============================*/
