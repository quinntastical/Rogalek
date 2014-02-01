#ifndef ACTOR_HEADER
#define ACTOR_HEADER
#include <allegro5\allegro.h>
class Actor
{
	public:
		Actor(void);
		void SetBitmap(ALLEGRO_BITMAP *bmp);
		void SetPos(int x, int y);
		void Draw(void);
		void Update(void);

	protected:
		int nPosX;
		int nPosY;
		ALLEGRO_BITMAP *nBitmap;
};
#endif