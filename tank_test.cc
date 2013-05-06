// Copyright (C) 2013, Tim Boldt
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <gtest/gtest.h>
#include "tank.h"
 
namespace tankbattle {

/*
class Tank {
 public:
  static const float kSpeedMax = 1.0;
  static const float kSpeedWhileRotating = 0.8;
  static const float kBodyRotationRateMax = 1.0;
  static const float kBodyRotationRateWhileDriving = 0.5;
  static const float kTurretRotationRateMax = 2.0;
  static const float kSpeedMultiplier = 100.0;
  static const float kRotationMultiplier = 100.0;

  Tank(float x, float y, float body_angle, float turret_angle); 
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

  float x() const { return bodySprite_.GetPosition().x; }
  float y() const { return bodySprite_.GetPosition().y; }
  float bodyRotation() const { return bodySprite_.GetRotation();
  float turretRotation() const { return turretSprite_.GetRotation();

  void onTimePasses(float elapsedTime);
  void onDraw();
  */
TEST(DrivingTest, SimpleDriveForward) { 
  Tank t(0.0, 0.0, 90.0, 90.0);
  t.startDrivingForwards();
  t.onTimePasses(1.0);
  ASSERT_EQ(Tank::kSpeedMax * Tank::kSpeedMultiplier, t.x());
  ASSERT_EQ(0.0, t.y());
}
 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
