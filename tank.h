// Copyright (C) 2013, Tim Boldt.  All rights reserved.

#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace tankbattle {

const float kSpeedMax = 100.0;
const float kSpeedWhileRotating = 80.0;

const float kBodyRotationRateMax = 45.0;
const float kBodyRotationRateWhileDriving = 22.5; 
const float kTurretRotationRateMax = 90.0;

typedef sf::Vector2<float> Vector;

class Tank {
 public:
  enum MotionDirection { kStopped, kForwards, kBackwards }; 
  enum RotationDirection { kNone, kRight, kLeft };

  Tank(float x, float y, float body_angle); 
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

  sf::Vector2<float> location() const { return bodyTransform_.getPosition(); }
  float bodyRotation() const { return bodyTransform_.getRotation(); }
  float turretRotation() const { return turretTransform_.getRotation(); }

  float speed() const;
  float bodyRotationRate();
  float turretRotationRate();

  void onTimePasses(float elapsedTime);
  void onDraw();

 private:
  MotionDirection motion_direction_;
  RotationDirection body_rotation_direction_;
  RotationDirection turret_rotation_direction_;

  sf::Transformable bodyTransform_;
  sf::Transformable turretTransform_;
};

::std::ostream& operator<<(::std::ostream& os, const Tank& t);

} // namespace tankbattle

namespace sf {
::std::ostream& operator<<(::std::ostream& os, const Vector2<float>& v);
} // namespace "sf" 
#endif
