#include "SDL2/SDL.h"    
#include <chip8.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <opcodes.h>
#include <display.h>
#include <time.h>
#include <unistd.h>
#include <debug.h>

/**
 * INITALIZE THE CHIP *
 * @param fptr This is the file pointer, which has already been validated and initialized
 * @return returns the initialized chip8 struct
 */
chip8 init_chip8(FILE * fptr){
    chip8 chip8Init;
    uint8_t buffer;
    for(int i=0;i<4096;i++){
        chip8Init.RAM[i] = 0xFF;
    }//this is properly initilized

    //intitialize the font sprites in memory.
    uint8_t fontSprites[0x50] = {0xF0, 0x90, 0x90, 0x90, 0xF0, 0x20, 0x60, 0x20, 0x20, 0x70, 0xF0, 0x10, 0xF0, 0x80, 0xF0, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x90, 0x90, 0xF0, 0x10, 0x10, 0xF0, 0x80, 0xF0, 0x10, 0xF0, 0xF0, 0x80, 0xF0, 0x90, 0xF0, 0xF0, 0x10, 0x20, 0x40, 0x40, 0xF0, 0x90, 0xF0, 0x90, 0xF0, 0xF0, 0x90, 0xF0, 0x10, 0xF0, 0xF0, 0x90, 0xF0, 0x90, 0x90, 0xE0, 0x90, 0xE0, 0x90, 0xE0,  0xF0, 0x80, 0x80, 0x80, 0xF0, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0xF0, 0x80, 0xF0, 0x80, 0xF0, 0xF0, 0x80, 0xF0, 0x80, 0x80};
    for(int i=0x50;i<0xA0;i++){
        chip8Init.RAM[i]=fontSprites[i-0x50];
    }
    chip8Init.PC= 0x200;

    while(!feof(fptr)){
        fread(&buffer,1,1,fptr);
        chip8Init.RAM[chip8Init.PC++]=buffer;
        fread(&buffer,1,1,fptr);
        chip8Init.RAM[chip8Init.PC++]=buffer;
    }//file has been written to memory

    //setup the display
    for(int i=0;i<W;i++){
        for(int j=0;j<H;j++){
            chip8Init.display[i][j]= false;
        }
    }

    //intialize stack and registers
    for(int i=0;i<16;i++){
        chip8Init.V[i]=0xFF;
        chip8Init.STACK[i]=0xFFFF;
    }
    chip8Init.SP = -1;

    //initializing Index register, Delay timer, sound timer, Program counter
    chip8Init.I=0xFFFF;
    chip8Init.DT = 0;
    chip8Init.ST = 0;
    chip8Init.PC = 0xFFFF;

    //initialize input array
    for(int i=0;i<16;i++){
        chip8Init.keypad[i]=false;
    }

    return chip8Init;
}

void handleInput(chip8* chip8, configs* chip8Configs,SDL_Event* windowEvent){
    //here we will update an array of the keypad

    (void)chip8Configs;

    while(SDL_PollEvent(windowEvent)){
            if(SDL_QUIT == windowEvent->type){
                exit(EXIT_SUCCESS);
                break;
            }
           
            if(SDL_KEYDOWN == windowEvent->type){
                switch(windowEvent->key.keysym.sym){
                    case(SDLK_1):
                        chip8->keypad[1]=true;
                        break;
                    case(SDLK_2):
                        chip8->keypad[2]=true;
                        break;
                    case(SDLK_3):
                        chip8->keypad[3]=true;
                        break;
                    case(SDLK_4):
                        chip8->keypad[0xC]=true;
                        break;
                    case(SDLK_q):
                        chip8->keypad[4]=true;
                        break;
                    case(SDLK_w):
                        chip8->keypad[5]=true;
                        break;
                    case(SDLK_e):
                        chip8->keypad[6]=true;
                        break;
                    case(SDLK_r):
                        chip8->keypad[0xD]=true;
                        break;
                    case(SDLK_a):
                        chip8->keypad[7]=true;
                        break;
                    case(SDLK_s):
                        chip8->keypad[8]=true;
                        break;
                    case(SDLK_d):
                        chip8->keypad[9]=true;
                        break;
                    case(SDLK_f):
                        chip8->keypad[0xE]=true;
                        break;
                    case(SDLK_z):
                        chip8->keypad[0xA]=true;
                        break;
                    case(SDLK_x):
                        chip8->keypad[0]=true;
                        break;
                    case(SDLK_c):
                        chip8->keypad[0xB]=true;
                        break;
                    case(SDLK_v):
                        chip8->keypad[0xF]=true;
                        break;

                    case(SDLK_SPACE):
                        //chip8Configs->debugMode=true;
                        break;
                    default:
                }
            }

            if(SDL_KEYUP == windowEvent->type){
                switch(windowEvent->key.keysym.sym){
                    case(SDLK_1):
                        chip8->keypad[1]=false;
                        break;
                    case(SDLK_2):
                        chip8->keypad[2]=false;
                        break;
                    case(SDLK_3):
                        chip8->keypad[3]=false;
                        break;
                    case(SDLK_4):
                        chip8->keypad[0xC]=false;
                        break;
                    case(SDLK_q):
                        chip8->keypad[4]=false;
                        break;
                    case(SDLK_w):
                        chip8->keypad[5]=false;
                        break;
                    case(SDLK_e):
                        chip8->keypad[6]=false;
                        break;
                    case(SDLK_r):
                        chip8->keypad[0xD]=false;
                        break;
                    case(SDLK_a):
                        chip8->keypad[7]=false;
                        break;
                    case(SDLK_s):
                        chip8->keypad[8]=false;
                        break;
                    case(SDLK_d):
                        chip8->keypad[9]=false;
                        break;
                    case(SDLK_f):
                        chip8->keypad[0xE]=false;
                        break;
                    case(SDLK_z):
                        chip8->keypad[0xA]=false;
                        break;
                    case(SDLK_x):
                        chip8->keypad[0]=false;
                        break;
                    case(SDLK_c):
                        chip8->keypad[0xB]=false;
                        break;
                    case(SDLK_v):
                        chip8->keypad[0xF]=false;
                        break;
                    default:
                }
            }
        }

    
}


int main(int argc, char** argv){

    //intitialize the chip8 struct
    chip8 system;
    system.PC = 0;

    configs chip8Configs;
    //set the defaults
    chip8Configs.debugMode=false;
    chip8Configs.scaleFactor = 8;
    chip8Configs.speed = DEFAULT_HZ;
    chip8Configs.r = DEFAULT_R;
    chip8Configs.g = DEFAULT_G;
    chip8Configs.b = DEFAULT_B;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    //if(!init_sdl(&window,renderer,chip8Configs)) exit(EXIT_FAILURE);

    SDL_CreateWindowAndRenderer(W*chip8Configs.scaleFactor,H*chip8Configs.scaleFactor,0,&window,&renderer);

    if(window==NULL){
        printf("Something went wrong, could not create window.\n");
        return 1;
    }

    if(renderer==NULL){
        printf("Something went wrong, could not create renderer.\n");
        return 1;
    }

    SDL_RenderSetScale(renderer,chip8Configs.scaleFactor,chip8Configs.scaleFactor);
    


    //file stuff!
    if(argc!=2){
        //they did not input a filename
        printf("Please execute with the format: %s 'ROM filepath'\n",argv[0]);
        return 1;
    }

    FILE * fptr = fopen(argv[1],"rb");

    if(fptr==NULL){
        printf("File could not be opened!\n");
        return 1;
    }

    system = init_chip8(fptr);

    fclose(fptr);


    SDL_Event windowEvent;

    uint8_t buffer;
    int nibbles[4];

    //bool undefinedInstruction=false;

    int x;
    system.PC = 0x200;

    struct timespec begin, end;
    double deltaTime;

    int countdown=0;

    double delay;

    //char windowTitle[20];
//so indiscriminately write inro memmory, then reAD form mwmoery!!
//begin the timer
// ill need to do instructions and display, maybe have them synchronized as well
//they will definitely need to be synchronized.

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&begin);
    for(system.PC=0x200;system.PC<4096;system.PC+=2){

        //count down the delay timers, synchronized with the Ticker!!!. multiply my a thing? 
        countdown++;

        if(countdown==8||countdown==16||countdown==25){
            //subtract from the relative timers. 
            
            if(system.DT!=0){
                system.DT--;
                if(chip8Configs.debugMode)printf("subtracting from DT\t value is: %d\n",system.DT);
            }

            if(system.ST!=0){
                system.ST--;
                if(chip8Configs.debugMode)printf("subtracting from ST\t value is: %d\n",system.ST);
            }

            if(chip8Configs.debugMode)printf("\n");

            //special case for 25.
            if(countdown==25){
                countdown=0;
            }
        }

        if(chip8Configs.debugMode)printf("%0X\t",system.PC);
        buffer = system.RAM[system.PC];
        nibbles[0]=buffer/16;
        nibbles[1]=buffer%16;

        buffer = system.RAM[system.PC+1];
        nibbles[2]=buffer/16;
        nibbles[3]=buffer%16;


        //printf("%1.x\t%1.x\t%1.x\t%1.x\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);

        //THE HEART OF THE EMULATOR

        //it doesnt matter, but why does what is initialized and unchanged from 0x FF bceom seemingly random after 0x 900 (2304)

        //so yeah, essentially it is correctly initialized all to FF, but for some readon once I get past 0x900 it begins to spit out gibberish and zeros.it ends at FA8
        //everything else works, and assuming the program has proper control flow it should not be an issue

        //ill need to spit out the registers with each instruction and essentially go step by step through a program and validate each instruction

        //break points
        
        if(system.PC==0x347){
            chip8Configs.debugMode=true;
        }

        switch(nibbles[0]){
            case(0x0):
                //Clear screen, rts, execute machine language routine
                if(nibbles[1]==0&&nibbles[2]==0xE&&nibbles[3]==0x0){
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tCLEAR SCREEN\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    clearScreen(&system);
                }else if(nibbles[1]==0&&nibbles[2]==0xE&&nibbles[3]==0xE){
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tRETURN FROM SUBROUTINE\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    returnFromSubroutine(&system);
                }else{
                    //ignore
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tMACHINE LANGUAGE ROUTINE\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    callSubroutine(&system,nibbles);
                }
                break;
            case(0x1):
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tJUMP\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                jump(&system,nibbles);
                break;
            case(0x2):
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tCALL SUBROUTINE\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                callSubroutine(&system,nibbles);
                break;
            case(0x3):
                //SEQ
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP ON EQUALS; IMMEDIATE ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                seqImmediate(&system,nibbles);
                break;
            case(0x4):
                //SNE
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP ON NOT EQUALS; IMMEDIATE ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                sneImmediate(&system,nibbles);
                break;
            case(0x5):
                //SEQ
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP ON EQUALS; REGISTER ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                seqDRD(&system,nibbles);
                break;
            case(0x6):
                //set
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET; IMMEDIATE ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                setImmediate(&system,nibbles);
                break;
            case(0x7):
                //add
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tADD; IMMEDIATE ADDRESSING \n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                addImmediate(&system,nibbles);
                break;
            case(0x8):
                //Logical and ariithmetic instructions
                switch(nibbles[3]){
                    case(0):
                        //set
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET; REGISTER ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        setDRD(&system,nibbles);
                        break;
                    case(1):
                        //OR
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tOR\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        or(&system,nibbles);
                        break;
                    case(2):
                        //AND
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tAND\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        and(&system,nibbles);
                        break;
                    case(3):
                        //XOR
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tXOR\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        xor(&system,nibbles);
                        break;
                    case(4):
                        //add
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tADD; REGISTER ADDRESSING \n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        addDRD(&system,nibbles);
                        break;
                    case(5):
                        //subtract
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSUBTRACT; VX - VY\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        subXY(&system,nibbles);
                        break;
                    case(6):
                        //this is ambiguous
                        //shift right
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSHIFT RIGHT\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        shiftRight(&system, nibbles);
                        break;
                    case(7):
                        //subtract
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSUBTRACT; VY - VX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        subYX(&system,nibbles);
                        break;
                    case(0xE):
                        //shift left
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSHIFT LEFT\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        shiftLeft(&system,nibbles);
                        break;
                    default:
                        //invalid
                        if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSPRITES\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                        //undefinedInstruction=true;
                }
                break;
            case(9):
                //SNE / BEQ
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP ON NOT EQUALS; REGISTER ADDRESSING\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                sneDRD(&system,nibbles);
                break;
            case(0xA):
                //set index
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET INDEX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                setIndex(&system,nibbles);
                break;
            case(0xB):
                //JUMP with offset
                //ambiguous
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tJJUMP WITH OFFSET\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                jumpWithOffset(&system,nibbles);
                break;
            case(0xC):
                //random
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tRANDOM\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                random(&system,nibbles);
                break;
            case(0xD):
                //draw
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tDRAW\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                draw(chip8Configs,&system,nibbles);
                break;
            case(0xE):
                //type of user input
                if(nibbles[2]==9&&nibbles[3]==0xE){
                    //skip if X is pressed
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP IF X\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    skipIfX(&system,nibbles);
                }else if(nibbles[2]==0xA&&nibbles[3]==1){
                    //skip if it is not pressed
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSKIP IF NOT X\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    skipIfNotX(&system,nibbles);
                }else{
                    //invalid
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSPRITES\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    //undefinedInstruction=true;
                }
                break;
            case(0xF):
                //timers,index,get key,font,binary to decimal

                if(nibbles[2]==0&&nibbles[3]==7){
                    //set vx to the delay timer
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET VX TO DT\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    setVXDT(&system,nibbles);
                }else if(nibbles[2]==1&&nibbles[3]==5){
                    //set the delay timer to vx
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET DT TO VX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    setDTVX(&system,nibbles);
                }else if(nibbles[2]==1&&nibbles[3]==8){
                    // set the Sound timer to VX
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSET ST TO VX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    setSTVX(&system,nibbles);
                }else if(nibbles[2]==1&&nibbles[3]==0xE){
                    //Add to index
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tADD VX TO I\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    addVXI(&system,nibbles);
                }else if(nibbles[2]==0&&nibbles[3]==0xA){
                    //Get key
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tWAIT FOR KEY IN VX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    getKey(&chip8Configs,&system,nibbles,&windowEvent);
                }else if(nibbles[2]==2&&nibbles[3]==9){
                    //font characcter
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tGET FONT CHARACTER\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    getFont(&system,nibbles);
                }else if(nibbles[2]==3&&nibbles[3]==3){
                    //BINARY TO DECIMAL
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tBINARY TO DECIMAL FROM VX INTO I\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    decimalVXI(&system,nibbles);
                }else if(nibbles[2]==5&&nibbles[3]==5){
                    //STORE MMEROY
                    //ambiguous
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSTORE REGISTERS FROM V0 - VX IN I\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    storeRegisters(&system,nibbles);
                }else if(nibbles[2]==6&&nibbles[3]==5){
                    //LOAD REGISTERS
                    //ambiguous
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tLOAD REGISTERS FROM I INTO V0 - VX\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    loadRegisters(&system,nibbles);
                }else{
                    //invalid
                    if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSPRITES\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                    //undefinedInstruction=true;
                }
                break;
            default:
                //invalid
                if(chip8Configs.debugMode)printf("%1.x\t%1.x\t%1.x\t%1.x\tSPRITES\n",nibbles[0],nibbles[1],nibbles[2],nibbles[3]);
                //undefinedInstruction=true;
        }
        //Debug
        if(chip8Configs.debugMode){
            printf("\nData registers:\t");
            for(int j=0;j<16;j++){
                printf("V[%d]: %0X\t",j,system.V[j]);
            }
            printf("\n\nStack:\t");
            for(int j=0;j<16;j++){
                printf("[%d]: %0X\t",j,system.STACK[j]);
            }
            printf("\n\nPC: %0X    I: %0X    DT: %0X    ST: %0X    SP: %d\nWould you like to set input? enter 5 to open the keypad, or enter 0 to exit debug mode.",system.PC,system.I,system.DT,system.ST,system.SP);

            scanf("%d",&x);
            getchar();
            if(x==5){
                set_keypad(&system, &chip8Configs,&windowEvent);
            }else if(x==0){
                chip8Configs.debugMode=false;
            }
        }

        updateDisplay(&system,chip8Configs,&renderer);
        handleInput(&system,&chip8Configs,&windowEvent);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
        deltaTime= end.tv_sec-begin.tv_sec + (end.tv_nsec-begin.tv_nsec)/1000000000.0;

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&begin);

        delay = (0.002 - deltaTime)*1000;
        if(delay>=0){
            SDL_Delay(delay);
        }

        if(chip8Configs.debugMode)printf("\n");
    }

    return 0;
}