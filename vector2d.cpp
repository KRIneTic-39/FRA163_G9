#include "vector2d.h"
#include <math.h>

Vector2D Vector2D::operator+(const Vector2D &v2){
    return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}
Vector2D Vector2D::operator-(const Vector2D &v2){
    return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}
Vector2D Vector2D::operator*(float scalar){
    return Vector2D(m_x * scalar, m_y * scalar);
}
Vector2D Vector2D::operator/(float scalar){
    return Vector2D(m_x / scalar, m_y / scalar);
}
float Vector2D::length(){
    return sqrt(m_x*m_x + m_y*m_y);
}
