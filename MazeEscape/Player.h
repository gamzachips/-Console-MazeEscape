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
	bool _attacking = false; //���� ���� ���� ���� üũ
	bool _visionExpanded = false; //�þ�Ȯ�忩��
	int _visionRange = 2; //�����¿� �þ� Ÿ�� ��

	float _visionItemPersistTime = 5.f;
	float _visionTimer = 0.f;
};

