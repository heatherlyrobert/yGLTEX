/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"



char
ygltex__unit_makerow    (char a_text [LEN_FULL], char r_row [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         l           =    0;
   for (i = 0; i < LEN_RECD; ++i)  r_row [i] = '\0';
   l = strlen (a_text);
   for (i = 0; i < l; ++i) {
      r_row [(i * 4) + 3] = ygltex_ramp_char2alpha ('s', a_text [i], NULL);
   }
   return 0;
}

/*> char                                                                                             <* 
 *> ygltex__unit_create     (cchar a_name [LEN_HUND], int a_width, int a_height)                     <* 
 *> {                                                                                                <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                      <* 
 *>    char        rce         =  -10;                                                               <* 
 *>    int         rc          =    0;                                                               <* 
 *>    /+---(header)-------------------------+/                                                      <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                                  <* 
 *>    /+---(open png file)------------------+/                                                      <* 
 *>    rc = ygltex_file_open  (a_name, 'W', zYGLTEX.f_name, &(zYGLTEX.f_mode), &(zYGLTEX.f_file));   <* 
 *>    if (rc == 0)  rc = yGLTEX__save_header  ();                                                   <* 
 *>    if (rc == 0)  rc = yGLTEX__save_attrib  (a_width, a_height);                                  <* 
 *>    if (rc == 0)  rc = yGLTEX__file_alloc   ();                                                   <* 
 *>    /+---(complete)-----------------------+/                                                      <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                                  <* 
 *>    return rc;                                                                                    <* 
 *> }                                                                                                <*/

/*> char                                                                              <* 
 *> ygltex__unit_save       (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    int         rc          =    0;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                   <* 
 *>    /+---(open png file)------------------+/                                       <* 
 *>    rc = yGLTEX__save_image   ('c');                                               <* 
 *>    rc = ygltex_file_close_easy    ();                                             <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                   <* 
 *>    return rc;                                                                     <* 
 *> }                                                                                 <*/

/*> char                                                                                             <* 
 *> ygltex__unit_read       (cchar a_name [LEN_HUND])                                                <* 
 *> {                                                                                                <* 
 *>    /+---(locals)-----------+-----------+-+/                                                      <* 
 *>    char        rce         = -10;           /+ return code for errors         +/                 <* 
 *>    int         rc          = 0;             /+ simple return code             +/                 <* 
 *>    /+---(header)-------------------------+/                                                      <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                                  <* 
 *>    /+---(open png file)------------------+/                                                      <* 
 *>    rc = ygltex_file_open  (a_name, 'R', zYGLTEX.f_name, &(zYGLTEX.f_mode), &(zYGLTEX.f_file));   <* 
 *>    if (rc == 0)  rc = yGLTEX__read_header  ();                                                   <* 
 *>    if (rc == 0)  rc = yGLTEX__read_attrib  ();                                                   <* 
 *>    if (rc == 0)  rc = yGLTEX__file_alloc   ();                                                   <* 
 *>    if (rc == 0)  rc = yGLTEX__read_image   ();                                                   <* 
 *>    /+---(complete)-----------------------+/                                                      <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                                  <* 
 *>    return rc;                                                                                    <* 
 *> }                                                                                                <*/

char
ygltex__unit_title      (char a_title [LEN_DESC], int a_used, int a_xmax, int a_ymax, int a_fields, int a_xscale, int a_yscale, int a_buffer)
{
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(report out)---------------------*/
   yURG_msg (':', "title  å%sæ %3du, %3dxm, %3dym, %1df, %3dxs, %3dys, %2db", a_title, a_used, a_xmax, a_ymax, a_fields, a_xscale, a_yscale, a_buffer);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex__unit_header     (int a_row, int a_col, char a_cat [LEN_LABEL], char a_sub [LEN_LABEL], char a_name [LEN_LABEL])
{
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(report out)---------------------*/
   yURG_msg (':', "header %3dr, %3dc, %-20.20s, %-20.20s, %-20.20s", a_row, a_col, a_cat, a_sub, a_name);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                              <* 
 *> ygltex__unit_close      (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    int         rc          =    0;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                   <* 
 *>    /+---(open png file)------------------+/                                       <* 
 *>    rc = ygltex_file_close_easy    ();                                             <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                   <* 
 *>    return rc;                                                                     <* 
 *> }                                                                                 <*/


char           unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
ygltex__unit_quiet      (void)
{
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ygltex__unit_loud       (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yGLTEX_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_by_name  ("ygltex"       , YURG_ON);
   DEBUG_YGLTEX  yLOG_info     ("yGLTEX"    , yGLTEX_version   ());
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ygltex__unit_end        (void)
{
   DEBUG_YGLTEX  yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX  yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}
