
#include <sstream>
#include <iomanip>
#include <time.h>
#include <stdio.h>

#include "Log.h"


Log::Log()
    : m_sFile("Globle.log")
    , m_eType(LOG_DEBUG)
{
}

Log::Log(const string sFile, const LogType eType)
    : m_sFile(sFile)
    , m_eType(eType)
{

}

Log::~Log(void)
{
}

bool Log::Init(const string sFile, const LogType eType)
{
    m_sFile = sFile;
    m_eType = eType;

    return true;
}

void Log::Write(const LogType eType, const char *sType, const int iLine, const char *pFunction, const char *pFormat, ...)
{

    if (eType <= m_eType)
    {
        char pLogInfo[4192];
        char pTime[32];
        char pBuffer[4192];


        va_list vaList;
        va_start(vaList, pFormat);
        vsnprintf_s(pLogInfo, sizeof(pLogInfo), sizeof(pLogInfo), pFormat, vaList);
        va_end(vaList);

        GetNowTime(pTime);

        int iLength = sprintf(
            pBuffer,
            "%s %s(%d) %s:%s\n",
            pTime,
            pFunction,
            iLine,
            sType,
            pLogInfo);


        FILE *pFile = fopen(m_sFile.c_str(),"a");
        if (pFile == NULL)
            return;

        fwrite(pBuffer, 1, iLength, pFile);

        fflush(pFile);
        fclose(pFile);
    }
}

void Log::GetNowTime(char *const csTime)
{
	time_t tmTime;
	time(&tmTime);
	struct tm stTime;
	localtime_s(&stTime,&tmTime);

	int nMonth = stTime.tm_mon + 1;
	int nDay = stTime.tm_mday;
	int nYear = stTime.tm_year + 1900;

	int nMinute = stTime.tm_min;
	int nSecond = stTime.tm_sec;
	int nHour = stTime.tm_hour;

    sprintf(csTime, "%04d-%02d-%02d %02d:%02d:%02d",
        stTime.tm_year + 1900,
        stTime.tm_mon + 1,
        stTime.tm_mday,
        stTime.tm_hour,
        stTime.tm_min,
        stTime.tm_sec);
}
