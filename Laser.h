#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#pragma once

class laser{
private:
	int spriteX;
	int spriteY;
	int width;
	int height;
	int posX;
	int posY;
	int speedX;
	int speedY;
	
public:
	laser();
	laser(int spriteX0, int spriteY0, int width0, int height0, int posX0, int posY0, int speedX0, int speedY0);
	
	void move();

	int getSpriteX();
	int getSpriteY();
	int getPosX();
	int getPosY();
	int getHeight();
	int getWidth();
	
	~laser();

};