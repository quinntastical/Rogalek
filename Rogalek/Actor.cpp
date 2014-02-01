#include "Actor.h"

Actor::Actor(void)
{
	this->nBitmap = NULL;
	this->nPosX = 0;
	this->nPosY = 0;
}

void Actor::SetBitmap(ALLEGRO_BITMAP *nBitmap)
{
	this->nBitmap = nBitmap;
}

void Actor::SetPos(int x, int y)
{
	this->nPosX = x;
	this->nPosY = y;
}