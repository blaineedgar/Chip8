CFLAGS:=-std=c11 -Wall -Wextra #-Werror #here we are compiling using c11 to make sure it is standardized!
LIBS:=lib
INCLUDES:=include #./include

# Target rule for compiling and linking the program
all: menu opcodes display debug
	gcc -g $(CFLAGS) -I$(INCLUDES) -L$(LIBS) -O2 -o bin/chip8 src/chip8.c build/menu.o build/opcodes.o build/display.o build/debug.o -lmingw32 -lSDL2main -lSDL2

menu:
	gcc -g $(CFLAGS) -I$(INCLUDES) -L$(LIBS) -O2 -o build/menu.o -c src/menu.c

opcodes:
	gcc -g $(CFLAGS) -I$(INCLUDES) -L$(LIBS) -O2 -o build/opcodes.o -c src/opcodes.c

display:
	gcc -g $(CFLAGS) -I$(INCLUDES) -L$(LIBS) -O2 -o build/display.o -c src/display.c

debug:
	gcc -g $(CFLAGS) -I$(INCLUDES) -L$(LIBS) -o build/debug.o -c src/debug.c

clean:
	rm -f chip8