#include "ComponentCamera.h"
#include "Application.h"


//ComponentCamera::ComponentCamera()
//{
//
//}

ComponentCamera::ComponentCamera(GameObject* parent) : Component(parent)
{
	frustrum.type = FrustumType::PerspectiveFrustum;

}

ComponentCamera::~ComponentCamera()
{

}

void ComponentCamera::NearPlane(float dist)
{
	frustrum.nearPlaneDistance = dist;
}

void ComponentCamera::FarPlane(float dist)
{
	frustrum.farPlaneDistance = dist;
}

void ComponentCamera::VerticalFOV(float vFOV, float width, float height)
{
	frustrum.verticalFov = vFOV;
	frustrum.horizontalFov = 2.f * atan((tan(frustrum.verticalFov * 0.5)) * (width/height));
}

void ComponentCamera::HorizontalFOV(float hFOV, float width, float height)
{
	frustrum.horizontalFov = hFOV;
	frustrum.verticalFov = 2.f * atan((tan(frustrum.horizontalFov * 0.5)) * (width / height));
}

float* ComponentCamera::GetProjectionMat()
{
	float4x4 projMat;
	projMat = frustrum.ProjectionMatrix();

	return (float*) projMat.v;
}

float* ComponentCamera::GetViewMat()
{
	float4x4 viewMat;
	frustrum.ViewMatrix();

	return (float*)viewMat.v;
}