#include "bomberlib.hh"
#include "AObject.hh"
#include "Fire.hh"
#include "MyGame.hh"


namespace Model
{
  Fire::Fire(MyGame *game)
  {
    this->game = game;
  }


  Fire::~Fire()
  {}


  void	Fire::initialize(void)
  {
    this->model_ = gdl::Model::load("../GDL-library/models/fire.FBX");
  }


  void	Fire::update(gdl::GameClock const &gameClock, gdl::Input &input)
  {
    this->model_.update(gameClock);
  }


  void	Fire::draw_object(Vector3f *position)
  {
    gdl::Model::Begin();

    glPushMatrix();

    glTranslatef(position->z + 0.50, 0.0f, position->x - 0.50);
    glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
    this->model_.draw();

    if ((this->game->getPlayer1()) && ((int)this->game->getPlayer1()->getposition_x() == (int)position->x)
	&& ((int)this->game->getPlayer1()->getposition_z() == (int)position->z))
      this->game->getPlayer1()->isKill();
    if ((this->game->getPlayer2()) && ((int)this->game->getPlayer2()->getposition_x() == (int)position->x)
	&& ((int)this->game->getPlayer2()->getposition_z() == (int)position->z))
      this->game->getPlayer2()->isKill();
    glPopMatrix();

    gdl::Model::End();
  }


  void	Fire::draw(void)
  {
    std::vector<std::pair<Vector3f*, float> >::iterator it;
    int	i = 0;

    this->model_.play("Take 001");
    for (it = this->positions.begin() ; it != this->positions.end() ; )
      {
	 this->positions[i].first->y += 1.0f;
	 this->draw_object(this->positions[i].first);
	 if (this->positions[i].first->y >= 10.0f)
	   this->positions.erase(it);
	 else
	   {
	     i++;
	     it++;
	   }
       }
  }

}
