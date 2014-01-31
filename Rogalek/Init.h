class Init{
	public:
	int initAllegro(ALLEGRO_DISPLAY *display, const int width, const int height);
	int initAddons();
	void registerEvents(ALLEGRO_EVENT_QUEUE *ev, ALLEGRO_DISPLAY *display);
	int gameLoop();
	void closeAllegro(ALLEGRO_EVENT_QUEUE *ev, ALLEGRO_DISPLAY *display);
};