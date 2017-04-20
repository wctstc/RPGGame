#include "Rsp.h"

using rsp::Rsp;

Rsp::Rsp()
{
}


Rsp::~Rsp()
{
}

void Rsp::Add(string sKey, int iValue)
{
	m_mapIntArg.insert(pair<string, int>(sKey, iValue));
}

void Rsp::Add(string sKey, string sValue)
{
	m_mapStringArg.insert(pair<string, string>(sKey, sValue));
}

void Rsp::Add(string sKey, vector<Rsp> vValue)
{
	m_mapVectorArg.insert(pair<string, vector<Rsp>>(sKey, vValue));
}


const int Rsp::GetInt(string sKey) const
{
	map<string, int>::const_iterator it = m_mapIntArg.find(sKey);
	if (it != m_mapIntArg.end())
		return it->second;
	else
		return 0;
}

const string Rsp::GetString(string sKey) const
{
	map<string, string>::const_iterator it = m_mapStringArg.find(sKey);
	if (it != m_mapStringArg.end())
		return it->second;
	else
		return "";
}

const vector<Rsp> Rsp::GetVector(string sKey) const
{
	map<string, vector<Rsp>>::const_iterator it = m_mapVectorArg.find(sKey);
	if (it != m_mapVectorArg.end())
		return it->second;
	else
		return vector<Rsp>();
}

const bool Rsp::HasInt(string sKey) const
{
	return m_mapIntArg.find(sKey) != m_mapIntArg.end();
}

const bool Rsp::HasString(string sKey) const
{
	return m_mapStringArg.find(sKey) != m_mapStringArg.end();
}

const bool Rsp::HasVector(string sKey) const
{
	return m_mapVectorArg.find(sKey) != m_mapVectorArg.end();
}
