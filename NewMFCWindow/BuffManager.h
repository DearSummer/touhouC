#pragma once
#include <vector>
#include "Buff.h"
#include "IGameLoop.h"

class BuffManager : IGameLoop
{
	std::vector<Buff *> buffList;

	void drawBuff(CDC *dc, CDC * canvasDC);
	BuffManager();
public:
	static BuffManager& getInstance();
	~BuffManager();

	void onStart() override;
	void update(CDC* dc, CDC* canvasDC) override;

	std::vector<Buff *> & getBuffList();

	void addBuff(Buff * buff);
	void removeBuff(int index);

	void reset();
};

