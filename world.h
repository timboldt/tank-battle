// Copyright (C) 2013, Tim Boldt

#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "tank.h"
//#include <iostream>

namespace tankbattle {

class World {
 public:
  World(); 
  virtual ~World();

  void ApplyPhysics(float elapsed_seconds);
  void Render(sf::RenderWindow& window);

  void SetDebugDraw(sf::RenderWindow* window);

 private:
  b2World* physics_;
  Tank* player1_;
  //TEMP
  b2Body* body_;
};

//::std::ostream& operator<<(::std::ostream& os, const World& w);

} // namespace tankbattle
#endif
