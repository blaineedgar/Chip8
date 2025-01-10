#include <SDL2/SDL.h>       
#include <chip8.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * MEMORY DUMP FOR DEGUGGINB
 * @param chip8 structure of memory to duomp
 */
void memory_Dump(chip8 chip8){
    //check for unitiialized bytes and then stop
    for(int i=0;i<4096;i++){
        printf("%0X;%0X\t",i,chip8.RAM[i]);
    }
    printf("\n");
}

/**
 * SET KEYPAD for degbuggging
 * 
 */
void set_keypad(chip8* chip8, configs * configs,SDL_Event* windowEvent){
    (void)configs;

    printf("setting the keypad. press Spacebar to quit");

    bool loop=true;
    while(loop){
        while(SDL_PollEvent(windowEvent)){
            if(SDL_QUIT == windowEvent->type){
                    break;
            }

/*
            if(SDL_MOUSEBUTTONDOWN){
                //xor the state of debug mode
                //chip8Configs->debugMode^=true;

                if(chip8Configs->debugMode){
                    chip8Configs->debugMode=false;
                }else if(!chip8Configs->debugMode){
                    chip8Configs->debugMode=true;
                }
            }
           */
            if(SDL_KEYDOWN == windowEvent->type){
                //printf("Key is down\n");

                //distinguish among the keys. switch??
                switch(windowEvent->key.keysym.sym){
                    case(SDLK_1):
                        if(!chip8->keypad[1]){
                            chip8->keypad[1]=true;
                        }else{
                            chip8->keypad[1]=false;
                        }
                        break;
                    case(SDLK_2):
                        if(!chip8->keypad[2]){
                            chip8->keypad[2]=true;
                        }else{
                            chip8->keypad[2]=false;
                        }
                        break;
                    case(SDLK_3):
                        if(!chip8->keypad[3]){
                            chip8->keypad[3]=true;
                        }else{
                            chip8->keypad[3]=false;
                        }
                        break;
                    case(SDLK_4):
                        if(!chip8->keypad[0xC]){
                            chip8->keypad[0xC]=true;
                        }else{
                            chip8->keypad[0xC]=false;
                        }
                        break;
                    case(SDLK_q):
                        if(!chip8->keypad[4]){
                            chip8->keypad[4]=true;
                        }else{
                            chip8->keypad[4]=false;
                        }
                        break;
                    case(SDLK_w):
                        if(!chip8->keypad[5]){
                            chip8->keypad[5]=true;
                        }else{
                            chip8->keypad[5]=false;
                        }
                        break;
                    case(SDLK_e):
                        if(!chip8->keypad[6]){
                            chip8->keypad[6]=true;
                        }else{
                            chip8->keypad[6]=false;
                        }
                        break;
                    case(SDLK_r):
                        if(!chip8->keypad[0xD]){
                            chip8->keypad[0xD]=true;
                        }else{
                            chip8->keypad[0xD]=false;
                        }
                        break;
                    case(SDLK_a):
                        if(!chip8->keypad[7]){
                            chip8->keypad[7]=true;
                        }else{
                            chip8->keypad[7]=false;
                        }
                        break;
                    case(SDLK_s):
                        if(!chip8->keypad[8]){
                            chip8->keypad[8]=true;
                        }else{
                            chip8->keypad[8]=false;
                        }
                        break;
                    case(SDLK_d):
                        if(!chip8->keypad[9]){
                            chip8->keypad[9]=true;
                        }else{
                            chip8->keypad[9]=false;
                        }
                        break;
                    case(SDLK_f):
                        if(!chip8->keypad[0xE]){
                            chip8->keypad[0xE]=true;
                        }else{
                            chip8->keypad[0xE]=false;
                        }
                        break;
                    case(SDLK_z):
                        if(!chip8->keypad[0xA]){
                            chip8->keypad[0xA]=true;
                        }else{
                            chip8->keypad[0xA]=false;
                        }
                        break;
                    case(SDLK_x):
                        if(!chip8->keypad[0]){
                            chip8->keypad[0]=true;
                        }else{
                            chip8->keypad[0]=false;
                        }
                        break;
                    case(SDLK_c):
                        if(!chip8->keypad[0xB]){
                            chip8->keypad[0xB]=true;
                        }else{
                            chip8->keypad[0xB]=false;
                        }
                        break;
                    case(SDLK_v):
                        if(!chip8->keypad[0xF]){
                            chip8->keypad[0xF]=true;
                        }else{
                            chip8->keypad[0xF]=false;
                        }
                        break;
                    case(SDLK_SPACE):
                        loop=false;
                        break;
                    default:
                        //printf("unassigned key pressed \n");
                }
            }

        }
    }  

    printf("\n%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n",chip8->keypad[1],chip8->keypad[2],chip8->keypad[3],chip8->keypad[0xC],chip8->keypad[4],chip8->keypad[5],chip8->keypad[6],chip8->keypad[0xD],chip8->keypad[7],chip8->keypad[8],chip8->keypad[9],chip8->keypad[0xE],chip8->keypad[0xA],chip8->keypad[0],chip8->keypad[0xB],chip8->keypad[0xF]);
}


void decodeDump(chip8 system){
    system.PC = 0;

    uint8_t buffer;
    int nibbles[4];



    for(system.PC=0x200;system.PC<4096;system.PC+=2){

        buffer = system.RAM[system.PC];
        //printf("%2.x\n",buffer);
        nibbles[0]=buffer/16;
        nibbles[1]=buffer%16;

        //fseek(fptr,1,SEEK_CUR);
        buffer = system.RAM[system.PC+1];
        //printf("%2.x\n",buffer);
        nibbles[2]=buffer/16;
        nibbles[3]=buffer%16;


        //system.PC+=2;
        //assuming it dosen
        /*
        if(nibbles[0]==15&&nibbles[1]==15&&nibbles[2]==15&&nibbles[3]==15){
            break;
        }*/

       //breakpoint
        if(system.PC==0x320){
            break; 
        }



        //printf("%1.x\t%1.x\t%1.x\t%1.x\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);

        //THE HEART OF THE EMULATOR

        //it doesnt matter, but why does what is initialized and unchanged from 0x FF bceom seemingly random after 0x 900 (2304)

        //so yeah, essentially it is correctly initialized all to FF, but for some readon once I get past 0x900 it begins to spit out gibberish and zeros.it ends at FA8
        //everything else works, and assuming the program has proper control flow it should not be an issue

        //ill need to spit out the registers with each instruction and essentially go step by step through a program and validate each instruction

        
    configs chip8Configs;
    //set the defaults
    chip8Configs.debugMode=true;
        
        printf("%0X\t",system.PC);
        switch(nibbles[0]){
            case(0x0):
                //printf("either 0NNN, 00E0, or 00EE\n");
                if(nibbles[1]==0&&nibbles[2]==0xE&&nibbles[3]==0x0){
                }else if(nibbles[1]==0&&nibbles[2]==0xE&&nibbles[3]==0xE){
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tRETURN FROM SUBROUTINE\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else{
                    //ignore
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tMACHINE LANGUAGE ROUTINE\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }
                break;
            case(0x1):
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tJUMP\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0x2):
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tCALL SUBROUTINE\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0x3):
                //SEQ
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP ON EQUALS; IMMEDIATE ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0x4):
                //SNE
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP ON NOT EQUALS; IMMEDIATE ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0x5):
                //SEQ
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP ON EQUALS; REGISTER ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0x6):
                //set
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET; IMMEDIATE ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0x7):
                //add
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tADD; IMMEDIATE ADDRESSING \n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0x8):
                //LOGIcal and ariithmetic instructions
                switch(nibbles[3]){
                    case(0):
                        //set
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET; REGISTER ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        break;
                    case(1):
                        //OR
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tOR\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        break;
                    case(2):
                        //AND
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tAND\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        break;
                    case(3):
                        //XOR
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tXOR\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        break;
                    case(4):
                        //add
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tADD; REGISTER ADDRESSING \n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        break;
                    case(5):
                        //subtract
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSUBTRACT; VX - VY\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        break;
                    case(6):
                        //this is ambiguous
                        //shift right
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSHIFT RIGHT\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        break;
                    case(7):
                        //subtract
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSUBTRACT; VY - VX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        break;
                    case(0xE):
                        //shift left
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSHIFT LEFT\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        break;
                    default:
                        //invalid
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSPRITES\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }
                break;
            case(9):
                //SNE / BEQ
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP ON NOT EQUALS; REGISTER ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0xA):
                //set index
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET INDEX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0xB):
                //JUMP with offset
                //ambigguosus
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tJJUMP WITH OFFSET\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0xC):
                //random
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tRANDOM\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0xD):
                //draw
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tDRAW\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                break;
            case(0xE):
                //type of user input

                //WTFFFFFFF how to do this
                if(nibbles[2]==9&&nibbles[3]==0xE){
                    //skip if X is pressed
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP IF X\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else if(nibbles[2]==0xA&&nibbles[3]==1){
                    //skip if it is not pressed
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP IF NOT X\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else{
                    //invalid
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSPRITES\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }
                break;
            case(0xF):
                //timers,index,get key,font,binary to decimal

                if(nibbles[2]==0&&nibbles[3]==7){
                    //set vx to the delay timer
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET VX TO DT\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else if(nibbles[2]==1&&nibbles[3]==5){
                    //set the delat timer to vx
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET DT TO VX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else if(nibbles[2]==1&&nibbles[3]==8){
                    // set the Sound timer to VX
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET ST TO VX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else if(nibbles[2]==1&&nibbles[3]==0xE){
                    //Add to index
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tADD VX TO I\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else if(nibbles[2]==0&&nibbles[3]==0xA){
                    //Get key
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tWAIT FOR KEY IN VX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else if(nibbles[2]==2&&nibbles[3]==9){
                    //font characcter
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tGET FONT CHARACTER\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else if(nibbles[2]==3&&nibbles[3]==3){
                    //BINARY TO DECIMAL
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tBINARY TO DECIMAL FROM VX INTO I\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else if(nibbles[2]==5&&nibbles[3]==5){
                    //STORE MMEROY
                    //ambiguous
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSTORE REGISTERS FROM V0 - VX IN I\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else if(nibbles[2]==6&&nibbles[3]==5){
                    //LOAD REGISTES
                    //ambiguous
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tLOAD REGISTERS FROM I INTO V0 - VX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }else{
                    //invalid
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSPRITES\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                }
                break;
            default:
                //invalid
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSPRITES\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
        }

    }
}