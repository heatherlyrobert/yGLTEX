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
#define     P_VERNUM    "0.3f"
#define     P_VERTXT    "code updated, namespace cleaned, most unit testing good"

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


/*
 * new extensions
 *   .asciiart   pure-text files but containing ascii art/tiles
 *   .pngtile    png-compatible files with encoded title and headers
 *
 */





/*> typedef  struct cYGLTEX  tYGLTEX;                                                 <* 
 *> struct cYGLTEX {                                                                  <* 
 *>    char        f_name      [LEN_HUND];                                            <* 
 *>    FILE       *f_file;                                                            <* 
 *>    char        f_mode;                                                            <* 
 *>    png_structp f_png;                                                             <* 
 *> };                                                                                <* 
 *> extern   tYGLTEX  zYGLTEX;                                                        <*/


extern char  *zYGLTEX_allow;
extern char  *zYGLTEX_minimal;
extern char  *zYGLTEX_shrike;



/*> extern      FILE       *s_file;                                                   <*/
/*> extern      png_structp s_png;                                                    <*/
/*> extern      png_infop   s_info;                                                   <*/
/*> extern      png_infop   s_end;                                                    <*/
/*> extern      png_byte   *s_image;                                                  <*/
/*> extern      png_bytep  *s_rows;                                                   <*/
/*> extern      int         s_width;                                                  <*/
/*> extern      int         s_height;                                                 <*/
/*> extern      int         s_rowbyte;                                                <*/
/*> extern      GLuint      s_tex;                                                    <*/




/*===[[ PETAL_FILE.C ]]=======================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
char        ygltex_file_open        (char a_name [LEN_PATH], char a_access, char r_name [LEN_PATH], char *r_mode, FILE **r_file);
char        ygltex_file_close       (char r_name [LEN_PATH], char *r_mode, FILE **r_file);
/*> char        ygltex_file_close_easy  (void);                                       <*/
char        ygltex_file_new         (cchar a_pngname [LEN_PATH], char a_source, int a_wide, int a_tall, cchar a_tilename [LEN_PATH], void *e_updater);
char        ygltex_file_exist       (cchar a_pngname [LEN_PATH], char a_dest, int *r_wide, int *r_tall, int *r_rbyte, png_byte **r_image, png_bytep **r_rows, int *r_tex, void *c_titles, void *c_headers);



/*===[[ PETAL_IMAGE.C ]]======================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
char        ygltex_image_alloc      (int a_wide, int a_tall, int a_rowbyte, png_byte **r_image, png_bytep **r_rows);
char        ygltex_image_free       (png_byte **r_image, png_bytep **r_rows);



/*===[[ PETAL_READ.C ]]=======================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
/*---(new)------------------*/
char        ygltex_read_header      (FILE *f, png_structp **r_png, png_infop **r_info, png_infop **r_end);
char        ygltex_read_free        (png_structp **r_png, png_infop **r_info, png_infop **r_end);
char        ygltex_read_attrib      (FILE *f, png_structp *a_png, png_infop *a_info, int *r_wide, int *r_tall, int *r_color, int *r_depth, int *r_rowbyte, int *r_channel);
char        ygltex_read_image       (png_structp *a_png, png_byte *a_image, png_bytep *a_rows, char a_dest, int a_wide, int a_tall, int *r_tex);
char        ygltex_read_parse       (int a_wide, int a_tall, int a_rbyte, png_bytep *a_rows, void *f_title, void *f_header);
/*---(depricated)-----------*/
/*> char        yGLTEX__read_header     (void);                                       <*/
/*> char        yGLTEX__read_attrib     (void);                                       <*/
/*> char        yGLTEX__read_image      (void);                                       <*/
/*> char        yGLTEX__read_tex        (void);                                       <*/
/*---(done)-----------------*/



/*===[[ PETAL_SAVE.C ]]=======================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
/*---(new)------------------*/
char        ygltex_save_header      (FILE *f, png_structp **r_png, png_infop **r_info);
char        ygltex_save_free        (png_structp **r_png, png_infop **r_info);
char        ygltex_save_attrib      (png_structp *a_png, png_infop *a_info, int a_wide, int a_tall, int *r_rowbyte);
char        ygltex_save_image       (png_structp *a_png, png_infop *a_info, png_byte *a_image, png_bytep *a_rows, char a_source, int a_wide, int a_tall);
/*---(depricated)-----------*/
/*> char        yGLTEX__save_header     (void);                                       <*/
/*> char        yGLTEX__save_attrib     (cint a_width, cint a_height);                <*/
/*> char        yGLTEX__save_image      (cchar a_source);                             <*/
/*---(done)-----------------*/







/*---(controls)-------------*/
char        ygltex_tile_ramp        (int a_line, char a_recd [LEN_HUGE], char *r_ramp);
char        ygltex_tile_title       (int a_line, char a_recd [LEN_HUGE], char r_title [LEN_DESC]);
char        ygltex_tile_layout      (int a_line, char a_recd [LEN_HUGE], int *x_count, int *y_count);
char        ygltex_tile_sizing      (int a_line, char a_recd [LEN_HUGE], int *x_scale, int *y_scale, int *r_margin);
char        ygltex_tile_fields      (int a_line, char a_recd [LEN_HUGE], int *r_fields);
/*---(title)----------------*/
char        ygltex_title_write      (int a_width, uchar *r_row, char a_title [LEN_DESC], int a_wide, int a_tall, int a_total, int a_used, int a_xmax, int a_ymax, int a_fields, int a_xscale, int a_yscale, int a_buffer);
char        ygltex_title_read       (int a_width, uchar *a_row, char r_title [LEN_DESC], int *r_wide, int *r_tall, int *r_total, int *r_used, int *r_xmax, int *r_ymax, int *r_fields, int *r_xscale, int *r_yscale, int *r_buffer);
/*---(header)---------------*/
char        ygltex_header_write     (int a_rlen, uchar *b_rdata, int a_col, int a_xscale, int a_margin, int a_fields, char a_cat [LEN_LABEL], char a_sub [LEN_LABEL], char a_name [LEN_LABEL]);
char        ygltex_header_read      (int a_rlen, uchar *a_rdata, int a_col, int a_xscale, int a_margin, int a_fields, char r_cat [LEN_LABEL], char r_sub [LEN_LABEL], char r_name [LEN_LABEL]);
char        ygltex_header_audit     (int a_line, int a_col, int x_beg, char a_fields, char a_ramp, char a_tile [LEN_FULL], char a_inside [LEN_FULL], char *r_ramp);
char        ygltex_header_parse     (char a_fields, char a_ramp, char a_inside [LEN_FULL], char r_cat [LEN_LABEL], char r_sub [LEN_LABEL], char r_name [LEN_LABEL], char *r_ramp);
char        ygltex_header_handler   (char a_pass, char a_ramp, int a_line, char a_recd [LEN_HUGE], int a_xscale, int a_buffer, int a_fields, int x_max, int *r_count, char r_ramps [LEN_HUND], int a_rlen, uchar *b_rdata);
/*---(detail)---------------*/
char        ygltex_detail_write     (int a_col, char a_ramp, int a_xscale, int a_buffer, char a_inside [LEN_FULL], int a_rlen, uchar *b_rdata);
char        ygltex_detail_audit     (int a_line, int a_col, int x_beg, char a_ramp, char a_tile [LEN_FULL], char a_inside [LEN_FULL]);
char        ygltex_detail_handler   (char a_pass, int a_line, char a_recd [LEN_HUGE], char a_ramps [LEN_HUND], int a_xscale, int a_buffer, int a_xlayout, int *r_count, int a_rlen, uchar *b_rdata);
/*---(driver)---------------*/
char        ygltex_tile_read        (FILE *f, int *b_line, int *r_len, char r_recd [LEN_HUGE], char *r_new);
char        ygltex_tile_default     (char a_pass, char *r_ready, char r_title [LEN_DESC], char *r_style, char *r_ramp, int *r_wide, int *r_tall, int *r_total, int *r_used, int *r_xscale, int *r_yscale, int *r_buffer, int *r_fields, int *r_xmax, int *r_ymax, int *r_xactual, int *r_yactual);
char        ygltex_tile_complete    (char a_pass, char a_title [LEN_DESC], char a_style, char a_ramp, int a_used, int a_xscale, int a_yscale, int a_buffer, int a_xmax, int a_ymax, int a_fields, int a_xactual, int a_yactual);
char        ygltex_tile_driver      (char a_pass, cchar a_name [LEN_HUND], int a_rbyte, png_bytep *b_rows);
char        ygltex_tile_handler     (cchar a_tilename [LEN_PATH], int a_wide, int a_tall, int a_rbyte, png_bytep *b_rows);
char        yGLTEX_ascii2tiles      (char a_mode, cchar a_pngname [LEN_PATH], cchar a_tilename [LEN_PATH]);
/*---(unittest)-------------*/
char*       ygltex__unit_show       (char a_ramp, int a_max, uchar a_row [LEN_RECD]);




/*===[[ PETAL_TEST.C ]]=======================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
/*---(helpers)--------------*/
char        ygltex__unit_makerow    (char a_text [LEN_FULL], char r_row [LEN_RECD]);
/*> char        ygltex__unit_create     (cchar a_name [LEN_HUND], int a_width, int a_height);   <*/
/*> char        ygltex__unit_save       (void);                                       <*/
/*> char        ygltex__unit_read       (cchar a_name [LEN_HUND]);                    <*/
/*> char        ygltex__unit_close      (void);                                       <*/
/*---(reading)--------------*/
char        ygltex__unit_title      (char a_title [LEN_DESC], int a_used, int a_xmax, int a_ymax, int a_fields, int a_xscale, int a_yscale, int a_buffer);
char        ygltex__unit_header     (int a_row, int a_col, char a_cat [LEN_LABEL], char a_sub [LEN_LABEL], char a_name [LEN_LABEL]);
/*---(program)--------------*/
char        ygltex__unit_quiet      (void);
char        ygltex__unit_loud       (void);
char        ygltex__unit_end        (void);
/*---(done)-----------------*/



/*===[[ PETAL_RAMP.C ]]=======================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
uchar       ygltex_ramp_alpha2char  (char a_type, uchar v, uchar *c);
uchar       ygltex_ramp_char2alpha  (char a_type, uchar c, uchar *a);
char        ygltex_ramp_audit       (int a_line, int a_col, int x_beg, char a_ramp, char a_inside [LEN_FULL]);



/*===[[ PETAL_TEXTIFY.C ]]====================================================*/ 
/*---rc---- ---name---------------- ---args-----------------------------------*/
char        ygltex_textify_prepare  (int a_wide, int a_xscale, int a_xmargin);
char*       ygltex_textify_print    (FILE *f, char a_which);
char        ygltex_textify_single   (FILE *f, int a_line, char a_style, int a_left, int a_xscale, int a_xmargin, int a_yscale, int a_ymargin, int a_rbyte, png_bytep a_row);
char        ygltex_textify_line     (FILE *f, int a_line, char a_style, int a_wide, int a_xscale, int a_xmargin, int a_yscale, int a_ymargin, int a_rbyte, png_bytep a_row);



#endif

/*============================----end-of-source---============================*/
