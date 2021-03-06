/*
**  inc/AObject.hh
**  Bomberman
**
**  Created by Quentin PIDOUX on 30/04/12.
**  Copyright (c) 2012 EPITECH. All rights reserved.
*/

#ifndef AObject_hh_
# define AObject_hh_

# include "Bomberlib.hh"
# include "Vector3f.hh"

# include <utility>
# include <vector>

class    AObject
{
public:
  AObject(void) {}
  virtual void initialize(void);
  virtual void update(gdl::GameClock const &, gdl::Input &) = 0;
  virtual void draw(void) = 0;
  void	add_positions(Vector3f *position, float rotation);

protected:
  std::vector<std::pair<Vector3f*, float> >positions;
};

#endif
