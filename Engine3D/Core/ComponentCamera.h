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
	
	bool Start();
	bool Update(float dt)override;
	bool PreUpdate(float dt);
	void OnSave();
	void OnLoad();
	void OnGui() override;
	void LookAt(const float3& point);
	//void VerticalFOV(float vFOV, float width, float height);
	void HorizontalFOV(float vFOV, float width, float height);

	float* GetProjectionMat();
	void CalculateViewMatrix();
	void RecalculateProjection();
	void DrawFrustum();

	float3 right, up, front, position, reference;
	Frustum cameraFrustum;
	float4x4 viewMatrix;
	float aspectRatio = 1.f;
	float verticalFOV = 60.f;
	float nearPlaneDistance = 0.1f;
	float farPlaneDistance = 5000.f;
	float cameraSensitivity = .5f;
	float cameraSpeed = 60.f;
	bool projectionIsDirty = false;
	float3 initialPos = float3(0.f, 0.f, -150.f);
public:
	Frustum frustum;
	float lastDeltaX = 0.f, lastDeltaY = 0.f;
};