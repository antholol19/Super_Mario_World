#pragma once
#ifndef SPRITE_COMPONENT
#define SPRITE_COMPONENT

#include "Component.h"
#include "Frame.h"
#include "ResourceManager.h"
#include "Layer.h"
#include "SDL.h"
#include "defs.h"
#include <string>
#include <vector>

class SpriteComponent : public Component
{
public:
	SpriteComponent();
	SpriteComponent(SDL_Renderer* renderer, std::string filepath);
	~SpriteComponent();

	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);

	// sprite position and size when rendered
	void setPositionDst(float x, float y);
	void setDimensionDst(int w, int h);

	// each frame must be the same size and the offset is -1
	void setFrames(int i, int j, int w, int h, int gridLineWidth);
	Frame getFrame(int frameNumber);

	std::string getName() { return _name; }
	virtual void setName(std::string name) { _name = name; }

	void setLayer(Layer layer) { _layer = layer; }
	Layer getLayer() { return _layer; }

protected:
	
	SDL_Rect _src;
	SDL_Rect _dst;
	std::vector<Frame> _frames;
	std::string _name;
	Layer _layer;

private:
	SDL_Texture* _texture;
	int _texWidth;
	int _texHeight;
	
};
#endif // !SPRITE_COMPONENT
