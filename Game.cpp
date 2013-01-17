#include "game.h"



//***************************
// GLOBAL VARIABLES - moving these to cpp file
//***************************
namespace game{
	bool done;
	bool render;

	int laser_cooldown;

	//player's ship
	ship player;
	ALLEGRO_BITMAP* player_ship;

	//player's lasers
	vector<laser> player_lasers;
	ALLEGRO_BITMAP* player_laser;

	//array for all keys used in game
	bool *keys;


	//int for next state
	STATES next_state;
}

using namespace game;






 
STATES gameState(bool* keys0, ALLEGRO_EVENT_QUEUE** event_queue0){


	//GLOBAL VARIABLE DECLARATIONS
	//****************************************
	done = false;
	render = true;

	laser_cooldown = 0;

	keys = keys0;	

	next_state = MAIN_MENU;
	//***************************************

		
	

	

	//SPRITE SHEETS
	//*****************************************************************
	player_ship = al_load_bitmap("images/player_ship.png");
	al_convert_mask_to_alpha(player_ship, al_map_rgb(255,0,255));

	player_laser = al_load_bitmap("images/player_laser.png");
	al_convert_mask_to_alpha(player_laser, al_map_rgb(255,0,255));

	//*****************************************************************


	// create player ship object, then draw
	player = ship(player_ship, 4, 4, 30, 48, 48, WIDTH/2 - 24, HEIGHT - 48, 0, 0, 2, 2);
	player.draw();

	

	

	al_flip_display();
	render = false;









	//**GAME LOOP****GAME LOOP****GAME LOOP**
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(*event_queue0, &ev);

		g_executeEvent(ev);

	}


	// Destroy all lasers
	while(!player_lasers.empty()){
		//al_destroy_bitmap(player_lasers[0].image);
		player_lasers.erase(player_lasers.begin());
	}


	// Clean up allegro objects
	al_destroy_bitmap(player_ship);
	al_destroy_bitmap(player_laser);
 
	return next_state;
}




//********************
//Function will call the appropriate function to hadle the event handed to it
//
//********************

void g_executeEvent(ALLEGRO_EVENT ev0){
	
	//KEYBOARD EVENTS

	//key down events
	if (ev0.type == ALLEGRO_EVENT_KEY_DOWN){
		g_keyDownEvents(ev0);
	}

	//key up events
	else if (ev0.type == ALLEGRO_EVENT_KEY_UP){
		g_keyUpEvents(ev0);
	}

	//timer events(frame refresh)
	else if (ev0.type == ALLEGRO_EVENT_TIMER){
		g_timerEvent();
	}
}


//********************
// Catch all function to store a key as pressed
//
//********************

void g_keyDownEvents(ALLEGRO_EVENT ev0){

	switch(ev0.keyboard.keycode){


	case ALLEGRO_KEY_UP:
		keys[KEY_UP] = true;
		break;
			
	case ALLEGRO_KEY_DOWN:
		keys[KEY_DOWN] = true;
		break;
			
	case ALLEGRO_KEY_RIGHT:
		keys[KEY_RIGHT] = true;
		break;
			
	case ALLEGRO_KEY_LEFT:
		keys[KEY_LEFT] = true;
		break;

	case ALLEGRO_KEY_ENTER:
		keys[KEY_ENTER] = true;
		break;
			
	case ALLEGRO_KEY_SPACE:
		keys[KEY_SPACE] = true;
		break;

	}
}

//********************
// Catch-all fucntion to store a key as not pressed
//
//********************

void g_keyUpEvents(ALLEGRO_EVENT ev0){

	switch(ev0.keyboard.keycode){

	case ALLEGRO_KEY_UP:
		keys[KEY_UP] = false;
		break;

	case ALLEGRO_KEY_DOWN:
		keys[KEY_DOWN] = false;
		break;

	case ALLEGRO_KEY_RIGHT:
		keys[KEY_RIGHT] = false;
		break;

	case ALLEGRO_KEY_LEFT:
		keys[KEY_LEFT] = false;
		break;

	case ALLEGRO_KEY_SPACE:
		keys[KEY_SPACE] = false;
		break;

	case ALLEGRO_KEY_ENTER:
		keys[KEY_ENTER] = false;
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

void g_timerEvent(){
	//**********************************
	//Update the metadata for the display 
	//
	//**********************************


	//check player ship movement keys
	if (keys[KEY_RIGHT]){
		g_rightKeyEvents();
	}

	if (keys[KEY_LEFT]){
		g_leftKeyEvents();
	}
			
	//manage fire laser key
	if (keys[KEY_SPACE]){
		g_spaceKeyEvents();
	}

	if (laser_cooldown > 0){
		//decrement cooldown
		laser_cooldown--;
	}

	if (!player_lasers.empty()){
		//if there are still lasers on screen, then update them on the display
		render = true;
	}

	
	// animate and move player ship
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

void g_rightKeyEvents(){
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

void g_leftKeyEvents(){
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

void g_spaceKeyEvents(){
	//if able to fire laser
	if (laser_cooldown == 0){

		//make new laser
		player_lasers.push_back(laser(player_laser, 2, 2, 30, 48, 48, player.getX(), player.getY(), 0, LASER_SPEED, 2, 2));
		

	 
		//reset coodlown
		laser_cooldown = LASER_COOLDOWN;
	}
}

