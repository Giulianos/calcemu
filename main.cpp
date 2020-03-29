#include "fractionio.h"
#include "lineio.h"
#include "powerio.h"
#include "screen.h"
#include "screenbuffer.h"
#include <SDL2/SDL.h>
#include <time.h>

void
renderMath(MathIO* mathio, Screen* s)
{
  s->beginRendering();
  ScreenBuffer sb(128, 32);
  mathio->render(&sb);
  for (int x = 0; x < 128; x++) {
    for (int y = 0; y < 32; y++) {
      s->setPixel(x, y, sb.getPixel(x, y) ? 255 : 0);
    }
  }
}

int
main()
{
  Screen s;

  LineIO num((uint8_t*)"123");
  LineIO den((uint8_t*)"123");
  FractionIO frac(&num, &den);
  frac.enableCursor(true);

  bool run = true;

  uint32_t lastBlinkTime = 0;
  while (run) {
    uint32_t currentTime = SDL_GetTicks();
    // Time to blink
    if (currentTime - lastBlinkTime > 500) {
      frac.toggleCursorVisibility();
      lastBlinkTime = SDL_GetTicks();
    }

    // Render formula
    renderMath(&frac, &s);
    s.display();

    SDL_Event e;
    if (SDL_WaitEventTimeout(&e, 1)) {
      if (e.type == SDL_QUIT) {
        run = false;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_RIGHT:
            frac.moveCursor(MathIO::CursorDir::Right);
            frac.forceCursorShow();
            lastBlinkTime = SDL_GetTicks();
            break;
          case SDLK_LEFT:
            frac.moveCursor(MathIO::CursorDir::Left);
            frac.forceCursorShow();
            lastBlinkTime = SDL_GetTicks();
            break;
          case SDLK_DOWN:
            frac.moveCursor(MathIO::CursorDir::Down);
            frac.forceCursorShow();
            lastBlinkTime = SDL_GetTicks();
            break;
          case SDLK_UP:
            frac.moveCursor(MathIO::CursorDir::Up);
            frac.forceCursorShow();
            lastBlinkTime = SDL_GetTicks();
            break;
        }
      }
    }
  }
}
