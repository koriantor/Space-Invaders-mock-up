#include "game.h"
#include "Pause_Menu.h"









Game::Game(){}
 
Game::Game(bool* keys0, ALLEGRO_EVENT_QUEUE* event_queue0):
	State(keys0, event_queue0)
{


	// VARIABLE DECLARATIONS
	//**********************************************************

	laser_cooldown = 0;

	//set keys ENTER and ESCAPE to false so no over-flow of information
	keys[KEY_ENTER] = false;
	keys[KEY_ESCAPE] = false;

	next_state = MAIN_MENU;
	

	//SPRITES
	//***************************************
	player_ship = al_load_bitmap("images/player_ship.png");
	al_convert_mask_to_alpha(player_ship, al_map_rgb(255,0,255));

	player_laser = al_load_bitmap("images/player_laser.png");
	al_convert_mask_to_alpha(player_laser, al_map_rgb(255,0,255));
	
	//**********************************************************

}

Game::~Game(){

	// Destroy all lasers
	while(!player_lasers.empty()){
		//al_destroy_bitmap(player_lasers[0].image);
		player_lasers.erase(player_lasers.begin());
	}


	// Clean up allegro objects
	al_destroy_bitmap(player_ship);
	al_destroy_bitmap(player_laser);

}



//*************************************************
// GAME STATE FUNCTION
// Returns the enum value for the next state
//
//*************************************************
STATES Game::StateFunction(){

	// FIRST SCREEN UPDATE
	//********************************

	// create player ship object, then draw
	player = ship(player_ship, 4, 4, 30, 48, 48, WIDTH/2 - 24, HEIGHT - 48, 0, 0, 2, 2);
	player.draw();

	al_flip_display();
	render = false;
	//******************************************





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

void Game::timerEvent(){
	//**********************************
	//Update the metadata for the display 
	//
	//**********************************


	//check player ship movement keys
	if (keys[KEY_RIGHT]){
		Key_Right_Events();
	}

	if (keys[KEY_LEFT]){
		Key_Left_Events();
	}
			
	//manage fire laser key
	if (keys[KEY_SPACE]){
		Key_Space_Events();
	}

	if (keys[KEY_ESCAPE]){
		done = true;
	}

	//Pause Screen
	if (keys[KEY_ENTER]){
		Pause_Menu pause = Pause_Menu(keys, event_queue);
		if (pause.StateFunction() == next_state){
			done = true; 
			return;
		}

		//set keys ENTER and ESCAPE to false so no over-flow of information
		keys[KEY_ENTER] = false;
		keys[KEY_ESCAPE] = false;
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

void Game::Key_Right_Events(){
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

void Game::Key_Left_Events(){
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

void Game::Key_Space_Events(){
	//if able to fire laser
	if (laser_cooldown == 0){

		//make new laser
		player_lasers.push_back(laser(player_laser, 2, 2, 30, 48, 48, player.getX(), player.getY(), 0, LASER_SPEED, 2, 2));
		

	 
		//reset cooldown
		laser_cooldown = LASER_COOLDOWN;
	}
}

