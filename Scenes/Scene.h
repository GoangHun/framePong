#pragma once

class GameObject;

class Scene
{
protected:
	SceneId sceneId;

	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;


	std::vector<std::tuple<ResourceTypes, std::string>> resources;
	std::list<GameObject*> gameObjects;

public:
	Scene(SceneId id = SceneId::None);
	virtual ~Scene();

	GameObject* FindGo(const std::string& name);
	void FindGo(std::list<GameObject*>& list, const std::string& name);
	bool Exist(GameObject* go);
	void AddGo(GameObject* go);
	void RemoveGo(GameObject* go);
	void SortGos();

	virtual void Init() = 0;
	virtual void Release();

	virtual void Enter();	//씬 전환을 할 때 Init 대신 사용
	virtual void Exit();	

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

};

