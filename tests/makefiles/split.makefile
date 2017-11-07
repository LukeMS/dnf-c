#based on http://scottmcpeak.com/autodepend/autodepend.html
#if depencies are renamed a make clean will be required

_MAKEFILE_ABS = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
_TARGET := $(basename $(notdir $(realpath $(lastword $(MAKEFILE_LIST)))))
_CWD = $(_MAKEFILE_ABS)..
.DEFAULT_GOAL = run
$(info $(_TARGET) makefile=$(_MAKEFILE_ABS))


BDIR = $(_CWD)/bin
ODIR = $(_CWD)/obj
IDIR = .
SDIR = .

INC = -I$(IDIR) -I/msys32/mingw32/include -I$(_CWD)/../../glibc4w/

LIB_DEPS = glibc4w.a
LIBS = $(_CWD)/../../glibc4w/libglibc4w.a
OBJS := $(_TARGET).o

#-pedantic
CFLAGS = -Wall -W -ggdb -std=c99 $(INC) $(LIB)

glibc4w.a:
	mingw32-make -C $(_MAKEFILE_ABS)../../../glibc4w --file=$(_MAKEFILE_ABS)../../../glibc4w/makefiles/glibc4w.makefile

# link
all: $(LIB_DEPS) $(OBJS)
	@IF NOT EXIST "$(BDIR)" (mkdir $(BDIR))
	gcc $(OBJS) $(LIBS) -o $(BDIR)/$(_TARGET)

#start cmd /K "$(_MAKEFILE_DIR)../$(BDIR)/$(_TARGET).exe"
#./$(BDIR)/$(_TARGET).exe
run: all
	$(BDIR)/$(_TARGET).exe

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
$(ODIR)/%.o: $(SDIR)/%.c
	@IF NOT EXIST "$(ODIR)" (mkdir $(ODIR))
	gcc -c $(CFLAGS) $*.c -o $(ODIR)/$*.o
	gcc -MM $(CFLAGS) $*.c > $(ODIR)/$*.d

# remove compilation products
clean:
	IF EXIST "$(BDIR)\$(_TARGET).exe" (del $(BDIR)\$(_TARGET).exe)
	IF EXIST "$(ODIR)\*.o" (del $(ODIR)\*.o)
	IF EXIST "$(ODIR)\*.d" (del $(ODIR)\*.d)
