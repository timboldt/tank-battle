// Copyright (C) 2013, Tim Boldt

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "tank.h"

int main()
{
  tankbattle::Tank t1(250, 250, 45.0);
  t1.startDrivingForwards();
  t1.startRotatingRight();

  sf::RenderWindow window(sf::VideoMode(800, 600), "Tank Battle");
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
          window.close();
      }
    }

    // Turning
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      t1.startRotatingLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      t1.startRotatingRight();
    } else {
      t1.stopRotating();
    }

    // Turning
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
      t1.startRotatingTurretLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
      t1.startRotatingTurretRight();
    } else {
      t1.stopRotatingTurret();
    }

    // Driving
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      t1.startDrivingForwards();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      t1.startDrivingBackwards();
    } else {
      t1.stopDriving();
    }


    sf::Time elapsed = clock.restart();
    t1.onTimePasses(elapsed.asSeconds());

    window.clear(sf::Color::Black);
    t1.onDraw(window);
    window.display();
  }

  return 0;
}
