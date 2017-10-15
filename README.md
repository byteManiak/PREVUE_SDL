# PREVUE_SDL
A PREVUE Guide remake written in SDL2 that works only in the UK (for now).

This program has the following dependencies:
- SDL2 - SDL2_image, SDL2_ttf, SDL2_mixer
- perl - Archive::Zip, IO::Scalar, Date::Manip
- XMLTV - tv_grab_uk_bleb (configure it before using PREVUE)
- txt_to_prv (see my GitHub)

To compile the program:
```g++ main.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer```
