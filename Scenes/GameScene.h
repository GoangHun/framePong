#pragma once
#include "Scene.h"
#include "Bat.h"
#include "Ball.h" 
#include "TextGo.h"
#include <sstream>

class GameScene :
    public Scene
{
protected:
	bool ballActive = false;

	Bat* bat = nullptr;
	Ball* ball = nullptr;
	TextGo* sl = nullptr;

    int score = 0;
	bool scoreCheck = false;
    int life = 3;

public:
	GameScene(SceneId id = SceneId::None);
	virtual ~GameScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;	//�� ��ȯ�� �� �� Init ��� ���
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

