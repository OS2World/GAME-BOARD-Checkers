#===================================================================
#   Checkers v1.0 - Open Watcom makefile
#===================================================================

CC      = wcc386
LINK    = wlink
RC      = wrc

CFLAGS  = -bt=os2 -mf -5 -fpi -Oaxt -W3 -ze -d0 -i=$(OS2TK)\h -i=src
RCFLAGS = -i=$(OS2TK)\h -i=src

OBJS = bin\checkers.obj  &
       bin\ckrboard.obj  &
       bin\ckrdraw.obj   &
       bin\ckrjudge.obj  &
       bin\ckrmoves.obj  &
       bin\ckrstrat.obj  &
       bin\ckrsetup.obj

all : bin\checkers.exe

bin\checkers.exe : $(OBJS) bin\checkers.res
	$(LINK) system os2v2 pm option stack=65536 option heapsize=4096 option map=bin\checkers.map name bin\checkers.exe file bin\checkers.obj, bin\ckrboard.obj, bin\ckrdraw.obj, bin\ckrjudge.obj, bin\ckrmoves.obj, bin\ckrstrat.obj, bin\ckrsetup.obj
	$(RC) bin\checkers.res bin\checkers.exe

bin\checkers.res : src\checkers.rc src\checkers.h src\checkers.ico
	$(RC) $(RCFLAGS) -r src\checkers.rc -fo=bin\checkers.res

bin\checkers.obj : src\checkers.c src\checkers.h src\lang.h
	$(CC) $(CFLAGS) -fo=bin\checkers.obj src\checkers.c

bin\ckrboard.obj : src\ckrboard.c src\checkers.h src\ckrdraw.h src\ckrmoves.h
	$(CC) $(CFLAGS) -fo=bin\ckrboard.obj src\ckrboard.c

bin\ckrdraw.obj : src\ckrdraw.c src\checkers.h src\ckrdraw.h
	$(CC) $(CFLAGS) -fo=bin\ckrdraw.obj src\ckrdraw.c

bin\ckrjudge.obj : src\ckrjudge.c src\checkers.h src\ckrmoves.h src\ckrstrat.h
	$(CC) $(CFLAGS) -fo=bin\ckrjudge.obj src\ckrjudge.c

bin\ckrmoves.obj : src\ckrmoves.c src\checkers.h src\ckrmoves.h
	$(CC) $(CFLAGS) -fo=bin\ckrmoves.obj src\ckrmoves.c

bin\ckrstrat.obj : src\ckrstrat.c src\checkers.h src\ckrstrat.h
	$(CC) $(CFLAGS) -fo=bin\ckrstrat.obj src\ckrstrat.c

bin\ckrsetup.obj : src\ckrsetup.c src\checkers.h src\ckrdraw.h
	$(CC) $(CFLAGS) -fo=bin\ckrsetup.obj src\ckrsetup.c

clean : .SYMBOLIC
	-del bin\checkers.obj 2>NUL
	-del bin\ckrboard.obj 2>NUL
	-del bin\ckrdraw.obj 2>NUL
	-del bin\ckrjudge.obj 2>NUL
	-del bin\ckrmoves.obj 2>NUL
	-del bin\ckrstrat.obj 2>NUL
	-del bin\ckrsetup.obj 2>NUL
	-del bin\checkers.res 2>NUL
	-del bin\checkers.map 2>NUL
	-del bin\checkers.exe 2>NUL
