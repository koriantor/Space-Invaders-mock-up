#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

#include "sprite.h"
#include "Constants.h"
#include "Main_Menu.h"
#include "game.h"





//************************
//GLOBAL CONSTANTS
//************************




//Title Values
#define TITLE_X 110
#define TITLE_Y 96

#define SHIP_X 480
#define SHIP_Y 105

#define TITLE_FINISH 160








//***************************
// GLOBAL VARIABLES
//***************************
bool done;
bool render;

ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;


//array for all keys used in game
bool keys[6];


//variables to control the title screen phase
int title_count;

//Title Sprites
ALLEGRO_BITMAP* title;

ALLEGRO_BITMAP* title_ship;
Sprite Title_Ship;


//variable to store current state
int current_state;


//********************************
// GLOBAL FUNCTIONS
//********************************

// Allegro macro functions
bool startAllegro ( int width0, int height0, ALLEGRO_DISPLAY** display0, ALLEGRO_EVENT_QUEUE** event_queue0, ALLEGRO_TIMER** timer0);

void executeEvent(ALLEGRO_EVENT ev0);

void keyDownEvents(ALLEGRO_EVENT ev0);
void keyUpEvents(ALLEGRO_EVENT ev0);
void timerEvent();

 //Event for every key
//void rightKeyEvents();
//void leftKeyEvents();
//void spaceKeyEvents();

//*******************************