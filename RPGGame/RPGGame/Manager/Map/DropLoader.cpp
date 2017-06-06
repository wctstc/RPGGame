#include "DropLoader.h"

#include "dataconfig_dropconfig.pb.h"

using dataconfig::DropConfigArray;
using dataconfig::DropConfig;

DropLoader::DropLoader()
{
}


DropLoader::~DropLoader()
{
}

bool DropLoader::Load()
{
    DropConfigArray arrayDrop;
    if (!GetConfigArray(arrayDrop))
        return false;

    for (int i = 0; i < arrayDrop.items_size(); ++i)
    {
        const DropConfig oConfig = arrayDrop.items(i);

        Drop oDrop;
        if (!oDrop.Init(oConfig.id(), oConfig.itemid(), oConfig.itemnum()))
            return false;

        m_mapDrop.insert(make_pair(oDrop.GetID(), oDrop));
    }

    return true;
}

const Drop & DropLoader::GetDropByID(const int iID) const
{
    map<int, Drop>::const_iterator it = m_mapDrop.find(iID);

    if (it != m_mapDrop.end())
        return it->second;

    return Drop::GetNoDrop();
}

int DropLoader::GetDropNum() const
{
    return m_mapDrop.size();
}
