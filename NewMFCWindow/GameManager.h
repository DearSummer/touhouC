#pragma once
#include "IGameLoop.h"
#include "Bullet.h"
#include <vector>
#include "EnemyPlane.h"
#include "Character.h"
#include "Crash.h"

struct Circle;

class GameManager:public IGameLoop
{
	std::string musicString[21];
	int musicIndex;

	std::vector<Bullet * > enemyBulletList;
	std::vector<Bullet *> playerBulletList;
	std::vector<EnemyPlane *> enemyPlaneList;

	std::vector<Buff *> buffList;

	Character * player;
	Animation * background;
	
	Sprite * bgAttr;
	Sprite * life;
	Sprite * lifeStar;
	Sprite * skill;
	Sprite * skillStar;

	Sprite * atk;
	Sprite * level;

	Sprite * num;


	void setNum(CDC * dc,CDC* canvasDC,int num, int x, int y) const;

	void enemyGetDamage(int index,int bulletIndex,int damage);

	void drawLifeStar(CDC *dc, CDC * canvasDC) const;
	void drawSkillStar(CDC *dc, CDC * canvasDC) const;

	void initMusic();
	void playMusic() const;
public:
	GameManager();
	~GameManager();

	

	static GameManager & getInstance();

	void onStart() override;
	void update(CDC* dc, CDC* canvasDC) override;

	void checkPlayerBulletToEnemy();
	void checkEnemyBulletToPlayer();

	void checkPlayerBuff();

	bool circleToSquareCollider(Circle circle,Rect rect) const;
	static bool squareToSquareCollider(Rect a,Rect b);

	bool gameStart;
	void finishGame();
};

