#pragma once
#include <iostream>

class vect2 {
private:
    int x, y;

public:
    // Constructors
    vect2() : x(0), y(0) {}
    vect2(int a, int b) : x(a), y(b) {}
    vect2(const vect2& other) : x(other.x), y(other.y) {}

    // Assignment
    vect2& operator=(const vect2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    // Index operator
    int& operator[](int idx) {
        return (idx == 0) ? x : y;
    }
    const int& operator[](int idx) const {
        return (idx == 0) ? x : y;
    }

    // Unary minus
    vect2 operator-() const {
        return vect2(-x, -y);
    }

    // Arithmetic with vectors
    vect2 operator+(const vect2& other) const {
        return vect2(x + other.x, y + other.y);
    }
    vect2 operator-(const vect2& other) const {
        return vect2(x - other.x, y - other.y);
    }
    vect2 operator*(int s) const {
        return vect2(x * s, y * s);
    }

    // Compound assignments
    vect2& operator+=(const vect2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    vect2& operator-=(const vect2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    vect2& operator*=(int s) {
        x *= s;
        y *= s;
        return *this;
    }

    // Comparison
    bool operator==(const vect2& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const vect2& other) const {
        return !(*this == other);
    }

    // Prefix ++ / --
    vect2& operator++() {
        ++x; ++y;
        return *this;
    }
    vect2& operator--() {
        --x; --y;
        return *this;
    }

    // Postfix ++ / --
    vect2 operator++(int) {
        vect2 temp(*this);
        ++(*this);
        return temp;
    }
    vect2 operator--(int) {
        vect2 temp(*this);
        --(*this);
        return temp;
    }

    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const vect2& v) {
        os << "{" << v.x << ", " << v.y << "}";
        return os;
    }
};

// Scalar * vector
inline vect2 operator*(int s, const vect2& v) {
    return vect2(v[0] * s, v[1] * s);
}