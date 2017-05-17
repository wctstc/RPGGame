
#include "Monster.h"

Monster::Monster()
:m_eType(Monster::MONSTER_TYPE_GENTLE)
,m_iDescription("")
,m_vDrop(vector<int>())
  
{  
  
}  
  
Monster::~Monster()  
{  
  
}  
  
bool Monster::Init()  
{

    m_eType = Monster::MONSTER_TYPE_GENTLE;
    m_iDescription = "";
    m_vDrop = vector<int>();

    return true;  
}  
  
bool Monster::Init(const Monster &monster)  
{  
    m_eType = monster.m_eType;
    m_iDescription = monster.m_iDescription;
    m_vDrop = monster.m_vDrop;

    return true;  
}  
      
bool Monster::Init(const Monster::MonsterType eType,const string iDescription,const vector<int>& vDrop)  
{  
    m_eType = eType;
    m_iDescription = iDescription;
    m_vDrop = vDrop;

    return true;  
}  
      
string Monster::ToString()const
{  
    char csBuffer[10240] = {'\0'};  
    return csBuffer;  
}  
  
bool Monster::FromString(const string sBuffer)
{  
    return true;  
}  
  
