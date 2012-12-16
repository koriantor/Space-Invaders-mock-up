#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "Ship.h"
#include "Laser.h"

using namespace std;


#define WIDTH 720
#define HEIGHT 480

#define FPS 60.0

#define LASER_SPEED -10
#define LASER_COOLDOWN 15

enum{
	RIGHT,
	LEFT,
	SPACE
};


//GLOBAL VARIABLES
//***************************
bool done;
bool display_changed = true;

int laser_cooldown = 0;

//player's ship
ship player;
	
//player's lasers
vector<laser> player_lasers;

//array for all keys used in game
bool keys[3];

//****************************


ALLEGRO_DISPLAY* startAllegro(int width0, int height0);

void keyDownEvents(ALLEGRO_EVENT ev0);
void keyUpEvents(ALLEGRO_EVENT ev0);
