#include "QueryLoader.h"



QueryLoader::QueryLoader()
{
}


QueryLoader::~QueryLoader()
{
}

bool QueryLoader::Init()
{
	m_mapQuerys.insert(pair<int, QueryBase&>(QUERY_ID_BAG, QueryBag()));

	return true;
}
