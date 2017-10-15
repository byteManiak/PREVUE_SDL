#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "screen_half.h"

class Upper_Half : public Screen_Half
{
public:
    Upper_Half(SDL_Renderer* renderer) : Screen_Half(renderer)
    {
        r = {0, 0, 1024, 384};
        line_r={0, 380, 1024, 4};
        t = SDL_CreateTextureFromSurface(renderer, IMG_Load("assets/PREVUE.jpg"));
        line = SDL_CreateTextureFromSurface(renderer, IMG_Load("assets/white.bmp"));
        SDL_SetTextureColorMod(line, 0, 0, 255);
    }
    ~Upper_Half() { SDL_DestroyTexture(t); SDL_DestroyTexture(line); }
    void Draw(SDL_Renderer*);
private:
    SDL_Rect line_r;
    SDL_Texture *t, *line;
};

void Upper_Half::Draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, t, NULL, &r);
    SDL_RenderCopy(renderer, line, NULL, &line_r);
}
