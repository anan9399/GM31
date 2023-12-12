#pragma once
#include"GameObject.h"
#include<memory>
#include<vector>
class Model;
class Player;

class Child : public GameObject
{

public:
	static void Load();
	static void UnLoad();

	void Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetParent(Player* parent)
	{
		m_parent = parent;
	}
private:
	Player* m_parent;
	static std::unique_ptr<Model> m_model;
	D3DXMATRIX m_world, m_scale, m_rot, m_trans;
protected:

	std::vector<D3DXVECTOR3> m_waypoints = { {10.0f,0.0f,10.0f},{10.0f,3.0f,10.0f},{20.0f,3.0f,10.0f} };

	float m_range = 5.0f;
	float m_nowRange = 0.0f;


};

