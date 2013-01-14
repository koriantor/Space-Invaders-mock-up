#include "allegro_test.h"



 
int main(int argc, char **argv){


	//GLOBAL VARIABLE DECLARATIONS
	//****************************************
	done = false;
	render = true;

	laser_cooldown = 0;

		

	//setup keyboard (with 3 keys for game)
	for (int i = 0; i < 3; i++){
		keys[i] = false;
	}
	//***************************************



	//**ALLEGRO RELATED CODE**
	
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	if (!startAllegro(WIDTH, HEIGHT, &display, &event_queue, &timer)){
		return -1;
	}

	
	//REGISTER EVENTS
	
	//keyboard is an event source
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//timer is an event source
	al_register_event_source(event_queue, al_get_timer_event_source(timer));


	

	//SPRITE SHEET
	player_ship = al_load_bitmap("player_ship.png");
	al_convert_mask_to_alpha(player_ship, al_map_rgb(255,0,255));

	player_laser = al_load_bitmap("player_laser.png");
	al_convert_mask_to_alpha(player_laser, al_map_rgb(255,0,255));

	// create player ship object, then draw
	player = ship(player_ship, 4, 4, 30, 48, 48, WIDTH/2 - 24, HEIGHT - 48, 0, 0, 2, 2);
	player.draw();

	

	

	al_flip_display();
	render = false;








	//start timer right before loop
	al_start_timer(timer);


	//**GAME LOOP****GAME LOOP****GAME LOOP**
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		executeEvent(ev);

	}


	// Destroy all lasers
	while(!player_lasers.empty()){
		//al_destroy_bitmap(player_lasers[0].image);
		player_lasers.erase(player_lasers.begin());
	}


	// Clean up allegro objects
	al_destroy_bitmap(player_ship);
	al_destroy_bitmap(player_laser);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
 
	return 0;
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
	
	//KEYBOARD EVENTS

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
		// bool keys[3]
		//
		// [0] - RIGHT
		// [1] - LEFT
		// [2] - SPACE
		//		
		//*****************

	case ALLEGRO_KEY_RIGHT:
		keys[RIGHT] = true;
		break;
			
	case ALLEGRO_KEY_LEFT:
		keys[LEFT] = true;
		break;

	case ALLEGRO_KEY_SPACE:
		keys[SPACE] = true;
		break;

	}
}

//********************
// Catch-all fucntion to store a key as not pressed
//
//********************

void keyUpEvents(ALLEGRO_EVENT ev0){

	switch(ev0.keyboard.keycode){

	case ALLEGRO_KEY_RIGHT:
		keys[RIGHT] = false;
		break;

	case ALLEGRO_KEY_LEFT:
		keys[LEFT] = false;
		break;

	case ALLEGRO_KEY_SPACE:
		keys[SPACE] = false;
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
	//**********************************
	//Update the metadata for the display 
	//
	//**********************************


	//check player ship movement keys
	if (keys[RIGHT]){
		rightKeyEvents();
	}

	if (keys[LEFT]){
		leftKeyEvents();
	}
			
	//manage fire laser key
	if (keys[SPACE]){
		spaceKeyEvents();
	}

	if (laser_cooldown > 0){
		//decrement cooldown
		laser_cooldown--;
	}

	if (!player_lasers.empty()){
		//if there are still lasers on screen, then update them on the display
		render = true;
	}

	
	//NEW CODE : animate and move player ship
	if (player.stepFrame()){
		render = true;
	}

		


	//*******************************************************
	// Refreshing the display (only refresh if render needed)
	//
	//*******************************************************

	if (render){

		//clear display
		al_clear_to_color(al_map_rgb(0,0,0));
	

		//draw lasers and destroy old lasers			
		for (size_t i = 0; i < player_lasers.size(); i++){

			if (player_lasers[i].getY() > 0 - player_lasers[i].getFrameHeight()){
					
				//draw laser sprite from data defined in laser object
				player_lasers[i].draw();

				//step the lasers by one and move them
				player_lasers[i].stepFrame();
				player_lasers[i].move();
						
						
			}else{
				player_lasers.erase(player_lasers.begin() + i);
				i--;
			}
		}

		
		// draw ship
		player.draw();
	
		


		//display ready to flip
		render = false;
		al_flip_display();
	}  
}


//********************
//Perform all calculations related to the right arrow key pressed
//
//********************

void rightKeyEvents(){
	player.setDX(PLAYER_SPEED);
	if (player.getX() <= 720 - player.getFrameWidth() - PLAYER_SPEED){
		player.move();
		render = true;
	}
}

//********************
//Perform all calculations related to the Left Arrow key pressed
//
//********************

void leftKeyEvents(){
	player.setDX(-PLAYER_SPEED);
	if (player.getX() >= PLAYER_SPEED){
		player.move();
		render = true;
	}
}

//********************
//Perform all calculations related to the Space key pressed
//
//********************

void spaceKeyEvents(){
	//if able to fire laser
	if (laser_cooldown == 0){

		//make new laser
		player_lasers.push_back(laser(player_laser, 2, 2, 30, 48, 48, player.getX(), player.getY(), 0, LASER_SPEED, 2, 2));
		

	 
		//reset coodlown
		laser_cooldown = LASER_COOLDOWN;
	}
}

