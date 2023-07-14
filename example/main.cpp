//
// Created by 屠昊天 on 2023/7/13.
//
#include "canvas.h"
#include "canvas.h"
#include "space3d.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

int height = 600;
int width = 800;

int main() {
    NekoGL::Canvas screen = NekoGL::Canvas(width, height);
    auto space3D = NekoGL::Space3D(&screen,NekoGL::Camera3D(600, 800, 100));

    // 初始化SDL
    SDL_Init(SDL_INIT_VIDEO);

    // 创建窗口
    SDL_Window *window = SDL_CreateWindow(
            "C++ Window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_SHOWN
    );

    // 创建渲染器
    auto renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
    );

    // 创建纹理
    auto texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            width,
            height
    );


    // 更新纹理

    bool quit = false;
    int rotate = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        screen.clear();
        rotate += 1;
        NekoGL::Triangle3D triangle3D = {
                {
                        {-100, 150, 0},
                        {100, 150, 0},
                        {0, 0, 0}
                }
        };
        triangle3D.rotateX((float)rotate / 180.0f * M_PI);
        triangle3D.translate(0,0,200);
        space3D.drawTriangle(triangle3D);
        SDL_UpdateTexture(texture, nullptr, screen.buffer, width * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    // 释放资源
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}