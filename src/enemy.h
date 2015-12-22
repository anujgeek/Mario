#include <string>
#include <vector>
#include "drawable.h"
#include "sprite.h"

class Enemy : public Sprite
{
public:

	Enemy(const std::string&);
	Enemy(const Enemy&);
	virtual ~Enemy();

	virtual void draw() const;
	virtual void update(Uint32 ticks);

protected:

	Enemy& operator=(const Enemy&);
};

