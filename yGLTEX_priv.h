/*============================----beg-of-source---============================*/
#include "yGLTEX.h"


#ifndef YGLTEX_PRIV
#define YGLTEX_PRIV loaded


/*===[[ ONE_LINERS ]]=========================================================*/
/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */

#define     P_FOCUS     ""
#define     P_NICHE     ""
#define     P_SUBJECT   "opengl texture handling"
#define     P_PURPOSE   ""

#define     P_NAMESAKE  "techne-daimona (art and craft)
#define     P_HERITAGE  ""
#define     P_IMAGERY   ""
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   ""

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""

#define     P_VERMAJOR  ""
#define     P_VERMINOR  ""
#define     P_VERNUM    "0.3e"
#define     P_VERTXT    "simply writing annotated png from tile file seem pretty good now ;)"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */
/*===[[ END ONE_LINERS ]]=====================================================*/


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

/* rapidly evolving version number to aid with visual change confirmation     */



/*===[[ RATIONAL LIMITS ]]====================================================*/
/*   LEN_ is a length or size of something
 *   MIN_ is a minimum count
 *   DEF_ is a default count
 *   MAX_ is a maximum count
 *
 */
/*3456789012+123456789012+123456789012+123456789012+123456789012+123456789012*/
/*---(string length)------------------*/
#define     LEN_STR      200
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



/*---(file)-----------------*/
char        ygltex__text_open       (char a_name [LEN_HUND], char a_access, FILE **r_file);
char        ygltex__text_close      (FILE **r_file);
/*---(title)----------------*/
char        ygltex__title_write     (char a_title [LEN_DESC], int x_count, int y_count, int x_scale, int y_scale, int a_margin, int a_max, uchar *r_row);
char        ygltex__title_read      (int a_max, uchar *a_row, char r_title [LEN_DESC], int *x_count, int *y_count, int *x_scale, int *y_scale, int *r_margin);
/*---(header)---------------*/
char        ygltex__header_write    (int x, char a_cat [LEN_LABEL], char a_sub [LEN_LABEL], char a_name [LEN_LABEL], int a_max, uchar *r_row);
char        ygltex__header_read     (int a_max, uchar *a_row, int x, char r_cat [LEN_LABEL], char r_sub [LEN_LABEL], char r_name [LEN_LABEL]);
/*---(text)-----------------*/
char        ygltex__text_read       (FILE *f, int *b_line, int *r_len, char r_recd [LEN_HUGE], char *r_new);
char        ygltex__text_sizing     (int a_line, char a_recd [LEN_HUGE], int *x_scale, int *y_scale, int *r_margin);
char        ygltex__text_layout     (int a_line, char a_recd [LEN_HUGE], int *x_count, int *y_count);
char        ygltex__text_title      (int a_line, char a_recd [LEN_HUGE], char r_title [LEN_DESC]);
char        ygltex__text_fields     (int a_line, char a_recd [LEN_HUGE], int *r_fields);
char        ygltex__text_hdr_audit  (int a_line, char a_recd [LEN_HUGE], int x_scale, int a_fields, int x_max, int *r_count);
char        ygltex__detail          (char a_pass, int a_line, char a_recd [LEN_HUGE], int x_scale, int a_margin, int x_max, int *r_count, int a_rlen, uchar *b_rdata);

char        ygltex_text_driver      (char a_pass, cchar a_name [LEN_HUND]);
/*---(png)------------------*/
char        ygltex__png_header_one  (int a_len, char a_recd [LEN_HUGE], int x, int w, int r_max, uchar *r_row);
char        ygltex__png_detail_one  (char a_recd [LEN_HUGE], int x, int w, int r_max, uchar *r_row);

char        ygltex__write_cell      (int a_len, char a_recd [LEN_HUGE], int x, int w, int r_max, uchar *r_row);
char*       ygltex__unit_show       (int a_max, uchar a_row [LEN_RECD]);


char        ygltex__unit_quiet      (void);
char        ygltex__unit_loud       (void);
char        ygltex__unit_end        (void);


#endif

/*============================----end-of-source---============================*/
