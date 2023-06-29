#pragma once
#include<memory>
#include"Scene.h"
#include"audio.h"
class Manager
{
private:
	Manager() {};
	static std::shared_ptr<Scene> m_Scene;

public:
	static Manager& GetInstance() {
		static Manager instance;
		return instance;
	}
	static std::shared_ptr<Scene> GetScene() {
		return m_Scene;
	}
	void Init();
	void Uninit();
	void Update();
	void Draw();
	
	template<typename T>
	static void SetScene() {
		if (m_Scene) {
			m_Scene->UnInit();
			m_Scene.reset();
		}

		m_Scene =std::make_shared<T>();
		m_Scene->Init();
	}
};