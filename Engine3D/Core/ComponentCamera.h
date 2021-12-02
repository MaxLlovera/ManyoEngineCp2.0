#pragma once

// -- Tools
#include <vector>
#include <string>
#include "Globals.h"
#include "Component.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "Geometry/Frustum.h"

class GameObject;

class ComponentCamera : public Component{

public:

	//ComponentCamera();
	ComponentCamera(GameObject* parent);
	~ComponentCamera();

	void Update();
	void OnSave();
	void OnLoad();

	void NearPlane(float dist);
	void FarPlane(float dist);
	void VerticalFOV(float vFOV, float width, float height);
	void HorizontalFOV(float hFOV, float width, float height);

	float* GetProjectionMat();
	float* GetViewMat();


public:
	Frustum frustrum;
};