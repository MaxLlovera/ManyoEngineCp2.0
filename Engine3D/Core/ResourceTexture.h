#pragma once
#include "Resource.h"

enum Format {
	color_index,
	rgb,
	rgba,
	bgr,
	bgra,
	luminance,
	unknown
};

class ResourceTexture : public Resource
{
public:
	//ResourceTexture(UID id);
	virtual ~ResourceTexture();
	//bool LoadInMemory() override;
	//void Save(Config& config) const override;
	//void Load(const Config& config) override;
public:
	uint width = 0;
	uint height = 0;
	uint depth = 0;
	uint mips = 0;
	uint bytes = 0;
	uint gpu_id = 0;
	Format format = unknown;
};