#include "screen.h"
#include <SDL2/SDL.h>
#include "fractionio.h"
#include "powerio.h"
#include "lineio.h"
#include "screenbuffer.h"

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
    LineIO den((uint8_t*)"7");
    LineIO exp((uint8_t*)"a");

    FractionIO base(&num, &den);
    PowerIO pow(&base, &exp);

    while(1) {
        SDL_Event e;
        if(SDL_WaitEvent(&e) && e.type == SDL_QUIT) {
            break;
        }
        renderMath(&pow, &s);
        s.display();
    }

}
