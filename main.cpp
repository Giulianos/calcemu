#include "screen.h"
#include <SDL2/SDL.h>
#include "fractionio.h"
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

    LineIO den("128");
    LineIO num("12");

    FractionIO fraction(&den, &num);

    while(1) {
        SDL_Event e;
        if(SDL_WaitEvent(&e) && e.type == SDL_QUIT) {
            break;
        }
        renderMath(&fraction, &s);
        s.display();
    }

}
