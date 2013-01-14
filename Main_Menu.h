#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "sprite.h"
#include "Constants.h"




//************************
// MAIN MENU CONSTANTS
//************************

// dimensions of the button sprites
#define BUTTON_WIDTH 400
#define BUTTON_HEIGHT 57

// locations of the button sprites
#define PLAY_X 50
#define PLAY_Y 100

#define OPTIONS_X 160
#define OPTIONS_Y 200

#define EXIT_X 375
#define EXIT_Y 300


// selection enum values corresponding to their listed location
enum SELECTIONS{
	PLAY_BUTTON,
	OPTIONS_BUTTON,
	EXIT_BUTTON
};



//*************************************************
// MAIN MENU STATE FUNCTION
// Returns the enum value for the next state
//
//*************************************************
int mainMenuState(bool* keys0, ALLEGRO_EVENT_QUEUE** event_queue0);




//***************************
// MAIN MENU FUNCTIONS
//***************************


//functions to move the menu selection up or down
void menuUp();
void menuDown();

//functions to advance button sprites
void advanceButton(int selection0);


// allegro event funcitons
void mm_executeEvent(ALLEGRO_EVENT ev0);

void mm_keyDownEvents(ALLEGRO_EVENT ev0);
void mm_keyUpEvents(ALLEGRO_EVENT ev0);
void mm_timerEvent();


