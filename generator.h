#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "entry.h"

std::ifstream f;

class PREVUE_Generator
{
public:
    PREVUE_Generator();
    ~PREVUE_Generator();
    void Generate_Grid(SDL_Renderer*);
    void Draw(SDL_Renderer* renderer)
    {
        for(entries_it=entries.begin(); entries_it!=entries.end();)
        {
            if((*entries_it)->Update())
            {
                (*entries_it)->Draw(renderer);
                ++entries_it;
            }
            else entries_it = entries.erase(entries_it);
        }
        if(entries.size()==0)
        {
            for(entries_it=entries.begin(); entries_it!=entries.end(); ++entries_it) (*entries_it).reset();
            entries.clear();
            Generate_Grid(renderer);
        }
    }
    int Entries_On_Screen()
    {
        int cnt = 0;
        for(int i=0; entries[i]->y_pos()<768; i++) cnt++;
        return cnt;
    }
private:
    SDL_Color current, prev, section_cols[4];
    std::vector<std::unique_ptr<PREVUE_Entry>> entries;
    std::vector<std::unique_ptr<PREVUE_Entry>>::iterator entries_it;
    int offset_y, s_col;
};

PREVUE_Generator::PREVUE_Generator()
{
    s_col = 0;
    current = prev = {0, 0, 0, 0};
    section_cols[0] = {0, 0, 255, 0};
    section_cols[1] = {255, 0, 0, 0};
    section_cols[2] = {0, 255, 0, 0};
    section_cols[3] = {255, 255, 0, 0};
}

void PREVUE_Generator::Generate_Grid(SDL_Renderer* renderer)
{
    offset_y=768;

       system("tv_grab_uk_bleb --days 1 --output list.tmp "
       "&& tv_to_text list.tmp --output list.txt "
       "&& ./txt_to_prv list.txt list.prv "
       "&& rm list.tmp list.txt");

    f.open("list.prv");
    if(!f.is_open())
    {
        entries.emplace_back(new PREVUE_Section(current, section_cols[(++s_col)%4], offset_y));
        entries[entries.size()-1]->add_string("Hello, Joe! I'm testing");
        offset_y+=64;
        entries.emplace_back(new PREVUE_Section(current, section_cols[(++s_col)%4], offset_y));
        entries[entries.size()-1]->add_string("the width of these sections.");
        offset_y+=64;
        entries.emplace_back(new PREVUE_Section(current, section_cols[(++s_col)%4], offset_y));
        entries[entries.size()-1]->add_string("As you can see, these squares");
        offset_y+=64;
        entries.emplace_back(new PREVUE_Section(current, section_cols[(++s_col)%4], offset_y));
        entries[entries.size()-1]->add_string("never touch the text.");
        offset_y+=64;
        entries.emplace_back(new PREVUE_Section(current, section_cols[(++s_col)%4], offset_y));
        entries[entries.size()-1]->add_string("I'll make the real-time listings");
        offset_y+=64;
        entries.emplace_back(new PREVUE_Section(current, section_cols[(++s_col)%4], offset_y));
        entries[entries.size()-1]->add_string("with another program I'm writing");
        offset_y+=64;
        entries.emplace_back(new PREVUE_Section(current, section_cols[(++s_col)%4], offset_y));
        entries[entries.size()-1]->add_string("which is called txt_to_prv.");
        offset_y+=64;
    }
    else
    {
        std::string str;
        while(std::getline(f, str, '\n'))
        {
            std::istringstream istr(str);
            if(istr.str().substr(0,1)=="!")
            {
                if(istr.str().find("insert") != str.npos)
                {
                    std::string tok;
                    std::getline(istr, tok, '\"');
                    std::getline(istr, tok, '\"');
                    entries.emplace_back(new PREVUE_Section(current, section_cols[(++s_col)%4], offset_y));
                    entries[entries.size()-1]->add_string(tok);
                    offset_y+=64;
                }
            }
            else
            {
                entries.emplace_back(new PREVUE_Listing(current, section_cols[s_col%4], offset_y));
                std::string tok;
                while(std::getline(istr, tok, '\\'))
                {
                    entries[entries.size()-1]->add_string(tok);
                    offset_y+=64;
                }
            }
        }
    }
    for(auto &i : entries) i->Generate_Textures(renderer);
    f.close();
}
