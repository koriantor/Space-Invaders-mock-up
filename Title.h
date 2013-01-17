#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "sprite.h"
#include "Constants.h"
#include "Keys.h"
#include "State.h"





//************************
//GLOBAL CONSTANTS
//************************

//Title Values
#define TITLE_X 110
#define TITLE_Y 96

#define SHIP_X 480
#define SHIP_Y 105

#define TITLE_FINISH 160



class Title: public State{
private:
	//***************************
	// VARIABLES
	//***************************


	//variables to control the title screen phase
	int title_count;

	//Title Sprites
	ALLEGRO_BITMAP* title;

	ALLEGRO_BITMAP* title_ship;
	Sprite Title_Ship;

	//*******************************

public:

	Title();

	Title(bool* keys0, ALLEGRO_EVENT_QUEUE* event_queue0);
	
	//******************************
	// THE ACTUAL TITLE FUNCTION
	//******************************
	
	virtual STATES StateFunction();

	void timerEvent();
};