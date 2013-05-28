// Copyright (C) 2013, Tim Boldt

#include <cmath>
#include <iomanip>
#include "tank.h"

namespace tankbattle {

Tank::Tank(b2World* physics, float x, float y, float body_angle)
  : motion_direction_(kStopped),
    body_rotation_direction_(kNone),
    turret_rotation_direction_(kNone) {

  // Tank Body
  {
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set(x, y);
    body_def.angle = body_angle; // TODO(tboldt) determine if we are going to use radians or degrees
    body_def.linearDamping = 1.0;
    body_def.angularDamping = 1.0;
    tank_body_ = physics->CreateBody(&body_def);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(8.0f, 4.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 2.0f;
    fixtureDef.friction = 0.3f;

    tank_body_->CreateFixture(&fixtureDef);
  }

  // Turret
  {
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set(x, y);
    body_def.angle = body_angle + 1.0; // TODO(tboldt) determine if we are going to use radians or degrees
    turret_body_ = physics->CreateBody(&body_def);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(6.0f, 3.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.3f;

    turret_body_->CreateFixture(&fixtureDef);

    b2RevoluteJointDef joint_def;
    joint_def.Initialize(tank_body_, turret_body_, tank_body_->GetWorldCenter());
    joint_def.enableMotor = true;
    joint_def.motorSpeed = 0;
    joint_def.maxMotorTorque = 100000;
    turret_joint_ = (b2RevoluteJoint*)physics->CreateJoint(&joint_def);
  }
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

void Tank::PrePhysics(float elapsed_seconds) {
  /*protected void updateWheelBody (World world, Body body, float deltaTime) {
  Vector2 velocity = body.getLinearVelocityFromLocalPoint(vector.set(0f, 0f));
  transformRcol2(body.getTransform(), vector);
  vector.mul(velocity.dot(vector)).sub(velocity);
  float len = vector.len();
  if (len > 0.00001f) {
    final float traction = 15f;
    if (len > traction) 
      vector.mul(traction / len);
    body.applyLinearImpulse(vector, body.getPosition());
  }
}*/
  float kTrackForce = 10000.0;
  b2Vec2 trackForce = tank_body_->GetWorldVector(b2Vec2(kTrackForce, 0));
  b2Vec2 rightTrackLocation = tank_body_->GetWorldPoint(b2Vec2(0, 2));
  b2Vec2 leftTrackLocation = tank_body_->GetWorldPoint(b2Vec2(0, -2));

  switch (motion_direction_) {
    case kForwards:
      tank_body_->ApplyForce(trackForce, rightTrackLocation);
      tank_body_->ApplyForce(trackForce, leftTrackLocation);
      break;
    case kBackwards:
      tank_body_->ApplyForce(-trackForce, rightTrackLocation);
      tank_body_->ApplyForce(-trackForce, leftTrackLocation);
      break;
  }
  switch (body_rotation_direction_) {
    case kRight:
      if (motion_direction_ != kBackwards) {
        tank_body_->ApplyForce(-trackForce, rightTrackLocation);
      }
      if (motion_direction_ != kForwards) {
        tank_body_->ApplyForce(trackForce, leftTrackLocation);
      }
      break;
    case kLeft:
      if (motion_direction_ != kForwards) {
        tank_body_->ApplyForce(trackForce, rightTrackLocation);
      }
      if (motion_direction_ != kBackwards) {
        tank_body_->ApplyForce(-trackForce, leftTrackLocation);
      }
      break;
  }

  float kTurretSpeed = 3;
  switch (turret_rotation_direction_) {
    case kRight:
      turret_joint_->SetMotorSpeed(kTurretSpeed);
      break;
    case kLeft:
      turret_joint_->SetMotorSpeed(-kTurretSpeed);
      break;
    default:
      turret_joint_->SetMotorSpeed(0);
  }
}

void Tank::PostPhysics(float elapsed_seconds) {
}

void Tank::Render(sf::RenderWindow& window) {
/*  sf::RectangleShape body_shell(Vector(40,32));
  body_shell.setFillColor(sf::Color::White);
  body_shell.setOrigin(16,16);
  body_shell.setPosition(bodyTransform_.getPosition());
  body_shell.setRotation(bodyTransform_.getRotation());

  sf::CircleShape turret_shell(10);
  turret_shell.setFillColor(sf::Color::Red);
  turret_shell.setOrigin(10,10);
  turret_shell.setPosition(bodyTransform_.getPosition());
  turret_shell.setRotation(bodyTransform_.getRotation());
  
  sf::RectangleShape turret_gun(Vector(30,4));
  turret_gun.setFillColor(sf::Color::Blue);
  turret_gun.setOrigin(0,2);
  turret_gun.setPosition(bodyTransform_.getPosition());
  turret_gun.setRotation(turretTransform_.getRotation());

  window.draw(body_shell);
  window.draw(turret_shell);
  window.draw(turret_gun);*/
}
/*
sf::Vector2<float> Tank::location() const {
  return bodyTransform_.getPosition();
}

float Tank::bodyRotation() const {
  return bodyTransform_.getRotation();
}

float Tank::turretRotation() const {
  return turretTransform_.getRotation();
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
  float r = kTurretRotationRateMax;

  switch (turret_rotation_direction_) {
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


::std::ostream& operator<<(::std::ostream& os, const Tank& t) {
  return os << ::std::fixed << ::std::setprecision(2) 
    << "Tank["
    << "x=" << t.location().x << " "
    << "y=" << t.location().y << " "
    << "body_angle=" << t.bodyRotation() << " "
    << "turret_angle=" << t.turretRotation() << "]";
}
*/
} // namespace TankBattle
