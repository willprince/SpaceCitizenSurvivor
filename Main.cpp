#include <sstream>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Arena.h"
using namespace sf;
using namespace std;

int main()
{
    enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
    State state = State::GAME_OVER;

    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window( VideoMode(resolution.x, resolution.y), "Space citizen: Survivor", Style::Fullscreen);

    View mainView(FloatRect(0, 0, resolution.x, resolution.y));
    
    Clock clock;
    Time gameTimeTotal;

    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    
    Player player;
    IntRect arena;

    VertexArray background;
	Texture textureBackground;
	if (!textureBackground.loadFromFile("graphics/background_sheet.png"))
	{
		std::cerr << "Error loading background texture" << std::endl;
		return -1;
	}

    while (window.isOpen())
    {
        /*
        ****************
        HANDLE PLAYER INPUT
        ****************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                // Pause a game while playing
                if (event.key.code == Keyboard::Return &&
                    state == State::PLAYING)
                {
                    state = State::PAUSED;
                }
                // Restart while paused
                else if (event.key.code == Keyboard::Return &&
                    state == State::PAUSED)
                {
                    state = State::PLAYING;
                    // Reset the clock so there isn't a frame jump
                    clock.restart();
                }
                // Start a new game while in GAME_OVER state
                else if (event.key.code == Keyboard::Return &&
                    state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                }
                if (state == State::PLAYING)
                {

                }
            }
            // Handle the player quitting
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
            // Handle WASD while playing
            if (state == State::PLAYING)
            {
                // Handle the pressing and releasing of WASD keys
                if (Keyboard::isKeyPressed(Keyboard::W))
                {
                    player.moveUp();
                }
                else
                {
                    player.stopUp();
                }
                if (Keyboard::isKeyPressed(Keyboard::S))
                {
                    player.moveDown();
                }
                else
                {
                    player.stopDown();
                }
                if (Keyboard::isKeyPressed(Keyboard::A))
                {
                    player.moveLeft();
                }
                else
                {
                    player.stopLeft();
                }
                if (Keyboard::isKeyPressed(Keyboard::D))
                {
                    player.moveRight();
                }
                else
                {
                    player.stopRight();
                }
            }// End WASD while playing
            // Handle the LEVELING up state
            if (state == State::LEVELING_UP)
            {
                // Handle the player LEVELING up
                if (event.key.code == Keyboard::Num1)
                {
                    state = State::PLAYING;
                }
                if (event.key.code == Keyboard::Num2)
                {
                    state = State::PLAYING;
                }
                if (event.key.code == Keyboard::Num3)
                {
                    state = State::PLAYING;
                }
                if (event.key.code == Keyboard::Num4)
                {
                    state = State::PLAYING;
                }
                if (event.key.code == Keyboard::Num5)
                {
                    state = State::PLAYING;
                }
                if (event.key.code == Keyboard::Num6)
                {
                    state = State::PLAYING;
                }
                if (state == State::PLAYING)
                {
                    arena.width = 500;
                    arena.height = 500;
                    arena.left = 0;
                    arena.top = 0;
                    int tileSize = createBackground(background, arena);
                    player.spawn(arena, resolution, tileSize);
                    clock.restart();
                }
            }// End LEVELING up
        }
        /*
        ****************
        UPDATE THE FRAME
        ****************
        */
        if (state == State::PLAYING)
        {
            // Update the delta time
            Time dt = clock.restart();
            // Update the total game time
            gameTimeTotal += dt;
            // Make a fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();
            // Where is the mouse pointer
            mouseScreenPosition = Mouse::getPosition();
            mouseWorldPosition = window.mapPixelToCoords(
            Mouse::getPosition(), mainView);
            // Update the player
            player.update(dtAsSeconds, Mouse::getPosition());
            Vector2f playerPosition(player.getCenter());
            mainView.setCenter(player.getCenter());

        }// End updating the scene
        /*
        **************
        Draw the scene
        **************
        */
        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(background, &textureBackground);
            window.draw(player.getSprite());
        }
        if (state == State::LEVELING_UP)
        {
        }
        if (state == State::PAUSED)
        {
        }
        if (state == State::GAME_OVER)
        {
        }
        window.display();
    }
    
    return 0;
}
