#pragma once

// -- Tools
#include <vector>
#include <string>
#include "GameObject.h"

enum COMPONENT_TYPE  {
	TRANSFORM,
	MESH,
	MATERIAL,
	CAMERA
};

class Component {

public:


	Component(GameObject* parent) : owner(parent)
	{
		if (parent)
			parent->AddComponent(this);
	};
	virtual ~Component() {};

	virtual bool Update(float dt) {
		return true;
	}

	virtual bool Enable() { return active = true; };
	virtual bool Disable() { return active = false; };
	virtual void OnGui() { }
	virtual COMPONENT_TYPE getType() { return componentType; }

public:

	GameObject* owner = nullptr;
	bool active = true;
	COMPONENT_TYPE componentType;
};