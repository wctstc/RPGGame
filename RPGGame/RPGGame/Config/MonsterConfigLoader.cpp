

#include "MonsterConfigLoader.h"

#include "dataconfig_monsterconfig.pb.h"
#include "Platform.h"

bool MonsterConfigLoader::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_monsterconfig.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[1024*1024];
	int iLength = fread(csBuffer, 1, 1024*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::MonsterConfigArray ayMonsterConfig;
	if (!ayMonsterConfig.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayMonsterConfig.items_size(); ++i)
	{
	    MonsterConfig oMonsterConfig;
		
		oMonsterConfig.iID = (int)(ayMonsterConfig.items(i).id());
		oMonsterConfig.eType = (MonsterType)(ayMonsterConfig.items(i).type());
		oMonsterConfig.iMaxHp = (int)(ayMonsterConfig.items(i).maxhp());
		oMonsterConfig.iAttack = (int)(ayMonsterConfig.items(i).attack());
		oMonsterConfig.iDefance = (int)(ayMonsterConfig.items(i).defance());

		oMonsterConfig.sName = platform::UTF_82ASCII(ayMonsterConfig.items(i).name());
		oMonsterConfig.sDescription = platform::UTF_82ASCII(ayMonsterConfig.items(i).description());

		for(int j = 0; j < ayMonsterConfig.items(i).dropid_size(); ++j)
		{
			oMonsterConfig.veciDropID.push_back(ayMonsterConfig.items(i).dropid(j));
		}


        m_vecRecords.push_back(oMonsterConfig);
	}
	
	return true;
}
const vector<MonsterConfig> &MonsterConfigLoader::GetAllConfig()
{
	return m_vecRecords;
}
const MonsterConfig *MonsterConfigLoader::GetMonsterConfigByIndex(const unsigned int uIndex)
{
	if (uIndex <= m_vecRecords.size())
	{
		return &m_vecRecords[uIndex];
	}
	return NULL;
}
	
const MonsterConfig *MonsterConfigLoader::GetMonsterConfigByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MonsterConfig *MonsterConfigLoader::GetMonsterConfigByType(const MonsterType eType)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].eType == eType)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MonsterConfig *MonsterConfigLoader::GetMonsterConfigByMaxHp(const int iMaxHp)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iMaxHp == iMaxHp)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MonsterConfig *MonsterConfigLoader::GetMonsterConfigByAttack(const int iAttack)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iAttack == iAttack)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MonsterConfig *MonsterConfigLoader::GetMonsterConfigByDefance(const int iDefance)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iDefance == iDefance)
			return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const MonsterConfig *MonsterConfigLoader::GetMonsterConfigByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MonsterConfig *MonsterConfigLoader::GetMonsterConfigByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
			return &m_vecRecords[i];
	}
	return NULL;
}
	
