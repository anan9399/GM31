#pragma once
#include<memory>
#include"Scene.h"
#include"audio.h"
class Manager
{
private:
	Manager() {};
	static std::shared_ptr<Scene> m_scene;
	static std::shared_ptr<Scene> m_nextScene;

public:
	static Manager& GetInstance() {
		static Manager instance;
		return instance;
	}
	static std::shared_ptr<Scene> GetScene() {
		return m_scene;
	}
	void Init();
	void Uninit();
	void Update();
	void Draw();
	
	template<typename T>
	static void SetScene() {
		m_nextScene =std::make_shared<T>();
	}


};