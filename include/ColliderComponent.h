#pragma once
#ifndef COLLIDER_COMPONENT
#define COLLIDER_COMPONENT

#include "Component.h"
#include "Layer.h"
#include "SDL.h"
#include "defs.h"
#include <string>

class ColliderComponent : public Component
{
public:
	ColliderComponent();
	~ColliderComponent();
	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);

	SDL_Rect& getColliderBoundingBox();

	SDL_bool isColliding(ColliderComponent& collider);

	Vec2D setBoundingBoxAuto(SDL_Surface* surface, uint8_t r, uint8_t g, uint8_t b);

	void setAbsolutePosition(float x, float y);
	void setDimensions(int w, int h);

	void setName(std::string name) { _name = name; }
	std::string getName() { return _name; }

	void setLayer(Layer layer) { _layer = layer; }
	Layer getLayer() { return _layer; }

private:
	SDL_Rect* _colliderRect;
	std::string _name;
	Layer _layer;

};
#endif // !COLLIDER_COMPONENT_H

