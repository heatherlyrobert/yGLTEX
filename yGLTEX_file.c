/*============================----beg-of-source---============================*/
#include "yGLTEX.h"
#include "yGLTEX_priv.h"


/*> GLuint         s_tex;                                                             <*/
/*> FILE          *s_file;                                                            <*/
/*> char           s_mode;                                                            <*/
/*> png_structp    s_png;                                                             <*/
/*> png_infop      s_info;                                                            <*/
/*> png_infop      s_end;                                                             <*/
/*> int            s_width;                                                           <*/
/*> int            s_height;                                                          <*/
/*> int            s_rowbyte;                                                         <*/
/*> png_byte      *s_image;                                                           <*/
/*> png_bytep     *s_rows;                                                            <*/




/*====================------------------------------------====================*/
/*===----                       file handling                          ----===*/
/*====================------------------------------------====================*/
static void      o___FILE_______________o (void) {;}

/*> char               /+ PURPOSE : make a png image into a texture --------------+/        <* 
 *> yGLTEX__file_open    (cchar *a_name, cchar a_mode)                                      <* 
 *> {                                                                                       <* 
 *>    /+---(locals)-----------+-----------+-+/                                             <* 
 *>    char        rce         = -10;           /+ return code for errors         +/        <* 
 *>    int         x_len       = 0;                                                         <* 
 *>    /+---(header)-------------------------+/                                             <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                         <* 
 *>    /+---(defense)------------------------+/                                             <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("a_name"    , a_name);                                 <* 
 *>    --rce;  if (a_name == NULL) {                                                        <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("a_name texture name can not be null");             <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                      <* 
 *>       return  rce;                                                                      <* 
 *>    }                                                                                    <* 
 *>    x_len = strlen (a_name);                                                             <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("x_len"     , x_len);                                  <* 
 *>    --rce;  if (x_len < 5) {                                                             <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("a_name texture name is too short ( < 5 chars)");   <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                      <* 
 *>       return  rce;                                                                      <* 
 *>    }                                                                                    <* 
 *>    DEBUG_YGLTEX    yLOG_info    ("a_name"    , a_name);                                 <* 
 *>    /+---(open png file)------------------+/                                             <* 
 *>    DEBUG_YGLTEX    yLOG_char    ("a_mode"    , a_mode);                                 <* 
 *>    switch (a_mode) {                                                                    <* 
 *>    case 'r' :                                                                           <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("selected read-binary mode");                       <* 
 *>       s_file = fopen (a_name, "rb");                                                    <* 
 *>       break;                                                                            <* 
 *>    case 'w' :                                                                           <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("selected write-binary mode");                      <* 
 *>       s_file = fopen (a_name, "wb");                                                    <* 
 *>       break;                                                                            <* 
 *>    default  :                                                                           <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("a_mode open mode must be 'r' or 'w'");             <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                      <* 
 *>       return  rce;                                                                      <* 
 *>       break;                                                                            <* 
 *>    }                                                                                    <* 
 *>    s_mode = a_mode;                                                                     <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("s_file"    , s_file);                                 <* 
 *>    --rce;  if (s_file == NULL) {                                                        <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("s_file texture file could not be openned");        <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                      <* 
 *>       return  rce;                                                                      <* 
 *>    }                                                                                    <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("file open and confirmed");                            <* 
 *>    /+---(complete)-----------------------+/                                             <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                         <* 
 *>    return 0;                                                                            <* 
 *> }                                                                                       <*/

/*> char               /+ PURPOSE : make a png image into a texture --------------+/   <* 
 *> yGLTEX__file_close   (void)                                                        <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-----------+-----------+-+/                                        <* 
 *>    char        rce         = -10;           /+ return code for errors         +/   <* 
 *>    /+---(header)-------------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);                                    <* 
 *>    /+---(destroy pointers)---------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_note    ("destroying png pointers");                       <* 
 *>    --rce;  switch (s_mode) {                                                       <* 
 *>    case 'r' :                                                                      <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("selected read-binary mode");                  <* 
 *>       png_destroy_read_struct (&s_png, &s_info, &s_end);                           <* 
 *>       break;                                                                       <* 
 *>    case 'w' :                                                                      <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("selected write-binary mode");                 <* 
 *>       png_destroy_write_struct (&s_png, &s_info);                                  <* 
 *>       break;                                                                       <* 
 *>    default  :                                                                      <* 
 *>       DEBUG_YGLTEX    yLOG_warn    ("a_mode mode must be 'r' or 'w'");             <* 
 *>       DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                 <* 
 *>       return  rce;                                                                 <* 
 *>       break;                                                                       <* 
 *>    }                                                                               <* 
 *>    /+---(clear memory)-------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("s_rows"    , s_rows);                            <* 
 *>    --rce;  if (s_rows  != NULL) {                                                  <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("free and null pointer");                      <* 
 *>       free     (s_rows);                                                           <* 
 *>       s_rows  = NULL;                                                              <* 
 *>    }                                                                               <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("s_image"   , s_image);                           <* 
 *>    --rce;  if (s_image != NULL) {                                                  <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("free and null pointer");                      <* 
 *>       free     (s_image);                                                          <* 
 *>       s_image = NULL;                                                              <* 
 *>    }                                                                               <* 
 *>    /+---(close file)---------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_point   ("s_file"    , s_file);                            <* 
 *>    --rce;  if (s_file  != NULL) {                                                  <* 
 *>       DEBUG_YGLTEX    yLOG_note    ("close and null pointer");                     <* 
 *>       fclose   (s_file);                                                           <* 
 *>       s_file  = NULL;                                                              <* 
 *>    }                                                                               <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);                                    <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

char
ygltex_file_open        (char a_name [LEN_PATH], char a_access, char r_name [LEN_PATH], char *r_mode, FILE **r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   FILE       *f           = NULL;
   char        x_access    [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("r_file"    , r_file);
   --rce;  if (r_file == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("file pointer (r_file) can not be null");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_file"   , *r_file);
   --rce;  if (*r_file != NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("file appears already open");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   if (r_name  != NULL)  strcpy (r_name, "");
   if (r_file  != NULL)  *r_file = NULL;
   if (r_mode  != NULL)  *r_mode = '-';
   /*---(secondary defense)--------------*/
   DEBUG_YGLTEX    yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_YGLTEX    yLOG_warn    ("file name (a_name) can not be null or empty");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("a_name"    , a_name);
   x_len = strlen (a_name);
   DEBUG_YGLTEX    yLOG_point   ("x_len"     , x_len);
   --rce;  if (x_len < 5) {
      DEBUG_YGLTEX    yLOG_warn    ("file (a_name) is too short ( < 5 chars)");
      DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
      return  rce;
   }
   /*---(check access)-------------------*/
   DEBUG_YGLTEX    yLOG_char    ("a_access"  , a_access);
   --rce;  switch (a_access) {
   case 'r' :   strcpy (x_access, "rt");   break;
   case 'w' :   strcpy (x_access, "wt");   break;
   case 'R' :   strcpy (x_access, "rb");   break;
   case 'W' :   strcpy (x_access, "wb");   break;
   default  :
                DEBUG_YGLTEX    yLOG_warn    ("access request not understood");
                DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
                return rce;
   }
   DEBUG_YGLTEX    yLOG_info    ("x_access"  , x_access);
   /*---(open)---------------------------*/
   f = fopen (a_name, x_access);
   DEBUG_YGLTEX    yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_YGLTEX    yLOG_warn    ("file could not be openned");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save·back)----------------------*/
   DEBUG_YGLTEX    yLOG_note    ("saving back to return arguments");
   if (r_name  != NULL)  ystrlcpy (r_name, a_name, LEN_HUND);
   if (r_file  != NULL)  *r_file = f;
   if (r_mode  != NULL)  *r_mode = a_access;
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ygltex_file_close       (char r_name [LEN_PATH], char *r_mode, FILE **r_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YGLTEX    yLOG_point   ("r_file"    , r_file);
   --rce;  if (r_file == NULL) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YGLTEX    yLOG_point   ("*r_file"   , *r_file);
   --rce;  if (*r_file == NULL) {
      DEBUG_YGLTEX    yLOG_note    ("file not open");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(destroy pointers)---------------*/
   /*> ygltex_file_free (*r_mode);                                                    <*/
   /*> if (r_mode != NULL) {                                                          <* 
    *>    DEBUG_YGLTEX    yLOG_note    ("destroying png pointers");                   <* 
    *>    --rce;  switch (*r_mode) {                                                  <* 
    *>    case 'R' :                                                                  <* 
    *>       DEBUG_YGLTEX    yLOG_note    ("selected read-binary mode");              <* 
    *>       png_destroy_read_struct (&s_png, &s_info, &s_end);                       <* 
    *>       break;                                                                   <* 
    *>    case 'W' :                                                                  <* 
    *>       DEBUG_YGLTEX    yLOG_note    ("selected write-binary mode");             <* 
    *>       png_destroy_write_struct (&s_png, &s_info);                              <* 
    *>       break;                                                                   <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*---(clear memory)-------------------*/
   /*> if (r_mode != NULL) {                                                          <* 
    *>    DEBUG_YGLTEX    yLOG_point   ("s_rows"    , s_rows);                        <* 
    *>    if (s_rows  != NULL) {                                                      <* 
    *>       DEBUG_YGLTEX    yLOG_note    ("free and null pointer");                  <* 
    *>       free     (s_rows);                                                       <* 
    *>       s_rows  = NULL;                                                          <* 
    *>    }                                                                           <* 
    *>    DEBUG_YGLTEX    yLOG_point   ("s_image"   , s_image);                       <* 
    *>    if (s_image != NULL) {                                                      <* 
    *>       DEBUG_YGLTEX    yLOG_note    ("free and null pointer");                  <* 
    *>       free     (s_image);                                                      <* 
    *>       s_image = NULL;                                                          <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*---(open)---------------------------*/
   fflush (*r_file);
   rc = fclose (*r_file);
   DEBUG_YGLTEX    yLOG_value   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YGLTEX    yLOG_warn    ("file could not be closed");
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   if (r_name  != NULL)  strcpy (r_name, "");
   if (r_file  != NULL)  *r_file = NULL;
   if (r_mode  != NULL)  *r_mode = '-';
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                                   <* 
 *> ygltex_file_close_easy  (void)                                                         <* 
 *> {                                                                                      <* 
 *>    return ygltex_file_close  (zYGLTEX.f_name, &(zYGLTEX.f_mode), &(zYGLTEX.f_file));   <* 
 *> }                                                                                      <*/



/*====================------------------------------------====================*/
/*===----                        main drivers                          ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVERS____________o (void) {;}

char
ygltex_file_new         (cchar a_pngname [LEN_PATH], char a_source, int a_wide, int a_tall, cchar a_tilename [LEN_PATH], void *e_updater)
{  /*---(design notes)-------------------*/
   /*
    *  png images are created new from :
    *    a) texture in opengl memory,
    *    b) already drawn window/screen, or
    *    c) generated with the e_updater function.
    */
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         x_final     =    0;
   char      (*x_updater)  (cchar a_tilename [LEN_PATH], int a_wide, int a_tall, int a_rbyte, png_bytep *a_rows) = NULL;
   FILE       *f           = NULL;
   char        x_mode      =  'W';
   png_structp x_png       = NULL;
   png_infop   x_info      = NULL;
   int         x_rbyte     =    0;
   png_byte   *x_image     = NULL;
   png_bytep  *x_rows      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_info    ("a_pngname" , a_pngname);
   DEBUG_YGLTEX    yLOG_complex ("source"    , "%c, %4dw, %4dt", a_source, a_wide, a_tall);
   /*---(save updater)-------------------*/
   x_updater = e_updater;
   DEBUG_YGLTEX    yLOG_point   ("x_updater" , x_updater);
   /*---(create file)--------------------*/
   rc = ygltex_file_open   (a_pngname, x_mode, NULL, NULL, &f);
   DEBUG_YGLTEX    yLOG_value   ("open"      , rc);
   --rce;  if (rc <  0)  x_final = rce;
   /*---(prepare image)------------------*/
   --rce;  if (rc == 0) {
      rc = ygltex_save_header (f, &x_png, &x_info);
      DEBUG_YGLTEX    yLOG_value   ("header"    , rc);
      if (rc <  0)  x_final = rce;
   }
   --rce;  if (rc == 0) {
      rc = ygltex_save_attrib (x_png, x_info, a_wide, a_tall, &x_rbyte);
      DEBUG_YGLTEX    yLOG_value   ("attrib"    , rc);
      if (rc <  0)  x_final = rce;
   }
   --rce;  if (rc == 0) {
      rc = ygltex_image_alloc (a_wide, a_tall, x_rbyte, &x_image, &x_rows);
      DEBUG_YGLTEX    yLOG_value   ("alloc"     , rc);
      if (rc <  0)  x_final = rce;
   }
   /*---(update optional)----------------*/
   --rce;  if (rc == 0 && a_source == YGLTEX_IMAGE && x_updater != NULL) {
      rc = x_updater (a_tilename, a_wide, a_tall, x_rbyte, x_rows);
      DEBUG_YGLTEX    yLOG_value   ("update"    , rc);
      if (rc <  0)  x_final = rce;
   }
   /*---(save)---------------------------*/
   --rce;  if (rc == 0) {
      rc = ygltex_save_image  (x_png, x_info , x_image, x_rows, a_source, a_wide, a_tall);
      DEBUG_YGLTEX    yLOG_value   ("save"      , rc);
      if (rc <  0)  x_final = rce;
   }
   /*---(clean-up)-----------------------*/
   rc = ygltex_image_free   (&x_image, &x_rows);
   DEBUG_YGLTEX    yLOG_value   ("image"     , rc);
   --rce;  if (x_final == 0 && rc <  0)  x_final = rce;
   rc = ygltex_save_free   (&x_png, &x_info);
   DEBUG_YGLTEX    yLOG_value   ("free"      , rc);
   --rce;  if (x_final == 0 && rc <  0)  x_final = rce;
   rc = ygltex_file_close  (NULL, NULL, &f);
   DEBUG_YGLTEX    yLOG_value   ("close"     , rc);
   --rce;  if (x_final == 0 && rc <  0)  x_final = rce;
   /*---(trouble)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("x_final"   , x_final);
   if (x_final <  0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, x_final);
      return  x_final;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> save screenprint as a png image -----------*/
yGLTEX_scr2png       (cchar a_pngname [LEN_PATH], cint a_wide, cint a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(handle)-------------------------*/
   rc = ygltex_file_new (a_pngname, a_wide, a_tall, YGLTEX_SCREEN, NULL, NULL);
   DEBUG_YGLTEX    yLOG_value   ("new"       , rc);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return rc;
}

char         /*-> save current texture as png image ---------*/
yGLTEX_tex2png       (cchar a_pngname [LEN_PATH], cint a_wide, cint a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(handle)-------------------------*/
   rc = ygltex_file_new (a_pngname, a_wide, a_tall, YGLTEX_TEXTURE, NULL, NULL);
   DEBUG_YGLTEX    yLOG_value   ("new"       , rc);
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return rc;
}


char
ygltex_file_exist       (cchar a_pngname [LEN_PATH], char a_dest, int *r_wide, int *r_tall, int *r_rbyte, png_byte **r_image, png_bytep **r_rows, int *r_tex, void *e_titles, void *e_headers)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         x_final     =    0;
   FILE       *f           = NULL;
   char        x_mode      =  'R';
   int         x_wide      =    0;
   int         x_tall      =    0;
   png_structp x_png       = NULL;
   png_infop   x_info      = NULL;
   png_infop   x_end       = NULL;
   int         x_rbyte     =    0;
   png_byte   *x_image     = NULL;
   png_bytep  *x_rows      = NULL;
   uint        x_tex       =    0;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   DEBUG_YGLTEX    yLOG_info    ("a_pngname" , a_pngname);
   DEBUG_YGLTEX    yLOG_complex ("source"    , "%c", a_dest);
   /*---(default)------------------------*/
   if (r_wide  != NULL)  *r_wide  = 0;
   if (r_tall  != NULL)  *r_tall  = 0;
   if (r_rbyte != NULL)  *r_rbyte = 0;
   if (r_image != NULL)  *r_image = NULL;
   if (r_rows  != NULL)  *r_rows  = NULL;
   if (r_tex   != NULL)  *r_tex   = 0;
   /*---(create file)--------------------*/
   rc = ygltex_file_open   (a_pngname, x_mode, NULL, NULL, &f);
   DEBUG_YGLTEX    yLOG_value   ("open"      , rc);
   --rce;  if (rc <  0)  x_final = rce;
   /*---(prepare image)------------------*/
   --rce;  if (rc == 0) {
      rc = ygltex_read_header (f, &x_png, &x_info, &x_end);
      DEBUG_YGLTEX    yLOG_value   ("header"    , rc);
      if (rc <  0)  x_final = rce;
   }
   --rce;  if (rc == 0) {
      rc = ygltex_read_attrib (f, x_png, x_info, &x_wide, &x_tall, NULL, NULL, &x_rbyte, NULL);
      DEBUG_YGLTEX    yLOG_value   ("attrib"    , rc);
      if (rc <  0)  x_final = rce;
   }
   --rce;  if (rc == 0) {
      rc = ygltex_image_alloc (x_wide, x_tall, x_rbyte, &x_image, &x_rows);
      DEBUG_YGLTEX    yLOG_value   ("alloc"     , rc);
      if (rc <  0)  x_final = rce;
   }
   /*---(save)---------------------------*/
   --rce;  if (rc == 0) {
      rc = ygltex_read_image  (x_png, x_image, x_rows, a_dest, x_wide, x_tall, &x_tex);
      DEBUG_YGLTEX    yLOG_value   ("read"      , rc);
      if (rc <  0)  x_final = rce;
   }
   /*---(extract data)-------------------*/
   rc = ygltex_read_parse (x_wide, x_tall, x_rbyte, x_rows, e_titles, e_headers);
   DEBUG_YGLTEX    yLOG_value   ("parse"     , rc);
   /*---(clean-up)-----------------------*/
   --rce;  if (a_dest != YGLTEX_IMAGE) {
      rc = ygltex_image_free   (&x_image, &x_rows);
      DEBUG_YGLTEX    yLOG_value   ("image"     , rc);
      if (x_final == 0 && rc <  0)  x_final = rce;
   }
   rc = ygltex_read_free   (&x_png, &x_info, &x_end);
   DEBUG_YGLTEX    yLOG_value   ("free"      , rc);
   --rce;  if (x_final == 0 && rc <  0)  x_final = rce;
   rc = ygltex_file_close  (NULL, NULL, &f);
   DEBUG_YGLTEX    yLOG_value   ("close"     , rc);
   --rce;  if (x_final == 0 && rc <  0)  x_final = rce;
   /*---(trouble)------------------------*/
   DEBUG_YGLTEX    yLOG_value   ("x_final"   , x_final);
   if (x_final <  0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, x_final);
      return  x_final;
   }
   /*---(save-back)----------------------*/
   if (r_wide  != NULL)  *r_wide = x_wide;
   if (r_tall  != NULL)  *r_tall = x_tall;
   switch (a_dest) {
   case YGLTEX_TEXTURE :
      if (r_tex   != NULL)  *r_tex   = x_tex;
      break;
   case YGLTEX_IMAGE   :
      if (r_rbyte != NULL)  *r_rbyte = x_rbyte;
      if (r_image != NULL)  *r_image = x_image;
      if (r_rows  != NULL)  *r_rows  = x_rows;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return 0;
}

uint         /*-> read png image into texture ---------------*/
yGLTEX_png2tex       (cchar a_pngname [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uint        x_tex       =   -1;
   /*---(header)-------------------------*/
   DEBUG_YGLTEX    yLOG_enter   (__FUNCTION__);
   /*---(handle)-------------------------*/
   rc = ygltex_file_exist (a_pngname, YGLTEX_TEXTURE, NULL, NULL, NULL, NULL, NULL, &x_tex, NULL, NULL);
   DEBUG_YGLTEX    yLOG_value   ("exist"     , rc);
   if (rc < 0 || x_tex < 0) {
      DEBUG_YGLTEX    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YGLTEX    yLOG_exit    (__FUNCTION__);
   return x_tex;
}




/*============================----end-of-source---============================*/
