//Niamh Andrews
//C00242944
//13-11-2019

#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <GameObject.h>
#include <Player.h>
#include <NPC.h>
#include <Input.h>
#include <Debug.h>

using namespace std;


/*class Capsule {
public:
	int capLenght = 20;
	int capRadius = 10;
};*/






int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");


	//Capsule creation
	int capLenght = 50;
	int capRadius = 15;
	sf::CircleShape capCircle1;
	sf::CircleShape capCircle2;
	sf::RectangleShape capRect;
	capCircle1.setRadius(capRadius);
	capCircle2.setRadius(capRadius);
	capRect.setSize(sf::Vector2f((capRadius *2), capLenght));
	capCircle1.setPosition(200, 200);
	capCircle2.setPosition(200, (200 + capLenght) );
	capRect.setPosition(200, (200 + capRadius));
	capCircle1.setFillColor(sf::Color::Color(50, 168, 82));
	capCircle2.setFillColor(sf::Color::Color(50, 168, 82));
	capRect.setFillColor(sf::Color::Color(50, 168, 82));





	//Polygon creation
	//sf::Vector2f polyPoint1{150,150};
	//sf::Vector2f polyPoint2{ 130,130 };
	//sf::Vector2f polyPoint3{ 170,130 };
	sf::Vertex polyPoint1{ sf::Vector2f{150,150}, sf::Color::Color(69, 200, 42) };
	sf::Vertex polyPoint2{ sf::Vector2f{130,130}, sf::Color::Color(69, 200, 42) };
	sf::Vertex polyPoint3{ sf::Vector2f{170,130}, sf::Color::Color(42, 42, 42) };

	sf::Lines;
	//???????????????????







	// Load a NPC's sprites to display
	sf::Texture npc_texture;
	if (!npc_texture.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Load a mouse texture to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile("assets\\player.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Setup NPC's Default Animated Sprite
	AnimatedSprite npc_animated_sprite(npc_texture);
	npc_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	npc_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);
	player_animated_sprite.addFrame(sf::IntRect(3, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(88, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(173, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(258, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(343, 3, 84, 84));
	player_animated_sprite.addFrame(sf::IntRect(428, 3, 84, 84));

	// Setup the NPC
	GameObject &npc = NPC(npc_animated_sprite);

	// Setup the Player
	GameObject &player = Player(player_animated_sprite);

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(npc.getAnimatedSprite().getPosition().x, npc.getAnimatedSprite().getPosition().y);
	aabb_npc.max = c2V(
		npc.getAnimatedSprite().getPosition().x +
		npc.getAnimatedSprite().getGlobalBounds().width, 
		npc.getAnimatedSprite().getPosition().y +
		npc.getAnimatedSprite().getGlobalBounds().height);

	//Setup Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(player.getAnimatedSprite().getPosition().x, player.getAnimatedSprite().getPosition().y);
	aabb_player.max = c2V(player.getAnimatedSprite().getGlobalBounds().width / 6, player.getAnimatedSprite().getGlobalBounds().width / 6);


	// Initialize Input
	Input input;

	// Collision result
	int result = 0;

	// Direction of movement of NPC
	sf::Vector2f direction(0.1f, 0.2f);
	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		player.getAnimatedSprite().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		
		// Move The NPC
		sf::Vector2f move_to(npc.getAnimatedSprite().getPosition().x + direction.x, npc.getAnimatedSprite().getPosition().y + direction.y);

		if (move_to.x < 0) {
			direction.x *= -1;
			move_to.x = 0 + npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.x + npc.getAnimatedSprite().getGlobalBounds().width >= 800) { 
			direction.x *= -1;
			move_to.x = 800 - npc.getAnimatedSprite().getGlobalBounds().width;
		}
		else if (move_to.y < 0) { 
			direction.y *= -1;
			move_to.y = 0 + npc.getAnimatedSprite().getGlobalBounds().height;
		}
		else if (move_to.y + npc.getAnimatedSprite().getGlobalBounds().height >= 600) {
			direction.y *= -1;
			move_to.y = 600 - npc.getAnimatedSprite().getGlobalBounds().height;
		}
		
		npc.getAnimatedSprite().setPosition(move_to);

		// Update NPC AABB set x and y
		aabb_npc.min = c2V(
			npc.getAnimatedSprite().getPosition().x, 
			npc.getAnimatedSprite().getPosition().y
		);

		aabb_npc.max = c2V(
			npc.getAnimatedSprite().getPosition().x +
			npc.getAnimatedSprite().getGlobalBounds().width,
			npc.getAnimatedSprite().getPosition().y +
			npc.getAnimatedSprite().getGlobalBounds().height
		);

		// Update Player AABB
		aabb_player.min = c2V(
			player.getAnimatedSprite().getPosition().x, 
			player.getAnimatedSprite().getPosition().y
		);
		aabb_player.max = c2V(
			player.getAnimatedSprite().getPosition().x +
			player.getAnimatedSprite().getGlobalBounds().width, 
			player.getAnimatedSprite().getPosition().y + 
			player.getAnimatedSprite().getGlobalBounds().height
		);

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					input.setCurrent(Input::Action::LEFT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					input.setCurrent(Input::Action::RIGHT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					input.setCurrent(Input::Action::UP);
				}
				break;
			default:
				input.setCurrent(Input::Action::IDLE);
				break;
			}
		}

		// Handle input to Player
		player.handleInput(input);

		// Update the Player
		player.update();

		// Update the Player
		npc.update();

		// Check for collisions
		result = c2AABBtoAABB(aabb_player, aabb_npc);
		cout << ((result != 0) ? ("Collision") : "") << endl;
		if (result){
			player.getAnimatedSprite().setColor(sf::Color(255,200,0));
		}
		else {
			player.getAnimatedSprite().setColor(sf::Color(100, 255, 0));
		}

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSprite());

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());


		//Capsule drawing
		window.draw(capCircle1);
		window.draw(capCircle2);
		window.draw(capRect);


		//Polygon drawing
		//window.draw(polyPoint1);
		//window.draw(polyPoint2);
		//window.draw(polyPoint3);


		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};