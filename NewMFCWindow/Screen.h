#pragma once
class Screen
{
	int width, height;
public:
	Screen();
	~Screen() = default;

	void setScreenSize(int width, int height);
	int getWidth() const;
	int getHeight() const;

};

extern Screen screen;

