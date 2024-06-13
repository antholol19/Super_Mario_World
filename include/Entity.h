#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "SDL.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "ComponentManager.h"
#include "BoxCollider2DComponent.h"
#include "Layer.h"
#include <memory>
#include <string>
#include <vector>


class Entity
{
public:
	Entity(std::string name);

	~Entity();

	virtual void update(float deltaTime);
	virtual void render(SDL_Renderer* renderer);

	void addSpriteComponent(SDL_Renderer* renderer, std::string filepath);
	void addCollider2DComponent();

	BoxCollider2DComponent& getBoxCollider2D(size_t index);

	virtual void setPosition(float x, float y);
	virtual void setDimensions(int w, int h);

	Vec2D getPosition() { return _pos; }
	Vec2D getVelocity() { return _vel; }

	void setLayer(Layer layer);
	Layer getLayer();

	inline std::string getName() { return _name; }
protected:
	
	std::shared_ptr<SpriteComponent> _sprite;
	Vec2D _pos;
	Vec2D _vel;
	std::vector<BoxCollider2DComponent*> _colliders;
	Layer _layer;
private:

	std::string _name;
};

#endif // !ENTITY_H
