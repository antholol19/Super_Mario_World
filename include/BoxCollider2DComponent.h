#pragma once
#ifndef BOX_COLLIDER2D_COMPONENT
#define BOX_COLLIDER2D_COMPONENT

#include "SDL.h"
#include "defs.h"

class BoxCollider2DComponent
{
public:
	BoxCollider2DComponent();
	~BoxCollider2DComponent();

	SDL_Rect& getColliderBoundingBox();

	SDL_bool isColliding(BoxCollider2DComponent& collider);

	Vec2D setBoundingBoxAuto(SDL_Surface* surface, uint8_t r, uint8_t g, uint8_t b);

	void setAbsolutePosition(float x, float y);
	void setDimensions(int w, int h);

private:
	SDL_Rect* _colliderRect;
};
#endif // !BOX_COLLIDER2D_COMPONENT

