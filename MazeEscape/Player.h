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
	bool _attacking = false; //이중 공격 막기 위한 체크
	bool _visionExpanded = false; //시야확장여부
	int _visionRange = 2; //상하좌우 시야 타일 수

	float _visionItemPersistTime = 5.f;
	float _visionTimer = 0.f;
};

