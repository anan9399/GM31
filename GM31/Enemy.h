#pragma once
#include "Player.h"

namespace BehaviorTree {
	class GuardBT;
	class Tree;
}


class Enemy : public Player
{
	
public:
	static void Load();
	static void UnLoad();
	
	void SetWayPoints(std::vector<D3DXVECTOR3> waypoints) {
		m_waypoints = waypoints;
	}

	void Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
protected:
	BehaviorTree::Tree* m_guardBT;
	static std::unique_ptr<Model> m_model;
	std::vector<D3DXVECTOR3> m_waypoints = { {10.0f,0.0f,10.0f},{10.0f,3.0f,10.0f},{20.0f,3.0f,10.0f} };

	float m_range = 5.0f;
	float m_nowRange = 0.0f;


};

