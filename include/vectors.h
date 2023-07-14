//
// Created by 屠昊天 on 2023/7/14.
//
#pragma once

#include <cstdint>

namespace NekoGL {
    class Vector3D {
    public:
        float x;
        float y;
        float z;

        Vector3D();

        Vector3D(float x, float y, float z);

        [[nodiscard]] Vector3D clone() const;

        void add(const Vector3D &rhs);

        Vector3D operator+(const Vector3D &rhs) const;

        static Vector3D zero();

    };

    class Matrix3D {
    public:
        Vector3D baseVectors[3];

        explicit Matrix3D(Vector3D baseVectors[3]);

        Vector3D operator*(const Vector3D &rhs) const;

        static Matrix3D fromRaw(float raw[3][3]);
    };

    class Vector4D {
    public:
        float x;
        float y;
        float z;
        float w;

        Vector4D(float x, float y, float z, float w);

        Vector4D();

        [[nodiscard]] Vector4D clone() const;

        void add(const Vector4D &rhs);

        Vector4D operator+(const Vector4D &rhs) const;

        static Vector4D zero();

        static Vector4D fromVector3D(const Vector3D &vector);
    };

    class Matrix4D {
    public:
        Vector4D baseVectors[4];

        explicit Matrix4D(Vector4D baseVectors[4]);

        Vector4D operator*(const Vector4D &rhs) const;

        static Matrix4D fromRaw(float raw[4][4]);
    };
}