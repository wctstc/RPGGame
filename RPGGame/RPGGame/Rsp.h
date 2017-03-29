#ifndef __RSP_H__
#define __RSP_H__

#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;
using std::pair;

class Rsp
{
public:
	Rsp();
	~Rsp();
public:
	void Add(string sKey, int iValue);
	void Add(string sKey, string sValue);
	void Add(string sKey, vector<Rsp> vValue);

	const int GetInt(string sKey)const;
	const string GetString(string sKey)const;
	const vector<Rsp> GetVector(string sKey)const;

	const bool HasInt(string sKey)const;
	const bool HasString(string sKey)const;
	const bool HasVector(string sKey)const;
private:
	map<string, int> m_mapIntArg;
	map<string, string> m_mapStringArg;
	map<string, vector<Rsp>> m_mapVectorArg;
};

#endif // __RSP_H__
