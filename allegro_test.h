//*************************************************************************
//
// This file contains all the global variables and functions for the game
// 
//
//************************************************************************


#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "Ship.h"
#include "Laser.h"

#pragma once

using namespace std;


//************************
//GLOBAL CONSTANTS
//************************

//dispaly values
#define WIDTH 720
#define HEIGHT 480

#define FPS 60.0

//laser values
#define LASER_SPEED -10
#define LASER_COOLDOWN 15

#define LASER_OFFSET 10

enum{
	RIGHT,
	LEFT,
	SPACE
};




//***************************
// GLOBAL VARIABLES
//***************************
bool done;
bool display_changed;

int laser_cooldown;

//player's ship
ship player;
ALLEGRO_BITMAP* player_spritesheet;
	
//player's lasers
vector<laser> player_lasers;

//array for all keys used in game
bool keys[3];





//********************************
// GLOBAL FUNCTIONS
//********************************

// Allegro macro functions
//ALLEGRO_DISPLAY* startAllegro(int width0, int height0);
bool startAllegro ( int width0, int height0, ALLEGRO_DISPLAY** display0, ALLEGRO_EVENT_QUEUE** event_queue0, ALLEGRO_TIMER** timer0);
ALLEGRO_EVENT_QUEUE* startEventQueue();

void executeEvent(ALLEGRO_EVENT ev0);

void keyDownEvents(ALLEGRO_EVENT ev0);
void keyUpEvents(ALLEGRO_EVENT ev0);
void timerEvent();

// Event for every key
void rightKeyEvents();
void leftKeyEvents();
void spaceKeyEvents();

//*******************************