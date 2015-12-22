#include <SDL.h>
#include <string>
#include <deque>
#include "vector2f.h"

class Manager;

// class Clock is a Singleton
class Clock {
public:
	static Clock& getInstance();
	unsigned int getTicksSinceLastFrame() const;
	unsigned int getTicksAtLastFrame() const;
	unsigned int getTicksSinceInit() const { return 0; }
	unsigned int getSeconds() const { return sumOfTicks / 1000; }

	void toggleSloMo();
	bool isStarted() const { return started; }
	bool isPaused() const  { return paused; }
	int getFps() const;
	int getMaxFps() const;
	bool isFpsCapped() const{ return capFrameRate; }
	void toggleCap() { capFrameRate = !capFrameRate; }

	void start();
	void pause();
	void unpause();
	void draw() const;  // For debugging
	void update();      // Increments ticks

	bool showHUD;
	bool hideHUDAfter3Seconds;

private:
	unsigned int frames;
	unsigned int ticksSinceLastFrame;
	unsigned int ticksAtLastFrame;
	unsigned int sumOfTicks;

	bool started;
	bool paused;
	bool sloMo;
	Vector2f fpsLoc;
	Vector2f secondsLoc;
	bool capFrameRate;
	unsigned int maxFrameRate;

	Clock();
	Clock(const Clock&);
	Clock&operator=(const Clock&);
};
