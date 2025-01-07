#ifndef OPCODES_H
#define OPCODES_H

#include "chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void clearScreen(chip8* chip8);
void returnFromSubroutine(chip8* chip);
void machineLanguageRoutine(chip8 chip8,int* nibbles);
void jump(chip8* chip8,int* nibbles);
void callSubroutine(chip8* chip8,int* nibbles);
void seqImmediate(chip8* chip8,int* nibbles);
void sneImmediate(chip8* chip8, int* nibbles);
void seqDRD(chip8* chip8, int* nibbles);
void setImmediate(chip8* chip8, int* nibbles);
void addImmediate(chip8* chip8, int* nibbles);
void setDRD(chip8* chip8, int* nibbles);
void or(chip8* chip8, int* nibbles);//hopefully these nanes dont cause an issue
void and(chip8* chip8, int* nibbles);
void xor(chip8* chip8, int* nibbles);
void addDRD(chip8* chip8, int* nibbles);
void subXY(chip8* chip8, int* nibbles);
void shiftRight(chip8* chip8,int* nibbles);
void subYX(chip8* chip8, int* nibbles);
void shiftLeft(chip8* chip8, int* nibbles);
void sneDRD(chip8* chip8, int* nibbles);
void setIndex(chip8* chip8, int* nibbles);
void jumpWithOffset(chip8* chip8, int* nibbles);
void random(chip8* chip8, int* nibbles);
void draw(configs chip8Configs, chip8* chip8, int* nibbles);
void skipIfX(chip8* chip8, int* nibbles);
void skipIfNotX(chip8* chip8, int* nibbles);
void setVXDT(chip8* chip8, int* nibbles);
void setDTVX(chip8* chip8, int* nibbles);
void setSTVX(chip8* chip8, int* nibbles);
void addVXI(chip8* chip8, int* nibbles);
void getKey(configs* chip8Configs,chip8* chip8, int* nibbles,SDL_Event* windowEvent);
void getFont(chip8* chip8, int* nibbles);
void decimalVXI(chip8* chip8, int* nibbles);
void storeRegisters(chip8* chip8, int* nibbles);
void loadRegisters(chip8* chip8, int* nibbles);

#endif