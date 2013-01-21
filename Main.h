#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

#include "sprite.h"
#include "Constants.h"
#include "Keys.h"
#include "Main_Menu.h"
#include "game.h"
#include "Title.h"





//************************
//GLOBAL CONSTANTS
//************************




//***************************
// GLOBAL VARIABLES
//***************************
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;


//array for all keys used in game
bool keys[KEYS_SIZE];


//variable to store current state
STATES current_state;




//********************************
// GLOBAL FUNCTIONS
//********************************

// Allegro macro functions
bool startAllegro ( int width0, int height0, ALLEGRO_DISPLAY** display0, ALLEGRO_EVENT_QUEUE** event_queue0, ALLEGRO_TIMER** timer0);

void nextState();
//*******************************