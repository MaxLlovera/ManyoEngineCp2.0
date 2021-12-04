#pragma once
#include "Globals.h"

#include <vector>
#include <string>

enum Type
{
	texture,
	mesh,
	audio,
	scene,
	bone,
	animation,
	unknown
};

class Resource
{
public:
	//Resource(UID uid, Type type);
	virtual ~Resource();
	Type GetType() const;
	//UID GetUID() const;
	const char* GetAssetFile() const;
	const char* GetLibraryFile() const;
	bool IsLoadedToMemory() const;
	bool LoadToMemory();
	uint GetReferenceCount() const;
	//virtual void Save(Config& config) const;
	//virtual void Load(const Config& config);
	//virtual bool LoadInMemory() = 0;
public:
	//UID uid = 0;
	std::string assetsFile;
	std::string Libraryile;
	Type type = unknown;
	uint referenceCount = 0;
};


