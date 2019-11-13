//Niamh Andrews
//C00242944
//11-11-2019

#include <iostream>
#include <math.h>
#include <time.h>

class Point {
public:
	int x;
	int y;

	void print() {
		std::cout << "x: " << x << " y: " << y << std::endl;
	}
};

class Circle {
public:
	Point p;
	int r;

	void print() {
		std::cout << "x: " << p.x << "  y: " << p.y << "  r: " << static_cast<int>(r) << std::endl;
	}
};

class Box { 
public: 
	Point p; 
	int w; 
	int h; 
	void print() { 
		std::cout << "x: " << p.x << " y: " << p.y << " w: " << static_cast<int>(w) << " h: " << static_cast<int>(h) << std::endl;
	} 
};


int calculate_hypotenuse(Point a, Point b) {
	int result = 0;

	// Find the distance (Length) of X and Y  

	int x_Distance = b.x - a.x;
	int y_Distance = b.y - a.y;

	// Now that we have the distance (Length)
	// of x and y, use Pythagoras theorem 
	// to get the distance (length of hypotenuse) 
	// between Point a and Point b 
	result = sqrt(pow(x_Distance, 2) + pow(y_Distance, 2));



	return result;
}


int check_box_collision(Point a, int a_w, int a_h,
							Point b, int b_w, int b_h)
{

	//Check if the sides of either rectangle are touching
	if (a.x + a_w >= b.x &&    // player box right edge past npc box left
		a.x <= b.x + b_w &&    // player box left edge past npc box right
		a.y + a_h >= b.y &&    // player box top edge past npc box bottom
		a.y <= b.y + b_h) {    // player box bottom edge past npc box top
		return true;
	}


	return false;
}




int main() {

	srand(time(NULL));

	// Point Collision
	Point player_point;
	player_point.x = rand() % 10 + 1;
	player_point.y = rand() % 10 + 1;

	Point npc_point;
	npc_point.x = rand() % 10 + 1;
	npc_point.y = rand() % 10 + 1;

	// Circle Collision
	Circle player_circle;
	player_circle.p.x = rand() % 10 + 1;
	player_circle.p.y = rand() % 10 + 1;
	player_circle.r = rand() % 2 + 1;
	
	Circle npc_circle;
	npc_circle.p.x = rand() % 10 + 1;
	npc_circle.p.y = rand() % 10 + 1;
	npc_circle.r = rand() % 2 + 1;


	// Box Collision
	Box player_box;
	player_box.p.x = rand() % 10 + 1;
	player_box.p.y = rand() % 10 + 1;
	player_box.w = rand() % 5 + 1; 
	player_box.h = rand() % 5 + 1;

	Box npc_box;
	npc_box.p.x = rand() % 10 + 1;
	npc_box.p.y = rand() % 10 + 1;
	npc_box.w = rand() % 5 + 1;
	npc_box.h = rand() % 5 + 1;




	while (true) {
		
		// Point Collision check
		if (calculate_hypotenuse(player_point, npc_point) == 0)
		{
			std::cout << "\nPoint Collision" << std::endl;
			player_point.print();
			npc_point.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Collision" << std::endl;
			player_point.print();
			npc_point.print();
		}

		player_point.x = rand() % 10 + 1;
		player_point.y = rand() % 10 + 1;


		// Circle Collision check
		if (calculate_hypotenuse(player_circle.p, npc_circle.p) < (player_circle.r + npc_circle.r))
		{
			std::cout << "\nCircle Collision" << std::endl;
			player_circle.print();
			npc_circle.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Collision" << std::endl;
			player_circle.print();
			npc_circle.print();
		}

		player_circle.p.x = rand() % 10 + 1;
		player_circle.p.y = rand() % 10 + 1;






		
		// Circle to Point Collision check
		if (calculate_hypotenuse(player_circle.p, npc_point) < player_circle.r)
		{
			std::cout << "\nCircle to Point Collision" << std::endl;
			player_circle.print();
			npc_point.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Collision" << std::endl;
			player_circle.print();
			npc_point.print();
		}

		player_circle.p.x = rand() % 10 + 1;
		player_circle.p.y = rand() % 10 + 1;
		//player_circle.r = rand() % 2 + 1;




		// Box to Box Collision Check
		if (check_box_collision(player_box.p, player_box.w, player_box.h,
								npc_box.p, npc_box.w, npc_box.h) == true)
		{
			std::cout << "\nBox to Box Collision" << std::endl;
			player_box.print();

			npc_box.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Collision" << std::endl;
			player_box.print();
			npc_box.print();
		}

			player_box.p.x = rand() % 10 + 1;
			player_box.p.y = rand() % 10 + 1;
			player_box.w = rand() % 5 + 1;
			player_box.h = rand() % 5 + 1;
	}



}