#ifndef __DROPLOADER_H__
#define __DROPLOADER_H__

#include "Loader.h"
#include "Drop.h"

class DropLoader:public Loader,public Singleton<DropLoader>
{
public:
    DropLoader();
    ~DropLoader();
public:
    virtual bool Load()override;
public:

private:
    map<int, Drop> m_mapDrop;
};



#endif // __DROPLOADER_H__
