#include "Main_Menu.h"





MainMenu::MainMenu(){}

MainMenu::MainMenu(bool* keys0, ALLEGRO_EVENT_QUEUE* event_queue0):
	State(keys0, event_queue0){
	
	//***************************
	// MAIN MENU VARIABLES
	//***************************
	
	//variable to store current selection
	selection = PLAY_BUTTON;

	//set keys ENTER and ESCAPE to false so no over-flow of information
	keys[KEY_ENTER] = false;
	keys[KEY_ESCAPE] = false;
	
	// these bools track keep track of when the up or down keys are actually being pressed
	bool key_up_still_pressed = false;
	bool key_down_still_pressed = false;


	// SPRITES
	//************
	play_button = al_load_bitmap("images/main_menu_play.png");
	Play_Button = Sprite(play_button, 1, 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT, PLAY_X, PLAY_Y, 0, 0);

	options_button = al_load_bitmap("images/main_menu_options.png");
	Options_Button = Sprite(options_button, 1, 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT, OPTIONS_X, OPTIONS_Y, 0, 0);

	exit_button = al_load_bitmap("images/main_menu_exit.png");
	Exit_Button = Sprite(exit_button, 1, 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT, EXIT_X, EXIT_Y, 0, 0);

	//************************
}
	
MainMenu::~MainMenu(){
	//delete bitmaps
	al_destroy_bitmap(play_button);
	al_destroy_bitmap(options_button);
	al_destroy_bitmap(exit_button);
}	
	



//*************************************************
// MAIN MENU STATE FUNCTION
// Returns the enum value for the next state
//
//*************************************************

STATES MainMenu::StateFunction(){

	// first screen update
	//****************************************
	
	//play button starts selected
	Play_Button.stepFrame();

	// draw buttons
	al_clear_to_color(al_map_rgb(0, 0, 0));
	Play_Button.draw();
	Options_Button.draw();
	Exit_Button.draw();

	render = false;
	al_flip_display();


	//********************************************











	//**Main Menu loop****Main Menu loop****Main Menu loop****Main Menu loop****Main Menu loop**

	while(!done){
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		executeEvent(ev);

	}


	if (keys[KEY_ENTER])
		return BUTTONSToSTATES(selection);
	else
		return EXIT;
}



//********************
// Timer/Screen update function
//
//********************

void MainMenu::timerEvent(){
	
	//*******************************************************
	// Update display's Metadata
	//
	//*******************************************************

	//default exit
	//if (keys[KEY_ESCAPE]){
	//	done = true;
	//	return;
	//}

	//check if selection has been affirmed
	if (keys[KEY_ENTER] || keys[KEY_ESCAPE]){
		done = true;
		return;
	}

	
	//maybe move button selection
	moveButtons();
	
	
	
	


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





//***************************
// MAIN MENU FUNCTIONS
//***************************


//functions to move the menu selection
void MainMenu::moveButtons(){
	//if key was just pressed, then move button and update still_pressed bools
	//if key was just released, then update still_pressed bools
	
	//key up
	if (keys[KEY_UP] && !key_up_still_pressed){
		menuUp();
		key_up_still_pressed = true;
	}
	else if (!keys[KEY_UP] && key_up_still_pressed){
		key_up_still_pressed = false;
	}
	
	//key down
	if (keys[KEY_DOWN] && !key_down_still_pressed){
		menuDown();
		key_down_still_pressed = true;
	}
	else if (!keys[KEY_DOWN] && key_down_still_pressed){
		key_down_still_pressed = false;
	}
}

void MainMenu::menuUp(){
	//advance old button sprite
	advanceButton();
	
	//determine new selection
	if (--selection < PLAY_BUTTON){
		selection = EXIT_BUTTON;
	}

	//advance new button sprite
	advanceButton();
}
void MainMenu::menuDown(){
	//advance old button sprite
	advanceButton();

	//determine new selection
	if (++selection > EXIT_BUTTON){
		selection = PLAY_BUTTON;
	}

	//advance new button sprite
	advanceButton();
}

//function to advance button sprites
void MainMenu::advanceButton(){
	switch(selection){

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

//function to change BUTTONS to STATES
STATES MainMenu::BUTTONSToSTATES(int state0){
	switch (state0){		
	case PLAY_BUTTON: 		return GAME; 			break;
	case OPTIONS_BUTTON: 	return OPTIONS_MENU; 	break;
	case EXIT_BUTTON: 		return EXIT; 			break;
	default:				return EXIT;			break;
	}
}





