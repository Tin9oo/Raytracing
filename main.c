#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000

struct Circle {
    double x;
    double y;
    double radius;
};

void FillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color) {
    double radius_squared = pow(circle.radius, 2);
    for(double x = circle.x - circle.radius; x <= circle.x + circle.radius; x++) {
        for(double y = circle.y - circle.radius; y <= circle.y + circle.radius; y++) {
            double distance_squared = pow(x-circle.x, 2) + pow(y-circle.y, 2);
            if(distance_squared < radius_squared) {
                SDL_Rect pixel = (SDL_Rect){x, y, 1, 1};
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // SDL 창 생성
    SDL_Window* window = SDL_CreateWindow(
        "RayTracing",                // 창 제목
        SDL_WINDOWPOS_UNDEFINED,     // x 위치
        SDL_WINDOWPOS_UNDEFINED,     // y 위치
        WIDTH, HEIGHT,                    // 너비, 높이
        SDL_WINDOW_SHOWN             // 창 표시
    );

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_Rect rect = (SDL_Rect) {200, 200, 200, 200};
    SDL_FillRect(surface, &rect, COLOR_WHITE);

    struct Circle circle = {200, 200, 80};
    struct Circle shadow_circle = {650, 300, 140};
    SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};

    // 이벤트 루프
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }

            if(e.type == SDL_MOUSEMOTION && e.motion.state != 0) {
                circle.x = e.motion.x;
                circle.y = e.motion.y;
            }
        }

        SDL_UpdateWindowSurface(window);

        SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
        FillCircle(surface, circle, COLOR_WHITE);
        FillCircle(surface, shadow_circle, COLOR_WHITE);

        // SDL_Delay(10);
    }

    // SDL 종료
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
