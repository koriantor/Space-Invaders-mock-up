#include "main.h"



int main (int argc, char** argv){

	//GLOBAL VARIABLE DECLARATIONS
	//****************************************
	done = false;
	render = true;

	//initialize all key states to false
	for (int i = 0; i < 6; i++){
		keys[i] = false;
	}


	//variable to control the title screen phase
	title_count = 0;


	//variable to store current state
	current_state = -1;


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

	



	// SPRITE SHEETS
	//*****************************************************************
	title = al_load_bitmap("title.png");
	//al_convert_mask_to_alpha(title, al_map_rgb(255, 0, 255));

	title_ship = al_load_bitmap("title_ship.png");
	al_convert_mask_to_alpha(title_ship, al_map_rgb(255, 0, 255));

	//*****************************************************************

	
	// DRAW FIRST FRAME 
	//*****************************************************************
	al_draw_bitmap(title, TITLE_X, TITLE_Y, 0);
	
	Title_Ship = Sprite(title_ship, 4, 4, 20, 48, 48, SHIP_X, SHIP_Y, 0, 0);
	Title_Ship.draw();

	al_flip_display();
	render = false;

	//*****************************************************************
















	//start timer right before loop
	al_start_timer(timer);


	//**GAME LOOP****GAME LOOP****GAME LOOP**
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		executeEvent(ev);

	}



	al_destroy_bitmap(title);
	al_destroy_bitmap(title_ship);
	
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
//Function will call the appropriate function to hadle the event handed to it
//
//********************

void executeEvent(ALLEGRO_EVENT ev0){
	
	//key down events
	if (ev0.type == ALLEGRO_EVENT_KEY_DOWN){
		keyDownEvents(ev0);
	}

	//key up events
	else if (ev0.type == ALLEGRO_EVENT_KEY_UP){
		keyUpEvents(ev0);
	}

	//timer events(frame refresh)
	else if (ev0.type == ALLEGRO_EVENT_TIMER){
		timerEvent();
	}
}


//********************
// Catch all function to store a key as pressed
//
//********************

void keyDownEvents(ALLEGRO_EVENT ev0){

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
		break;
			
	case ALLEGRO_KEY_DOWN:
		keys[DOWN] = true;
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

void keyUpEvents(ALLEGRO_EVENT ev0){

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

void timerEvent(){
	
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

	//Game state switching***********************************************************
	else {
		if (current_state == -1){
			current_state = MAIN_MENU;
		}

		switch(current_state){

		//enter Main menu state
		case MAIN_MENU:
			current_state = mainMenuState(keys, &event_queue);
			break;

		//enter the game state
		case GAME:
			current_state = gameState(keys, &event_queue);
			break;

		//enter Options menu state
		case OPTIONS_MENU:

			break;

		//exiting the game state
		case EXIT:
			done = true;
			break;

		}


		//done = true;



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