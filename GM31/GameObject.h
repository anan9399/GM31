#pragma once
#include"main.h"
#include<wrl.h>
#include"Component.h"
#include<vector>
#include<list>
#include<memory>
#include"Bindable.h"

class GameObject 
{
protected:
	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	std::vector<std::shared_ptr<Bindable>> m_binds;

	std::vector<Component*> m_Component;
	bool m_Destory = false;

public:
	virtual void Init() 
	{
	
	};
	virtual void Uninit() 
	{
		for (auto& g : m_Component) {
			g->Uninit();
		}
		m_Component.clear();
	};
	virtual void Update() 
	{
		for (auto& g : m_Component) {
			g->Update();
		}
	};
	virtual void Draw() 
	{
		for (auto& g : m_Component) {
			g->Draw();
		}
	};
	

	virtual void Hurt() {};


	void SetPos(D3DXVECTOR3 pos) {
		m_Position = pos;
	}
	/*GameObject* SetPos(D3DXVECTOR3 pos) {
		m_Position = pos;
		return this;
	}*/

	void SetScale(D3DXVECTOR3 scale) {
		m_Scale = scale;
	}
	void SetRotation(D3DXVECTOR3 rot) {
		m_Rotation= rot;
	}

	void SetDestory() {
		m_Destory = true;
	}

	

	bool Destory() {
		if (m_Destory) {
			Uninit();
			delete this;
			return true;
		}
		return false;
	}
	D3DXVECTOR3* GetPosAdress() {
		return &m_Position;
	}

	D3DXVECTOR3 GetPos()const {
		return m_Position;
	}
	D3DXVECTOR3 GetScale()const {
		return m_Scale;
	}

	D3DXVECTOR3 GetForward()const {
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DVECTOR forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;
		return forward;
	}

	D3DXVECTOR3 GetForwardR(float angle)const {
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y+angle, m_Rotation.x, m_Rotation.z);

		D3DVECTOR forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;
		return forward;
	}


	D3DXVECTOR3 GetRight() const {
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DVECTOR right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;
		return right;
	}


	void RotateOne() {
		if (m_Rotation.y <= 3.1415f) {
			m_Rotation.y += 1.0f/ 3.1415f;
		}
		else
		{
			m_Rotation.y = 0.0f;
		}
		
	}



	template<typename T>
	T* AddComponent(){
		Component* component = new T();
		m_Component.push_back(component);
		component->Init();

		return static_cast<T*>(component);
	}
	void BindAll()const noexcept {
		for (auto& b : m_binds)
		{
			b->Bind();
		}
	}

	void AddBind(std::shared_ptr<Bindable> bind) noexcept {
		m_binds.push_back(std::move(bind));
	}

};