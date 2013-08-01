/*
**  src/Character.cpp
**  Bomberman
**
**  Created by Evan HERVE on 03/05/12.
**  Copyright (c) 2012 EPITECH. All rights reserved.
*/

#include "../inc/Character.hh"
#include "../inc/Fire.hh"

Character::Character(map::map *map, Setting *setting, int nb, Bombe *bomb)
  : Player(map, bomb)
{
  int		i = 0;
  int		j = 0;
  bool		end = false;

  this->choice = nb;
  this->Up = setting->Up;
  this->Down = setting->Down;
  this->Right = setting->Right;
  this->Left = setting->Left;
  this->Space = setting->Space;
  this->camera_ = new MenuCamera();
  this->map = map;
  this->position_ = new Vector3f(0.00f, 0.0f, 0.00f);
  this->rotation_ = new Vector3f(0.00f, 0.0f, 0.00f);

  for (i = 0; i < map->getWidth() && end == false; i++)
    {
      for(j = 0; j < map->getLength() && end == false; j++)
	{
	  if (map->getPos(i, j) == 1)
	    {
	      this->setPosY(i);
	      this->setPosX(j);
	      map->setPos(9,j, i);
	      end = true;
	    }
	}
    }
}

Character::~Character()
{}

void Character::initialize()
{
  switch (this->choice){
  case 1:
    this->model_ = gdl::Model::load( "./asserts/anims/bomberman_white_run.FBX");
    break;
  case 2:
    this->model_ = gdl::Model::load( "./asserts/anims/bomberman_black_run.FBX");
    break;
  case 3:
    this->model_ = gdl::Model::load( "./asserts/anims/bomberman_blue_run.FBX");
    break;
  case 4:
    this->model_ = gdl::Model::load( "./asserts/anims/bomberman_red_run.FBX");
    break;
  case 5:
    this->model_ = gdl::Model::load( "./asserts/anims/bomberman_pink_run.FBX");
    break;
  case 6:
    this->model_ = gdl::Model::load( "./asserts/anims/bomberman_gold_run.FBX");
    break;
  }
}

void Character::update(gdl::GameClock const &gameClock, gdl::Input &input)
{
  this->model_.update(gameClock);
  this->Action(input);
  draw();
}

void Character::draw()
{
  if (this->alive == false)
    return ;
  gdl::Model::Begin();

  glPushMatrix();

  this->model_.play("Take 001");
  glTranslatef(this->position_->x, 0.0f, this->position_->y);
  //glRotatef(90,0,1,0);

  this->model_.draw();

  glPopMatrix();

  gdl::Model::End();
}

void    Character::Action(gdl::Input &input)
{
  if ((this->alive && input.isKeyDown(this->Down) == true) &&
      ((this->map->getPos(this->getPosX(), this->getPosY() + 1) >= 5) && ((this->map->getPos(this->getPosX(), this->getPosY() + 1) <= 9))))
    {
      this->rotation_->x = 0;
      this->map->setPos(9, this->getPosX(), this->getPosY());
      this->setPosY(this->getPosY() + 1);
      checkBonus(this->map->getPos(this->getPosX(), this->getPosY()));
    }

  if ((this->alive && input.isKeyDown(this->Up) == true) &&
      ((this->map->getPos(this->getPosX(), this->getPosY() - 1) >= 5) && ((this->map->getPos(this->getPosX(), this->getPosY() - 1) <= 9))))
    {
      this->rotation_->x = 180;
      this->map->setPos(9, this->getPosX(), this->getPosY());
      this->setPosY(this->getPosY() - 1);
      checkBonus(this->map->getPos(this->getPosX(), this->getPosY()));

    }
  if ((this->alive && input.isKeyDown(this->Right) == true) &&
      ((this->map->getPos(this->getPosX() + 1, this->getPosY()) >= 5) && ((this->map->getPos(this->getPosX() + 1, this->getPosY()) <= 9))))
    {
      this->rotation_->x = 90;
      this->map->setPos(9, this->getPosX(), this->getPosY());
      this->setPosX(this->getPosX() + 1);
      checkBonus(this->map->getPos(this->getPosX(), this->getPosY()));
    }
  if ((this->alive && input.isKeyDown(this->Left) == true) &&
      ((this->map->getPos(this->getPosX() - 1, this->getPosY()) >= 5) && ((this->map->getPos(this->getPosX() - 1, this->getPosY()) <= 9))))
    {
      this->rotation_->x = 270;
      this->map->setPos(9, this->getPosX(), this->getPosY());
      this->setPosX(this->getPosX() - 1);
      checkBonus(this->map->getPos(this->getPosX(), this->getPosY()));
    }
  if (this->alive && input.isKeyDown(this->Space) == true)
    {
      this->map->setPos(4, this->getPosX(), this->getPosY());
      this->dropBomb();
      //    this->map->affMap();
      //this->bomb->add_positions(new Vector3f(this->position_->x, 0.0f, this->position_->z), this->_power);
    }
}

void		Character::dropBomb()
{
  this->explose(1, 0, this->getPosX(), this->getPosY(), this->getPower());
  this->explose(1, 1, this->getPosX(), this->getPosY(), this->getPower());
  this->explose(-1, 0, this->getPosX(), this->getPosY(), this->getPower());
  this->explose(-1, 1, this->getPosX(), this->getPosY(), this->getPower());
  this->eraseFire();
}

void		Character::explose(int i, int y, int posx, int posy, int power)
{
  if (power >= 0)
    {
      if (y == 0)
	{
	  if (explose2(posx, posy) == 1)
	    {
	      this->map->setPos(42, posx, posy);
	      explose(i, y, posx + i, posy, power -1);
	    }
	  else
	    return;
	}
      if (y == 1)
	{
	  if (explose2(posx, posy) == 1)
	    {
	      this->map->setPos(42, posx, posy);
	      explose(i, y, posx, posy + i, power -1);
	    }
	  else
	    return;
	}
    }
}

int		Character::explose2(int posx, int posy)
{
  int res = 0;

  if (this->map->getPos(posx, posy) == 2 || (this->map->getPos(posx, posy) >= 5 && this->map->getPos(posx, posy) <= 8))
    {
      res = rand() % 2;
      if (res == 1 || (this->map->getPos(posx, posy) >= 5 && this->map->getPos(posx, posy) <= 8))
	this->map->setPos(9, posx, posy);
      else
	{
	  res = rand() % 4;
	  this->generateBonus(res, posx, posy);
	}
      return 0;
    }
  else if (this->map->getPos(posx, posy) == 3)
    return 0;
  else
    return 1;
}

void		Character::eraseFire()
{

  int y, x;

  for (y = 0; y < this->map->getWidth(); y++)
    {
      for(x = 0; x < this->map->getLength(); x++)
	{
	  if (this->map->getPos(x, y) == 42)
	    {
	      this->map->setPos(42, x, y);
	      this->map->setPos(9, x, y);
	    }
	}
    }
}

void		Character::generateBonus(int res, int x, int y)
{
  if (res == 0)
    this->map->setPos(5, x, y);
  if (res == 1)
    this->map->setPos(6, x, y);
  if (res == 2)
    this->map->setPos(7, x, y);
  if (res == 3)
    this->map->setPos(8, x, y);
}

void    Character::checkBonus(int bloctype)
{
  if (bloctype == 5 || bloctype == 6)
    {
      if (bloctype == 5)
	this->_nbBombs = this->_nbBombs + 1;
      else if (bloctype == 6 && this->_nbBombs > 1)
	this->_nbBombs = this->_nbBombs - 1;
      this->map->setPos(9, this->getPosX(), this->getPosY());
    }
  else if (bloctype == 7 || bloctype == 8)
    {
      if (bloctype == 7)
	this->_power = this->_power + 1;
      else if (bloctype == 8 && this->_power > 2)
	this->_power = this->_power - 1;
      this->map->setPos(9, this->getPosX(), this->getPosY());
    }
}
