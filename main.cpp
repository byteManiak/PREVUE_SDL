#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>
#include "screen_half.h"
#include "upper_half.h"
#include "lower_half.h"

const Uint8* state = SDL_GetKeyboardState(NULL);
TTF_Font* fon;

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    TTF_Init();

    Mix_Music* prevue_music = Mix_LoadMUS("assets/prevue.ogg");
    Mix_PlayMusic(prevue_music, -1);

    SDL_Window *TV = SDL_CreateWindow("PREVUE GUIDE", 20, 20, 1024, 768, 1);
    SDL_Renderer *renderer = SDL_CreateRenderer(TV, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderSetLogicalSize(renderer, 1024, 768);

    fon = TTF_OpenFont("assets/PrevueGrid.ttf", 56);
    std::vector<std::unique_ptr<Screen_Half>> halves;
    halves.emplace_back(new Upper_Half(renderer));
    halves.emplace_back(new Lower_Half(renderer));

    while(!state[SDL_SCANCODE_ESCAPE])
    {
        SDL_RenderClear(renderer);
        halves[1]->Draw(renderer);
        halves[0]->Draw(renderer);
        SDL_RenderPresent(renderer);
        SDL_PumpEvents();
    }

    TTF_CloseFont(fon);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(TV);
    SDL_Quit();
    return 0;
}
