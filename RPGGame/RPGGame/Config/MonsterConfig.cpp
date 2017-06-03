

#include "MonsterConfig.h"

#include "dataconfig_monster.pb.h"
#include "Platform.h"

bool MonsterConfig::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_monster.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[1024*1024];
	int iLength = fread(csBuffer, 1, 1024*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::MONSTERArray ayMonster;
	if (!ayMonster.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayMonster.items_size(); ++i)
	{
	    Monster oMonster;
		
		oMonster.iID = (int)(ayMonster.items(i).id());
		oMonster.eType = (MonsterType)(ayMonster.items(i).type());
		oMonster.iMaxHp = (int)(ayMonster.items(i).maxhp());
		oMonster.iAttack = (int)(ayMonster.items(i).attack());
		oMonster.iDefance = (int)(ayMonster.items(i).defance());

		oMonster.sName = platform::UTF_82ASCII(ayMonster.items(i).name());
		oMonster.sDescription = platform::UTF_82ASCII(ayMonster.items(i).description());

		for(int j = 0; j < ayMonster.items(i).drop_id_size(); ++j)
		{
			oMonster.veciDrop_id.push_back(ayMonster.items(i).drop_id(j));
		}


        m_vecRecords.push_back(oMonster);
	}
	
	return true;
}
	
const Monster *MonsterConfig::GetMonsterByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Monster *MonsterConfig::GetMonsterByType(const MonsterType eType)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].eType == eType)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Monster *MonsterConfig::GetMonsterByMaxHp(const int iMaxHp)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iMaxHp == iMaxHp)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Monster *MonsterConfig::GetMonsterByAttack(const int iAttack)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iAttack == iAttack)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Monster *MonsterConfig::GetMonsterByDefance(const int iDefance)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iDefance == iDefance)
		 return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const Monster *MonsterConfig::GetMonsterByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Monster *MonsterConfig::GetMonsterByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
		 return &m_vecRecords[i];
	}
	return NULL;
}
	
