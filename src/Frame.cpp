#include "Frame.h"

Frame::Frame(int w, int h) : _width(w), _height(h)
{
	_pos = { 0.0f, 0.0f };
}

Frame::~Frame()
{

}

void Frame::setFramePosition(const Vec2D& pos)
{
	_pos = pos;
}

void Frame::setFrameDimension(int w, int h)
{
	_width = w;
	_height = h;
}
