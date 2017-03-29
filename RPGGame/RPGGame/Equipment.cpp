#include "Equipment.h"



Equipment::Equipment()
{
}


Equipment::~Equipment()
{
}

bool Equipment::Init(int iBaseMaxHp, int iBaseAttack, int iBaseDefance)
{
	SetMaxHp(0);
	SetAttack(0);
	SetDefance(0);
	return true;
}
