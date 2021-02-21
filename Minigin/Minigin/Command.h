#pragma once
#include "GameObject.h"

class Command
{
public:
	Command(GameObject* pGameObject) :m_pGameObject{ pGameObject } {};
	virtual ~Command() = default;
	virtual void Execute() = 0;
protected:
	GameObject* GetGameObject() const { return m_pGameObject; };
private:
	GameObject* m_pGameObject{ nullptr };
};

//commands for game objects

class JumpCommand : public Command
{
public:
	JumpCommand(GameObject* pGameObject) :Command{ pGameObject } {};
	void Execute() override 
	{ 
		//if (GetGameObject()) 
			//GetGameObject()->Jump();
	};
};

class DuckCommand : public Command
{
public:
	DuckCommand(GameObject* pGameObject) :Command{ pGameObject } {};
	void Execute() override 
	{ 
		//if (GetGameObject()) 
			//GetGameObject()->Duck(); 
	};
};

class FireCommand : public Command
{
public:
	FireCommand(GameObject* pGameObject) :Command{ pGameObject } {};
	void Execute() override 
	{ 
		//if (GetGameObject())
			//GetGameObject()->Fire();
	};
};

class FartCommand : public Command
{
public:
	FartCommand(GameObject* pGameObject) :Command{ pGameObject } {};
	void Execute() override
	{ 
		//if (GetGameObject())
			//GetGameObject()->Fart();
	};
};