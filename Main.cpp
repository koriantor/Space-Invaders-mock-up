#include "main.h"



int main (int argc, char** argv){

	//GLOBAL VARIABLE DECLARATIONS
	//****************************************

	//initialize all key states to false
	for (int i = 0; i < KEYS_SIZE; i++){
		keys[i] = false;
	}
	
	//variable to store current state
	current_state = TITLE;


	//****************************************




	//**ALLEGRO RELATED CODE**
	
	display = NULL;
	event_queue = NULL;
	timer = NULL;

	if (!startAllegro(WIDTH, HEIGHT, &display, &event_queue, &timer)){
		return -1;
	}

	
	// REGISTER ALLEGRO EVENTS
	//*****************************************************************

	//keyboard is an event source
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//timer is an event source
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//*****************************************************************

	




	//start timer right before loop
	al_start_timer(timer);


	//**GAME LOOP****GAME LOOP****GAME LOOP**
	while(current_state != EXIT){
		nextState();

	}

	
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

}



//*********************
// Function will start allegro and return a bool as to whether it successfully initialized everything
// - al_init()
// - al_init_image_addon()
// - al_install_keyboard()
// - al_create_display(width, height)
// - al_create_event_queue()
// - al_create_timer(1.0/FPS)
//
//*********************

bool startAllegro ( int width0, int height0, ALLEGRO_DISPLAY** display0, ALLEGRO_EVENT_QUEUE** event_queue0, ALLEGRO_TIMER** timer0){
	
	//initialize allegro
	if(!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to initialize allegro!", NULL, NULL);
		return NULL;
	}

	//initialize image addon
	if (!al_init_image_addon()){
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to initialize images!\n", NULL, NULL);
		return NULL;
	}

	//install keyboard
	if (!al_install_keyboard()){
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to install keyboard!\n", NULL, NULL);
		return NULL;
	}


	//try to make display
	*display0 = al_create_display(width0, height0);
	if(display0 == NULL) {
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to create display!\n", NULL, NULL);

		return false;
	} 


	//try to make event queue
	*event_queue0 = al_create_event_queue();
	if(event_queue0 == NULL) {
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to create event queue!\n", NULL, NULL);

		al_destroy_display(*display0);
		return false;
	}

	//try to make timer
	*timer0 = al_create_timer(1.0 / FPS);
	if(timer0 == NULL) {
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to create timer!\n", NULL, NULL);

		al_destroy_display(*display0);
		al_destroy_event_queue(*event_queue0);
		return false;
	}

	//display nuetral black screen immediately
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();

	return true;

}





//********************
// Game state switching
//
//********************

void nextState(){

	State* state;
	switch(current_state){

	case TITLE:
		state = new Title(keys, event_queue);
		break;

	case MAIN_MENU:
		state = new MainMenu(keys, event_queue);
		break;

	case GAME:
		current_state = gameState(keys, &event_queue);
		break;

	case OPTIONS_MENU://***
		break;

	//exit the program
	case EXIT:
		//should not ever reach this case, becase the state handling loop exts...
		break;
	}

	if (state != NULL){
		current_state = state->StateFunction();
		delete state;
	}

}