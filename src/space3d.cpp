//
// Created by 屠昊天 on 2023/7/14.
//

#include "space3d.h"
#include "neko_math.h"

namespace NekoGL {

    Space3D::Space3D(Canvas *canvas, Camera3D camera) : camera(camera) {
        this->canvas = canvas;
    }

    void Space3D::drawTriangle(const Triangle3D &triangle, Color color) {
        Vector4D points[3] = {
                Vector4D::fromVector3D(triangle.points[0]),
                Vector4D::fromVector3D(triangle.points[1]),
                Vector4D::fromVector3D(triangle.points[2])};
        for (auto &point: points) {
            point = this->camera.viewMatrix * point;
            point.x /= point.w;
            point.y /= point.w;
            point.z /= point.w;
            point.w /= point.w;
            point.y *= -1;
            point.x += 1;
            point.y += 1;
            point.x /= 2;
            point.y /= 2;
        }
        this->canvas->drawLine((int32_t) (points[0].x * (float) this->canvas->width),
                               (int32_t) (points[0].y * (float) this->canvas->height),
                               (int32_t) (points[1].x * (float) this->canvas->width),
                               (int32_t) (points[1].y * (float) this->canvas->height), color);
        this->canvas->drawLine((int32_t) (points[1].x * (float) this->canvas->width),
                               (int32_t) (points[1].y * (float) this->canvas->height),
                               (int32_t) (points[2].x * (float) this->canvas->width),
                               (int32_t) (points[2].y * (float) this->canvas->height), color);
        this->canvas->drawLine((int32_t) (points[2].x * (float) this->canvas->width),
                               (int32_t) (points[2].y * (float) this->canvas->height),
                               (int32_t) (points[0].x * (float) this->canvas->width),
                               (int32_t) (points[0].y * (float) this->canvas->height), color);

    }

    Camera3D::Camera3D(float height, float width, float near)
            : height(height), width(width), near(near), viewMatrix(calculateViewMatrix(height, width, near)) {};

    Matrix4D Camera3D::calculateViewMatrix(float height, float width, float near) {
        float raw[4][4]{{near / width, 0,             0, 0},
                        {0,            near / height, 0, 0},
                        {0,            0,             1, 0},
                        {0,            0,             1, 0}};
        return Matrix4D::fromRaw(raw);
    }

    Camera3D::Camera3D() : height(0), width(0), near(0), viewMatrix(calculateViewMatrix(0, 0, 0)) {
    }


    void Triangle3D::rotateX(float x) {
        float raw[3][3]{{1, 0,       0},
                        {0, cos(x),  sin(x)},
                        {0, -sin(x), cos(x)}};
        Matrix3D matrix = Matrix3D::fromRaw(raw);
        for (auto &point: this->points) {
            point = matrix * point;
        }
    }

    void Triangle3D::rotateY(float y) {
        float raw[3][3]{{cos(y), 0, -sin(y)},
                        {0,      1, 0},
                        {sin(y), 0, cos(y)}};
        Matrix3D matrix = Matrix3D::fromRaw(raw);
        for (auto &point: this->points) {
            point = matrix * point;
        }
    }

    void Triangle3D::rotateZ(float z) {
        float raw[3][3]{{cos(z),  sin(z), 0},
                        {-sin(z), cos(z), 0},
                        {0,       0,      1}};
        Matrix3D matrix = Matrix3D::fromRaw(raw);
        for (auto &point: this->points) {
            point = matrix * point;
        }
    }

    void Triangle3D::translate(float x, float y, float z) {
        for (auto &point: this->points) {
            point.x += x;
            point.y += y;
            point.z += z;
        }
    }

}