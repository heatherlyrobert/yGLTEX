/*============================----beg-of-source---============================*/
#ifndef YGLTEX
#define YGLTEX loaded

#include    <ySTR_solo.h>


#define     YGLTEX_NORMAL    '-'
#define     YGLTEX_AUDIT     'a'
#define     YGLTEX_SAMPLE    's'


#define     YGLTEX_TOPLEF    1
#define     YGLTEX_TOPCEN    2
#define     YGLTEX_TOPRIG    3

#define     YGLTEX_MIDLEF    4
#define     YGLTEX_MIDCEN    5
#define     YGLTEX_MIDRIG    6

#define     YGLTEX_BOTLEF    10
#define     YGLTEX_BOTCEN    11
#define     YGLTEX_BOTRIG    12

#define     YGLTEX_GREGG     20


typedef     const char          cchar;
typedef     unsigned int        uint;
typedef     const int           cint;
typedef     const unsigned int  cuint;
typedef     const float         cfloat;


char*       yGLTEX_version       (void);
char        yGLTEX_config        (void);

char        yGLTEX_new           (uint *a_tex, uint *a_fbo, uint *a_depth, cint a_wide, cint a_tall);
char        yGLTEX_free          (uint *a_tex, uint *a_fbo, uint *a_depth);

char        yGLTEX_draw          (uint a_tex, uint a_fbo, cchar a_pos, cint a_wide, cint a_tall, cfloat a_scale);
char        yGLTEX_done          (uint a_tex);

uint        yGLTEX_png2tex       (cchar *a_name);
char        yGLTEX_scr2png       (cchar *a_name, cint a_width, cint a_height);
char        yGLTEX_tex2png       (cchar *a_name, cint a_width, cint a_height);

char        yGLTEX_get_size      (int *a_wide, int *a_tall);

char        yGLTEX_png2txt          (cchar a_name [LEN_HUND]);
char        yGLTEX_txt2png          (char a_mode, cchar a_name [LEN_HUND], cchar a_dest [LEN_HUND]);


#endif

/*============================----end-of-source---============================*/
