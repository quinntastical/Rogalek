#include <allegro5\allegro.h>
#include "Init.h"
#include "Consts.h"
int main()
{
	/* Procedura startowa:
	- Inicjalizacja biblioteki Allegro 5
	- Inicjalizacja dodatków dla Allegro 5
	- Rejestracja zdarzeñ Allegro 5
	- Uruchomienie g³ównej pêtli
	- Zamkniêcie biblioteki Allegro 5
	- Koniec programu
	*/
	Init initializer;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	if(!initializer.initAllegro(display, resolutionWidth, resolutionHeight))
	{
		return 1; // coœ posz³o nie tak, wychodzimy...
	}
	if(!initializer.initAddons())
	{
		return 1; // coœ posz³o nie tak, wychodzimy...
	}
	initializer.registerEvents(event_queue, display);
	//gameLoop(); // Nale¿y do Game.h
	initializer.closeAllegro(event_queue, display);

	return 0;
}