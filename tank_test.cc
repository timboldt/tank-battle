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
/*
bool HasSpeed(const Tank& t, float speed) {
  float kFudgeFactor = 0.1;

  return fabs(t.speed() - speed) < kFudgeFactor;
}*/

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
/*


func TestDriveInACircle(t *testing.T) {
	checkFloat(t, "Angle after travelling 180 degrees", tank.BodyAngle(), North)
	tank.OnTimePasses(180.0 / BodyRotationRateWhileDriving)
	checkLocation(t, "After travelling 360 degrees", tank.Location(), Vector2D{1.0, 0.0})
}
*/
/*
TEST(DrivingTest, DriveForward) { 
  {
    Tank t(0.0, 0.0, kEast, 0.0);

    t.startDrivingForwards();
    t.onTimePasses(1.0);
    EXPECT_PRED2(IsNearLocation, t, Vector(kSpeedMax, 0));
  }

  {
    Tank t(0.0, 0.0, kWest, 0.0);

    t.startDrivingForwards();
    t.onTimePasses(1.0);
    EXPECT_PRED2(IsNearLocation, t, Vector(-1.0 * kSpeedMax, 0));
  }

  {
    Tank t(0.0, 0.0, kNorth, 0.0);

    t.startDrivingForwards();
    t.onTimePasses(1.0);
    EXPECT_PRED2(IsNearLocation, t, Vector(0, -1.0 * kSpeedMax));
  }

  {
    Tank t(0.0, 0.0, kSouth, 0.0);

    t.startDrivingForwards();
    t.onTimePasses(1.0);
    EXPECT_PRED2(IsNearLocation, t, Vector(0, kSpeedMax));
  }

  {
    // 3-4-5 triangle = 36.86 degrees
    Tank t(0.0, 0.0, 36.86, 0.0);

    t.startDrivingForwards();
    t.onTimePasses(5.0);
    EXPECT_PRED2(IsNearLocation, t, Vector(4.0 * kSpeedMax, 3.0 * kSpeedMax));
  }
}

TEST(DrivingTest, SimpleForwardBackwards) { 
  Tank t(0.0, 0.0, kSouth, 0.0);

  t.startDrivingForwards();
  t.onTimePasses(1.0);
  EXPECT_PRED2(IsNearLocation, t, Vector(0.0, 1.0 * kSpeedMax));

  t.stopDriving();
  t.onTimePasses(1.0);
  EXPECT_PRED2(IsNearLocation, t, Vector(0.0, 1.0 * kSpeedMax));

  // Assumes tank speed is the same forward and backwards
  t.startDrivingBackwards();
  t.onTimePasses(1.0);
  EXPECT_PRED2(IsNearLocation, t, Vector(0.0, 0.0));
}

TEST(DrivingTest, SquarePattern) { 
  Tank t(0.0, 0.0, kEast, 0.0);

  for (int i = 0; i < 4; ++i) {
    t.startDrivingForwards();
    t.onTimePasses(1.0);

    t.stopDriving();
    t.onTimePasses(1.0);
    EXPECT_NEAR(1.0, std::max(fabs(t.location().x), fabs(t.location().y)), 0.1);

    t.startRotatingRight();
    const float kBodyRotationPerTimeUnit = 90.0; //TODO
    t.onTimePasses(90.0 / kBodyRotationPerTimeUnit);
    t.stopRotating();
    EXPECT_NEAR(90.0 * i, t.bodyRotation(), 0.1);
  }
  EXPECT_PRED2(IsNearLocation, t, Vector(0.0, 0.0));
}
*/
} // Namespace

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
