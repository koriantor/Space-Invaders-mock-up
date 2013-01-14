#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "Ship.h"
#include "Laser.h"
#include "Constants.h"

#pragma once

using namespace std;


//************************
// GAME CONSTANTS
//************************

//PLAYER VALUES
#define PLAYER_SPEED 5

//laser values
#define LASER_SPEED -5
#define LASER_COOLDOWN 15



int gameState(bool* keys0, ALLEGRO_EVENT_QUEUE** event_queue0);


//********************************
// GAME FUNCTIONS
//********************************

void g_executeEvent(ALLEGRO_EVENT ev0);

void g_keyDownEvents(ALLEGRO_EVENT ev0);
void g_keyUpEvents(ALLEGRO_EVENT ev0);
void g_timerEvent();

// Event for every key
void g_rightKeyEvents();
void g_leftKeyEvents();
void g_spaceKeyEvents();

//*******************************