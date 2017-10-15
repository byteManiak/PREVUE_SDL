#pragma once
#include <vector>
#include <string>
#include <SDL2/SDL_ttf.h>

extern TTF_Font* fon;

class PREVUE_Entry
{
public:
    PREVUE_Entry(SDL_Color fil, SDL_Color border, int offset_y)
    {
        fil_col = fil;
        border_col = border;
        y = offset_y;
    }
    ~PREVUE_Entry()
    {
        for(std::vector<SDL_Texture*>::iterator it = elems.begin(); it!=elems.end(); ++it)
            SDL_DestroyTexture(*it);
    }

    int y_pos() { return y; }

    virtual void Generate_Textures(SDL_Renderer*) {}
    virtual void add_string(std::string) {}

    bool Update()
    {
        if(rects[rects.size()-1].y>384-rects[rects.size()-1].h)
        {
            for(auto&& i : rects) i.y--;
            return true;
        }
        return false;
    }

    void Draw(SDL_Renderer* renderer)
    {
        for(unsigned i=0; i<elems.size(); i++)
            SDL_RenderCopy(renderer, elems[i], NULL, &rects[i]);
    }

protected:
    std::vector<SDL_Texture*> elems;
    std::vector<SDL_Rect> rects;
    int y;
    SDL_Color fil_col, border_col;
};

class PREVUE_Section : public PREVUE_Entry
{
public:
    PREVUE_Section(SDL_Color fil_col, SDL_Color border_col, int offset_y) : PREVUE_Entry(fil_col, border_col, offset_y) {}
    ~PREVUE_Section()
    {
        for(std::vector<SDL_Texture*>::iterator it = elems.begin(); it!=elems.end(); ++it)
            SDL_DestroyTexture(*it);
    }

    void add_string(std::string t)
    {
        for(unsigned i=0; i<t.size(); i++)
            str.push_back(t[i]);
    }

    void Generate_Textures(SDL_Renderer* renderer)
    {
        SDL_Surface *temp = TTF_RenderText_Solid(fon, str.c_str(), {255, 255, 255, 0});
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, temp);
        elems.emplace_back(texture);
        rects.push_back({512-(Uint16)str.length()*12, y+12, (Uint16)str.length()*24, 48});
        SDL_FreeSurface(temp);

        temp = IMG_Load("assets/white.bmp");

        texture = SDL_CreateTextureFromSurface(renderer, temp);
        elems.emplace_back(texture);
        SDL_SetTextureColorMod(elems[1], border_col.r, border_col.g, border_col.b);
        rects.push_back({0, y+60, 1024, 4});

        for(unsigned i=0; i<7; i++)
        {
            texture = SDL_CreateTextureFromSurface(renderer, temp);
            elems.emplace_back(texture);
            SDL_SetTextureColorMod(elems[elems.size()-1], border_col.r, border_col.g, border_col.b);
            rects.push_back({438-14*str.size(), y+(int)i*8+4, 64, 4});

            texture = SDL_CreateTextureFromSurface(renderer, temp);
            elems.emplace_back(texture);
            SDL_SetTextureColorMod(elems[elems.size()-1], border_col.r, border_col.g, border_col.b);
            rects.push_back({522+14*str.size(), y+(int)i*8+4, 64, 4});
        }

        SDL_FreeSurface(temp);
    }

private:
    std::string str;
};

class PREVUE_Listing : public PREVUE_Entry
{
public:
    PREVUE_Listing(SDL_Color fil_col, SDL_Color border_col, int offset_y) : PREVUE_Entry(fil_col, border_col, offset_y) {}
    ~PREVUE_Listing()
    {
        for(std::vector<SDL_Texture*>::iterator it = elems.begin(); it!=elems.end(); ++it)
            SDL_DestroyTexture(*it);
    }

    void add_string(std::string t)
    {
        std::string temp;
        for(unsigned i=0; i<t.size(); i++) temp.push_back(t[i]);
        text.push_back(temp);
    }
    void Generate_Textures(SDL_Renderer* renderer)
    {
        int i;
        SDL_Surface *temp = IMG_Load("assets/white.bmp");
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, temp);
        elems.emplace_back(texture);
        SDL_SetTextureColorMod(elems[0], fil_col.r, fil_col.g, fil_col.b);
        rects.push_back({0, y, 1024, 0});
        SDL_FreeSurface(temp);

        for(i=0; i<text.size(); i++)
        {
            temp = TTF_RenderText_Solid(fon, text[i].c_str(), {255, 255, 255, 0});
            texture = SDL_CreateTextureFromSurface(renderer, temp);
            elems.emplace_back(texture);
            rects.push_back({24, (int)y+(int)i*64+12, (int)text[i].length()*24, 48});
            rects[0].h+=64;
            SDL_FreeSurface(temp);
        }

        temp = IMG_Load("assets/white.bmp");
        texture = SDL_CreateTextureFromSurface(renderer, temp);
        elems.emplace_back(texture);
        SDL_SetTextureColorMod(elems[elems.size()-1], border_col.r, border_col.g, border_col.b);
        rects.push_back({0, y+(int)i*64-4, 1024, 4});
        rects[0].h-=4;
        SDL_FreeSurface(temp);
    }
private:
    std::vector<std::string> text;
};
