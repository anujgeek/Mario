#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include "drawable.h"
#include "twowaymultisprite.h"
#include "collisionStrategy.h"

class Player : public TwoWayMultiSprite
{
public:

	static Player& getInstance();
	virtual ~Player();

	virtual void draw() const;
	virtual void update(Uint32 ticks);
	void up();
	void down();
	void left();
	void right();
	void stop();

	bool collidedWith(const Drawable* d) const {
		return strategy->execute(Player::getInstance(), *d);
	}

protected:

	bool isStopped;

	Player& operator=(const Player&);
	void advanceFrame(Uint32 ticks);

private:

	Player(const std::string&, const std::string&, const std::string&);
	Player(const Player&);

	std::vector<CollisionStrategy*> strategies;
	CollisionStrategy* strategy;

	float bottomY, topY;
};
#endif