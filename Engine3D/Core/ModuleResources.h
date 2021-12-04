#pragma once
#include "Module.h"
#include "Globals.h"

#include <string>
#include <map>

class Resource;

class ModuleResources : public Module
{
public:
	ModuleResources(Application* app, bool start_enabled = true);
	~ModuleResources();

	//UID Find(const char* file_in_assets) const;
	//UID ImportFile(const char* new_file_in_assets);
	//UID GenerateNewUID();
	//const Resources* RequestResource(UID uid) const;
	//Resource* RequestResource(UID uid);
	//void ReleaseResource(UID uid);

public:
	//Resource* CreateNewResource(const char* assetsFile, Type type);
	//std::map<UID, Resources*> resources;
};
