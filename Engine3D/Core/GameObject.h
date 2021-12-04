#pragma once

#include <vector>
#include <string>
#include "Geometry/AABB.h"
#include "Geometry/OBB.h"
#include "rapidjson-1.1.0/include/rapidjson/prettywriter.h"
#include "rapidjson-1.1.0/include/rapidjson/document.h"

class Component;
class ComponentTransform;
class ComponentMesh;

typedef rapidjson::PrettyWriter<rapidjson::StringBuffer> JSONWriter;
typedef rapidjson::Value JSONReader;

class GameObject {

public:

	GameObject();
	GameObject(const std::string name, const int UUID);

	~GameObject();

	void Update(float dt);
	void OnGui();
	void save(JSONWriter& writer);

	template<class T> T* CreateComponent()
	{
		T* newComponent = new T(this);
		//int parentUUID = 
		return newComponent;
	}

	template<class T> T* GetComponent()
	{
		T* component = nullptr; 
		for (Component* c : components)
		{
			component = dynamic_cast<T*>(c);
			if (component)
				break;
		}
		return component;
	}

	void DeleteComponent(Component* component);
	void AddComponent(Component* component);
	void AttachChild(GameObject* child);
	void RemoveChild(GameObject* child);
	void PropagateTransform();
	void GenerateGlobalAABB(ComponentMesh* mesh);
	void DrawAABB();

	std::string name;
	GameObject* parent = nullptr;
	ComponentTransform* transform = nullptr;
	std::vector<GameObject*> children;
	std::vector<Component*> components;
	
	void MousePicking();


	int UUID;

	AABB aabb;
	OBB oobb;

	bool active = true;
	bool isSelected = false;

};

