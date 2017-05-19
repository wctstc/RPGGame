#include "FileUtil.h"



FileUtil::FileUtil()
{
}


FileUtil::~FileUtil()
{
}

int FileUtil::LoadFileWithBinary(const string sFile, char *const csBuffer, const int iSize)
{
    if (sFile.empty() || csBuffer == NULL || iSize <= 0)
        return -1;

    FILE *pFile = NULL;
    fopen_s(&pFile, sFile.c_str(), "rb");
    if (pFile == NULL)
        return -1;


    int iLength = fread(csBuffer, 1, iSize, pFile);
    if (iLength > iSize || iLength <=0)
    {
        fclose(pFile);
        return -1;
    }

    fclose(pFile);
    return iLength;
}

int FileUtil::SaveFileWithBinary(const string sFile, const char *const csBuffer, const int iLength)
{
    if (sFile.empty() || csBuffer == NULL || iLength <= 0)
        return -1;

    FILE *pFile = NULL;
    fopen_s(&pFile, sFile.c_str(), "wb");
    if (pFile == NULL)
        return -1;

    int iWriteLength = fwrite(csBuffer, 1, iLength, pFile);

    
    if (iWriteLength <=0 )
    {
        fclose(pFile);
        return -1;
    }

    fclose(pFile);
    return iWriteLength;
}

int FileUtil::LoadFileWithChar(const string sFile, char *const csBuffer, const int iSize)
{
    if (sFile.empty() || csBuffer == NULL || iSize <= 0)
        return -1;

    FILE *pFile = NULL;
    fopen_s(&pFile, sFile.c_str(), "r");
    if (pFile == NULL)
        return -1;


    int iLength = fread(csBuffer, 1, iSize, pFile);
    if (iLength > iSize || iLength <= 0)
    {
        fclose(pFile);
        return -1;
    }

    fclose(pFile);
    return iLength;
}

int FileUtil::SaveFileWithChar(const string sFile, const char *const csBuffer, const int iLength)
{
    if (sFile.empty() || csBuffer == NULL || iLength <= 0)
        return -1;

    FILE *pFile = NULL;
    fopen_s(&pFile, sFile.c_str(), "w");
    if (pFile == NULL)
        return -1;

    int iWriteLength = fwrite(csBuffer, 1, iLength, pFile);


    if (iWriteLength <= 0)
    {
        fclose(pFile);
        return -1;
    }

    fclose(pFile);
    return iWriteLength;
}
