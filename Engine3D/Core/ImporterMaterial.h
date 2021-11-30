#pragma once

#include "Core/Globals.h"
#include <string>

class aiMaterial;
class ComponentMaterial;

namespace ImporterMaterial
{
	void Import(const aiMaterial* material, ComponentMaterial* ourMaterial);
	uint64 Save(const ComponentMaterial* ourMaterial, char** fileBuffer);
	void Load(const char* fileBuffer, ComponentMaterial* ourMaterial);

};