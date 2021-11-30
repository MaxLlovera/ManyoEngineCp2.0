#pragma once


#include "Core/Globals.h"
#include <string>

class aiMesh;
class ComponentMesh;

namespace ImporterMesh
{
	void Import(const aiMesh* mesh, ComponentMesh* ourmesh);
	uint64 Save(const ComponentMesh* ourmesh, char** fileBuffer);
	void Load(const char* fileBuffer, ComponentMesh* ourmesh);

};