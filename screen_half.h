#pragma once

class Screen_Half
{
public:
    Screen_Half(SDL_Renderer*) {}
    ~Screen_Half() {}
    virtual void Update() {}
    virtual void Draw(SDL_Renderer*) {}
protected:
    SDL_Rect r;
};
