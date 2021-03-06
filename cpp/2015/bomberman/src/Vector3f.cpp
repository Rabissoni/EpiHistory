/*
**  src/Vector3f.cpp
**  Bomberman
**
**  Created by Quentin PIDOUX on 30/04/12.
**  Copyright (c) 2012 EPITECH. All rights reserved.
*/

#include "../inc/Vector3f.hh"
#include <iostream>

Vector3f::Vector3f(void)
    : x(0.0f), y(0.0f), z(0.0f)
{
}
Vector3f::Vector3f(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

void Vector3f::setX(float x)
{
  this->x = x;
}

void Vector3f::setY(float y)
{
  this->y = y;
}

void Vector3f::setZ(float z)
{
  this->z = z;
}

void Vector3f::addX(float x)
{
  this->x += x;
}

void Vector3f::addY(float y)
{
  this->y += y;
}

void Vector3f::addZ(float z)
{
  this->z += z;
}
