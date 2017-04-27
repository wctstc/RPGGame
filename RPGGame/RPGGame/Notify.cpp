#include "Notify.h"



notify::Notify::Notify()
{
}


notify::Notify::~Notify()
{
}

bool notify::Notify::Init(cmd::Command eCmd)
{
    m_eCmd = eCmd;
    m_mapIntArg.clear();
    m_mapStringArg.clear();
    m_mapVectorArg.clear();
    return true;
}

cmd::Command notify::Notify::GetCmd()
{
    return m_eCmd;
}

void notify::Notify::Add(string sKey, int iValue)
{
    m_mapIntArg.insert(pair<string, int>(sKey, iValue));
}

void notify::Notify::Add(string sKey, string sValue)
{
    m_mapStringArg.insert(pair<string, string>(sKey, sValue));
}

void notify::Notify::Add(string sKey, vector<notify::Notify> vValue)
{
    m_mapVectorArg.insert(pair<string, vector<notify::Notify>>(sKey, vValue));
}

const int notify::Notify::GetInt(string sKey) const
{
    map<string, int>::const_iterator it = m_mapIntArg.find(sKey);
    if (it != m_mapIntArg.end())
        return it->second;
    else
        return 0;
}

const string notify::Notify::GetString(string sKey) const
{
    map<string, string>::const_iterator it = m_mapStringArg.find(sKey);
    if (it != m_mapStringArg.end())
        return it->second;
    else
        return "";
}

const vector<notify::Notify> notify::Notify::GetVector(string sKey) const
{
    map<string, vector<notify::Notify>>::const_iterator it = m_mapVectorArg.find(sKey);
    if (it != m_mapVectorArg.end())
        return it->second;
    else
        return vector<notify::Notify>();
}

const bool notify::Notify::HasInt(string sKey) const
{
    return m_mapIntArg.find(sKey) == m_mapIntArg.end();
}

const bool notify::Notify::HasString(string sKey) const
{
    return m_mapStringArg.find(sKey) == m_mapStringArg.end();
}

const bool notify::Notify::HasVector(string sKey) const
{
    return m_mapVectorArg.find(sKey) == m_mapVectorArg.end();
}