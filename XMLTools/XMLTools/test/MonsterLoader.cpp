

#include "MonsterLoader.h"

#include "dataconfig_monster.pb.h"
#include "Platform.h"

bool MonsterLoader::Init()
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
		
		oMonster.iID = (property_type)(ayMonster.items(i).id());
		oMonster.eType = (property_type)(ayMonster.items(i).type());
		oMonster.iMaxHp = (property_type)(ayMonster.items(i).maxhp());
		oMonster.iAttack = (property_type)(ayMonster.items(i).attack());
		oMonster.iDefance = (property_type)(ayMonster.items(i).defance());

		oMonster.sName = platform::UTF_82ASCII(ayMonster.items(i).name());
		oMonster.sDescription = platform::UTF_82ASCII(ayMonster.items(i).description());

		for(int j = 0; j < ayMonster.items(i).drop_id_size(); ++j)
		{
			oMonster.veciDrop_id.push_back(ayMonster.items(i).drop_id());
		}


        m_vecRecords.push_back(oMonster);
	}
}
	
const Monster *MonsterLoader::GetMonsterByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Monster *MonsterLoader::GetMonsterByType(const Monster::MonsterType eType)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].eType == eType)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Monster *MonsterLoader::GetMonsterByMaxHp(const int iMaxHp)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iMaxHp == iMaxHp)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Monster *MonsterLoader::GetMonsterByAttack(const int iAttack)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iAttack == iAttack)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Monster *MonsterLoader::GetMonsterByDefance(const int iDefance)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iDefance == iDefance)
		 return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const Monster *MonsterLoader::GetMonsterByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
		 return "m_vecRecords[i]
	}
	return NULL;
}
		
const Monster *MonsterLoader::GetMonsterByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
		 return "m_vecRecords[i]
	}
	return NULL;
}
	
