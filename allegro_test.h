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




