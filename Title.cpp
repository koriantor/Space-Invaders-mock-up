#include "Title.h"



Title::Title(){}

Title::Title(bool* keys0, ALLEGRO_EVENT_QUEUE* event_queue0):
	State(keys0, event_queue0)
{

	// VARIABLE DECLARATIONS
	//****************************************
	next_state = MAIN_MENU;

	
	//variable to "time" the title screen phase
	title_count = 0;


	
	// SPRITES
	//*****************************************************************
	title = al_load_bitmap("images/title.png");

	title_ship = al_load_bitmap("images/title_ship.png");
	al_convert_mask_to_alpha(title_ship, al_map_rgb(255, 0, 255));
	
	//Sprite object for the animated ship
	Title_Ship = Sprite(title_ship, 4, 4, 20, 48, 48, SHIP_X, SHIP_Y, 0, 0);

	//*****************************************************************

}

Title::~Title(){
	al_destroy_bitmap(title);
	al_destroy_bitmap(title_ship);
}



STATES Title::StateFunction(){
	
	// DRAW FIRST FRAME 
	//*****************************************************************
	
	//draw title text
	al_draw_bitmap(title, TITLE_X, TITLE_Y, 0);
	
	//draw title ship
	Title_Ship.draw();

	//show on screen
	al_flip_display();
	render = false;

	//*****************************************************************



	//**GAME LOOP****GAME LOOP****GAME LOOP**
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		executeEvent(ev);

	}

	return next_state;
}









//********************
// Timer/Screen update function
//
//********************

void Title::timerEvent(){
	
	//*******************************************************
	// Update display's Metadata
	//
	//*******************************************************

	//display title screen
	if (title_count <= TITLE_FINISH){
		
		//step the ship sprite animation, and render if changed
		if (Title_Ship.stepFrame()) {
			render = true;
		}

		title_count++;
	} 
	else {
		done = true;
	}

	



	//*******************************************************
	// Refreshing the display (only refresh if render needed)
	//
	//*******************************************************

	if (render){

		//clear display
		al_clear_to_color(al_map_rgb(0,0,0));
	

		//refresh the title screen
		al_draw_bitmap(title, TITLE_X, TITLE_Y, 0);
		Title_Ship.draw();
		


		//display ready to flip
		render = false;
		al_flip_display();
	}  
}