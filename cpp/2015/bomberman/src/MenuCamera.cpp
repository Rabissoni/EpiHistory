/*
**  src/MenuCamera.cpp
**  Bomberman
**
**  Created by Quentin PIDOUX on 30/04/12.
**  Copyright (c) 2012 EPITECH. All rights reserved.
*/

#include "../inc/MenuCamera.hh"
#include "../inc/Vector3f.hh"
#include <iostream>

MenuCamera::MenuCamera()
  : position_(0.0f, 30.0f, 6.0f), rotation_(0.0f, 0.0f, 0.0f)
{}

MenuCamera::~MenuCamera()
{}

void MenuCamera::initialize()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f, 800.0f/600.0f, 1.0f, 10000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(position_.x, position_.y, position_.z,
	    rotation_.x, rotation_.y, rotation_.z,
	    0.0f, 1.0f, 0.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void  MenuCamera::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  (void)gameClock;
  (void)input;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f, 800.0f/600.0f, 1.0f, 10000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(position_.x, position_.y, position_.z,
	    rotation_.x, rotation_.y, rotation_.z,
	    0.0f, 1.0f, 0.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void MenuCamera::setpos(float x, float y, float z)
{
  this->position_.setX(x);
  this->position_.setY(y);
  this->position_.setZ(z);
}

void MenuCamera::setrot(float x, float y, float z)
{
  this->rotation_.setX(x);
  this->rotation_.setY(y);
  this->rotation_.setZ(z);
}
