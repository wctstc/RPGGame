#ifndef __FRAMELOADER_H__
#define __FRAMELOADER_H__

#include <map>

using std::map;
using std::pair;

#include "dataconfig_frame.pb.h"

#include "Singleton.h"
#include "Frame.h"

#define FRAMEFIEL "proto/data/dataconfig_frame.data"

using dataconfig::FRAME;
using dataconfig::FRAMEArray;

using data::Direction;

class FrameLoader : public Singleton<FrameLoader>
{
public:
	bool Init();
public:
	Frame *GetFrameByID(int iID);
	void ReleaseFrame(Frame *pFrame);
private:
	Frame *CreateFrameInstanceByID(const int iID);
private:
	map<int, FrameData> m_mapFrameDatas;
};




#endif // __FRAMELOADER_H__
