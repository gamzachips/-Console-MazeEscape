#pragma once
#include "Creature.h"

class Player : public Creature
{
public:
	Player();
	void Update();
	void Input();
	void Move(Pos nextPos);
	void StartAttack();

	int GetVisionRange();
	int GetHP() { return _hp; }
	void SetIsAttacking(bool isAttacking) { _attacking = isAttacking; }
private:
	//attack
	bool _attacking = false; //���� ���� ���� ���� üũ

	int _visionRange = 2;
};

