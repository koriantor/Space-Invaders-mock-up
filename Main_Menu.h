#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "sprite.h"
#include "Constants.h"
#include "State.h"




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
enum BUTTONS{
	PLAY_BUTTON,
	OPTIONS_BUTTON,
	EXIT_BUTTON
};

//************************






class MainMenu:public State{
private:

	//***************************
	// MAIN MENU VARIABLES
	//***************************

	//variable to store current buttton
	int selection;
	
	// these bools track keep track of when the up or down keys are actually being pressed
	bool key_up_still_pressed;
	bool key_down_still_pressed;

	
	// SPRITES
	//************
	ALLEGRO_BITMAP* play_button;
	Sprite Play_Button;
	ALLEGRO_BITMAP* options_button;
	Sprite Options_Button;
	ALLEGRO_BITMAP* exit_button;
	Sprite Exit_Button;

	
	//************************

	
public:

	MainMenu();

	MainMenu(bool* keys0, ALLEGRO_EVENT_QUEUE* event_queue0);
	
	
	
	//*************************************************
	// MAIN MENU STATE FUNCTION
	// Returns the enum value for the next state
	//
	//*************************************************
	STATES StateFunction();

	//********************
	// Timer/Screen update function
	//
	//********************
	void timerEvent();


	
	//***************************
	// MAIN MENU FUNCTIONS
	//***************************

	//functions to move the menu selection up or down
	void moveButtons();
	
	void menuUp();
	void menuDown();

	//function to advance button sprites
	void advanceButton(int selection0);

	//function to convert BUTTONS to STATES
	STATES BUTTONSToSTATES(int state0);

		
	//************************
};
