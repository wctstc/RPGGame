#pragma once
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

