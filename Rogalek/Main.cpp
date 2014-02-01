#include <allegro5\allegro.h>
#include "Init.h"
#include "Consts.h"
#include "Game.h"
int main()
{
	/* Procedura startowa:
	- Inicjalizacja biblioteki Allegro 5
	- Inicjalizacja dodatk�w dla Allegro 5
	- Rejestracja zdarze� Allegro 5
	- Uruchomienie g��wnej p�tli
	- Zamkni�cie biblioteki Allegro 5
	- Koniec programu
	*/
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	Init initializer;

	if(!initializer.initAllegro(display, event_queue, resolutionWidth, resolutionHeight))
	{
		return 1; // co� posz�o nie tak, wychodzimy...
	}
	if(!initializer.initAddons())
	{
		return 1; // co� posz�o nie tak, wychodzimy...
	}
	initializer.registerEvents(display, event_queue);
	gameLoop();
	initializer.closeAllegro(display, event_queue);

	return 0;
}