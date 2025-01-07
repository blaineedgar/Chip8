#ifndef DISPLAY_H
#define DISPLAY_H

#include "chip8.h"
#include "SDL2/SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

void updateDisplay(chip8* chip8,configs chip8Configs, SDL_Renderer ** renderer);
bool init_sdl();
void final_cleanup(void);

#endif