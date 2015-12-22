#include "player.h"
#include "gamedata.h"

Player& Player::getInstance()
{
	static Player player = Player("player", "playerRight", "playerLeft");
	return player;
}

Player::Player(const std::string& name, const std::string& name1, const std::string& name2)
	: TwoWayMultiSprite(name, name1, name2),
	isStopped(true),
	strategies(),
	strategy(NULL),
	bottomY(Gamedata::getInstance().getXmlInt(name + "/startLoc/y")),
	topY(bottomY - 125)
{
	strategies.push_back(new MidPointCollisionStrategy);
	strategies.push_back(new RectangularCollisionStrategy);
	strategies.push_back(new PerPixelCollisionStrategy);
	strategy = strategies[1];
	stop();
}

Player::Player(const Player& s)
	: TwoWayMultiSprite(s),
	isStopped(s.isStopped),
	strategies(s.strategies),
	strategy(s.strategy),
	bottomY(s.bottomY),
	topY(s.topY)
{
	stop();
}

Player::~Player()
{
	for (unsigned i = 0; i < strategies.size(); ++i) {
		delete strategies[i];
	}
}

void Player::draw() const
{
	TwoWayMultiSprite::draw();
}

void Player::update(Uint32 ticks)
{
	if (!isStopped)
	{
		TwoWayMultiSprite::advanceFrame(ticks);
		float XIncrement = getVelocity()[0] * static_cast<float>(ticks)* 0.001;
		X(X() + XIncrement);

		if (X() < 0) {
			velocityX(abs(velocityX()));
		}
		if (X() > worldWidth - frameWidth) {
			velocityX(-abs(velocityX()));
		}
	}

	float YIncrement = getVelocity()[1] * static_cast<float>(ticks)* 0.001;
	Y(Y() + YIncrement);

	if (Y() < topY)
	{
		velocityY(abs(velocityY()));
	}
	else if (Y() >= bottomY)
	{
		velocityY(-abs(velocityY()));
	}
}

void Player::stop()
{
	isStopped = true;
	if (velocityX() > 0)
	{
		frames = frames1;
		currentFrame = 0;
	}
	else if (velocityX() < 0)
	{
		frames = frames2;
		currentFrame = numberOfFrames - 1;
	}
	velocityX(0);
}
void Player::right()
{
	isStopped = false;
	if (X() < worldWidth - frameWidth)
	{
		velocityX(movementVelocityX());
	}
}
void Player::left()
{
	isStopped = false;
	if (X() > 0)
	{
		velocityX(-movementVelocityX());
	}
}
void Player::up()
{
	//isStopped = true;
	/*if (Y() > 0)
	{
	velocityY(-movementVelocityY());
	}
	if (Y() < worldHeight - frameHeight)
	{
	velocityY(movementVelocityY());
	}*/
}
void Player::down()
{
	stop();
}