#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "Ship.h"
#include "Laser.h"

using namespace std;




enum{
	RIGHT,
	LEFT,
	SPACE
};

 
int main(int argc, char **argv){


	//**GAME SPECIFIC VARIABLES**
	const int WIDTH = 720;
	const int HEIGHT = 480;

	bool done = false;
	bool display_changed = true;
	double FPS = 60.0;

	const int LASER_SPEED = 0;
	const int LASER_COOLDOWN = 15;
	int laser_cooldown = 0;
	laser* laser0;


	//player's ship
	ship player;
	//**player ship information
	player.spriteX = 0;
	player.spriteY = 0;
	player.width = 48;
	player.height = 48;
	player.posX = WIDTH/2 - player.width/2;
	player.posY = HEIGHT - player.height;
	player.speedX = 5;
	//**end player ship
	


	//player's lasers
	vector<laser> player_lasers;
	//**end player lasers





	//**ALLEGRO SPECIFIC CODE**
	
	if(!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to initialize allegro!", NULL, NULL);
		return -1;
	}
 
	//setup display
	ALLEGRO_DISPLAY *display = NULL;

	display = al_create_display(WIDTH, HEIGHT);
	if(!display) {
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to create display!\n", NULL, NULL);
		return -1;
	}
 
	//display nuetral black screen immediately
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();




	//setup keyboard
	al_install_keyboard();
	bool keys[3] = {false, false, false};




	//register events
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();

	//keyboard is an event source
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//timer is an event source
	ALLEGRO_TIMER *timer = NULL;
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));




	//initialize image addon and load sprites
	al_init_image_addon();

	//player's ship created
	ALLEGRO_BITMAP* player_spritesheet = al_load_bitmap("player_spritesheet.png");
	
	al_convert_mask_to_alpha(player_spritesheet, al_map_rgb(255,0,255));

	//draw ship
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

		//keyboard events

		//key down events
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN){

			switch(ev.keyboard.keycode){

				/*
				
				bool keys[3]

				[0] - RIGHT
				[1] - LEFT
				[2] - SPACE
				
				*/

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
		//key up events
		else if (ev.type == ALLEGRO_EVENT_KEY_UP){

			switch(ev.keyboard.keycode){

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


		//timer events(frame refresh)
		else{
			//check player ship movement
			if (keys[RIGHT]){
				if (player.posX <= 720 - player.width - player.speedX){
					player.posX += player.speedX;
					display_changed = true;
				}
			}

			if (keys[LEFT]){
				if (player.posX >= player.speedX){
					player.posX -= player.speedX;
					display_changed = true;
				}
			}
			
			//manage player lasers
			if (keys[SPACE]){
				if (laser_cooldown == 0){
					//make new laser
					const int LASER_OFFSET = 10;
					
	
					/*OLD CODE
					laser0 = new laser(player.posX, player.posY - LASER_OFFSET, 0, LASER_SPEED, "player_laser.png");
					//store laser
					player_lasers.push_back(*laser0);
					//*/
	
					player_lasers.push_back(laser(48, 0, 48, 48, player.posX, player.posY - LASER_OFFSET, 0, LASER_SPEED));
	
	
					//reset coodlown
					laser_cooldown = LASER_COOLDOWN;
				}
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
						
						/* OLD CODE
						ALLEGRO_BITMAP* image0 = al_load_bitmap( player_lasers[i].getFilename() );
						al_convert_mask_to_alpha(image0, al_map_rgb(255,0,255));
						//*/
	
	
						//draw sprite from data defined in laser object
						al_draw_bitmap_region ( player_spritesheet, 
											 player_lasers[i].getSpriteX(), player_lasers[i].getSpriteY(),
											 player_lasers[i].getWidth(), player_lasers[i].getHeight(), 
											 player_lasers[i].getPosX(), player_lasers[i].getPosY(),    0);
						player_lasers[i].move();
						
						/* OLD CODE
						//Destroy the bitmap before leaving the context
						al_destroy_bitmap(image0);
						//*/
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
	}

	//destroy all lasers
	//*
	while(!player_lasers.empty()){
		//al_destroy_bitmap(player_lasers[0].image);
		player_lasers.erase(player_lasers.begin());
	}//*/


	al_destroy_bitmap(player_spritesheet);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
 
	return 0;
}