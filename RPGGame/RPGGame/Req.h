#ifndef __REQ_H__
#define __REQ_H__

#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;
using std::pair;

class Req
{
public:
	Req();
	~Req();
public:
	void Add(string sKey, int iValue);
	void Add(string sKey, string sValue);
	void Add(string sKey, vector<Req> vValue);

	const int GetInt(string sKey)const;
	const string GetString(string sKey)const;
	const vector<Req> GetVector(string sKey)const;

	const bool HasInt(string sKey)const;
	const bool HasString(string sKey)const;
	const bool HasVector(string sKey)const;
private:
	map<string, int> m_mapIntArg;
	map<string, string> m_mapStringArg;
	map<string, vector<Req>> m_mapVectorArg;
};


#endif // __REQ_H__
