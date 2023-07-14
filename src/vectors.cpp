//
// Created by 屠昊天 on 2023/7/14.
//


#include "vectors.h"

namespace NekoGL {

    Vector3D::Vector3D(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3D Vector3D::clone() const {
        return {this->x, this->y, this->z};
    }

    void Vector3D::add(const Vector3D &rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
    }

    Vector3D Vector3D::operator+(const Vector3D &rhs) const {
        return {this->x + rhs.x, this->y + rhs.y, this->z + rhs.z};
    }

    Vector3D Vector3D::zero() {
        return {0, 0, 0};
    }

    Vector3D::Vector3D() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Vector4D::Vector4D(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Vector4D Vector4D::clone() const {
        return {this->x, this->y, this->z, this->w};
    }

    void Vector4D::add(const Vector4D &rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        this->w += rhs.w;
    }

    Vector4D Vector4D::operator+(const Vector4D &rhs) const {
        return {this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w};
    }

    Vector4D Vector4D::zero() {
        return {0, 0, 0, 0};
    }

    Vector4D::Vector4D() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
    }

    Vector4D Vector4D::fromVector3D(const Vector3D &vector) {
        return {vector.x, vector.y, vector.z, 1};
    }

    Matrix4D::Matrix4D(Vector4D baseVectors[4]) {
        this->baseVectors[0] = baseVectors[0];
        this->baseVectors[1] = baseVectors[1];
        this->baseVectors[2] = baseVectors[2];
        this->baseVectors[3] = baseVectors[3];
    }

    Vector4D Matrix4D::operator*(const Vector4D &rhs) const {
        return {baseVectors[0].x * rhs.x +
                baseVectors[0].y * rhs.y +
                baseVectors[0].z * rhs.z +
                baseVectors[0].w * rhs.w,
                baseVectors[1].x * rhs.x +
                baseVectors[1].y * rhs.y +
                baseVectors[1].z * rhs.z +
                baseVectors[1].w * rhs.w,
                baseVectors[2].x * rhs.x +
                baseVectors[2].y * rhs.y +
                baseVectors[2].z * rhs.z +
                baseVectors[2].w * rhs.w,
                baseVectors[3].x * rhs.x +
                baseVectors[3].y * rhs.y +
                baseVectors[3].z * rhs.z +
                baseVectors[3].w * rhs.w};
    }

    Matrix4D Matrix4D::fromRaw(float (*raw)[4]) {
        Vector4D baseVectors[4];
        for (int i = 0; i < 4; i++) {
            baseVectors[i] = Vector4D(raw[i][0], raw[i][1], raw[i][2], raw[i][3]);
        }
        return Matrix4D(baseVectors);
    }

    Matrix3D::Matrix3D(Vector3D *baseVectors) {
        this->baseVectors[0] = baseVectors[0];
        this->baseVectors[1] = baseVectors[1];
        this->baseVectors[2] = baseVectors[2];
    }

    Vector3D Matrix3D::operator*(const Vector3D &rhs) const {
        return {baseVectors[0].x * rhs.x +
                baseVectors[0].y * rhs.y +
                baseVectors[0].z * rhs.z,
                baseVectors[1].x * rhs.x +
                baseVectors[1].y * rhs.y +
                baseVectors[1].z * rhs.z,
                baseVectors[2].x * rhs.x +
                baseVectors[2].y * rhs.y +
                baseVectors[2].z * rhs.z};
    }

    Matrix3D Matrix3D::fromRaw(float (*raw)[3]) {
        Vector3D baseVectors[3];
        for (int i = 0; i < 3; i++) {
            baseVectors[i] = Vector3D(raw[i][0], raw[i][1], raw[i][2]);
        }
        return Matrix3D(baseVectors);
    }
}