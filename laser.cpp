#include "Laser.h"



laser::laser(){	
}

laser::laser(int spriteX0, int spriteY0, int width0, int height0, int posX0, int posY0, int speedX0, int speedY0){
	spriteX = spriteX0;
	spriteY = spriteY0;
	width = width0;
	height = height0;
	posX = posX0;
	posY = posY0;
	speedX = speedX0;
	speedY = speedY0;
}

void laser::move(){
	posX += speedX;
	posY += speedY;
}

int laser::getSpriteX(){return spriteX;}
int laser::getSpriteY(){return spriteY;}
int laser::getPosX(){return posX;}
int laser::getPosY(){return posY;}
int laser::getHeight(){return height;}
int laser::getWidth(){return width;}
	
laser::~laser(){
}
