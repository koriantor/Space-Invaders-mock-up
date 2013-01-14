#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Sprite.h"

#pragma once

class ship : public Sprite{
private:
	//hitbox variables
	int boundX;
	int boundY;
	
public:
	ship();

	ship (ALLEGRO_BITMAP* spritesheet0, int COLUMNS0, int MAX_FRAMES0, int animationDelay0,
			int frameWidth0, int frameHeight0, int x0, int y0, int dx0, int dy0, int boundX0, int boundY0);
	

	
	~ship();

};




/* OLD CODE
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>

#pragma once

struct ship{
	int spriteX;
	int spriteY;
	int width;
	int height;
	int posX;
	int posY;
	int speedX;
};
// END OLD CODE*/