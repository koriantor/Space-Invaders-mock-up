#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#pragma once

class Sprite{
private:
	//Where is the sprite and how does it animate
	ALLEGRO_BITMAP* spritesheet;
	int COLUMNS;
	int MAX_FRAMES;
	int curFrame;
	int animationDelay;
	int delayCount;
	int frameWidth;
	int frameHeight;

	int x;
	int y;

	//speed variables
	int dx;
	int dy;



public:
	Sprite();

	Sprite ( ALLEGRO_BITMAP* spritesheet0, int COLUMNS0, int MAX_FRAMES0, int animationDelay0,
			int frameWidth0, int frameHeight0, int x0, int y0, int dx0, int dy0);

	void draw();

	bool stepFrame();

	void move();


	void setX(int x0);
	void setY(int y0);
	void setDX(int dx0);
	void setDY(int dy0);
	
	//ALLEGRO_BITMAP* getSpritesheet();
	//int getSpriteRow();
	//int getMaxFrames();
	//int getCurFrame();
	//int getAnimationDelay;

	int getFrameWidth();
	int getFrameHeight();

	int getX();
	int getY();

	int getDX();
	int getDY();

};