#include <vector>
#include <SDL.h>
#include "clock.h"
#include "ioManager.h"
#include "world.h"
#include "viewport.h"
#include "player.h"
#include "sound.h"

class Manager {
public:
	Manager();
	~Manager();
	void play();

	void switchSprite();

private:
	const bool env;
	const IOManager& io;
	Clock& clock;

	SDL_Surface * const screen;

	World worldBack;
	World worldFront;

	Viewport& viewport;

	bool GodMode;
	int currentSprite;
	std::vector<Drawable*> sprites;
	std::vector<Sprite*> enemies;
	Sprite* trophy;

	bool makeVideo;
	int frameCount;
	const std::string username;
	const std::string title;
	const int frameMax;

	void draw() const;
	void update();
	void restart();
	void checkForCollisions();

	void drawHUD(SDL_Surface*, int, int) const;
	const int HUD_WIDTH;
	const int HUD_HEIGHT;
	const Vector2f HUD_POSITION;

	Manager(const Manager&);
	Manager& operator=(const Manager&);
	void makeFrame();
	void reset();
};
