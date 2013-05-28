// Copyright (C) 2013, Tim Boldt

#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

namespace tankbattle {

class Tank {
 public:
  enum MotionDirection { kStopped, kForwards, kBackwards }; 
  enum RotationDirection { kNone, kRight, kLeft };

 public:
  Tank(b2World* physics_, float x, float y, float body_angle); 
  virtual ~Tank();

  void startDrivingForwards();
  void startDrivingBackwards();
  void stopDriving();

  void startRotatingLeft();
  void startRotatingRight();
  void stopRotating();

  void startRotatingTurretLeft();
  void startRotatingTurretRight();
  void stopRotatingTurret();

//  b2Vec2 location() const { return tank_body_.GetPosition(); }
//  float bodyRotation() const { return body_body_.GetAngle(); }
//  float turretRotation() const { return turret_body_.GetAngle(); }

//  b2Vec2 speed() const { return tank_body_.GetLinearVelocity(); }
//  float bodyRotationRate() const { return tank_body_.GetAngularVelocity(); }
//  float turretRotationRate() const { return turret_body_.GetAngularVelocity(); }

  void PrePhysics(float elapsed_seconds);
  void PostPhysics(float elapsed_seconds);

  void Render(sf::RenderWindow& window);

 private:
  MotionDirection motion_direction_;
  RotationDirection body_rotation_direction_;
  RotationDirection turret_rotation_direction_;

  b2Body* tank_body_;
  b2Body* turret_body_;
  b2RevoluteJoint* turret_joint_;
};

//::std::ostream& operator<<(::std::ostream& os, const Tank& t);

} // namespace tankbattle

#endif
