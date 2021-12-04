#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "glew.h"
#include "ImGui/imgui.h"
#include "ModuleImport.h"
#include "ModuleTextures.h"
#include "ModuleCamera3D.h"
#include "ModuleEditor.h"
#include "Component.h"
#include "ComponentTransform.h"
#include <stack>
#include <queue>
#include "Algorithm/Random/LCG.h"
#include "ModuleFileSystem.h"
#include "GameObject.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	LCG num;
	int UUID = num.Int();

	root = new GameObject("Root", UUID);

	//Loading house and textures since beginning
	//App->import->LoadGeometry("Assets/Models/BakerHouse.fbx");
	loadScene();
	saveScene();



	return ret;
}

bool ModuleScene::CleanUp()
{
	std::stack<GameObject*> S;
	for (GameObject* child : root->children)
	{
		S.push(child);
	}
	root->children.clear();

	while (!S.empty())
	{
		GameObject* go = S.top();
		S.pop();
		for (GameObject* child : go->children)
		{
			S.push(child);
		}
		go->children.clear();
		delete go;
	}

	//delete root;

	return true;
}

update_status ModuleScene::Update(float dt)
{
	std::queue<GameObject*> S;
	for (GameObject* child : root->children)
	{
		S.push(child);
	}

	while (!S.empty())
	{
		GameObject* go = S.front();
		go->Update(dt);
		S.pop();
		for (GameObject* child : go->children)
		{
			S.push(child);
		}
	}

	glDisable(GL_DEPTH_TEST);

	if (App->editor->gameobjectSelected)
	{
		ComponentTransform* transform = App->editor->gameobjectSelected->GetComponent<ComponentTransform>();
		float3 pos = transform->GetPosition();
		glLineWidth(10.f);
		glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(pos.x, pos.y, pos.z);
		glVertex3f(pos.x + transform->Right().x, pos.y + transform->Right().y, pos.z + transform->Right().z);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(pos.x, pos.y, pos.z);
		glVertex3f(pos.x + transform->Front().x, pos.y + transform->Front().y, pos.z + transform->Front().z);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(pos.x, pos.y, pos.z);
		glVertex3f(pos.x + transform->Up().x, pos.y + transform->Up().y, pos.z + transform->Up().z);
		glEnd();
		glLineWidth(1.f);
	}

	glEnable(GL_DEPTH_TEST);


	return UPDATE_CONTINUE;
}

GameObject* ModuleScene::CreateGameObject(GameObject* parent) {

	GameObject* temp = new GameObject();
	if (parent)
		parent->AttachChild(temp);
	else
		root->AttachChild(temp);
	return temp;
}
GameObject* ModuleScene::CreateGameObject(const std::string name, GameObject* parent)
{
	GameObject* temp = new GameObject(name, root->UUID);
	if (parent)
		parent->AttachChild(temp);
	else
		root->AttachChild(temp);
	return temp;
}

void ModuleScene::loadScene()
{
	char* buffer = nullptr;
	uint bytesFile = App->fileSystem->Load(fileName, &buffer);

	if (bytesFile)
	{
		rapidjson::Document document;
		if (document.Parse<rapidjson::kParseStopWhenDoneFlag>(buffer).HasParseError())
		{
			LOG("Error loading %d", fileName);
		}
		else
		{
			int originalRootUUID = root->UUID;
			for (const auto& currentGameObjectJson : document["Game Objects"].GetArray())
			{
				const std::string name = currentGameObjectJson["Name"].GetString();
				const bool isRootGO = isRoot(name);
				const int parentUUID = currentGameObjectJson["ParentUUID"].GetInt();
				const int UUID = currentGameObjectJson["UUID"].GetInt();

				GameObject* parent = getParent(root->children, parentUUID);
				GameObject* gameObject = CreateGameObject(name, parent);

				gameObject->UUID = UUID;

				if (isRootGO && originalRootUUID == root->UUID) root = gameObject;

				float3 pos;
				pos.x = currentGameObjectJson["Translation"].GetArray()[0].GetFloat();
				pos.y = currentGameObjectJson["Translation"].GetArray()[1].GetFloat();
				pos.z = currentGameObjectJson["Translation"].GetArray()[2].GetFloat();

				float3 rotation;
				rotation.x = currentGameObjectJson["Rotation"].GetArray()[0].GetFloat();
				rotation.y = currentGameObjectJson["Rotation"].GetArray()[1].GetFloat();
				rotation.z = currentGameObjectJson["Rotation"].GetArray()[2].GetFloat();

				float3 scale;
				scale.x = currentGameObjectJson["Scale"].GetArray()[0].GetFloat();
				scale.y = currentGameObjectJson["Scale"].GetArray()[1].GetFloat();
				scale.z = currentGameObjectJson["Scale"].GetArray()[2].GetFloat();

				gameObject->transform->SetPosition(pos);
				gameObject->transform->SetRotation(rotation);
				gameObject->transform->SetScale(scale);

				const char* meshPath = "";
				const char* texturePath = nullptr;
				for (const auto& currentComponentJson : currentGameObjectJson["Components"].GetArray())
				{
					const int type = currentComponentJson["Type"].GetInt();
					switch (type)
					{
					default:
						break;
					case 0:
						meshPath = currentComponentJson["Path"].GetString();
						break;
					case 1:
						texturePath = currentComponentJson["Path"].GetString();
						break;

					}
				}
				App->import->LoadGeometry(meshPath, gameObject, texturePath);
			}

		}
	}
	RELEASE_ARRAY(buffer);
}

void ModuleScene::saveScene()
{
	rapidjson::StringBuffer buffer;
	JSONWriter writer(buffer );

	writer.StartObject();
	writer.String("Game Objects");
	writer.StartObject();
	writer.StartArray();
	root->save(writer);

	writeChildren(writer, root->children);

	writer.EndArray();
	writer.EndObject();

	if (App->fileSystem->Save(fileName, buffer.GetString(), strlen(buffer.GetString()), false))
	{
		LOG("Scene saved.");
	}
	else
	{
		LOG("Scene not saved.");
	}
}


GameObject* ModuleScene::getParent(const std::vector<GameObject*> children, const int parentUUID)
{
	for (int i = 0; i < children.size(); ++i)
	{
		if (children[i]->UUID == parentUUID)
		{
			return children[i];
		}

		if (children[i]->children.size() > 0) return getParent(children[i]->children, parentUUID);
	}

	return nullptr;
}

bool ModuleScene::isRoot(std::string name)
{
	for (auto& c : name) c = tolower(c);

	return name.find("root") != std::string::npos;
}

void ModuleScene::writeChildren(JSONWriter& writer, std::vector<GameObject*> children)
{
	for (GameObject* sceneGO : children)
	{
		sceneGO->save(writer);

		if (sceneGO->children.size() > 0) writeChildren(writer, sceneGO->children);
	}
}
