#include <chip8.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

bool init_sdl(SDL_Window* window, SDL_Renderer* renderer, configs configs){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        SDL_Log("Could not initialize SDL subsystems! %s\n", SDL_GetError());
        return false;
    }

    SDL_CreateWindowAndRenderer(W*configs.scaleFactor,H*configs.scaleFactor,0,&window,&renderer);

    if(window==NULL){
        printf("Something went wrong, could not create window.\n");
        return false;
    }

    if(renderer==NULL){
        printf("Something went wrong, could not create renderer.\n");
        return false;
    }

    SDL_RenderSetScale(renderer,configs.scaleFactor,configs.scaleFactor);

    return true;
}

void final_cleanup(void){
    SDL_Quit();
}

void updateDisplay(chip8* chip8,configs chip8Configs, SDL_Renderer ** renderer){
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            //hopefully this doesnt take too long 
            //maybe there is a faster way
            if(chip8->display[j][i]==0){
                SDL_SetRenderDrawColor(*renderer,0,0,0,255);
            }else if(chip8->display[j][i]==1){
                SDL_SetRenderDrawColor(*renderer,chip8Configs.r,chip8Configs.g,chip8Configs.b,255);
            }else{//maybe dont do an else. 
                //error
            }
            
            SDL_RenderDrawPoint(*renderer,j,i);
        }
    }

    SDL_RenderPresent(*renderer);
}