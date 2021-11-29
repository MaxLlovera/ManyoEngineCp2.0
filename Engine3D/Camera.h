#pragma once

// -- Tools
#include <vector>
#include <string>
#include "Core/Globals.h"
#include "Core/Component.h"

#include "Geometry/Frustum.h"

class GameObject;

class Camera: public Component {

public:

	Camera();
	Camera(GameObject* gameObject);
	~Camera();

	void Update();


public:

};