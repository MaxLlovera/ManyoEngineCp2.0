#pragma once

// -- Tools
#include "Module.h"
#include "Globals.h"
#include "ModuleImport.h"

#include "GameObject.h"

struct jsonGameObject {
	std::string modelPath;
	ComponentTransform transform;
};

class ModuleScene : public Module
{
public:


	ModuleScene(Application* app, bool start_enabled = true);

	bool Start() override;
	update_status Update(float dt) override;
	bool CleanUp() override;

	GameObject* CreateGameObject(GameObject* parent = nullptr);
	GameObject* CreateGameObject(const std::string name, GameObject* parent = nullptr);

	void loadJSON();
	GameObject* getParent(const std::vector<GameObject*> children, const int parentUUID);

	GameObject* root;
};
