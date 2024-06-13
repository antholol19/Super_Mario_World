#pragma once
#ifndef FRAME_H
#define FRAME_H

#include "defs.h"

class Frame
{
public:
	Frame(int w, int h);
	~Frame();

	// Set the frame position in pixel on the texture
	void setFramePosition(const Vec2D& pos);

	// Set the frame dimension in pixel on the texture
	void setFrameDimension(int w, int h);

	Vec2D getFramePosition() { return _pos; }
	float getFramePositionX() { return _pos.x; }
	float getFramePositionY() { return _pos.y; }
	int getFrameWidth() { return _width; }
	int getFrameHeight() { return _height; }

private:
	Vec2D _pos;
	int _width;
	int _height;

};

#endif // !FRAME_H
