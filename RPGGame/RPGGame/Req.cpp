#include "Req.h"



Req::Req()
{
}


Req::~Req()
{
}

void Req::Add(string sKey, int iValue)
{
	m_mapIntArg.insert(pair<string, int>(sKey, iValue));
}

void Req::Add(string sKey, string sValue)
{
	m_mapStringArg.insert(pair<string, string>(sKey, sValue));
}

void Req::Add(string sKey, vector<Req> vValue)
{
	m_mapVectorArg.insert(pair<string, vector<Req>>(sKey, vValue));
}

const int Req::GetInt(string sKey) const
{
	map<string, int>::const_iterator it = m_mapIntArg.find(sKey);
	if (it != m_mapIntArg.end())
		return it->second;
	else
		return 0;
}

const string Req::GetString(string sKey) const
{
	map<string, string>::const_iterator it = m_mapStringArg.find(sKey);
	if (it != m_mapStringArg.end())
		return it->second;
	else
		return "";
}

const vector<Req> Req::GetVector(string sKey) const
{
	map<string, vector<Req>>::const_iterator it = m_mapVectorArg.find(sKey);
	if (it != m_mapVectorArg.end())
		return it->second;
	else
		return vector<Req>();
}

const bool Req::HasInt(string sKey) const
{
	return m_mapIntArg.find(sKey) == m_mapIntArg.end();
}

const bool Req::HasString(string sKey) const
{
	return m_mapStringArg.find(sKey) == m_mapStringArg.end();
}

const bool Req::HasVector(string sKey) const
{
	return m_mapVectorArg.find(sKey) == m_mapVectorArg.end();
}
