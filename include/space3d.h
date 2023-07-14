//
// Created by 屠昊天 on 2023/7/14.
//

#pragma once

#include "canvas.h"
#include "vectors.h"

namespace NekoGL {
    class Camera3D {
    private:
        static Matrix4D calculateViewMatrix(float height, float width, float near);

    public:
        const float height;
        const float width;
        const float near;
        const Matrix4D viewMatrix;

        Camera3D();

        Camera3D(const Camera3D &rhs) = default;

        Camera3D(float height, float width, float near);
    };

    class Triangle3D {
    public:
        Vector3D points[3];

        void rotateX(float x);

        void rotateY(float y);

        void rotateZ(float z);

        void translate(float x, float y, float z);
    };

    class Space3D {
    private:
        Canvas *canvas;
        Camera3D camera;
    public:
        explicit Space3D(Canvas *canvas, Camera3D camera);

        void drawTriangle(const Triangle3D &triangle);
    };
}