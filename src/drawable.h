#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>
#include <string>
#include "vector2f.h"
#include "frame.h"

// Drawable is an Abstract Base Class (ABC) that
// specifies the methods that derived classes may
// and must have.
class Drawable
{
public:
	Drawable(const std::string& n, const Vector2f& pos, const Vector2f& vel) :
		name(n), position(pos), velocity(vel), movementVelocity(vel) {}

	Drawable(const Drawable& s) :
		name(s.name), position(s.position), velocity(s.velocity), movementVelocity(s.movementVelocity)
	{ }

	virtual ~Drawable() {}

	const std::string& getName() const { return name; }
	void setName(const std::string& n) { name = n; }
	virtual const Frame* getFrame() const = 0;

	virtual void draw() const = 0;
	virtual void update(Uint32 ticks) = 0;

	float X() const { return position[0]; }
	void X(float x) { position[0] = x; }
	float Y() const { return position[1]; }
	void Y(float y) { position[1] = y; }
	const Vector2f& getPosition() const   { return position; }
	void setPosition(const Vector2f& pos) { position = pos; }

	float velocityX() const  { return velocity[0]; }
	void velocityX(float vx) { velocity[0] = vx; }
	float velocityY() const  { return velocity[1]; }
	void velocityY(float vy) { velocity[1] = vy; }
	const Vector2f& getVelocity() const   { return velocity; }
	void setVelocity(const Vector2f& vel) { velocity = vel; }

	float movementVelocityX() const  { return movementVelocity[0]; }
	void movementVelocityX(float vx) { movementVelocity[0] = vx; }
	float movementVelocityY() const  { return movementVelocity[1]; }
	void movementVelocityY(float vy) { movementVelocity[1] = vy; }
	const Vector2f& getMovementVelocity() const   { return movementVelocity; }
	void setMovementVelocity(const Vector2f& vel) { movementVelocity = vel; }

	virtual bool collidedWith(const Drawable*) const
	{
		throw std::string("No collidedWith");
	}

private:
	std::string name;
	Vector2f position;
	Vector2f velocity;
	Vector2f movementVelocity;
};
#endif
