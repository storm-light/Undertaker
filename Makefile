# A simple Makefile for compiling small SDL projects

# set the compiler
CC := g++

# set the compiler flags
CFLAGS := -g -Wall -l SDL2 -l SDL2_image -l SDL2_ttf

# add header files here
HDRS := GlobalVars.h Yahdu.h GameState.h Titlescreen.h Landscape.h Lab.h HelperFunctions.h 

# add source files here
SRCS := Main.cpp Yahdu.cpp HelperFunctions.cpp Titlescreen.cpp Landscape.cpp Lab.cpp 

# generate names of object files
OBJS := $(SRCS:.cpp=.o)

# name of executable
EXEC := Undertaker_v1.1

# build an app bundle!
# build : Makefile.build
# 	make -f Makefile.build

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files $(@:.o=.c)
$(OBJS): $(SRCS) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.cpp) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean build
