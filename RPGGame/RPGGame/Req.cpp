#include "Req.h"


req::Req::Req()
{
}


req::Req::~Req()
{
}

bool req::Req::Init(cmd::Command eCmd)
{
    m_eCmd = eCmd;
    m_mapIntArg.clear();
    m_mapStringArg.clear();
    m_mapVectorArg.clear();
    return true;
}

cmd::Command req::Req::GetCmd()
{
    return m_eCmd;
}

void req::Req::Add(string sKey, int iValue)
{
	m_mapIntArg.insert(pair<string, int>(sKey, iValue));
}

void req::Req::Add(string sKey, string sValue)
{
	m_mapStringArg.insert(pair<string, string>(sKey, sValue));
}

void req::Req::Add(string sKey, vector<req::Req> vValue)
{
	m_mapVectorArg.insert(pair<string, vector<req::Req>>(sKey, vValue));
}

const int req::Req::GetInt(string sKey) const
{
	map<string, int>::const_iterator it = m_mapIntArg.find(sKey);
	if (it != m_mapIntArg.end())
		return it->second;
	else
		return 0;
}

const string req::Req::GetString(string sKey) const
{
	map<string, string>::const_iterator it = m_mapStringArg.find(sKey);
	if (it != m_mapStringArg.end())
		return it->second;
	else
		return "";
}

const vector<req::Req> req::Req::GetVector(string sKey) const
{
	map<string, vector<req::Req>>::const_iterator it = m_mapVectorArg.find(sKey);
	if (it != m_mapVectorArg.end())
		return it->second;
	else
		return vector<req::Req>();
}

const bool req::Req::HasInt(string sKey) const
{
	return m_mapIntArg.find(sKey) == m_mapIntArg.end();
}

const bool req::Req::HasString(string sKey) const
{
	return m_mapStringArg.find(sKey) == m_mapStringArg.end();
}

const bool req::Req::HasVector(string sKey) const
{
	return m_mapVectorArg.find(sKey) == m_mapVectorArg.end();
}
