COMPILER = clang
#SOURCE_LIBS = -Ilib/
#OSX_OPT = -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a
OSX_OUT = -g -o "bin/build_osx"
CFILES = src/*.c

# unused in build_osx: $(SOURCE_LIBS) $(OSX_OUT)
build_osx:
	$(COMPILER) $(CFILES) $(OSX_OPT)
