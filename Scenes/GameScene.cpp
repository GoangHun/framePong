#include "stdafx.h"
#include "GameScene.h"
#include "InputMgr.h"
#include "ResourceMgr.h"

GameScene::GameScene(SceneId id)
{
	resources.push_back(std::make_tuple(ResourceTypes::Font, "fonts/DS-DIGI.ttf"));
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	Release();
	Scene::Init();

	AddGo(new Bat("Bat"));
    bat = (Bat*)FindGo("Bat");
	AddGo(new Ball("Ball"));
    ball = (Ball*)FindGo("Ball");
    AddGo(new TextGo("SL"));
    sl = (TextGo*)FindGo("SL");

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void GameScene::Release()
{
	Scene::Release();
	if (gameObjects.empty())
	{
		return;
	}
	for (auto go : gameObjects)
	{
		delete go;
	}
	gameObjects.clear();
}

void GameScene::Enter()
{
	Scene::Enter();
}

void GameScene::Exit()
{
	Scene::Exit();
}

void GameScene::Update(float dt)
{
	//Scene::Update(dt);

    if (!ballActive && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
    {
        ballActive = true;    
        ball->Fire(Utils::Normalize({ 1.f, -1.f }), 1000.f);
    }
    else if (ballActive && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
    {
        ballActive = false;
        ball->Init();
    }

    bat->Update(dt);
    if (!ballActive)
    {
        ball->SetPosition(bat->GetPosition());
    }
    ball->Update(dt);

    //충돌 체크
    sf::FloatRect ballRect = ball->GetBounds();
    if (ballRect.top < 0.f)
    {
        ball->OnCollisionTop();
    }
    else if (ballRect.top + ballRect.height > 720.f)    //CircleShape의 상단에 높이를 더해서 하단 계산
    {
        ball->OnCollisionBottom();
        --life;

        ballActive = false;
        ball->Init();
        if (life == 0)
        {
            bat->Init();
            score = 0;
            life = 3;
        }

    }
    else if (ballRect.left < 0.f)
    {
        ball->OnCollisionLeft();
    }
    else if (ballRect.left + ballRect.width > 1280.f)
    {
        ball->OnCollisionRight();

    }

    if (ballRect.intersects(bat->GetBounds()))
    {
        if (ball->GetCenterPos().x < bat->GetTLPos().x && Utils::Distance(ball->GetCenterPos(), bat->GetTLPos()) < 10.f)
        {
            ball->OnCollisionBottom(ball->GetCenterPos() - bat->GetTLPos());
        }
        else if (ball->GetCenterPos().x > bat->GetTRPos().x && Utils::Distance(ball->GetCenterPos(), bat->GetTRPos()) < 10.f)
        {
            ball->OnCollisionBottom(ball->GetCenterPos() - bat->GetTRPos());
        }
        else
        {
            ball->OnCollisionBottom();       
        }     

        if (!scoreCheck)
        {
            score++;
        }
        scoreCheck = true;
    }
    else
    {
        scoreCheck = false;
    }

    std::stringstream ss;
    ss << "Score: " << score << "\tLife: " << life;
    sl->SetText(ss.str(), 50, sf::Color::White, 20, 20);
    sl->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));
    sl->Update(dt);
}

void GameScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}
