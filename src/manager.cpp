#include <iostream>
#include <string>
#include <iomanip>
#include "manager.h"
#include "sprite.h"
#include "multisprite.h"
#include "twowaymultisprite.h"
#include "explodingSprite.h"
#include "player.h"
#include "enemy.h"
#include "gamedata.h"
#include "aaline.h"

Manager::Manager() :
env(SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center"))),
io(IOManager::getInstance()),
clock(Clock::getInstance()),
screen(io.getScreen()),
worldBack("back", Gamedata::getInstance().getXmlInt("back/factor")),
worldFront("front", Gamedata::getInstance().getXmlInt("front/factor")),
viewport(Viewport::getInstance()),
GodMode(false),
currentSprite(0),
sprites(),
enemies(),
trophy(new Sprite("Trophy")),
makeVideo(false),
frameCount(0),
username(Gamedata::getInstance().getXmlStr("username")),
title(Gamedata::getInstance().getXmlStr("screenTitle")),
frameMax(Gamedata::getInstance().getXmlInt("frameMax")),
HUD_WIDTH(Gamedata::getInstance().getXmlInt("hud/width")),
HUD_HEIGHT(Gamedata::getInstance().getXmlInt("hud/height")),
HUD_POSITION(Vector2f(Gamedata::getInstance().getXmlInt("hud/loc/x"), Gamedata::getInstance().getXmlInt("hud/loc/y")))
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw string("Unable to initialize SDL: ");
	}
	SDL_WM_SetCaption(title.c_str(), NULL);
	atexit(SDL_Quit);

	for (unsigned i = 0; i < 10; ++i)
	{
		TwoWayMultiSprite* birdSmall = new TwoWayMultiSprite("BirdSmall", "BirdSmallRight", "BirdSmallLeft");
		birdSmall->X(i * 100);
		birdSmall->Y(birdSmall->Y() + (i % 2 == 0 ? 0 : 25));
		sprites.push_back(birdSmall);
	}

	for (unsigned i = 0; i < 10; ++i)
	{
		TwoWayMultiSprite* bird = new TwoWayMultiSprite("Bird", "BirdRight", "BirdLeft");
		bird->X(i * 100);
		bird->Y(bird->Y() + (i % 2 == 0 ? 0 : 25));
		sprites.push_back(bird);
	}

	enemies.push_back(new Enemy("Enemy"));
	enemies.push_back(new Enemy("Enemy"));
	enemies.push_back(new Enemy("Enemy"));

	enemies[1]->X(enemies[0]->X() + 100);
	enemies[2]->X(enemies[0]->X() + 200);

	viewport.setObjectToTrack(&Player::getInstance());
}

Manager::~Manager() {
	// These deletions eliminate "definitely lost" and
	// "still reachable"s in Valgrind.
	for (unsigned i = 0; i < sprites.size(); ++i) {
		delete sprites[i];
	}
	for (unsigned i = 0; i < enemies.size(); ++i) {
		delete enemies[i];
	}

	delete trophy;
}

void Manager::checkForCollisions() {
	if (GodMode == false)
	{
		for (unsigned i = 0; i < enemies.size(); ++i) {
			ExplodingSprite* e = dynamic_cast<ExplodingSprite*>(enemies[i]);
			if (!e && Player::getInstance().collidedWith(enemies[i])) {
				Sprite* sprite = enemies[i];
				enemies[i] = new ExplodingSprite(sprite);
				delete sprite;
			}
		}
	}
	ExplodingSprite* e = dynamic_cast<ExplodingSprite*>(trophy);
	if (!e && Player::getInstance().collidedWith(trophy)) {
		Sprite* sprite = trophy;
		trophy = new ExplodingSprite(trophy);
		delete sprite;
	}
}

void Manager::draw() const {
	worldBack.draw();
	for (unsigned i = 0; i < sprites.size() / 2; ++i) {
		sprites[i]->draw();
	}
	worldFront.draw();
	for (unsigned i = sprites.size() / 2; i < sprites.size(); ++i) {
		sprites[i]->draw();
	}
	for (unsigned i = 0; i < enemies.size(); ++i) {
		enemies[i]->draw();
	}
	trophy->draw();
	Player::getInstance().draw();

	io.printMessageAt(title, 575, 415);

	if (clock.showHUD)
	{
		clock.draw();
		drawHUD(screen, HUD_POSITION[0], HUD_POSITION[1]);
		io.printMessageAt("MARIO", HUD_POSITION[0] + 5, HUD_POSITION[1] + 5);
		io.printMessageAt("Press a - Left", HUD_POSITION[0] + 5, HUD_POSITION[1] + 60);
		io.printMessageAt("Press d - Right", HUD_POSITION[0] + 5, HUD_POSITION[1] + 75);
		io.printMessageAt("Press s - Stop", HUD_POSITION[0] + 5, HUD_POSITION[1] + 90);
		io.printMessageAt("Press F1 - Toggle HUD", HUD_POSITION[0] + 5, HUD_POSITION[1] + 120);
		io.printMessageAt("Press F2 - Restart", HUD_POSITION[0] + 5, HUD_POSITION[1] + 150);
		io.printMessageAt("Press F3 - Toggle GodMode", HUD_POSITION[0] + 5, HUD_POSITION[1] + 180);
	}

	viewport.draw();

	SDL_Flip(screen);
}

void Manager::drawHUD(SDL_Surface* screen, int x, int y) const
{
	const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
	Draw_AALine(screen, x, y + HUD_HEIGHT / 2, x + HUD_WIDTH, y + HUD_HEIGHT / 2, HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff / 2);
	Draw_AALine(screen, x, y, x + HUD_WIDTH, y, RED);
}

void Manager::makeFrame() {
	std::stringstream strm;
	strm << "frames/" << username << '.'
		<< std::setfill('0') << std::setw(4)
		<< frameCount++ << ".bmp";
	std::string filename(strm.str());
	std::cout << "Making frame: " << filename << std::endl;
	SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
	currentSprite = (currentSprite + 1) % sprites.size();
	viewport.setObjectToTrack(sprites[currentSprite]);
}

void Manager::update() {
	clock.update();
	Uint32 ticks = clock.getTicksSinceLastFrame();

	for (unsigned int i = 0; i < sprites.size(); ++i) {
		sprites[i]->update(ticks);
	}
	for (unsigned i = 0; i < enemies.size(); ++i) {
		enemies[i]->update(ticks);
	}
	trophy->update(ticks);
	Player::getInstance().update(ticks);
	checkForCollisions();

	if (makeVideo && frameCount < frameMax) {
		makeFrame();
	}
	worldBack.update();
	worldFront.update();
	viewport.update(); // always update viewport last
}

void Manager::play()
{
	SDLSound sound;
	SDL_Event event;
	bool done = false;
	float lastTime = 0.0f;
	float timeBehind = 0.0f;
	float targetTimeStep = 1000.0f / clock.getMaxFps();
	clock.start();

	while (!done)
	{
		Uint8 *keystate = SDL_GetKeyState(NULL);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				done = true;
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (keystate[SDLK_ESCAPE] || keystate[SDLK_q])
				{
					done = true;
					break;
				}
				if (keystate[SDLK_t])
				{
					//switchSprite();
				}
				if (keystate[SDLK_p])
				{
					if (clock.isPaused()) clock.unpause();
					else clock.pause();
				}
				if (keystate[SDLK_F1])
				{
					clock.showHUD = !clock.showHUD;
				}
				if (keystate[SDLK_F2])
				{
					restart();
				}
				if (keystate[SDLK_F3])
				{
					GodMode = !GodMode;
				}
				if (keystate[SDLK_F4] && !makeVideo)
				{
					std::cout << "Making video frames" << std::endl;
					makeVideo = true;
				}

				if (keystate[SDLK_a] && keystate[SDLK_d])
				{
					Player::getInstance().stop();
				}
				else if (keystate[SDLK_a])
				{
					Player::getInstance().left();
				}
				else if (keystate[SDLK_s])
				{
					Player::getInstance().down();
				}
				else if (keystate[SDLK_d])
				{
					Player::getInstance().right();
				}
				else if (keystate[SDLK_w])
				{
					Player::getInstance().up();
					sound[0];
				}
			}
		}

		if (clock.isFpsCapped())
		{
			timeBehind += SDL_GetTicks() - lastTime;
			lastTime = SDL_GetTicks();
			while (timeBehind >= targetTimeStep)
			{
				update();
				timeBehind -= targetTimeStep;
			}
		}
		else
		{
			update();
		}
		draw();
	}
}

void Manager::restart()
{
	Player::getInstance().setPosition(Vector2f(Gamedata::getInstance().getXmlInt(Player::getInstance().getName() + "/startLoc/x"), Gamedata::getInstance().getXmlInt(Player::getInstance().getName() + "/startLoc/y")));
	Player::getInstance().velocityX(0);
}

void Manager::reset()
{
	Player::getInstance().stop();
}