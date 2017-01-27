#*============================----beg-of-source---============================*#



#===[[ VARABLES ]]======================================================================================================================================================#

#===(current variables)=================================================================================================================================================#
BASE    = yGLTEX
DEBUG   = ${BASE}_debug
UNIT    = ${BASE}_unit
#*---(dirs and docs)------------------*#
HDIR    = /home/system/yGLTEX.opengl_texture_handling
#*---(library documentation)----------*#
MNUM    = 3
MDIR    = /usr/share/man/man${MNUM}
MBASE   = ${BASE}.${MNUM}
#*---(overview)-----------------------*#
ONUM    = 0
ODIR    = /usr/share/man/man${ONUM}
OBASE   = ${BASE}.${ONUM}

#===(compilier variables)===============================================================================================================================================#
# must have "-x c" on gcc line so stripped files work with alternate extensions
COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
INCS    = -I/usr/local/include

#===(linker options)====================================================================================================================================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)-------------- (A)-------------- (B)-------------- (C)-------------- (D)-------------- (E)-------------- (F)--------------
LINK    = gcc
LIBDIR  = -L/usr/local/lib
LIBS    = ${LIBDIR}         -lX11             -lGL              -lm               -lpng             -lySTR            -lyURG
LIBD    = ${LIBDIR}         -lX11             -lGL              -lm               -lpng             -lySTR_debug      -lyURG_debug      -lyLOG
LIBU    = ${LIBDIR}         -lX11             -lGL              -lm               -lpng             -lySTR_debug      -lyURG_debug      -lyLOG            -lyUNIT           -lyVAR

#===(file lists)============================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)-------------- (A)-------------- (B)-------------- (C)-------------- (D)-------------- (5)--------------
HEADS   = ${BASE}.h         ${BASE}_priv.h
OBJS    = ${BASE}_main.os   ${BASE}_file.os   ${BASE}_read.os   ${BASE}_save.os
OBJD    = ${BASE}_main.o    ${BASE}_file.o    ${BASE}_read.o    ${BASE}_save.o   
OBJU    = ${BASE}_unit.o    ${OBJD}

#===(make variables)====================================================================================================================================================#
COPY    = cp -f
CLEAN   = rm -f
PRINT   = @printf
STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 



#*---(executables)--------------------*#
#all                : ${DEBUG}  ${BASE}  ${UNIT}
all                : ${DEBUG}  ${BASE}

${BASE}            : ${OBJS}
	${LINK}  -shared -Wl,-soname,lib${BASE}.so.1   ${LIBS}  -o lib${BASE}.so.1.0   ${OBJS}
	ar       rcs  lib${BASE}.a   ${OBJS}

${DEBUG}           : ${OBJD}
	${LINK}  -shared -Wl,-soname,lib${DEBUG}.so.1  ${LIBD}  -o lib${DEBUG}.so.1.0  ${OBJD}
	ar       rcs  lib${DEBUG}.a  ${OBJD}

${DEBUG}           : ${OBJD}

#${UNIT}            : ${OBJU}
#	${LINK}  -o ${UNIT}        ${OBJU}   ${LIBU}



#*---(components)---------------------*#

${BASE}_main.o     : ${HEADS}       ${BASE}_main.c
	${COMP}  -fPIC  ${BASE}_main.c                           ${INC}
	${STRIP}        ${BASE}_main.c      > ${BASE}_main.cs
	${COMP}  -fPIC  ${BASE}_main.cs    -o ${BASE}_main.os    ${INC}

${BASE}_file.o     : ${HEADS}       ${BASE}_file.c
	${COMP}  -fPIC  ${BASE}_file.c                           ${INC}
	${STRIP}        ${BASE}_file.c      > ${BASE}_file.cs
	${COMP}  -fPIC  ${BASE}_file.cs    -o ${BASE}_file.os    ${INC}

${BASE}_read.o     : ${HEADS}       ${BASE}_read.c
	${COMP}  -fPIC  ${BASE}_read.c                           ${INC}
	${STRIP}        ${BASE}_read.c      > ${BASE}_read.cs
	${COMP}  -fPIC  ${BASE}_read.cs    -o ${BASE}_read.os    ${INC}

${BASE}_save.o     : ${HEADS}       ${BASE}_save.c
	${COMP}  -fPIC  ${BASE}_save.c                           ${INC}
	${STRIP}        ${BASE}_save.c      > ${BASE}_save.cs
	${COMP}  -fPIC  ${BASE}_save.cs    -o ${BASE}_save.os    ${INC}

${UNIT}.o          : ${HEADS} ${BASE}.unit
	koios    ${BASE}
	${COMP}  ${UNIT}.c  ${INCS}



#*---(housecleaning)------------------*#
clean              :
	${PRINT}  "\n--------------------------------------\n"
	${PRINT}  "cleaning out local object, backup, and temp files\n"
	${CLEAN} lib${BASE}.so.1
	${CLEAN} lib${BASE}.so.1.0
	${CLEAN} lib${DEBUG}.so.1
	${CLEAN} lib${DEBUG}.so.1.0
	${CLEAN} *.o
	${CLEAN} *.cs
	${CLEAN} *.os
	${CLEAN} *~
	${CLEAN} temp*
	${CLEAN} ${BASE}_unit.c

bigclean           :
	${PRINT}  "\n--------------------------------------\n"
	${PRINT}  "clean out local swap files\n"
	${CLEAN}  '.'*.sw?

remove             :
	${PRINT}  "\n--------------------------------------\n"
	${PRINT}  "remove ${BASE} from production\n"
	_lib      -d  ${BASE}
	_lib      -d  ${DEBUG}
	ldconfig

install            :
	#---(production version)--------------#
	sha1sum   lib${BASE}.so.1.0
	_lib      -s ${BASE}
	ldconfig
	sha1sum   lib${BASE}.a
	_lib      -a ${BASE}
	ldconfig
	#---(debug version)-------------------#
	sha1sum   lib${DEBUG}.so.1.0
	_lib      -S ${DEBUG}
	ldconfig
	sha1sum   lib${DEBUG}.a
	_lib      -A ${DEBUG}
	ldconfig
	#---(overview)------------------------#
	rm -f     ${ODIR}/${OBASE}.bz2
	cp -f     ${OBASE}    ${ODIR}
	bzip2     ${ODIR}/${OBASE}
	chmod     0644  ${ODIR}/${OBASE}.bz2
	#---(documentation)-------------------#
	rm -f     ${MDIR}/${MBASE}.bz2
	cp -f     ${MBASE}    ${MDIR}
	bzip2     ${MDIR}/${MBASE}
	chmod     0644  ${MDIR}/${MBASE}.bz2
	#---(done)----------------------------#


#*============================----end-of-source---============================*#
