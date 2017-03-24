#ifndef __QUERYMANAGER_H__
#define __QUERYMANAGER_H__

#include <map>

#include "Manager.h"
#include "Singleton.h"

#include "QueryBase.h"
#include "QueryBag.h"

using std::map;
using std::pair;


#define QUERY_ID_BAG 100

class QueryLoader:public Singleton<QueryLoader>
{
protected:
	QueryLoader();
	~QueryLoader();
public:
	virtual bool Init();

private:
	map<int, QueryBase&> m_mapQuerys;
};


#endif // __QUERYMANAGER_H__

