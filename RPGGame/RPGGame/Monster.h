#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Actor.h"

class Monster:public Actor
{
public:
    enum MonsterType
    {
        /*!< 温和 */
        MONSTER_TPE_GENTLE,

        /*!< 中立 */
        MONSTER_TYPE_NEUTRAL,

        /*!< 敌对 */
        MOSTER_TYPE_HOSTIL,
    };
public:
    Monster();
    ~Monster();
public:
    static const Monster &GetNoMonster();
public:
    bool Init(Monster& oMonster);
    bool Init(
        const int iID,
        const string sName,
        const int iHp,
        const int iMaxHp,
        const int iAttack,
        const int iDefance,
        const Monster::MonsterType eType,
        const string sDescription,
        const vector<int> &vDrop);
public:
    SET_GET(Monster::MonsterType, e, Type,        m_stMonsterData.eType)
    SET_GET(string,               s, Description, m_stMonsterData.sDescription)
    SET_GET(vector<int>&,         v, Drop,        m_stMonsterData.vDrop)
private:
    struct MonsterData
    {
        Monster::MonsterType eType;
        string sDescription;
        vector<int> vDrop;
    };
private:
    MonsterData m_stMonsterData;
};


#endif // __MONSTER_H__


