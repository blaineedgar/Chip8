#ifndef DEBUG_H
#define DEBUG_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

//debug function headers in the debug file
void memory_Dump(chip8 chip8);
void set_keypad(chip8* chip8, configs * configs,SDL_Event * windowEvent);
void decodeDump(chip8 system);

#endif