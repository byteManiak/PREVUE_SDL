#pragma once
#include "screen_half.h"
#include "generator.h"
#include "entry.h"

class Lower_Half : public Screen_Half
{
public:
    Lower_Half(SDL_Renderer* renderer) : Screen_Half(renderer)
    {
        gen = new PREVUE_Generator();
        gen->Generate_Grid(renderer);
    }
    ~Lower_Half() { delete gen; }
    void Draw(SDL_Renderer* renderer) { gen->Draw(renderer); }
private:
    PREVUE_Generator *gen;
};
