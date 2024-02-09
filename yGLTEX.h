/*============================----beg-of-source---============================*/
#ifndef YGLTEX
#define YGLTEX loaded

#include    <ySTR_solo.h>


/*---(modes)--------------------------*/
#define     YGLTEX_NORMAL    '-'
#define     YGLTEX_AUDIT     'a'
#define     YGLTEX_SAMPLE    's'

/*---(sources/destinations)-----------*/
#define     YGLTEX_IMAGE     'c'
#define     YGLTEX_TEXTURE   't'
#define     YGLTEX_SCREEN    'w'
#define     YGLTEX_READONLY  'r'

/*---(ramps)--------------------------*/
#define     YGLTEX_MINIMAL   '-'
#define     YGLTEX_SHRIKE    's'
#define     YGLTEX_RAMPS     "-s"

/*---(alignments)---------------------*/
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

/*-> read png image into texture ---------------*/
uint        yGLTEX_png2tex       (cchar a_pngname [LEN_PATH]);

/*-> save screenprint as a png image -----------*/
char        yGLTEX_scr2png       (cchar a_pngname [LEN_PATH], cint a_wide, cint a_tall);

/*-> save current texture as png image ---------*/
char        yGLTEX_tex2png       (cchar *a_name, cint a_wide, cint a_tall);

char        yGLTEX_get_size      (int *a_wide, int *a_tall);

/*-> convert png symbols into ascii-art --------*/
char        yGLTEX_png2ascii        (cchar a_pngname [LEN_PATH], cchar a_tilename [LEN_PATH], char a_style, int a_xscale, int a_xmargin, int a_yscale, int a_ymargin);

/*-> convert ascii-art to png tiles ------------*/
char        yGLTEX_ascii2tiles      (char a_mode, cchar a_pngname [LEN_PATH], cchar a_tilename [LEN_PATH]);

/*-> critical data from last ascii2tiles -------*/
char        yGLTEX_tile_data        (char *r_ready, char r_title [LEN_DESC], char *r_style, char *r_ramp, int *r_wide, int *r_tall, int *r_total, int *r_used, int *r_xscale, int *r_yscale, int *r_buffer, int *r_fields, int *r_xmax, int *r_ymax, int *r_xactual, int *r_yactual);



#endif

/*============================----end-of-source---============================*/
