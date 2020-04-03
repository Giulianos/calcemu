#include <SDL2/SDL.h>
#include <MathIO.h>
#include <LineIO.h>
#include <screenbuffer.h>
#include <screenbufferwindow.h>
#include "screen.h"

void
renderMath(MathIO* mathio, Screen* s)
{
  s->beginRendering();
  ScreenBuffer sb(128, 32);
  ScreenBufferWindow sbw(&sb, 1, 1);
  mathio->Render(&sbw);
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

  MathIO mainIO;
  mainIO.AttachCursor();

  bool run = true;

  while (run) {
    // Render formula
    renderMath(&mainIO, &s);
    s.display();

    SDL_Event e;
    if (SDL_WaitEventTimeout(&e, 1)) {
      if (e.type == SDL_QUIT) {
        run = false;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_RIGHT:
            mainIO.MoveCursor(MathIO::CursorDirection::Right);
            break;
          case SDLK_LEFT:
            mainIO.MoveCursor(MathIO::CursorDirection::Left);
            break;
          case SDLK_DOWN:
            mainIO.MoveCursor(MathIO::CursorDirection::Down);
            break;
          case SDLK_UP:
            mainIO.MoveCursor(MathIO::CursorDirection::Up);
            break;
          case SDLK_0:
            mainIO.InsertCharacter('0');
            break;
          case SDLK_1:
            mainIO.InsertCharacter('1');
            break;
        }
      }
    }
  }
}
