#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Init.h"
class Init{

	int initAllegro(ALLEGRO_DISPLAY *display, const int width, const int height)
	{
		if(!al_init())
		{
			std::cout << "FATAL: Allegro initialization failed!" << std::endl;
			return 1;
		}
		//Spróbuj stworzyæ ALLEGRO_DISPLAY
		display = al_create_display(width,height);
		if(!display)
		{
			std::cout << "FATAL: Could not create a display!" << std::endl;
			return 1;
		}
		if(!al_install_keyboard())
		{
			std::cout << "FATAL: Could not install the keyboard!" << std::endl;
			return 1;
		}
		//Wszystko OK!
		return 0;
	}
	int initAddons()
	{
		if(!al_init_image_addon())
		{
			std::cout << "FATAL: Could not load the image addon!"<< std::endl;
			return 1;
		}
		if(!al_init_primitives_addon())
		{
			std::cout << "FATAL: Could not load the primitives addon!"<< std::endl;
			return 1;
		}
		
		al_init_font_addon(); //Nie zwraca ¿adnej wartoœci - nie sprawdzamy go

		if(!al_init_ttf_addon())
		{
			std::cout << "FATAL: Could not load the image addon!"<< std::endl;
			return 1;

		}
		//Wszystko OK!
		return 0;
	}
	void registerEvents(ALLEGRO_EVENT_QUEUE *ev, ALLEGRO_DISPLAY *display)
	{
		al_register_event_source(ev, al_get_display_event_source(display));
		al_register_event_source(ev, al_get_keyboard_event_source());
	}
};