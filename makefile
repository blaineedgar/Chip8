CFLAGS:=-std=c11 -Wall -Wextra #-Werror #here we are compiling using c11 to make sure it is standardized!
LIBS:=lib
INCLUDES:=include #./include

# Target rule for compiling and linking the program
all: menu opcodes display debug
	gcc -g $(CFLAGS) -I$(INCLUDES) -L$(LIBS) -O0 -o  chip8 src/chip8.c menu.o opcodes.o display.o debug.o -lmingw32 -lSDL2main -lSDL2 

menu:
	gcc -g $(CFLAGS) -I$(INCLUDES) -L$(LIBS) -O0 -c src/menu.c

opcodes:
	gcc -g $(CFLAGS) -I$(INCLUDES) -L$(LIBS) -O0 -c src/opcodes.c

display:
	gcc -g $(CFLAGS) -I$(INCLUDES) -L$(LIBS) -O0 -c src/display.c

debug:
	gcc -g $(CFLAGS) -I$(INCLUDES) -L$(LIBS) -O0 -c src/debug.c
#SDL2:
#	gcc -o SDL lib/SDL2/SDL.h

# Clean rule (optional but recommended)
clean:
	rm -f chip8