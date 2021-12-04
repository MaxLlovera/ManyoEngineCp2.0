#include "GameObject.h"
#include "Application.h"
#include "glew.h"
#include "SDL/include/SDL_opengl.h"
#include "ModuleScene.h"
#include "ModuleFileSystem.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "ImGui/imgui.h"
#include "Algorithm/Random/LCG.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "ModuleCamera3D.h"

GameObject::GameObject() {

	name = name + ("GameObject");
	parent = nullptr;
	LCG num;
	UUID = num.Int();
	transform = CreateComponent<ComponentTransform>();

	active = true;
}


GameObject::GameObject(const std::string name, const int UUID) : name(name), UUID(UUID)
{
	transform = CreateComponent<ComponentTransform>();
	active = true;
}


GameObject::~GameObject() {

	for (size_t i = 0; i < components.size(); i++) {
		RELEASE(components[i]);
	}

	components.clear();

	for (GameObject* go : children)
	{
		RELEASE(go);
	}

	parent = nullptr;
}

void GameObject::Update(float dt) 
{
	for (Component* component : components)
	{
		component->Update(dt);
	}
}

void GameObject::OnGui()
{
	if (App->scene->root != this)
	{
		ImGui::Text("%s", name.c_str());
		ImGui::Separator();

		for (Component* component : components)
		{
			component->OnGui();
		}
	}
}

void GameObject::DeleteComponent(Component* component) {

	auto componentIt = std::find(components.begin(), components.end(), component);
	if (componentIt != components.end())
	{
		components.erase(componentIt);
		components.shrink_to_fit();
	}
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
}

void GameObject::AttachChild(GameObject* child)
{
	child->parent = this;
	children.push_back(child);
	child->transform->NewAttachment();
	child->PropagateTransform();
}

void GameObject::RemoveChild(GameObject* child)
{
	auto it = std::find(children.begin(), children.end(), child);
	if (it != children.end())
	{
		children.erase(it);
	}
}

void GameObject::PropagateTransform()
{
	for (GameObject* go : children)
	{
		go->transform->OnParentMoved();
	}
}

void GameObject::GenerateGlobalAABB(ComponentMesh* mesh)
{
	// Generate global OBB
	oobb = mesh->localAABB;
	oobb.Transform(transform->transformMatrix);

	// Generate global AABB
	aabb.SetNegativeInfinity();
	aabb.Enclose(oobb);

	DrawAABB();
}

void GameObject::DrawAABB()
{
	float3 cornerPoints[8];
	int points[24] = {0,2, 2,6, 6,4, 4,0, 0,1, 1,3, 3,2, 3,7, 7,5, 5,1, 6,7, 5,4};

	aabb.GetCornerPoints(cornerPoints);

	glBegin(GL_LINES);

	for (int i = 0; i < 24; ++i)
	{
		glVertex3fv(&cornerPoints[points[i]].x);
	}

	glEnd();
}


void GameObject::MousePicking()
{
	float normalized_x = -1.0 + 2.0 * App->input->GetMouseX() / App->window->width;
	float normalized_y = -(1.0 - 2.0 * App->input->GetMouseY() / App->window->height);

	//LineSegment picking;

	LineSegment picking = App->camera->cameraFrustum.UnProjectLineSegment(normalized_x, normalized_y);

	for (int i = 0; i < children.size(); ++i)
	{
		bool hit = picking.Intersects(children[i]->aabb); // ray vs. AABB
	}
	
	//bool hit = ray_local_space.Intersects(tri, &distance, &hit_point); // ray vs. triangle


}


