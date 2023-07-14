//
// Created by 屠昊天 on 2023/7/13.
//

#include <canvas.h>
#include <cstring>

// Cohen-Sutherland clipping algorithm
#define INSIDE  0
#define LEFT    1
#define RIGHT   2
#define BOTTOM  4
#define TOP     8

typedef uint8_t OutCode;

OutCode computeOutCode(int32_t x, int32_t y, int32_t xMin, int32_t yMin, int32_t xMax, int32_t yMax) {
    OutCode code = INSIDE;
    if (x < xMin) {
        code |= LEFT;
    } else if (x > xMax) {
        code |= RIGHT;
    }
    if (y < yMin) {
        code |= BOTTOM;
    } else if (y > yMax) {
        code |= TOP;
    }
    return code;
}

bool
clipLine(int32_t &x1, int32_t &y1, int32_t &x2, int32_t &y2, int32_t xMin, int32_t yMin, int32_t xMax, int32_t yMax) {
    OutCode outCode1 = computeOutCode(x1, y1, xMin, yMin, xMax, yMax);
    OutCode outCode2 = computeOutCode(x2, y2, xMin, yMin, xMax, yMax);
    while (true) {
        if (!(outCode1 | outCode2)) {
            return true;
        } else if (outCode1 & outCode2) {
            return false;
        } else {
            int32_t x, y;
            OutCode outCode = outCode1 ? outCode1 : outCode2;
            if (outCode & TOP) {
                x = x1 + (x2 - x1) * (yMax - y1) / (y2 - y1);
                y = yMax;
            } else if (outCode & BOTTOM) {
                x = x1 + (x2 - x1) * (yMin - y1) / (y2 - y1);
                y = yMin;
            } else if (outCode & RIGHT) {
                y = y1 + (y2 - y1) * (xMax - x1) / (x2 - x1);
                x = xMax;
            } else {
                y = y1 + (y2 - y1) * (xMin - x1) / (x2 - x1);
                x = xMin;
            }
            if (outCode == outCode1) {
                x1 = x;
                y1 = y;
                outCode1 = computeOutCode(x1, y1, xMin, yMin, xMax, yMax);
            } else {
                x2 = x;
                y2 = y;
                outCode2 = computeOutCode(x2, y2, xMin, yMin, xMax, yMax);
            }
        }
    }
}

namespace NekoGL {
    Canvas::Canvas(uint32_t width, uint32_t height) : width(width), height(height) {
        buffer = new uint32_t[width * height];
    }

    void Canvas::drawFrame(uint32_t *pixels) const {
        for (uint32_t x = 0; x < width; x++) {
            for (uint32_t y = 0; y < height; y++) {
                drawPixel(x, y, pixels[y * width + x]);
            }
        }
    }

    void Canvas::drawPixel(uint32_t x, uint32_t y, Color color) const {
        buffer[y * width + x] = color;
    }

    void Canvas::clear() const {
        memset(buffer, 0, width * height * sizeof(uint32_t));
    }

    Canvas::~Canvas() {
        delete[] buffer;
    }

    void Canvas::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color color) {
        if (clipLine(x1, y1, x2, y2, 0, 0, (int32_t) width - 1, (int32_t) height - 1)) {
            if (x2 >= x1) {
                bresenhamLine(x1, y1, x2, y2, color);
            } else {
                bresenhamLine(x2, y2, x1, y1, color);
            }
        }
    }

    void Canvas::bresenhamLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Color color) const {
        uint32_t x = x1;
        uint32_t y = y1;
        bool y_increase = y2 > y1;
        int64_t dx = x2 - x1;
        int64_t dy = y_increase ? y2 - y1 : y1 - y2;
        int64_t eps = -dx;
        while (x <= x2) {
            uint32_t pixelAmount;
            if (dx == 0) {
                pixelAmount = dy;
            } else if (eps >= 0) {
                pixelAmount = eps / 2 / dx + 1;
                eps -= pixelAmount * 2 * dx;
                y = y_increase ? y + 1 : y - 1;
            } else {
                pixelAmount = 1;
            }
            for (uint32_t i = 0; i < pixelAmount; i++) {
                if (i != 0) {
                    y = y_increase ? y + 1 : y - 1;
                }
                drawPixel(x, y, color);
            }
            eps += 2 * dy;
            x++;
        }
    }
}