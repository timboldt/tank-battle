// Copyright (C) 2013, Tim Boldt

#include <cmath>
#include <iomanip>
#include "tank.h"

namespace tankbattle {

Tank::Tank(float x, float y, float body_angle)
  : motion_direction_(kStopped),
    body_rotation_direction_(kNone),
    turret_rotation_direction_(kNone) {
  bodyTransform_.setPosition(x, y);
  bodyTransform_.setRotation(body_angle);
  turretTransform_.setPosition(x, y);
  turretTransform_.setRotation(body_angle);
}

Tank::~Tank() {
}

void Tank::startDrivingForwards() {
  motion_direction_ = kForwards;
}

void Tank::startDrivingBackwards() {
  motion_direction_ = kBackwards;
}

void Tank::stopDriving() {
  motion_direction_ = kStopped;
}

void Tank::startRotatingLeft() {
  body_rotation_direction_ = kLeft;
}

void Tank::startRotatingRight() {
  body_rotation_direction_ = kRight;
}

void Tank::stopRotating() {
  body_rotation_direction_ = kNone;
}

void Tank::startRotatingTurretLeft() {
  turret_rotation_direction_ = kLeft;
}

void Tank::startRotatingTurretRight() {
  turret_rotation_direction_ = kRight;
}

void Tank::stopRotatingTurret() {
  turret_rotation_direction_ = kNone;
} 

void Tank::onTimePasses(float elapsedTime) {
  for (float totalTime = 0.0; totalTime < elapsedTime; totalTime += 0.1) {
    float deltaTime = std::min(0.1f, elapsedTime - totalTime);

    bodyTransform_.rotate(bodyRotationRate() * deltaTime);

    float delta = speed() * deltaTime;
    float xv = cos(bodyTransform_.getRotation()*M_PI/180);
    float yv = sin(bodyTransform_.getRotation()*M_PI/180);
    bodyTransform_.move(delta * xv, delta * yv);
  }
}

void Tank::onDraw(sf::RenderWindow& window) {
  sf::RectangleShape body_shell(Vector(32,32));
  body_shell.setFillColor(sf::Color::White);
  body_shell.setOrigin(16,16);
  body_shell.setPosition(bodyTransform_.getPosition());
  body_shell.setRotation(bodyTransform_.getRotation());

  sf::CircleShape turret_shell(10);
  turret_shell.setFillColor(sf::Color::Red);
  turret_shell.setOrigin(10,10);
  turret_shell.setPosition(bodyTransform_.getPosition());
  turret_shell.setRotation(bodyTransform_.getRotation());
  
  sf::RectangleShape turret_gun(Vector(24,4));
  turret_gun.setFillColor(sf::Color::Blue);
  turret_gun.setOrigin(0,2);
  turret_gun.setPosition(bodyTransform_.getPosition());
  turret_gun.setRotation(turretTransform_.getRotation());

  window.draw(body_shell);
  window.draw(turret_shell);
  window.draw(turret_gun);
}

float Tank::speed() const {
  float s = (body_rotation_direction_ == kNone) ? kSpeedMax : kSpeedWhileRotating;

  switch (motion_direction_) {
    case kForwards:
      break;
    case kBackwards:
      s *= -1.0;
      break;
    default:
      s = 0.0;
  }

  return s;
}

float Tank::bodyRotationRate() {
  float r = (motion_direction_ == kStopped) ?
                kBodyRotationRateMax :
                kBodyRotationRateWhileDriving; 

  switch (body_rotation_direction_) {
    case kRight:
      break;
    case kLeft:
      r *= -1.0;
      break;
    default:
      r = 0.0;
  }

  return r;
}

float Tank::turretRotationRate() {
  // TODO
  return 10.0;
}


::std::ostream& operator<<(::std::ostream& os, const Tank& t) {
  return os << ::std::fixed << ::std::setprecision(2) 
    << "Tank["
    << "x=" << t.location().x << " "
    << "y=" << t.location().y << " "
    << "body_angle=" << t.bodyRotation() << " "
    << "turret_angle=" << t.turretRotation() << "]";
}

} // namespace TankBattle


namespace sf {
::std::ostream& operator<<(::std::ostream& os, const Vector2<float>& v) {
  return os << ::std::fixed << ::std::setprecision(2) 
    << "Vector["
    << "x=" << v.x << " "
    << "y=" << v.y << "]";
}
} // namespace "sf" 
