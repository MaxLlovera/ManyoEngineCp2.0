#include "ComponentCamera.h"
#include "Application.h"
#include "ImGui/imgui.h"
#include "glew.h"
#include "SDL/include/SDL_opengl.h"
#include "GameObject.h"
#include "ModuleViewportFrameBuffer.h"
#include "ComponentTransform.h"
//ComponentCamera::ComponentCamera()
//{
//
//}

ComponentCamera::ComponentCamera(GameObject* parent) : Component(parent)
{
	frustum.type = FrustumType::PerspectiveFrustum;
	
	frustum.farPlaneDistance = farPlaneDistance;
	frustum.nearPlaneDistance = nearPlaneDistance;

	frustum.front = float3(0.0f, 0.0f, 1.0f);
	frustum.up = float3(0.0f, 1.0f, 0.0f);
	
	frustum.verticalFov = DEGTORAD * 60.0;
	HorizontalFOV(frustum.verticalFov, 16.0f, 9.0f);

	componentType = COMPONENT_TYPE::CAMERA;
}

ComponentCamera::~ComponentCamera()
{

}

bool ComponentCamera::Start()
{
	LOG("Setting up the camera");

	LookAt(float3::zero);
	owner->transform->position = initialPos;
	frustum.pos = owner->transform->GetPosition();
	bool ret = true;

	return ret;
}

bool ComponentCamera::Update(float dt)
{
	frustum.pos = owner->transform->GetPosition();
	frustum.front = owner->transform->GetForward();
	frustum.up = owner->transform->GetUp();
	viewMatrix = frustum.ViewMatrix();
	if (drawFrustum)
	{
		DrawFrustum();
	}
	
	bool ret = true;

	return ret;
}

bool ComponentCamera::PreUpdate(float dt)
{
	App->viewportBufferGame->PreUpdate(dt);
	//CalculateViewMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(frustum.ProjectionMatrix().Transposed().ptr());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(viewMatrix.Transposed().ptr());
	bool ret = true;

	return ret;
}

void ComponentCamera::LookAt(const float3& point)
{
	reference = point;
	frustum.front = (reference - frustum.pos).Normalized();
	right = float3(0.0f, 1.0f, 0.0f).Cross(frustum.front).Normalized();
	frustum.up = front.Cross(right);
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

void ComponentCamera::CalculateViewMatrix()
{
	if (projectionIsDirty)
		RecalculateProjection();

	cameraFrustum.pos = position;
	cameraFrustum.front = front.Normalized();
	cameraFrustum.up = up.Normalized();
	float3::Orthonormalize(cameraFrustum.front, cameraFrustum.up);
	right = up.Cross(front);
	viewMatrix = cameraFrustum.ViewMatrix();
}

void ComponentCamera::RecalculateProjection()
{
	frustum.type = FrustumType::PerspectiveFrustum;
	//frustum.nearPlaneDistance = nearPlaneDistance;
	//frustum.farPlaneDistance = farPlaneDistance;
	frustum.verticalFov = (verticalFOV * 3.141592 / 2) / 180.f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);
}

void ComponentCamera::DrawFrustum()
{
	static float3 corners[8];
	frustum.GetCornerPoints(corners);
	int points[24] = { 0,2, 2,6, 6,4, 4,0, 0,1, 1,3, 3,2, 3,7, 7,5, 5,1, 6,7, 5,4 };
	glBegin(GL_LINES);

	for (int i = 0; i < 24; ++i)
	{
		glVertex3fv(&corners[points[i]].x);
	}

	glEnd();
}

void ComponentCamera::OnGui()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		if (ImGui::SliderFloat("Near Plane", &frustum.nearPlaneDistance, 0.1f,500.f))
		{
			projectionIsDirty = true;
		}
		if (ImGui::SliderFloat("Far Plane", &frustum.farPlaneDistance,100.f,1000.f))
		{
			projectionIsDirty = true;
		}
		if (ImGui::SliderFloat("FOV", &verticalFOV,1.f,300.f))
		{
			projectionIsDirty = true;
			RecalculateProjection();
		}
		ImGui::Checkbox("Show Frustum:", &drawFrustum);
	}
}