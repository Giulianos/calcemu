#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

class Screen
{
  SDL_Renderer* _r;
  SDL_Window* _w;

public:
  Screen();
  ~Screen();

  void setPixel(int x, int y, unsigned char value);
  void beginRendering();
  void clear();
  void display();
};

#endif
