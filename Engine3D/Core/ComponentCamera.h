#pragma once

// -- Tools
#include <vector>
#include <string>
#include "Core/Globals.h"
#include "Core/Component.h"

#include "Geometry/Frustum.h"

class GameObject;

class ComponentCamera: public Component {

public:

	ComponentCamera();
	ComponentCamera(GameObject* gameObject);
	~ComponentCamera();

	void Update();
	void OnSave();
	void OnLoad();

public:

};