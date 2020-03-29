#include "screen.h"
#include <SDL2/SDL.h>
#include "fractionio.h"
#include "powerio.h"
#include "lineio.h"
#include "screenbuffer.h"
#include <time.h>

void renderMath(MathIO * mathio, Screen * s) {
    s->beginRendering();
    ScreenBuffer sb(128, 32);
    mathio->render(&sb);
    for (int x=0; x < 128; x++) {
        for (int y=0; y < 32; y++) {
            s->setPixel(x, y, sb.getPixel(x,y) ? 255 : 0);
        }
    }
}

int main() {
    Screen s;

    LineIO num((uint8_t*)"123");
    num.setCompactMode(true);
    num.enableCursor(true);

    bool run = true;

    uint32_t lastBlinkTime = 0;
    while(run) {
	uint32_t currentTime = SDL_GetTicks();
	// Time to blink
	if (currentTime  - lastBlinkTime > 500) {
		num.toggleCursorVisibility();
		lastBlinkTime = SDL_GetTicks();
	}

	// Render formula
	renderMath(&num, &s);
	s.display();

        SDL_Event e;
        if(SDL_WaitEventTimeout(&e, 1)) {
		if(e.type == SDL_QUIT) {
			run = false;
		} else if(e.type == SDL_KEYDOWN) {
			switch(e.key.keysym.sym) {
				case SDLK_RIGHT:
					num.moveCursor(MathIO::CursorDir::Right);
					num.forceCursorShow();
					lastBlinkTime = SDL_GetTicks();
					break;
				case SDLK_LEFT:
					num.moveCursor(MathIO::CursorDir::Left);
					num.forceCursorShow();
					lastBlinkTime = SDL_GetTicks();
					break;
			}
		}
        }
    }

}
