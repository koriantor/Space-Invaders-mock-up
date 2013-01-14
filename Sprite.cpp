#include "Sprite.h"



Sprite::Sprite(){
};


Sprite::Sprite ( ALLEGRO_BITMAP* spritesheet0, int COLUMNS0, int MAX_FRAMES0, int animationDelay0,
		int frameWidth0, int frameHeight0, int x0, int y0, int dx0, int dy0){
			

	spritesheet = spritesheet0;
	COLUMNS = COLUMNS0;
	
	MAX_FRAMES = MAX_FRAMES0;
	curFrame = 0;
	
	animationDelay = animationDelay0;
	delayCount = animationDelay;

	frameWidth = frameWidth0;
	frameHeight = frameHeight0;

	x = x0;
	y = y0;
	
	dx = dx0;
	dy = dy0;
}

void Sprite::draw(){
	al_draw_bitmap_region(spritesheet, (curFrame % COLUMNS) * frameWidth,
		(curFrame / COLUMNS) * frameHeight, frameWidth, frameHeight, x, y, 0);
}

//returns true only if the sprite's frame has changed
bool Sprite::stepFrame(){
	//increment deelay count
	if (delayCount <= animationDelay){
		delayCount++;
		return false;
	} 
	
	//otherwise, just decrement counter
	else {
		curFrame++;
		if (curFrame == MAX_FRAMES){
			curFrame = 0;
		}
		delayCount = 0;
		return true;
	}

}

void Sprite::move(){
	x += dx;
	y += dy;
}

//SET FUNCTIONS AS APPROPRIATE
//****************************
void Sprite::setX(int x0){
	x = x0;
	return;
}
void Sprite::setY(int y0){
	y = y0;
	return;
}
void Sprite::setDX(int dx0){
	dx = dx0;
	return;
}
void Sprite::setDY(int dy0){
	dy = dy0;
	return;
}
	



//ALLEGRO_BITMAP* getSpritesheet();
//int getSpriteRow();
//int getMaxFrames();
//int getCurFrame();
//int getAnimationDelay;


//GET FUNCTIONS AS APPROPRIATE
//****************************
int Sprite::getFrameWidth(){return frameWidth;}
int Sprite::getFrameHeight(){return frameHeight;}

int Sprite::getX(){return x;}
int Sprite::getY(){return y;}

int Sprite::getDX(){return dx;}
int Sprite::getDY(){return dy;}
