#pragma once
#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H


#include "SpriteComponent.h"
#include "SDL.h"
#include <string>

class TileComponent : public SpriteComponent
{
public:
	TileComponent(int id, SDL_Texture* texture, SDL_Rect& src, SDL_Rect& dst);
	~TileComponent();

	virtual void update(float deltaTime) override;
	virtual void render(SDL_Renderer* renderer) override;

	int getId() { return _id; }


private:
	int _id;
	Vec2D _pos;
	SDL_Texture* _texture;

};

#endif // !TILE_COMPONENT_H
