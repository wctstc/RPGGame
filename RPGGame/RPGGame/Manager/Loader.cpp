#include "Loader.h"
#include "FileUtil.h"


Loader::Loader()
{
}


Loader::~Loader()
{
}

bool Loader::Init(const string sFile)
{
    m_sFile = sFile;

    return Load();
}

bool Loader::GetConfigArray(google::protobuf::Message &oProtobuf)
{
    if (m_sFile.empty())
        return false;

    char csBuffer[10240];
    int iLength = sizeof(csBuffer);
    iLength = FileUtil::LoadFileWithBinary(m_sFile, csBuffer, iLength);

    if (iLength <= 0)
        return false;

    if (!oProtobuf.ParseFromArray(csBuffer, iLength))
        return false;

    return true;
}
