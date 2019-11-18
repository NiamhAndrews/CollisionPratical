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
#include <math.h>

using namespace std;




int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	bool circleActive = false;








	//Capsule creation
	int capLenght = 50;
	int capRadius = 15;
	sf::CircleShape capCircle1;
	sf::CircleShape capCircle2;
	sf::RectangleShape capRect;

	capCircle1.setRadius(capRadius);
	capCircle2.setRadius(capRadius);
	capRect.setSize(sf::Vector2f((capRadius * 2), capLenght));

	capCircle1.setPosition(200, 200);
	capCircle2.setPosition(200, (200 + capLenght));
	capRect.setPosition(200, (200 + capRadius));

	capCircle1.setFillColor(sf::Color::Color(50, 168, 82));
	capCircle2.setFillColor(sf::Color::Color(50, 168, 82));
	capRect.setFillColor(sf::Color::Color(50, 168, 82));

	//Set up capsule collision
	c2Capsule collisionCapsule;
	collisionCapsule.a.x = capCircle1.getPosition().x + capRadius;
	collisionCapsule.a.y = capCircle1.getPosition().y + capRadius;

	collisionCapsule.b.x = capCircle2.getPosition().x + capRadius;
	collisionCapsule.b.y = capCircle2.getPosition().y + capRadius;

	collisionCapsule.r = capRadius;





	//Polygon creation
	sf::VertexArray poly{ sf::Triangles, 3 };
	poly.clear();

	sf::Vector2f position = { 300.0f, 100.0f };
	sf::Vector2f size = { 100.0f, 100.0f };

	poly.append({ {position.x + (size.x / 2.0f), position.y}, sf::Color(69, 200, 42) });
	poly.append({ {position.x + size.x, position.y + size.y}, ::Color(69, 200, 42) });
	poly.append({ { position.x, position.y + size.y }, sf::Color(69, 200, 42) });

	//Set up Poly collision
	c2Poly collisionPoly;
	collisionPoly.count = 3;
	collisionPoly.verts[0] = { poly[0].position.x, poly[0].position.y };
	collisionPoly.verts[1] = { poly[1].position.x, poly[1].position.y };
	collisionPoly.verts[2] = { poly[2].position.x, poly[2].position.y };

	c2MakePoly(&collisionPoly);




	//Ray creation
	sf::VertexArray ray{ sf::Lines };
	ray.clear();

	ray.append({ { 650.0f, 300.0f }, sf::Color(250, 161, 37) });
	ray.append({ { 750.0f, 100.0f }, sf::Color(37, 232, 250) });

	c2Ray collisionRay;

	sf::Vector2f distanceVector = ray[1].position - ray[0].position;
	float magnitude = sqrt((distanceVector.x * distanceVector.x) + (distanceVector.y * distanceVector.y));
	sf::Vector2f unitVector = distanceVector / magnitude;

	collisionRay.p = { ray[0].position.x, ray[0].position.y };
	collisionRay.t = magnitude;
	collisionRay.d = { unitVector.x, unitVector.y};

	c2Raycast rayCast;








	//Circle shape
	sf::CircleShape playerCirc;
	int circRadius = 40;
	playerCirc.setRadius(circRadius);
	playerCirc.setPosition(400, 400);
	playerCirc.setFillColor(sf::Color::Color(151, 37, 250));

	c2Circle playerCircle;
	playerCircle.p = { playerCirc.getPosition().x - circRadius, playerCirc.getPosition().y - circRadius };
	playerCircle.r = circRadius;


	sf::CircleShape npcCirc;
	int npcRadius = 40;
	npcCirc.setRadius(circRadius);
	npcCirc.setPosition(500, 500);
	npcCirc.setFillColor(sf::Color::Color(250, 37, 186));
	
	c2Circle collisionCircle;
	collisionCircle.p = { npcCirc.getPosition().x + npcRadius, npcCirc.getPosition().y + (circRadius) };
	collisionCircle.r = npcRadius;














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
		playerCirc.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		playerCircle.p.x = playerCirc.getPosition().x + playerCircle.r;
		playerCircle.p.y = playerCirc.getPosition().y + playerCircle.r;

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
				if (sf::Keyboard::Space == event.key.code)
				{
					circleActive = !circleActive;
				}
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


		if (!circleActive)
		{

			// Check for collisions for aabb to aabb
			if (c2AABBtoAABB(aabb_player, aabb_npc))
			{
				std::cout << "Collision aabb to aabb" << std::endl;
				player.getAnimatedSprite().setColor(sf::Color(255, 200, 0));
			}
			else
			{
				player.getAnimatedSprite().setColor(sf::Color(100, 255, 0));
			}

			//Check sollision for AABB to Crapsule
			if (c2AABBtoCapsule(aabb_player, collisionCapsule))
			{
				std::cout << "Collision AABB to Capsule" << std::endl;
				capCircle1.setFillColor(sf::Color(255, 200, 0));
				capCircle2.setFillColor(sf::Color(255, 200, 0));
				capRect.setFillColor(sf::Color(255, 200, 0));
			}
			else
			{
				capCircle1.setFillColor(sf::Color(50, 168, 82));
				capCircle2.setFillColor(sf::Color(50, 168, 82));
				capRect.setFillColor(sf::Color(50, 168, 82));
			}


			//Check collision for AABB to Polygon
			if (c2AABBtoPoly(aabb_player, &collisionPoly, NULL))
			{
				std::cout << "Collision AABB to Poly" << std::endl;
				poly.clear();
				poly.append({ {position.x + (size.x / 2.0f), position.y}, sf::Color::Color(42, 42, 42) });
				poly.append({ {position.x + size.x, position.y + size.y}, sf::Color::Color(245, 99, 66) });
				poly.append({ { position.x, position.y + size.y }, sf::Color::Color(245, 99, 66) });
			}
			else
			{
				poly.clear();
				poly.append({ {position.x + (size.x / 2.0f), position.y}, sf::Color::Color(69, 200, 42) });
				poly.append({ {position.x + size.x, position.y + size.y}, sf::Color::Color(69, 200, 42) });
				poly.append({ { position.x, position.y + size.y }, sf::Color::Color(42, 42, 42) });
			}



			//Check collision for AABB to Ray
			if (c2CastRay(collisionRay, &aabb_player, nullptr, C2_AABB, &rayCast))
			{
				std::cout << "Collision AABB to Ray" << std::endl;
				ray.clear();
				ray.append({ { 650.0f, 300.0f }, sf::Color(37, 232, 250) });
				ray.append({ { 750.0f, 100.0f }, sf::Color(250, 161, 37) });
			}
			else
			{
				ray.clear();
				ray.append({ { 650.0f, 300.0f }, sf::Color(250, 161, 37) });
				ray.append({ { 750.0f, 100.0f }, sf::Color(37, 232, 250) });
			}
		}
		else //If circle IS active
		{
			//Check collisison for CIRCLE to Circle
			if (c2CircletoCircle(playerCircle, collisionCircle))
			{
				std::cout << "Collision CIRCLE to Circle" << std::endl;


				npcCirc.setFillColor(sf::Color(252, 118, 111));
			}
			else
			{
				npcCirc.setFillColor(sf::Color::Color(250, 37, 186));
			}



			//Check collision for Circle to AABB
			if (c2CircletoAABB(playerCircle, aabb_npc))
			{
				std::cout << "Collision CIRCLE to AABB" << std::endl;
			}



			//Check collision for Circle to Capsule
			if (c2CircletoCapsule(playerCircle, collisionCapsule))
			{
				std::cout << "Collision CIRCLE to Capsule" << std::endl;
				capCircle1.setFillColor(sf::Color(255, 200, 0));
				capCircle2.setFillColor(sf::Color(255, 200, 0));
				capRect.setFillColor(sf::Color(255, 200, 0));
			}
			else
			{
				capCircle1.setFillColor(sf::Color(50, 168, 82));
				capCircle2.setFillColor(sf::Color(50, 168, 82));
				capRect.setFillColor(sf::Color(50, 168, 82));
			}
			

			//Check collision for Circle to Poly
			if (c2CircletoPoly(playerCircle, &collisionPoly, NULL))
			{
				std::cout << "Collision CIRCLE to Poly" << std::endl;
				poly.clear();
				poly.append({ {position.x + (size.x / 2.0f), position.y}, sf::Color::Color(42, 42, 42) });
				poly.append({ {position.x + size.x, position.y + size.y}, sf::Color::Color(245, 99, 66) });
				poly.append({ { position.x, position.y + size.y }, sf::Color::Color(245, 99, 66) });
			}
			else
			{
				poly.clear();
				poly.append({ {position.x + (size.x / 2.0f), position.y}, sf::Color::Color(69, 200, 42) });
				poly.append({ {position.x + size.x, position.y + size.y}, sf::Color::Color(69, 200, 42) });
				poly.append({ { position.x, position.y + size.y }, sf::Color::Color(42, 42, 42) });
			}

			//Check collision for Circle to Ray
			if (c2CastRay(collisionRay, &playerCircle, nullptr, C2_AABB, &rayCast))
			{
				std::cout << "Collision CIRCLE to Ray" << std::endl;
				ray.clear();
				ray.append({ { 650.0f, 300.0f }, sf::Color(37, 232, 250) });
				ray.append({ { 750.0f, 100.0f }, sf::Color(250, 161, 37) });
			}
			else
			{
				ray.clear();
				ray.append({ { 650.0f, 300.0f }, sf::Color(250, 161, 37) });
				ray.append({ { 750.0f, 100.0f }, sf::Color(37, 232, 250) });
			}



		}




		// Clear screen
		window.clear();



		if (circleActive == false)
		{
			// Draw the Players Current Animated Sprite
			window.draw(player.getAnimatedSprite());
		}
		else
		{
			window.draw(playerCirc);
		}


		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSprite());


		//Capsule drawing
		window.draw(capCircle1);
		window.draw(capCircle2);
		window.draw(capRect);


		//Polygon drawing
		window.draw(poly);

		//Ray drawing
		window.draw(ray);

		//Circle drawing

		window.draw(npcCirc);




		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};