#include "Main_Menu.h"


//***************************
// MAIN MENU VARIABLES
//***************************
namespace main_menu {
	bool done;
	bool render;

	//local pointer for keys array
	bool* keys;

	//variable to store current selection
	int selection;

	//Sprites for menu choices
	ALLEGRO_BITMAP* play_button;
	Sprite Play_Button;
	ALLEGRO_BITMAP* options_button;
	Sprite Options_Button;
	ALLEGRO_BITMAP* exit_button;
	Sprite Exit_Button;
}
using namespace main_menu;





//*************************************************
// MAIN MENU STATE FUNCTION
// Returns the enum value for the next state
//
//*************************************************
int mainMenuState(bool* keys0, ALLEGRO_EVENT_QUEUE** event_queue0){

	//GLOBAL VARIABLE DECLARATIONS
	//****************************************
	done = false;
	render = true;

	keys = keys0;

	//variable to store current selection
	selection = PLAY_BUTTON;
	
	
	//****************************************




	// first screen update
	//****************************************

	al_clear_to_color(al_map_rgb(0, 0, 0));

	// button sprites
	play_button = al_load_bitmap("main_menu_play.png");
	Play_Button = Sprite(play_button, 1, 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT, PLAY_X, PLAY_Y, 0, 0);

	options_button = al_load_bitmap("main_menu_options.png");
	Options_Button = Sprite(options_button, 1, 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT, OPTIONS_X, OPTIONS_Y, 0, 0);

	exit_button = al_load_bitmap("main_menu_exit.png");
	Exit_Button = Sprite(exit_button, 1, 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT, EXIT_X, EXIT_Y, 0, 0);

	//play button starts selected
	Play_Button.stepFrame();

	// draw buttons
	Play_Button.draw();
	Options_Button.draw();
	Exit_Button.draw();

	render = false;
	al_flip_display();


	//********************************************











	//**Main Menu loop****Main Menu loop****Main Menu loop****Main Menu loop****Main Menu loop**

	while(!done){
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(*event_queue0, &ev);

		mm_executeEvent(ev);

	}

	//delete bitmaps
	al_destroy_bitmap(play_button);
	al_destroy_bitmap(options_button);
	al_destroy_bitmap(exit_button);


	if (keys[ENTER])
		return selection + 1;
	else
		return 3;
}

//functions to move the menu selection up or down
void menuUp(){
	//advance old button sprite
	advanceButton(selection);
	
	//determine new selection
	if (--selection < PLAY_BUTTON){
		selection = EXIT_BUTTON;
	}

	//advance new button sprite
	advanceButton(selection);
}
void menuDown(){
	//advance old button sprite
	advanceButton(selection);

	//determine new selection
	if (++selection > EXIT_BUTTON){
		selection = PLAY_BUTTON;
	}

	//advance new button sprite
	advanceButton(selection);
}

//function to advance button sprites
void advanceButton(int selection0){
	switch(selection0){

	case PLAY_BUTTON:
		Play_Button.stepFrame();
		break;

	case OPTIONS_BUTTON:
		Options_Button.stepFrame();
		break;

	case EXIT_BUTTON:
		Exit_Button.stepFrame();
		break;
	}

	render = true;
}





// Event handling functions





//********************
//Function will call the appropriate function to hadle the event handed to it
//
//********************

void mm_executeEvent(ALLEGRO_EVENT ev0){
	
	//key down events
	if (ev0.type == ALLEGRO_EVENT_KEY_DOWN){
		mm_keyDownEvents(ev0);
	}

	//key up events
	else if (ev0.type == ALLEGRO_EVENT_KEY_UP){
		mm_keyUpEvents(ev0);
	}

	//timer events(frame refresh)
	else if (ev0.type == ALLEGRO_EVENT_TIMER){
		mm_timerEvent();
	}
}


//********************
// Catch all function to store a key as pressed
//
//********************

void mm_keyDownEvents(ALLEGRO_EVENT ev0){

	switch(ev0.keyboard.keycode){

		//*****************
		//
		// enum KEYS
		//
		// [0] - UP
		// [1] - DOWN
		// [2] - RIGHT
		// [3] - LEFT
		// [4] - SPACE
		// [5] - ENTER
		//
		//*****************

	case ALLEGRO_KEY_UP:
		keys[UP] = true;
		menuUp();
		break;
			
	case ALLEGRO_KEY_DOWN:
		keys[DOWN] = true;
		menuDown();
		break;
			
	case ALLEGRO_KEY_RIGHT:
		keys[RIGHT] = true;
		break;
			
	case ALLEGRO_KEY_LEFT:
		keys[LEFT] = true;
		break;

	case ALLEGRO_KEY_SPACE:
		keys[SPACE] = true;
		break;

	case ALLEGRO_KEY_ENTER:
		keys[ENTER] = true;
		break;
			
	}
}

//********************
// Catch-all fucntion to store a key as not pressed
//
//********************

void mm_keyUpEvents(ALLEGRO_EVENT ev0){

	switch(ev0.keyboard.keycode){

		//*****************
		//
		// enum KEYS
		//
		// [0] - UP
		// [1] - DOWN
		// [2] - RIGHT
		// [3] - LEFT
		// [4] - SPACE
		// [5] - ENTER
		//
		//*****************

	case ALLEGRO_KEY_UP:
		keys[UP] = false;
		break;
			
	case ALLEGRO_KEY_DOWN:
		keys[DOWN] = false;
		break;
			
	case ALLEGRO_KEY_RIGHT:
		keys[RIGHT] = false;
		break;

	case ALLEGRO_KEY_LEFT:
		keys[LEFT] = false;
		break;

	case ALLEGRO_KEY_SPACE:
		keys[SPACE] = false;
		break;

	case ALLEGRO_KEY_ENTER:
		keys[ENTER] = false;
		break;

	case ALLEGRO_KEY_ESCAPE:
		done = true;
		break;
	}
}

//********************
// Timer/Screen update function
//
//********************

void mm_timerEvent(){
	
	//*******************************************************
	// Update display's Metadata
	//
	//*******************************************************

	//check if selection hs been affirmed
	if (keys[ENTER]){
		done = true;
	}




	//*******************************************************
	// Refreshing the display (only refresh if render needed)
	//
	//*******************************************************

	if (render){

		//clear display
		al_clear_to_color(al_map_rgb(0,0,0));
	

		Play_Button.draw();
		Options_Button.draw();
		Exit_Button.draw();
		


		//display ready to flip
		render = false;
		al_flip_display();
	}  
}