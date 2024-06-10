#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "SDL.h"
#include "TextureRectangle.h"
#include <string>
#include <vector>
#include "BoxCollider2DComponent.h"
#include "Layer.h"

class Entity
{
public:
	Entity();
	Entity(std::string name, SDL_Renderer* renderer);

	~Entity();

	virtual void update(float deltaTime);
	virtual void render();

	// Adding Components
	void addTextureRectangleComponent(std::string spritePath);
	void addTextureRectangleComponent(std::string spritePath, int redColorKey, int greenColorKey, int blueColorKey);
	void addCollider2DComponent();

	TextureRectangle& getTextureRectangle();
	BoxCollider2DComponent& getBoxCollider2D(size_t index);

	virtual void setPosition(float x, float y);
	virtual void setDimensions(int w, int h);

	Vec2D getPosition() { return _pos; }
	Vec2D getVelocity() { return _vel; }

	void setLayer(Layer layer);
	Layer getLayer();

	inline std::string getName() { return _name; }
protected:
	SDL_Renderer* _renderer;
	TextureRectangle* _sprite;
	Vec2D _pos;
	Vec2D _vel;
	std::vector<BoxCollider2DComponent*> _colliders;
	Layer _layer;
	std::string _name;
};

#endif // !ENTITY_H
