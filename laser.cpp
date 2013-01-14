#include "Laser.h"



laser::laser(){	
	Sprite();
}

laser::laser( ALLEGRO_BITMAP* spritesheet0, int COLUMNS0, int MAX_FRAMES0, int animationDelay0, 
		int frameWidth0, int frameHeight0, int x0, int y0, int dx0, int dy0, int boundX0, int boundY0)

	: Sprite (spritesheet0, COLUMNS0, MAX_FRAMES0, animationDelay0,
		frameWidth0, frameHeight0, x0, y0, dx0, dy0)
{

	boundX = boundX0;
	boundY = boundY0;
	

}


	
laser::~laser(){
}
