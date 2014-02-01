#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER
#include <string>
#include <allegro5\allegro.h>
#include "Resource.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"
class Graphics
{
public:
	void DrawSprite(const std::string& name, int x, int y, int flags, ResourceManager<Sprite>& SpriteManager, const std::string &path = "./")
	{
		al_draw_bitmap(SpriteManager.getElement(name)->getBitmap(),x,y,flags);
	}
};
#endif