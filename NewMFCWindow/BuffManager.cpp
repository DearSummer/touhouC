#include "BuffManager.h"



void BuffManager::drawBuff(CDC * dc, CDC * canvasDC)
{
	for(int i = 0;i < buffList.size();i++)
	{
		if(!buffList[i])
			continue;

		if(buffList[i]->getState() == DISPLAY)
		{
			buffList[i]->draw(dc, canvasDC);
		}
		else if(buffList[i]->getState() == DIE_OUT_OF_RANGE)
		{
			removeBuff(i);
		}
		
	}
}

BuffManager::BuffManager()
{
}


BuffManager& BuffManager::getInstance()
{
	static BuffManager instance;
	return instance;
}

BuffManager::~BuffManager()
{
}

void BuffManager::onStart()
{
}

void BuffManager::update(CDC * dc, CDC * canvasDC)
{
	drawBuff(dc, canvasDC);
}

std::vector<Buff*>& BuffManager::getBuffList()
{
	// TODO: insert return statement here
	return buffList;
}

void BuffManager::addBuff(Buff * buff)
{
	for(int i = 0;i < buffList.size();i++)
	{
		if (!buffList[i])
		{
			buffList[i] = buff;
			return;
		}
		
	}
	buffList.push_back(buff);
}

void BuffManager::removeBuff(int index)
{
	if (index < 0 || index >= buffList.size())
		return;

	delete buffList[index];
	buffList[index] = nullptr;
}

void BuffManager::reset()
{
	buffList.clear();
}
