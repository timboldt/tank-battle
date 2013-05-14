// Copyright (C) 2013, Tim Boldt.  All rights reserved.

//#include <SFML/Vector2.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "tank.h"

namespace tankbattle {

const float kEast = 0.0;
const float kWest = 180.0;
const float kNorth = 270.0;
const float kSouth = 90.0;
const float kTriangle345 = 36.86; // A 3-4-5 triangle has this angle between the "4" and "5" sides 

bool IsNearLocation(const Tank& t, const Vector& v) {
  float kFudgeFactor = 0.1;
  const Vector& vt = t.location();

  return fabs(vt.x - v.x) < kFudgeFactor && fabs(vt.y - v.y) < kFudgeFactor;
}

TEST(DrivingTest, SimpleForwardBackward) {
  Tank t(0.0, 0.0, kNorth);
  t.startDrivingForwards();
  t.onTimePasses(1.0);
  EXPECT_PRED2(IsNearLocation, t, Vector(0.0, -1.0 * kSpeedMax))
    << "After driving forward";

  t.stopDriving();
  t.onTimePasses(1.0);
  EXPECT_PRED2(IsNearLocation, t, Vector(0.0, -1.0 * kSpeedMax))
    << "After being stopped";

  t.startDrivingBackwards();
  t.onTimePasses(1.0);
  EXPECT_PRED2(IsNearLocation, t, Vector(0.0, 0.0))
    << "After driving backward";
}

TEST(DrivingTest, DriveAtAnAngle) { 
  Tank t(0.0, 0.0, kTriangle345);
  t.startDrivingForwards();
  t.onTimePasses(5.0);
  EXPECT_PRED2(IsNearLocation, t, Vector(4.0 * kSpeedMax, 3.0 * kSpeedMax));
}

TEST(DrivingTest, DriveInASquarePattern) { 
  Tank t(0.0, 0.0, kEast);

  t.startDrivingForwards();
  t.onTimePasses(1.0);
  t.stopDriving();
  EXPECT_PRED2(IsNearLocation, t, Vector(kSpeedMax, 0.0))
    << "After travelling east";

  t.startRotatingRight();
  t.onTimePasses(90.0 / kBodyRotationRateMax);
  t.stopRotating();

  t.startDrivingForwards();
  t.onTimePasses(1.0);
  t.stopDriving();
  EXPECT_PRED2(IsNearLocation, t, Vector(kSpeedMax, kSpeedMax))
    << "After travelling south";

  t.startRotatingRight();
  t.onTimePasses(90.0 / kBodyRotationRateMax);
  t.stopRotating();

  t.startDrivingForwards();
  t.onTimePasses(1.0);
  t.stopDriving();
  EXPECT_PRED2(IsNearLocation, t, Vector(0.0, kSpeedMax))
    << "After travelling west";

  t.startRotatingRight();
  t.onTimePasses(90.0 / kBodyRotationRateMax);
  t.stopRotating();

  t.startDrivingForwards();
  t.onTimePasses(1.0);
  t.stopDriving();
  EXPECT_PRED2(IsNearLocation, t, Vector(0.0, 0.0))
    << "After travelling north";
}

TEST(DrivingTest, DriveInACircle) { 
  Tank t(1.0, 0.0, kSouth);

  t.startDrivingForwards();
  t.startRotatingRight();
  t.onTimePasses(180.0 / kBodyRotationRateWhileDriving);
  EXPECT_NEAR(kNorth, t.bodyRotation(), 0.1);
  t.onTimePasses(180.0 / kBodyRotationRateWhileDriving);
  EXPECT_PRED2(IsNearLocation, t, Vector(1.0, 0.0));
}

} // Namespace

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
