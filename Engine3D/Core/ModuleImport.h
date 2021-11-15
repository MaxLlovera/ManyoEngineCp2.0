#pragma once
#include "Module.h"

#include <string>

class ComponentMesh;
struct aiScene;
class TextureObject;

class ModuleImport : public Module
{
public:
	
	ModuleImport(Application* app, bool start_enabled = true);

	bool Init() override;
	update_status Update(float dt) override;
	bool CleanUp() override;

	bool LoadGeometry(const char* path);

	void FindNodeName(const aiScene* scene, const size_t i, std::string& name);

	//void Import(const aiMaterial* material, TextureObject* ourTexture);
	bool Save(std::string path);
	void Load(std::string path, TextureObject* ourTexture);

};