// Copyright (C) 2013, Tim Boldt

#include <cmath>
#include <iomanip>
#include <cstdio>
#include "world.h"

namespace tankbattle {

const int RATIO = 1;

// TODO (tboldt) move this to its own source file
class DebugDraw : public b2Draw {
 public:
  DebugDraw(sf::RenderWindow* window) : window_(window) {
    puts("DebugDraw: Initialized");
  }

  virtual ~DebugDraw() {}

  //convert a Box2D (float 0.0f - 1.0f range) color to a SFML color (uint8 0 - 255 range)
  sf::Color B2SFColor(const b2Color &color, int alpha = 255)
  {
    sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8) alpha);
    return result;
  }

  /// Draw a closed polygon provided in CCW order.
  virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape polygon(vertexCount);
    for (int32 i = 0; i < vertexCount; ++i) {
      b2Vec2 p1 = vertices[i];
      polygon.setPoint(i, sf::Vector2f(p1.x, p1.y));
    }
    // TODO(timboldt) This seems like a bad idea to use transparent as a fill color
    polygon.setFillColor(B2SFColor(color, 0));
    polygon.setOutlineColor(B2SFColor(color));
    polygon.setOutlineThickness(1.0);
    window_->draw(polygon);
  }

  /// Draw a solid closed polygon provided in CCW order.
  virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape polygon(vertexCount);
    for (int32 i = 0; i < vertexCount; ++i) {
      b2Vec2 p1 = vertices[i];
      polygon.setPoint(i, sf::Vector2f(p1.x, p1.y));
    }
    polygon.setFillColor(B2SFColor(color, 50));
    polygon.setOutlineColor(B2SFColor(color));
    polygon.setOutlineThickness(1.0);
    window_->draw(polygon);
    DrawPolygon(vertices, vertexCount, color);
  }

  /// Draw a circle.
  virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center.x*RATIO, center.y*RATIO);
    //circle.setFillColor(B2SFColor(color, 50));
    circle.setOutlineColor(B2SFColor(color));
    circle.setOutlineThickness(1.0);
    window_->draw(circle);
  }

  /// Draw a solid circle.
  virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center.x*RATIO, center.y*RATIO);
    circle.setFillColor(B2SFColor(color, 50));
    circle.setOutlineColor(B2SFColor(color));
    circle.setOutlineThickness(1.0);

    window_->draw(circle);

    // line of the circle wich shows the angle
    DrawSegment(center, center + (radius * axis), color);
  }

  /// Draw a line segment.
  virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    sf::Vertex line[] = {
      sf::Vertex(sf::Vector2f(p1.x, p1.y), B2SFColor(color)),
      sf::Vertex(sf::Vector2f(p2.x, p2.y), B2SFColor(color))
    };
    window_->draw(line, 2, sf::Lines);
  }

  /// Draw a transform. Choose your own length scale.
  /// @param xf a transform.
  virtual void DrawTransform(const b2Transform& xf) {
    // TODO(tboldt) I'm not convinced this is correct - check it out later
    b2Vec2 p1 = xf.p;
    const float32 kAxisScale = 4.0; //0.4f;

    {
      b2Vec2 p2 = p1 + kAxisScale * xf.q.GetXAxis();
      DrawSegment(p1, p2, b2Color(0.9, 0, 0));
    }
    {
      b2Vec2 p2 = p1 + kAxisScale * xf.q.GetYAxis();
      DrawSegment(p1, p2, b2Color(0, 0.9, 0));
    }
  }

private:
  sf::RenderWindow* window_;  // Does not own
};

World::World() : physics_(NULL), player1_(NULL) {
  b2Vec2 gravity(0.0f, 0.0f);
  physics_ = new b2World(gravity);
  player1_ = new Tank(physics_, 20, 20, 0.0);
  new Tank(physics_, 80, 20, 2);

  // TEMPORARY
 /* Define the dynamic body. We set its position and call the body factory.
  {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(20.0f, 20.0f);
        body_ = physics_->CreateBody(&bodyDef);

        // Define another box shape for our dynamic body.
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(8.0f, 4.0f);

        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;

        // Set the box density to be non-zero, so it will be dynamic.
        fixtureDef.density = 1.0f;

        // Override the default friction.
        fixtureDef.friction = 0.3f;

        // Add the shape to the body.
        body_->CreateFixture(&fixtureDef);
  }*/
        b2BodyDef body_def;
        body_def.type = b2_dynamicBody;
  
  body_def.position.Set(50.0f, 50.0f);
  body_ = physics_->CreateBody(&body_def);

  b2CircleShape shape;
  //circle.m_p.Set(20.0f, 30.0f);
  shape.m_radius = 10.0f;

  body_->CreateFixture(&shape, 0.0f);

  // Create world edges
  b2Vec2 vs[5];
  vs[0].Set(0.0, 0.0);
  vs[1].Set(200.0, 0.0);
  vs[2].Set(200.0, 200.0);
  vs[3].Set(0.0, 200.0);
  vs[4].Set(0.0, 0.0);
  b2ChainShape chain;
  chain.CreateChain(vs, 5);
  b2BodyDef ground_body_def;
  b2Body* ground_body = physics_->CreateBody(&ground_body_def);
  b2Fixture* ground_fixture = ground_body->CreateFixture(&chain, 0.0);
  ground_fixture->SetFriction(0.3);
  ground_fixture->SetRestitution(0.2);
}

World::~World() {
  delete player1_;
  player1_ = NULL;
  delete physics_;
  physics_ = NULL;
}

void World::ApplyPhysics(float elapsed_seconds) {
  const int32 kVelocityIterations = 8;
  const int32 kPositionIterations = 3;

  // Turning body
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player1_->startRotatingLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player1_->startRotatingRight();
  } else {
    player1_->stopRotating();
  }

  // Turning turret
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
    player1_->startRotatingTurretLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
    player1_->startRotatingTurretRight();
  } else {
    player1_->stopRotatingTurret();
  }

  // Driving
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    player1_->startDrivingForwards();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    player1_->startDrivingBackwards();
  } else {
    player1_->stopDriving();
  }

  player1_->PrePhysics(elapsed_seconds);
  physics_->Step(elapsed_seconds, kVelocityIterations, kPositionIterations);
  player1_->PostPhysics(elapsed_seconds);

  // TEMP: Now print the position and angle of the body.
      b2Vec2 position = body_->GetPosition();
      float32 angle = body_->GetAngle();

      printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle); 
}

void World::Render(sf::RenderWindow& window) {
  player1_->Render(window);
  physics_->DrawDebugData();
}

void World::SetDebugDraw(sf::RenderWindow* window) {
  // TODO(tboldt) determine who owns the DebugDraw object - most likely, this
  // is a memory leak.
  DebugDraw* draw = new DebugDraw(window);
  physics_->SetDebugDraw(draw);
  draw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit /*| b2Draw::e_aabbBit*/ | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit); 
}

} // Namespace
