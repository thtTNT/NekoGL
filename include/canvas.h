//
// Created by 屠昊天 on 2023/7/13.
//
#pragma once

#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF

#include <cstdint>

typedef uint32_t Color;

namespace NekoGL {
    class Canvas {
    private:
        void bresenhamLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Color color) const;
    public:
        uint32_t *buffer;
        const uint32_t width;
        const uint32_t height;

        Canvas(uint32_t width, uint32_t height);

        ~Canvas();

        void drawPixel(uint32_t x, uint32_t y, Color color) const;

        void drawFrame(uint32_t *pixels) const;

        void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color color);

        void clear() const;
    };
}
