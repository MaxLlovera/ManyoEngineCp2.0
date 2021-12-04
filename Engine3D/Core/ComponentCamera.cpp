#include "ComponentCamera.h"
#include "Application.h"


//ComponentCamera::ComponentCamera()
//{
//
//}

ComponentCamera::ComponentCamera(GameObject* parent) : Component(parent)
{
	frustum.type = FrustumType::PerspectiveFrustum;
	
	frustum.farPlaneDistance=100.0f;
	frustum.nearPlaneDistance=1.0f;


	frustum.up = float3(0.0f, 1.0f, 0.0f);
	frustum.front = float3(0.0f, 0.0f, 1.0f);
	
	frustum.pos = float3(0.0f, 5.0f, -15.0f);

	frustum.verticalFov = DEGTORAD * 90.0;
	HorizontalFOV(frustum.verticalFov, 16.0f, 9.0f);

	componentType = COMPONENT_TYPE::CAMERA;
}

ComponentCamera::~ComponentCamera()
{

}

void ComponentCamera::HorizontalFOV(float vFOV, float width, float height)
{
	frustum.horizontalFov = 2.0f * atan((tan(vFOV/2)) * (width / height));
}

float* ComponentCamera::GetProjectionMat()
{
	float4x4 projMat;
	projMat = frustum.ProjectionMatrix();

	return (float*) projMat.v;
}

float* ComponentCamera::GetViewMat()
{
	float4x4 viewMat;
	frustum.ViewMatrix();

	return (float*)viewMat.v;
}