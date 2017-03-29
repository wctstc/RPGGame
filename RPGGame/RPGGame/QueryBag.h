#ifndef __QUERYBAG_H__
#define __QUERYBAG_H__


#include "QueryBase.h"
class QueryBag : public QueryBase
{
public:
	QueryBag();
	~QueryBag();
public:
	virtual string GetFrameDescription();
	virtual vector<string> GetOptionsDescription();
};


#endif // __QUERYBAG_H__
