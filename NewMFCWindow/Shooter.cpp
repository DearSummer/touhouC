#include "Shooter.h"
#include "Time.h"


Shooter::Shooter(Bullet * bullet, const float reloadTime)
	:bullet(bullet),timer(0),reloadTime(reloadTime),reloaded(true)
{
}

Shooter::~Shooter()
{
	delete bullet;
}

void Shooter::tick()
{
	timer += Time.detlaTime;
	if(timer > reloadTime)
	{
		timer = 0;
		reload(nullptr);
	}

}

void Shooter::setReloadTime(const float reloadTime)
{
	this->reloadTime = reloadTime;
}

void Shooter::reload(Bullet * bullet)
{
	if (bullet && bullet != this->bullet)
		this->bullet = bullet;
	reloaded = true;
}

Bullet * Shooter::fire()
{
	if (reloaded)
	{
		reloaded = false;
		return bullet->clone();
	}
		
	return nullptr;
}
