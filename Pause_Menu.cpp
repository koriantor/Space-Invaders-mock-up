#include "Pause_Menu.h"





Pause_Menu::Pause_Menu(){}

Pause_Menu::Pause_Menu(bool* keys0, ALLEGRO_EVENT_QUEUE* event_queue0):
	State(keys0, event_queue0)
{
	
	//************************
	// VARIABLES
	//************************

	selection = PAUSE_RESUME;

	//set keys ENTER and ESCAPE to false so no over-flow of information
	keys[KEY_ENTER] = false;
	keys[KEY_ESCAPE] = false;

	// these bools track keep track of when the up or down keys are actually being pressed
	key_up_still_pressed = false;
	key_down_still_pressed = false;


	// SPRITES
	//************
	pause_title = al_load_bitmap("images/pause_title.png");
	pause_resume = al_load_bitmap("images/pause_resume.png");
	pause_exit = al_load_bitmap("images/pause_exit.png");
	
	Pause_Title = Sprite(pause_title, 1, 1, 0, PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_HEIGHT, 0, 0, 0, 0);
	Pause_Resume = Sprite(pause_resume, 1, 2, 0, PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_HEIGHT, 0, 58, 0, 0);
	Pause_Exit = Sprite(pause_exit, 1, 2, 0, PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_HEIGHT, 0, 116, 0, 0);
}

Pause_Menu::~Pause_Menu(){
	al_destroy_bitmap(pause_title);
	al_destroy_bitmap(pause_resume);
	al_destroy_bitmap(pause_exit);
}


//*********************************
// PAUSE MENU STATE FUNCTION
//*********************************
STATES Pause_Menu::StateFunction(){
	
	//first frame update
	al_clear_to_color(al_map_rgb(0,0,0));

	Pause_Title.draw();
	Pause_Resume.stepFrame();
	Pause_Resume.draw();
	Pause_Exit.draw();
	
	al_flip_display();
	render = false;

	
	
	
	//**GAME LOOP****GAME LOOP****GAME LOOP**
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		executeEvent(ev);

	}

	return next_state;

}

//*********************************
// Timer Event/Screen Update
//*********************************
void Pause_Menu::timerEvent(){

	//check up and down keys and apply movement
	moveButtons();

	//check enter key for end of state
	if (keys[KEY_ENTER]){
		done = true;
		//MAKE A FUNCTION FOR THIS \/ YOU LAZY ASS
		if (selection == PAUSE_EXIT)
			next_state = MAIN_MENU;

		return;
	}

	if (keys[KEY_ESCAPE]){
		done = true;
		return;
	}


	
	//render if needed
	if (render){

		//simply update the buttons
		al_clear_to_color(al_map_rgb(0,0,0));
		
		Pause_Title.draw();
		Pause_Resume.draw();
		Pause_Exit.draw();
	
		al_flip_display();
		render = false;
		
	}
}




//***************************
// MAIN MENU FUNCTIONS
//***************************


//functions to move the menu selection
void Pause_Menu::moveButtons(){
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

void Pause_Menu::menuUp(){
	//advance old button sprite
	advanceButton();
	
	//determine new selection
	if (--selection < PAUSE_RESUME){
		selection = PAUSE_EXIT;
	}

	//advance new button sprite
	advanceButton();
}
void Pause_Menu::menuDown(){
	//advance old button sprite
	advanceButton();

	//determine new selection
	if (++selection > PAUSE_EXIT){
		selection = PAUSE_RESUME;
	}

	//advance new button sprite
	advanceButton();
}

//function to advance button sprites
void Pause_Menu::advanceButton(){
	switch(selection){

	case PAUSE_RESUME:
		Pause_Resume.stepFrame();
		break;

	case PAUSE_EXIT:
		Pause_Exit.stepFrame();
		break;
	}

	render = true;
}