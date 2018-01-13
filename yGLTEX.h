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



#define     YGLTEX_TOPLEF    1
#define     YGLTEX_TOPCEN    2
#define     YGLTEX_TOPRIG    3

#define     YGLTEX_MIDLEF    4
#define     YGLTEX_MIDCEN    5
#define     YGLTEX_MIDRIG    6

#define     YGLTEX_BOTLEF    7
#define     YGLTEX_BOTCEN    8
#define     YGLTEX_BOTRIG    9

#define     YGLTEX_GREGG     10


typedef     const char          cchar;
typedef     unsigned int        uint;
typedef     const unsigned int  cuint;
typedef     const float         cfloat;


char*       yGLTEX_version       (void);
char        yGLTEX_init          (void);

char        yGLTEX_new           (uint  *a_tex , uint  *a_fbo  , uint *a_depth, cint a_wide, cint a_tall);
char        yGLTEX_free          (uint  *a_tex , uint  *a_fbo  , uint *a_depth);

char        yGLTEX_draw_start    (cuint  a_fbo , cchar  a_pos  , cint  a_wide , cint a_tall, cfloat a_scale);
char        yGLTEX_draw_end      (cuint  a_tex );

GLuint      yGLTEX_png2tex       (cchar *a_name);
char        yGLTEX_scr2png       (cchar *a_name, cint   a_width, cint  a_height);

char        yGLTEX_get_size      (int *a_wide, int *a_tall);


#endif

/*============================----end-of-source---============================*/
