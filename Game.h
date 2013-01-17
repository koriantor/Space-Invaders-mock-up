#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "Ship.h"
#include "Laser.h"
#include "Constants.h"
#include "State.h"

#pragma once

using namespace std;


//************************
// GAME CONSTANTS
//************************

//PLAYER VALUES
#define PLAYER_SPEED 5

//laser values
#define LASER_SPEED -5
#define LASER_COOLDOWN 15




class Game:public State{
private:

	//***************************
	// GLOBAL VARIABLES
	//***************************


	//player's ship
	ship player;
	ALLEGRO_BITMAP* player_ship;

	//player's lasers
	vector<laser> player_lasers;
	ALLEGRO_BITMAP* player_laser;
	
	int laser_cooldown;

	//**************************

public:

	Game();
	Game(bool* keys0, ALLEGRO_EVENT_QUEUE* event_queue0);

	STATES StateFunction();
	void timerEvent();


	//********************************
	// GAME FUNCTIONS
	//********************************

	// Event for every key
	void Key_Right_Events();
	void Key_Left_Events();
	void Key_Space_Events();

	//*******************************


};