// Copyright (C) 2013, Tim Boldt

#include <Box2D/Box2D.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "world.h"

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Tank Battle");
  sf::Clock clock;

  sf::View view = window.getView();
  sf::FloatRect rect = view.getViewport();
  rect.width *= 3.0;
  rect.height *= 3.0;
  view.setViewport(rect);
  window.setView(view);

  window.clear(sf::Color::Black);
  window.display();
  tankbattle::World world;
  world.SetDebugDraw(&window);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
          window.close();
      }
    }

    window.clear(sf::Color::Black);
    sf::Time elapsed = clock.restart();
    world.ApplyPhysics(elapsed.asSeconds());
    world.Render(window);
    window.display();
  }

  return 0;
}
