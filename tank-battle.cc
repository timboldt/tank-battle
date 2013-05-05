#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
  sf::SoundBuffer tank_sound_buffer;
  tank_sound_buffer.LoadFromFile("tank1.wav");
  sf::Sound tank_sound;
  tank_sound.SetBuffer(tank_sound_buffer);
  tank_sound.Play();

  sf::Image tank_image;
  tank_image.LoadFromFile("tank1.jpg");
  sf::Sprite tank_sprite;
  tank_sprite.SetImage(tank_image);
  tank_sprite.FlipX(true);
  tank_sprite.Move(0, 400);
  float x_velocity = 100.0;

  // Create the main rendering window
  sf::RenderWindow App(sf::VideoMode(900, 600, 32), "SFML Graphics");

  // Start game loop
  while (App.IsOpened()) {
    // Process events
    sf::Event Event;
    while (App.GetEvent(Event)) {
      // Close window : exit
      if (Event.Type == sf::Event::Closed)
      App.Close();
    }

    if (x_velocity > 0 && tank_sprite.GetPosition().x > 500) {
      x_velocity = -1.0 * x_velocity;
      tank_sprite.FlipX(false);
      tank_sound.Play();
    } else if (x_velocity < 0 && tank_sprite.GetPosition().x < 10) {
      x_velocity = -1.0 * x_velocity;
      tank_sprite.FlipX(true);
      tank_sound.Play();
    }

    float ElapsedTime = App.GetFrameTime();
    tank_sprite.Move(ElapsedTime * x_velocity, 0);

    // Clear the screen (fill it with black color)
    App.Clear(sf::Color(255, 255, 255));
    App.Draw(tank_sprite);

    // Display window contents on screen
    App.Display();
  }

  return EXIT_SUCCESS;
}
