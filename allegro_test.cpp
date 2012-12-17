#include "allegro_test.h"



 
int main(int argc, char **argv){


	//GLOBAL VARIABLE DECLARATIONS
	//****************************************
	done = false;
	display_changed = true;

	laser_cooldown = 0;


	//**player ship information
	player.spriteX = 0;
	player.spriteY = 0;
	player.width = 48;
	player.height = 48;
	player.posX = WIDTH/2 - player.width/2;
	player.posY = HEIGHT - player.height;
	player.speedX = 5;
	//**end player ship
	

	//setup keyboard (with 3 keys for game)
	for (int i = 0; i < 3; i++){
		keys[i] = false;
	}
	//***************************************



	//**ALLEGRO RELATED CODE**
	
	
	//call allegro start funcion and verify succesful start
	ALLEGRO_DISPLAY *display = startAllegro(WIDTH, HEIGHT);

	if (display == NULL){
		return -1;
	}

	

	//REGISTER EVENTS
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();

	//keyboard is an event source
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//timer is an event source
	ALLEGRO_TIMER *timer = NULL;
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));


	

	//MASTER SPRITE SHEET
	player_spritesheet = al_load_bitmap("player_spritesheet.png");
	al_convert_mask_to_alpha(player_spritesheet, al_map_rgb(255,0,255));

	//draw player ship in starting position
	al_draw_bitmap_region(player_spritesheet, player.spriteX, player.spriteY,
						 player.width, player.height, player.posX, player.posY, 0);

	al_flip_display();
	display_changed = false;








	//start timer right before loop
	al_start_timer(timer);


	//**GAME LOOP****GAME LOOP****GAME LOOP**
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		executeEvent(ev);

		////KEYBOARD EVENTS

		////key down events
		//if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
		//	keyDownEvents(ev);
		//}

		////key up events
		//else if (ev.type == ALLEGRO_EVENT_KEY_UP){
		//	keyUpEvents(ev);
		//}

		////timer events(frame refresh)
		//else if (ev.type == ALLEGRO_EVENT_TIMER){
		//	timerEvent();

		////	//check player ship movement keys
		////	if (keys[RIGHT]){
		////		rightKeyEvents();
		////	}

		////	if (keys[LEFT]){
		////		leftKeyEvents();
		////	}
		////	
		////	//manage fire laser key
		////	if (keys[SPACE]){
		////		spaceKeyEvents();
		////	}

		////	if (laser_cooldown > 0){
		////		//decrement cooldown
		////		laser_cooldown--;
		////	}

		////	if (!player_lasers.empty()){
		////		//if there are still lasers on screen, then update them on the display
		////		display_changed = true;
		////	}
		////	



		////	//handling the display (only refresh if display has changed)
		////	if (display_changed){

		////		//clear display
		////		al_clear_to_color(al_map_rgb(0,0,0));
	
		////		//draw lasers and destroy old lasers			
		////		for (size_t i = 0; i < player_lasers.size(); i++){
		////			if (player_lasers[i].getPosY() > 0 - player_lasers[i].getHeight()){
		////				
		////					
	
		////				//draw laser sprite from data defined in laser object
		////				al_draw_bitmap_region ( player_spritesheet, 
		////									 player_lasers[i].getSpriteX(), player_lasers[i].getSpriteY(),
		////									 player_lasers[i].getWidth(), player_lasers[i].getHeight(), 
		////									 player_lasers[i].getPosX(), player_lasers[i].getPosY(),    0);
		////				player_lasers[i].move();
		////				
		////				
		////			}else{
		////				player_lasers.erase(player_lasers.begin() + i);
		////				i--;
		////			}
		////		}
	


		////		//draw ship from sprite sheet from data in ship object
		////		//(maybe animate later?)
		////		al_draw_bitmap_region ( player_spritesheet, 
		////							 player.spriteX, player.spriteY, 
		////							 player.width, player.height,
		////							 player.posX, player.posY,      0);
		////		



		////		//display ready to flip
		////		display_changed = false;
		////		al_flip_display();
		////	}
		////}   
	
		//}
	}


	// Destroy all lasers
	while(!player_lasers.empty()){
		//al_destroy_bitmap(player_lasers[0].image);
		player_lasers.erase(player_lasers.begin());
	}


	// Clean up allegro objects
	al_destroy_bitmap(player_spritesheet);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
 
	return 0;
}


//*********************
// Function will start allegro and return a functional display pointer, or null pointer(if failed)
// - al_init()
// - al_init_image_addon()
// - al_install_keyboard()
// - al_create_display(width, height)
//
//*********************

ALLEGRO_DISPLAY* startAllegro(int width0, int height0){
	
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

	//setup display
	ALLEGRO_DISPLAY *display = NULL;

	display = al_create_display(width0, height0);
	if(!display) {
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to create display!\n", NULL, NULL);
		return NULL;
	}
 
	//display nuetral black screen immediately
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();	
	return display;
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
		display_changed = true;
	}
		



	//handling the display (only refresh if display has changed)
	if (display_changed){

		//clear display
		al_clear_to_color(al_map_rgb(0,0,0));
	
		//draw lasers and destroy old lasers			
		for (size_t i = 0; i < player_lasers.size(); i++){
			if (player_lasers[i].getPosY() > 0 - player_lasers[i].getHeight()){
					
				//draw laser sprite from data defined in laser object
				al_draw_bitmap_region ( player_spritesheet, 
									 player_lasers[i].getSpriteX(), player_lasers[i].getSpriteY(),
									 player_lasers[i].getWidth(), player_lasers[i].getHeight(), 
									 player_lasers[i].getPosX(), player_lasers[i].getPosY(),    0);
				player_lasers[i].move();
						
						
			}else{
				player_lasers.erase(player_lasers.begin() + i);
				i--;
			}
		}
	


		//draw ship from sprite sheet from data in ship object
		//(maybe animate later?)
		al_draw_bitmap_region ( player_spritesheet, 
							 player.spriteX, player.spriteY, 
							 player.width, player.height,
							 player.posX, player.posY,      0);
				



		//display ready to flip
		display_changed = false;
		al_flip_display();
	}  
}

//********************
//Perform all calculations related to the right arrow key pressed
//
//********************

void rightKeyEvents(){
	if (player.posX <= 720 - player.width - player.speedX){
		player.posX += player.speedX;
		display_changed = true;
	}
}

//********************
//Perform all calculations related to the Left Arrow key pressed
//
//********************

void leftKeyEvents(){
	if (player.posX >= player.speedX){
		player.posX -= player.speedX;
		display_changed = true;
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
		player_lasers.push_back(laser(48, 0, 48, 48, player.posX, player.posY - LASER_OFFSET, 0, LASER_SPEED));

	 
		//reset coodlown
		laser_cooldown = LASER_COOLDOWN;
	}
}

