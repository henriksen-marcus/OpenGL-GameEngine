#include "Renderer.h"
#include "Actor.h"
#include "Skybox.h"

Renderer::Renderer(unsigned amount)
{
	mObjects.reserve(amount);
}

void Renderer::Add(const std::string& name, Actor* object)
{
	mObjects[name] = object;
}

void Renderer::Remove(const std::string& name)
{
	mObjects.erase(name);
}

void Renderer::Remove(Actor* actor)
{
	auto it = std::find_if(mObjects.begin(), mObjects.end(), 
		[&](const auto& pair) { return pair.second == actor; });

	if (it != mObjects.end())
	{
		mObjects.erase(it->first);
	}
}

Actor* Renderer::Get(const std::string& name)
{
	return mObjects.at(name); // Can be nullptr
}


void Renderer::BeginPlay()
{
	for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		it->second->BeginPlay();
	}
}

Actor* Renderer::Find(const std::string& name)
{
	auto it = mObjects.find(name);
	if (it != mObjects.end()) {
		return it->second;
	}
	return nullptr;
}

void Renderer::DrawObjects(float deltaTime)
{
	if (mSkybox) 
	{
		mSkybox->Draw();
	}

	for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		it->second->Tick(deltaTime);
		it->second->Draw();
	}
}
