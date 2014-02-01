#ifndef INIT_HEADER
#define INIT_HEADER
class Init{
	public:
		bool initAllegro(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue, const int width, const int height);
		bool initAddons();
		void registerEvents(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue);
		void closeAllegro(ALLEGRO_DISPLAY* &display, ALLEGRO_EVENT_QUEUE* &event_queue);
	public:
		ALLEGRO_EVENT_QUEUE *event_queue;
};
#endif