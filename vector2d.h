#pragma once

class Vector2D {
private:
    float m_x;
    float m_y;
public:
    Vector2D(): m_x(0.0),m_y(0.0) {}
    Vector2D(float x, float y): m_x(x),m_y(y) {}
    float getX() {return m_x;}
    float getY() {return m_y;}
    void setX(float x) {m_x = x;}
    void setY(float y) {m_y = y;}
    float length();
    Vector2D operator+(const Vector2D &v2);
    Vector2D operator-(const Vector2D &v2);
    Vector2D operator*(float scalar);
    Vector2D operator/(float scalar);
};
