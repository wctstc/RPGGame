#ifndef __QUERYBASE_H__
#define __QUERYBASE_H__

#include <vector>
#include <string>

using std::vector;
using std::string;

class QueryBase
{
public:
	QueryBase();
	~QueryBase();
public:
	virtual string GetFrameDescription() = 0;
	virtual vector<string> GetOptionsDescription() = 0;
};



#endif // __QUERYBASE_H__
