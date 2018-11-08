#pragma once
#include "Bullet.h"

class Shooter
{

	Bullet * bullet;

	float timer,reloadTime;
	bool reloaded;

public:
	Shooter(Bullet * bullet,float reloadTime);
	~Shooter();


	void tick();
	void setReloadTime(float reloadTime);

	void reload(Bullet * bullet);
	Bullet * fire();
};

