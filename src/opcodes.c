//define opcodes!!
//i should be finally ready to define the 

#include <SDL2/SDL.h>
#include <chip8.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void clearScreen(chip8* chip8){
    //00E0
    for(int i=0;i<W;i++){
        for(int j=0;j<H;j++){
            chip8->display[i][j]=false;
        }
    }

    //update the SDL?
}

void returnFromSubroutine(chip8* chip8){
    //00EE
    //how tf does the stack wrk
    //the stack will work with a array based stack. how will behave?
    //i could increment through the stack until i find an invalid value. becasue I do not think I will have a stack pointer. Or maybe I will??
    chip8->PC = chip8->STACK[chip8->SP];
    chip8->SP -=1;
}

void machineLanguageRoutine(chip8 chip8,int* nibbles){
    (void)chip8;
    (void)nibbles;
    //0NNN
    //no need to implement;
}

void jump(chip8* chip8,int* nibbles){
    //1NNN
    //concatenate the nibbles 

    uint16_t address = (nibbles[1]*pow(16,2) + (nibbles[2]*16) + nibbles[3]);
    //printf("\n[%d][%d][%d]\n",nibbles[1],nibbles[2],nibbles[3]);
    //printf("\n\nthe address is %d\n",address);
    chip8->PC = address - 2;
    
}

void callSubroutine(chip8* chip8,int* nibbles){
    //2NNN

    //set and push PC to stack.

    uint16_t address = (nibbles[1]*pow(16,2) + (nibbles[2]*16) + nibbles[3]);
    //printf("\n\nthe address is %0X\n",address);
    chip8->STACK[++chip8->SP] = chip8->PC;
    chip8->PC = address - 2;
}

void seqImmediate(chip8* chip8,int* nibbles){
    //3XKK
    //SE 
    if(chip8->V[nibbles[1]]==(nibbles[2]*16 + nibbles[3])){
        chip8->PC+=2;
    }
}

void sneImmediate(chip8* chip8, int* nibbles){
    //4XKK
    //SNE
    if(chip8->V[nibbles[1]]!=(nibbles[2]*16 + nibbles[3])){
        chip8->PC+=2;
    }
}

void seqDRD(chip8* chip8, int* nibbles){
    //5XY0

    if(chip8->V[nibbles[1]]==chip8->V[nibbles[2]]){
        chip8->PC+=2;
    }
}

void setImmediate(chip8* chip8, int* nibbles){
    //6XKK

    //well set vx to the last 2 nibbles
    chip8->V[nibbles[1]]=(nibbles[2]*16 + nibbles[3]);


}

void addImmediate(chip8* chip8, int* nibbles){
    //7XKK
//maybe dont do this?
    //add , ignore setting flags

    chip8->V[nibbles[1]]+=((nibbles[2]*16)+nibbles[3]);
    /*
    if(chip8->V[0]==0xFF&&nibbles[1]==0&&nibbles[2]==0&&nibbles[3]==1){
        chip8->V[nibbles[1]]+=((nibbles[2]*16)+nibbles[3]);//must also consider the carry flag. but not when V0. when subroutines we hav to do flags? thats how i would imagine
    }else{
        if(chip8->V[nibbles[1]]+((nibbles[2]*16)+nibbles[3])>255){//overflow
            chip8->V[nibbles[1]]+=((nibbles[2]*16)+nibbles[3]);
            chip8->V[0xF] = chip8->V[0xF]&1;
        }else{
            chip8->V[nibbles[1]]+=((nibbles[2]*16)+nibbles[3]);
            chip8->V[0xF] = chip8->V[0xF]&0;
        }
    }*/

    /*
    if(chip8->V[nibbles[1]]>=255){//if overflow
        
    }*/
}

void setDRD(chip8* chip8, int* nibbles){
    //8XY0

    //VX is set to VY

    chip8->V[nibbles[1]]=chip8->V[nibbles[2]];
}

void or(chip8* chip8, int* nibbles){
    //8XY1

    //Vx = VX|VY

    chip8->V[nibbles[1]]=chip8->V[nibbles[1]]|chip8->V[nibbles[2]];
}

void and(chip8* chip8, int* nibbles){
    //8XY2

    chip8->V[nibbles[1]]=chip8->V[nibbles[1]]&chip8->V[nibbles[2]];
}

void xor(chip8* chip8, int* nibbles){
    //8XY3

    chip8->V[nibbles[1]]=chip8->V[nibbles[1]]^chip8->V[nibbles[2]];
}

void addDRD(chip8* chip8, int* nibbles){
    //8XY4

    if(chip8->V[nibbles[1]]+chip8->V[nibbles[2]]>255){//overflow
        chip8->V[nibbles[1]]=chip8->V[nibbles[1]]+chip8->V[nibbles[2]];
        chip8->V[0xF] = chip8->V[0xF]&1;
    }else{
        chip8->V[nibbles[1]]=chip8->V[nibbles[1]]+chip8->V[nibbles[2]];
        chip8->V[0xF] = chip8->V[0xF]&0;
    }
}

void subXY(chip8* chip8, int* nibbles){
    //8XY5
    
    chip8->V[nibbles[1]]=chip8->V[nibbles[1]]-chip8->V[nibbles[2]];

    //flag stuuff
    if(chip8->V[nibbles[1]]>=chip8->V[nibbles[2]]){
        chip8->V[15]=1;
    }else{
        chip8->V[15]=0;
    }
}

void shiftRight(chip8* chip8, int* nibbles){
    //8XY6
    //ambiguous

    //set vx to vy, vf is remainder, then divide by 2

    chip8->V[nibbles[1]]=chip8->V[nibbles[2]];

    chip8->V[15]=chip8->V[nibbles[1]]%2;

    chip8->V[nibbles[1]]=chip8->V[nibbles[1]]/2;
}

void subYX(chip8* chip8, int* nibbles){
    //8XY7

    chip8->V[nibbles[1]]=chip8->V[nibbles[2]]-chip8->V[nibbles[1]];

    //flag 
    if(chip8->V[nibbles[2]]>=chip8->V[nibbles[1]]){
        chip8->V[15]=1;
    }else{
        chip8->V[15]=0;
    }
}

void shiftLeft(chip8* chip8, int* nibbles){
    //8XYE
    //ambiguous

    //multiply by 2, if it is greater than 255 set the carry
    chip8->V[nibbles[1]]=chip8->V[nibbles[2]];

    if(chip8->V[nibbles[1]]*2>255){
        chip8->V[15]=1;
    }else{
        chip8->V[15]=0;
    }
    chip8->V[nibbles[1]]=chip8->V[nibbles[1]]*2;

}

void sneDRD(chip8* chip8, int* nibbles){
    //9XY0

    if(chip8->V[nibbles[1]]!=chip8->V[nibbles[2]]){
        chip8->PC+=2;
    }
}

void setIndex(chip8* chip8, int* nibbles){
    //ANNN
    chip8->I=(nibbles[1]*pow(16,2) + (nibbles[2]*16) + nibbles[3]);
}

void jumpWithOffset(chip8* chip8, int* nibbles){
    //BNNN
    chip8->PC=(nibbles[1]*pow(16,2) + (nibbles[2]*16) + nibbles[3]) + chip8->V[0];
}

void random(chip8* chip8, int* nibbles){
    //CXNN

    //genereate a random number! then and it with NN
    int r = rand() % 256;

    chip8->V[nibbles[1]]= r & ((nibbles[2]*16) + nibbles[3]);
}

void draw(configs chip8Configs, chip8* chip8, int* nibbles){
    //DXYN
    //read in n bytes from I. then 
    int spriteBuffer[15];
    bool collision=false;
    //decompose each byte into bits, pixels.. an array of the things
    //not gonna dynamically allocate.
    uint8_t sprite [15][8];

    for(int i=chip8->I;i<chip8->I+nibbles[3];i++){
        spriteBuffer[i-chip8->I]=chip8->RAM[i];
    }
    
    if(chip8Configs.debugMode){
        printf("\n");
        //test the buffer
        for(int i=0;i<15;i++){
            printf("%0X\t",spriteBuffer[i]);
        }
        printf("\n");
    }

    //now well do the dividing thing to set the sprite array.
    for(int i=0;i<nibbles[3];i++){
        for(int j=7;j>=0;j--){
            sprite[i][j]=spriteBuffer[i]%2;
            spriteBuffer[i]=spriteBuffer[i]/2;
        }
    }

    //test the sprite. 
    if(chip8Configs.debugMode){    
        printf("\n");
        for(int i=0;i<nibbles[3];i++){
            for(int j=0;j<8;j++){
                printf("%d",sprite[i][j]);
            }
            printf("\n");
        }
    }
    //it works.!!

    //now xor onto the screen. if the xor is ever 0 then we set the flag
//display[x][y]
    for(int i=0;i<nibbles[3];i++){
        for(int j=0;j<8;j++){
            if(chip8->display[(j+chip8->V[nibbles[1]])%64][(i+chip8->V[nibbles[2]])%32]==1&&sprite[i][j]==1){
                //set flag!!!
                //printf("collision!\n"); 
                collision=true;
            }
            chip8->display[(j+chip8->V[nibbles[1]])%64][(i+chip8->V[nibbles[2]])%32]=chip8->display[(j+chip8->V[nibbles[1]])%64][(i+chip8->V[nibbles[2]])%32]^sprite[i][j];
        }
    }

    if(collision){
        chip8->V[15]=1;
    }else{
        chip8->V[15]=0;
    }
}

void skipIfX(chip8* chip8, int *nibbles){
    //EX9E
    //checks the event currently. what is this window for oppurtunity?


    if(chip8->keypad[chip8->V[nibbles[1]]]){
        chip8->PC+=2;
    }

}

void skipIfNotX(chip8* chip8, int* nibbles){
    //EXA1
    //checks the event currently. what is this window for oppurtunity?
    //exhaust event poll. I will take in the last one as the 'input'. I will risk processing multiple inputs at once, but they should be processed fast enough so that they aren't actually an issue/ 

    //we could have a segafault here!
    
    if(!chip8->keypad[chip8->V[nibbles[1]]]){
        chip8->PC+=2;
    }
}

void setVXDT(chip8* chip8, int* nibbles){
    //FX07

    //just set it dont worry about the countdown. we'll count these down at the same time that we update the display.

    chip8->V[nibbles[1]]=chip8->DT;
}

void setDTVX(chip8* chip8, int* nibbles){
    //FX15
    chip8->DT=chip8->V[nibbles[1]];
}

void setSTVX(chip8* chip8, int* nibbles){
    //FX18
    chip8->ST=chip8->V[nibbles[1]];
}

void addVXI(chip8* chip8, int*  nibbles){
    //FX1E

    //Jump tables
    //ambiguous instruction.......!!;  it overflows on the amiga?

    //ill have to pass in the configs to ambiguous insturctions

    chip8->I+=chip8->V[nibbles[1]];
}

void getKey(configs* chip8Configs,chip8* chip8, int* nibbles,SDL_Event* windowEvent){
    //FX0A

    (void)nibbles;
    //wait for a key to be down and up!!!!!!!!!!!!!!!!!
    //gonna need a weird thing, a weird weird thing.

    //check if any are true. if none are true then we'll decrment the pc. if howevever there is one thats true do nothing
    ///configure the legit way l8r
    int pressedKeys[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    bool upDown=false;



    while(!upDown){
        handleInput(chip8,chip8Configs,windowEvent);

        //check whats down
        for(int i=0;i<16;i++){
            if(chip8->keypad[i]){
                pressedKeys[i]=1;
            }
            //check whats up
            if(!chip8->keypad[i]&&pressedKeys[i]==1){
                pressedKeys[i]=2;
            }

            //try inside and outside the loop
            if(pressedKeys[i]==2){
                upDown=true;
            }
        }

    }


}

void getFont(chip8* chip8, int* nibbles){
    //FX29

    //v[nibbles[1]] will be found in memory. algorithm or switch statemetn??

    chip8->I=(5*nibbles[1])+0x50;//this should work...    
}

void decimalVXI(chip8* chip8, int* nibbles){
    //FX33
    int tempVX = chip8->V[nibbles[1]];

    int ones = tempVX%10;
    tempVX/=10;
    
    int tens = tempVX%10;
    tempVX/=10;
    
    int hundreds = tempVX%10;

    //printf("\n\n[%d][%d][%d]\n\n",hundreds,tens,ones);

    //now write it to I!!!
    //ignore the big thing? maybe ill have to mod 256 everytime i use it
    //this can cause segfault!
    chip8->RAM[chip8->I%4096]=hundreds;
    chip8->RAM[(chip8->I+1)%4096]=tens;
    chip8->RAM[(chip8->I+2)%4096]=ones;
}

//two more!! that are ambiguougus
void storeRegisters(chip8* chip8, int* nibbles){
    //FX55
    //.....ok.

    for(int i=0;i<=nibbles[1];i++){
        chip8->RAM[(chip8->I+i)%4096]=chip8->V[i];
    }
}

void loadRegisters(chip8* chip8, int* nibbles){
    //FX65
    for(int i=0;i<=nibbles[1];i++){
        chip8->V[i]=chip8->RAM[(chip8->I+i)%4096];
    }
}