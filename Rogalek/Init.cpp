#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Init.h"

bool Init::initAllegro(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, const int width, const int height)
{
	if(!al_init())
	{
		std::cout << "FATAL: Allegro initialization failed!" << std::endl;
		return false;
	}
	//Spróbuj stworzyæ ALLEGRO_DISPLAY
	display = al_create_display(width,height);
	if(!display)
	{
		std::cout << "FATAL: Could not create a display!" << std::endl;
		return false;
	}

	event_queue = al_create_event_queue();
	if(!event_queue)
	{
		std::cout << "FATAL: Could not initialize the event queue!"<< std::endl;
		return false;
	}

	if(!al_install_keyboard())
	{
		std::cout << "FATAL: Could not install the keyboard!" << std::endl;
		return false;
	}

	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	//Wszystko OK!
	return true;
}
bool Init::initAddons()
{
	if(!al_init_image_addon())
	{
		std::cout << "FATAL: Could not load the image addon!"<< std::endl;
		return false;
	}
	if(!al_init_primitives_addon())
	{
		std::cout << "FATAL: Could not load the primitives addon!"<< std::endl;
		return false;
	}
	
	al_init_font_addon(); //Nie zwraca ¿adnej wartoœci - nie sprawdzamy go
	if(!al_init_ttf_addon())
	{
		std::cout << "FATAL: Could not load the image addon!"<< std::endl;
		return false;
	}
	//Wszystko OK!
	return true;
}
void Init::registerEvents(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue)
{
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
}
void Init::closeAllegro(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue)
{
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
}
	