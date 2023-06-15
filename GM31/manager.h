#pragma once
#include<memory>

class Scene;

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


};