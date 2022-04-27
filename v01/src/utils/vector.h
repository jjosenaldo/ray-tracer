#include <cmath>
#include <stdlib.h>
#include <iostream>

class Vec3 {

    private:
        float e[3];

    public:
        Vec3() {}

        Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
        float getX () const { return e[0]; }
        float getY () const { return e[1]; }
        float getZ () const { return e[2]; }
        float getR () const { return e[0]; }
        float getG () const { return e[1]; }
        float getB () const { return e[2]; }

        const Vec3& operator+() const { return *this; }
        Vec3 operator-() const { return Vec3(-e[0],-e[1],-e[2]); }
        float operator[](int i) const { return e[i]; }
        float& operator[](int i) { return e[i]; }

        Vec3& operator+=(const Vec3 &v2);
        Vec3& operator-=(const Vec3 &v2);
        Vec3& operator*=(const Vec3 &v2);
        Vec3& operator/=(const Vec3 &v2);
        Vec3& operator*=(const float t);
        Vec3& operator/=(const float t);

        float length() const {
            return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
        }
        float squared_length() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
        void make_unit_vector();

        std::istream& operator>>(std::istream &is, Vec3 &t) {
            is >> t.e[0] >> t.e[1] >> t.e[2];
            return is;
        }

        std::ostream& operator<<(std::ostream &os, Vec3 &t) {
            os << t.e[0] << " " << t.e[1] << " " << t.e[2];
            return os;
        }
};

inline void Vec3::make_unit_vector() {
    float k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k; e[1] *= k; e[2] *= k;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ());
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.getX() - v2.getX(), v1.getY() - v2.getY(), v1.getZ() - v2.getZ());
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.getX() * v2.getX(), v1.getY() * v2.getY(), v1.getZ() * v2.getZ());
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.getX() / v2.getX(), v1.getY() / v2.getY(), v1.getZ() / v2.getZ());
}

inline Vec3 operator*(float t, const Vec3 &v) {
    return Vec3(t * v.getX(), t * v.getY(), t * v.getZ());
}

inline Vec3 operator*(const Vec3 &v, float t) {
    return Vec3(t * v.getX(), t * v.getY(), t * v.getZ());
}

inline Vec3 operator/(const Vec3 v, float t) {
    return Vec3(v.getX() / t, v.getY() / t, v.getZ() / t);
}

inline float dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
    return Vec3( (v1.getY()*v2.getZ() - v1.getZ()*v2.getY()),
                (-(v1.getX()*v2.getZ() - v1.getZ()*v2.getX())),
                (v1.getX()*v2.getY() - v1.getY()*v2.getX())
            );
}

inline Vec3& Vec3::operator+=(const Vec3 &v) {
    e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2];
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3 &v) {
    e[0] -= v.e[0]; e[1] -= v.e[1]; e[2] -= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 &v) {
    e[0] *= v.e[0]; e[1] *= v.e[1]; e[2] *= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3 &v) {
    e[0] /= v.e[0]; e[1] /= v.e[1]; e[2] /= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const float t) {
    e[0] *= t; e[1] *= t; e[2] *= t;
    return *this;
}

inline Vec3& Vec3::operator/=(const float t) {
    float k = 1.0 / t;
    e[0] *= k; e[1] *= k; e[2] *= k;
    return *this;
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}
