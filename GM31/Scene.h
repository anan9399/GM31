#pragma once
#include<memory>
#include<typeinfo>
#include<vector>
#include <list>
#include "GameObject.h"
#include "polygon2D.h"
#include"Field.h"
#include"Camera.h"
#include"Player.h"
#include"Enemy.h"
#include"Bullet.h"
#include"Explosion.h"
#include"Billboard.h"

class Scene {

protected:
	std::list<GameObject*> m_GameObjs[3];

public:
	
	void Init() 
	{
		
		AddGameObj<Camera>(0);
		AddGameObj<Field>(1)->SetPos({ -10.0f,0.0f,10.0f });
		AddGameObj<Field>(1)->SetPos({ 10.0f,0.0f,10.0f });
		AddGameObj<Field>(1)->SetPos({ -10.0f,0.0f,-10.0f });
		AddGameObj<Field>(1)->SetPos({ 10.0f,0.0f,-10.0f });

		AddGameObj<Billboard>(1)->SetPos({ 3.0f,2.0f,5.0f });
		
		AddGameObj<Player>(1);
		
		AddGameObj<Enemy>(1)->SetPos({ -3.0f,1.0f,3.0f });
		AddGameObj<Enemy>(1)->SetPos({ 3.0f,1.0f,3.0f });

		AddGameObj<polygon2D>(2);
		
	};
	void UnInit() 
	{
		for (int i = 0; i < 3; i++) {
			for (auto& g : m_GameObjs[i]) {
				g->Uninit();
			}
			m_GameObjs[i].clear();
		}
	};


	void Update() 
	{
		for (int i = 0; i < 3; i++) {
			for (auto& g : m_GameObjs[i]) {
				g->Update();

			}

			m_GameObjs[i].remove_if([](GameObject* object)
				{return object->Destory(); });
		}
	//m_GameObjs.erase(std::remove_if(m_GameObjs.begin(), m_GameObjs.end(),
	//					[](GameObject* object){return object->Destory(); }
	//				), m_GameObjs.end()
	//);

	};
	void Draw() 
	{
		for(int i = 0;i < 3; i++){
			for (auto& g : m_GameObjs[i]) {
				g->Draw();
			}
		}
	};


	template<typename T>
	T* AddGameObj(int layer) {
		T* component = new T();
		m_GameObjs[layer].push_back(component);
		component->Init();

		return static_cast<T*>(component);
	}

	template<typename T>
	T* GetGameObj() {
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObjs[i]) {
				if (typeid(*object) == typeid(T&))
				{
					return static_cast<T*>(object);
				}
			}
		}
		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetGameObjs() {
		std::vector<T*> objects;
		for (int i = 0; i < 3; i++) {
			for (GameObject* object : m_GameObjs[i]) {
				if (typeid(*object) == typeid(T&))
				{
					objects.push_back(static_cast<T*>(object));
				}
			}
		}

		return objects;
	}

};