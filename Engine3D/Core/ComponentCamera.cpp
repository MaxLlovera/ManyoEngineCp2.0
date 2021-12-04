#include "ComponentCamera.h"
#include "Application.h"


//ComponentCamera::ComponentCamera()
//{
//
//}

ComponentCamera::ComponentCamera(GameObject* parent) : Component(parent)
{
	frustrum.type = FrustumType::PerspectiveFrustum;
	
	frustrum.farPlaneDistance=100.0f;
	frustrum.nearPlaneDistance=1.0f;

	
	frustrum.verticalFov = DEGTORAD * 90.0;
	HorizontalFOV(frustrum.verticalFov, 16.0f, 9.0f);
}

ComponentCamera::~ComponentCamera()
{

}

void ComponentCamera::HorizontalFOV(float vFOV, float width, float height)
{
	frustrum.horizontalFov = 2.0f * atan((tan(vFOV/2)) * (width / height));
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