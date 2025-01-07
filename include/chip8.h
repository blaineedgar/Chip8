#ifndef CHIP8_H
#define CHIP8_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

//I am supposed to do conversions from int to char?
#define DEFAULT_SF 8
#define DEFAULT_HZ 700
#define DEFAULT_R 255
#define DEFAULT_G 255
#define DEFAULT_B 255

#define H 32
#define W 64

//#define HEX[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}

typedef struct chip8{
    //memory
    //our ram i dont think will have mirrors
    uint8_t RAM[4096];
    //diplay
    /**
     * we xor sprites onto the screen
     * in order to xor something, I need to know its current value, and I cannot get that value from the SDL Display.
     * so i will use this 2d array, which ill know the values of and then xor them accordingly.
     * then once I'dve xor the array I'll use nested loops to update the screen, and then use SDLL_PRESENT.
     */
    uint8_t display[W][H]; //so we'll have this i think then write to it then update it?  not too sure the conclusion i came to. OK I REMEBEMR. 
    //program counter
    uint16_t PC;
    //index register
    uint16_t I;
    //stack; the stack will work and the stack pointer will start small.
    uint16_t STACK[16];
    int SP;
    //delaytimer
    uint8_t DT;
    //soundtimer
    uint8_t ST;
    //16 registers
    uint8_t V[16];
    
    bool keypad[16];
}chip8;

typedef struct configs{
    bool debugMode;
    int scaleFactor;//must be positive.
    int speed;
    //you can change the colour of the 
    uint8_t r;//rgb thing. enter in hex? that would be nice!
    uint8_t g;
    uint8_t b;
    //window name??

    //change game, name the window the filename if we can
    
}configs;

//function headers defined in the opcode file

void handleInput(chip8* chip8, configs* chip8Configs,SDL_Event* windowEvent);


#endif