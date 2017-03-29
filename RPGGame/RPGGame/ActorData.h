#ifndef __ACTORPROPERTY__H__
#define __ACTORPROPERTY__H__

#include <string>

using std::string;

class ActorData
{
public:
	ActorData();
	~ActorData();
public:
	virtual bool Init( int iID, int iHp, int iMaxHp, int iAttack, int iDefance);
	virtual bool Init(const ActorData &oActorData=ActorData());
public:
	int GetID() const { return m_iID; }
	int GetHp() const { return m_iHp; }
	int GetMaxHp() const { return m_iMaxHp; }
	int GetAttack() const { return m_iAttack; }
	int GetDefance() const { return m_iDefance; }
	void SetHp(int iHp) { m_iHp = iHp; }
	void SetMaxHp(int iMaxHp) { m_iMaxHp = iMaxHp; }
	void SetAttack(int iAttack) { m_iAttack = iAttack; }
	void SetDefance(int iDefance) { m_iDefance = iDefance; }
private:
	int m_iID;
	int m_iHp;
	int m_iMaxHp;
	int m_iAttack;
	int m_iDefance;
};




#endif