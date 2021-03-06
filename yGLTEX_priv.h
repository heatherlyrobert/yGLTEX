/*============================----beg-of-source---============================*/
#include "yGLTEX.h"


#ifndef YGLTEX_PRIV
#define YGLTEX_PRIV loaded



/* rapidly evolving version number to aid with visual change confirmation     */
#define     P_VERNUM    "0.3d"
#define     P_VERTXT    "can now save a texture as a png"



/*===[[ RATIONAL LIMITS ]]====================================================*/
/*   LEN_ is a length or size of something
 *   MIN_ is a minimum count
 *   DEF_ is a default count
 *   MAX_ is a maximum count
 *
 */
/*3456789012+123456789012+123456789012+123456789012+123456789012+123456789012*/
/*---(string length)------------------*/
#define     LEN_RECD     2000
#define     LEN_STR      200
#define     LEN_LABEL    20
#define     MAX_TEX      300


extern      FILE       *s_file;
extern      png_structp s_png;
extern      png_infop   s_info;
extern      png_infop   s_end;
extern      png_byte   *s_image;
extern      png_bytep  *s_rows;
extern      int         s_width;
extern      int         s_height;
extern      int         s_rowbyte;
extern      GLuint      s_tex;



char        yGLTEX__file_open    (cchar *a_name, cchar a_mode);
char        yGLTEX__file_close   (void);
char        yGLTEX__file_alloc   (void);

char        yGLTEX__read_header  (void);
char        yGLTEX__read_attrib  (void);
char        yGLTEX__read_image   (void);
char        yGLTEX__read_tex     (void);

char        yGLTEX__save_header  (void);
char        yGLTEX__save_attrib  (cint a_width, cint a_height);
char        yGLTEX__save_image   (cchar a_source);


#endif

/*============================----end-of-source---============================*/
