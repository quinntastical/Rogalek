#ifndef RESOURCETYPES_CLASS_HEADER
#define RESOURCETYPES_CLASS_HEADER
#include <allegro5\allegro.h>
#include "Resource.h"
class Sprite:public Resource{

private:
	int m_handle;
	ALLEGRO_BITMAP *m_bmp;
public:
	Sprite(const int handle, const std::string& name, const std::string& path = "./")
		:Resource(handle, name, path)
	{
		m_handle = handle;
		m_bmp = al_load_bitmap((this->getFileName().c_str()));
	}
	ALLEGRO_BITMAP* getBitmap()
	{
		return m_bmp;
	}
};
#endif