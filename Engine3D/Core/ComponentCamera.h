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
	void OnGui() override;
	//void VerticalFOV(float vFOV, float width, float height);
	void HorizontalFOV(float vFOV, float width, float height);

	float* GetProjectionMat();
	float* GetViewMat();

	void DrawFrustum();
public:
	Frustum frustum;
	float farDistance = 500.0f;
	float nearDistance = 1.0f;

};