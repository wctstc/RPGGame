#ifndef __FRAMELOADER_H__
#define __FRAMELOADER_H__

#include <map>

using std::map;
using std::pair;

#include "Singleton.h"
#include "Frame.h"


class FrameLoader : public Singleton<FrameLoader>
{
public:
	bool Init();
public:
	Frame *GetFrameByID(int iID);
private:
	map<int, Frame> m_frame_data;
};




#endif // __FRAMELOADER_H__
