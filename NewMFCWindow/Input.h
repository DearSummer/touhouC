#pragma once
class Input
{
	
	float timer;

	Input() = default;
public:
	
	~Input() = default;

	static Input& getInstance();

	void update();

	void reset();

	int mouseX, mouseY;

	bool	keyADown, keySDown, keyDDown, keyWDown, 
			lButtonDown, rButtonDown,
			keyUpDown, keyLeftDown, keyRightDown, keyDownDown,
			keyZDown, keyXDown;
};

