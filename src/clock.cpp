#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance()
{
	if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
	{
		throw std::string("Must init SDL before Clock");
	}
	static Clock clock;
	return clock;
}

Clock::Clock() :
showHUD(true),
hideHUDAfter3Seconds(true),
frames(0),
ticksSinceLastFrame(0),
ticksAtLastFrame(0),
sumOfTicks(0),
started(false),
paused(false),
sloMo(false),
fpsLoc(Gamedata::getInstance().getXmlInt("clock/fpsLoc/x"),
Gamedata::getInstance().getXmlInt("clock/fpsLoc/y")),
secondsLoc(Gamedata::getInstance().getXmlInt("clock/secondsLoc/x"),
Gamedata::getInstance().getXmlInt("clock/secondsLoc/y")),
capFrameRate(Gamedata::getInstance().getXmlBool("framesAreCapped")),
maxFrameRate(Gamedata::getInstance().getXmlInt("frameCap"))
{
	start();
}

Clock::Clock(const Clock& c) :
showHUD(c.showHUD),
hideHUDAfter3Seconds(c.hideHUDAfter3Seconds),
frames(c.frames),
ticksSinceLastFrame(c.ticksSinceLastFrame),
ticksAtLastFrame(c.ticksAtLastFrame),
sumOfTicks(c.sumOfTicks),
started(c.started),
paused(c.paused),
sloMo(c.sloMo),
fpsLoc(c.fpsLoc),
secondsLoc(c.secondsLoc),
capFrameRate(c.capFrameRate),
maxFrameRate(c.maxFrameRate)
{
	// The next line seems wrong; so I will delete it!
	//start();
}

void Clock::draw() const
{
	IOManager::getInstance().printMessageValueAt("fps: ", getFps(), fpsLoc[0], fpsLoc[1]);
	IOManager::getInstance().printMessageValueAt("seconds: ", getSeconds(), secondsLoc[0], secondsLoc[1]);
}

void Clock::update()
{
	if (paused) return;
	++frames;
	unsigned int clockTicks = SDL_GetTicks();
	ticksSinceLastFrame = clockTicks - ticksAtLastFrame;
	sumOfTicks += ticksSinceLastFrame;
	ticksAtLastFrame = clockTicks;

	if (hideHUDAfter3Seconds && getSeconds() > 3)
	{
		hideHUDAfter3Seconds = false;
		showHUD = false;
	}
}

unsigned int Clock::getTicksSinceLastFrame() const
{
	if (paused) return 0;
	return ticksSinceLastFrame;
}

unsigned int Clock::getTicksAtLastFrame() const
{
	if (paused) return 0;
	return ticksAtLastFrame;
}

void Clock::toggleSloMo()
{
	std::cout << "Slo Mo not implemented yet!" << std::endl;
}

int Clock::getFps() const
{
	if (getSeconds() > 0 && frames > 0) return frames / getSeconds();
	return 0;
}

int Clock::getMaxFps() const
{
	return maxFrameRate;
}

void Clock::start()
{
	started = true;
	paused = false;
	frames = 0;
	ticksAtLastFrame = SDL_GetTicks();
}

void Clock::pause()
{
	if (started && !paused) {
		paused = true;
	}
}
void Clock::unpause()
{
	if (started && paused)
	{
		ticksAtLastFrame = SDL_GetTicks();
		paused = false;
	}
}