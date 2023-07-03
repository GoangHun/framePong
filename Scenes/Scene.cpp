#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceMgr.h"


Scene::Scene(SceneId id) : sceneId(id)
{
}

Scene::~Scene()
{
	Release();
}

GameObject* Scene::FindGo(const std::string& name)
{
	//람다식 표현 - 공부 필요
	auto compare = [name](GameObject* go) { return go->GetName() == name; };
	//find()에 람다 표현식을 사용할 경우 find_if를 사용함
	auto it = std::find_if(gameObjects.begin(), gameObjects.end(), compare);
	if (it == gameObjects.end())
	{
		return nullptr;
	}
	return *it;
	

	//다른 방법
	/*for (auto go : gameObjects)
	{
		if (go->GetName() == name)
		{
			return go;
		}
	}
	return nullptr;*/
}

void Scene::FindGo(std::list<GameObject*>& list, const std::string& name)
{
	//list.clear();
	for (auto go : gameObjects)
	{
		if (go->GetName() == name)
		{
			list.push_back(go);
		}
	}
}

//존재확인
bool Scene::Exist(GameObject* go)
{
	return std::find(gameObjects.begin(), gameObjects.end(), go) != gameObjects.end();
}

//중복확인 후 삽입
void Scene::AddGo(GameObject* go)
{
	if (!Exist(go))
	{
		gameObjects.push_back(go);
	}
}

void Scene::RemoveGo(GameObject* go)
{
	gameObjects.remove(go);
	//delete go
}

void Scene::SortGos()
{
	gameObjects.sort([](GameObject* lhs, GameObject* rhs) {
		if (lhs->sortLayer != rhs->sortLayer)
			return lhs->sortLayer < rhs->sortLayer;

		return lhs->sortOrder < rhs->sortOrder; });
}

void Scene::Init()
{
}

void Scene::Release()
{
}

void Scene::Enter()
{
	RESOURCE_MGR.Load(resources);

	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void Scene::Exit()
{
	RESOURCE_MGR.Load(resources);

}

void Scene::Update(float dt)
{
	for (auto go : gameObjects)
	{
		if (go->GetActive())
		{
			go->Update(dt);
		}
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	SortGos();

	for (auto go : gameObjects)
	{
		if (go->GetActive())
		{
			go->Draw(window);
		}
	}
}


