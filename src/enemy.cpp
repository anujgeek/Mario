#include "enemy.h"
#include "player.h"
#include "gamedata.h"


Enemy::Enemy(const std::string& name)
	: Sprite(name)
{

}

Enemy::Enemy(const Enemy& s)
	: Sprite(s)
{

}

Enemy::~Enemy()
{
}

void Enemy::draw() const
{
	Sprite::draw();
}

void Enemy::update(Uint32 ticks)
{
	Vector2f incr = getVelocity() * static_cast<float>(ticks)* 0.001;
	setPosition(getPosition() + incr);

	if (Y() < 0) {
		velocityY(abs(velocityY()));
	}
	if (Y() > worldHeight - frameHeight) {
		velocityY(-abs(velocityY()));
	}

	float xPositionDifference = getPosition()[0] - Player::getInstance().getPosition()[0];

	if (X() < 0 || xPositionDifference < 0) {
		velocityX(abs(velocityX()));
	}
	if (X() > worldWidth - frameWidth || xPositionDifference > 0) {
		velocityX(-abs(velocityX()));
	}
}