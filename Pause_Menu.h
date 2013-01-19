#pragma once 

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include "State.h"
#include "Sprite.h"

//****************************
// CONSTANTS
//****************************

#define PAUSE_BUTTON_WIDTH 400
#define PAUSE_BUTTON_HEIGHT 58

enum P_BUTTONS{
	PAUSE_RESUME,
	PAUSE_EXIT
};




class Pause_Menu:public State{
private:

	//************************
	// VARIABLES
	//************************
	
	int selection;

	// these bools track keep track of when the up or down keys are actually being pressed
	bool key_up_still_pressed;
	bool key_down_still_pressed;


	// SPRITES
	//************
	ALLEGRO_BITMAP* pause_title;
	ALLEGRO_BITMAP* pause_resume;
	ALLEGRO_BITMAP* pause_exit;
	
	Sprite Pause_Title;
	Sprite Pause_Resume;
	Sprite Pause_Exit;
	




public:
	Pause_Menu();
	Pause_Menu(bool* keys0, ALLEGRO_EVENT_QUEUE* event_queue0);
	~Pause_Menu();

	//*********************************
	// PAUSE MENU STATE FUNCTION
	//*********************************
	STATES StateFunction();

	//*********************************
	// Timer Event/Screen Update
	//*********************************
	void timerEvent();




	//functions to move the menu selection up or down
	void moveButtons();
	
	void menuUp();
	void menuDown();

	//function to advance button sprites
	void advanceButton();


};
