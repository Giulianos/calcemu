#include "screen.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define EMU_PIXEL_SIZE 5
#define EMU_PIXEL_MARGIN 0

#define WINDOW_WIDTH SCREEN_WIDTH*(EMU_PIXEL_MARGIN + EMU_PIXEL_SIZE) - 1
#define WINDOW_HEIGHT SCREEN_HEIGHT*(EMU_PIXEL_MARGIN + EMU_PIXEL_SIZE) - 1

Screen::Screen()
{
  SDL_Init(SDL_INIT_VIDEO);

  _w = SDL_CreateWindow(
    "CalcEmu",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH * (EMU_PIXEL_SIZE + EMU_PIXEL_MARGIN) - EMU_PIXEL_MARGIN,
    SCREEN_HEIGHT * (EMU_PIXEL_SIZE + EMU_PIXEL_MARGIN) - EMU_PIXEL_MARGIN,
    0);
  _r = SDL_CreateRenderer(_w, -1, SDL_RENDERER_ACCELERATED);

  SDL_RenderClear(_r);
  SDL_RenderPresent(_r);
}

void
Screen::beginRendering()
{
  SDL_SetRenderDrawColor(_r, 0, 0, 0, 255);
  SDL_RenderClear(_r);
}

void
Screen::setPixel(int x, int y, unsigned char value)
{
  SDL_Rect rect;
  rect.x = x * (EMU_PIXEL_SIZE + EMU_PIXEL_MARGIN);
  rect.y = y * (EMU_PIXEL_SIZE + EMU_PIXEL_MARGIN);

  rect.w = EMU_PIXEL_SIZE;
  rect.h = EMU_PIXEL_SIZE;

  SDL_SetRenderDrawColor(_r, value, value, value, 255);
  SDL_RenderFillRect(_r, &rect);
}

void
Screen::clear()
{
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
      setPixel(x, y, 255);
    }
  }
}

void
Screen::display()
{
  SDL_RenderPresent(_r);
}

Screen::~Screen()
{
  SDL_DestroyRenderer(_r);
  SDL_DestroyWindow(_w);
}
