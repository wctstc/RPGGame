#include "FrameLoader.h"

#include "BagFrame.h"


enum FrameType
{
	FRAME_TYPE_NORMAL = 0,
	FRAME_TYPE_BAG = 4,
};

bool FrameLoader::Init()
{
	FRAMEArray ayFrames;
	FILE *file;
	file = fopen("proto/data/dataconfig_frame.data", "rb");
	if (file == NULL)
		return 0;
	char buffer[1024];
	int length = fread(buffer, 1, 1024, file);
	printf("length:%d", length);

	ayFrames.ParseFromArray(buffer, length);

	const FRAME *pFrameConfig;
	FrameData oFrameData;
	Option oOptionData;
	vector<Option> vOptions;
	for (int i = 0; i < ayFrames.items_size(); ++i)
	{
		vOptions.clear();
		pFrameConfig = &(ayFrames.items(i));
		oFrameData.iID = pFrameConfig->id();
		oFrameData.eDirection = static_cast<Direction>(pFrameConfig->direction());
		oFrameData.oPosition.iX = pFrameConfig->x();
		oFrameData.oPosition.iY = pFrameConfig->y();
		oFrameData.oSize.iWidth = pFrameConfig->width();
		oFrameData.oSize.iHeigth = pFrameConfig->height();
		oFrameData.sDescription = pFrameConfig->description().c_str();
		if (pFrameConfig->has_handle_id())
			oFrameData.iHandlerID = pFrameConfig->handle_id();
		else
			oFrameData.iHandlerID = NO_HANDLER;
		for (int j = 0; j < pFrameConfig->option().size(); ++j )
		{
			oOptionData.sDescription = pFrameConfig->option(j).description();
			oOptionData.iFrameID = pFrameConfig->option(j).frame_id();
			vOptions.push_back(oOptionData);
		}
		oFrameData.vOptions = vOptions;
		m_mapFrameDatas.insert(pair<int, FrameData>(oFrameData.iID, oFrameData));
	}

	return true;
}

Frame *FrameLoader::GetFrameByID(int iID)
{
	Frame *pFrame = NULL;
	map<int, FrameData>::iterator it = m_mapFrameDatas.find(iID);
	if (it != m_mapFrameDatas.end())
	{
		pFrame = CreateFrameInstanceByID(iID);
		pFrame->Init(it->second);
	}
	return pFrame;
}

void FrameLoader::ReleaseFrame(Frame *pFrame)
{
	if (pFrame != NULL)
		delete pFrame;
}

Frame * FrameLoader::CreateFrameInstanceByID(const int iID)
{
	Frame *pFrame = NULL;
	switch (iID)
	{
	case 1:
		pFrame = new BagFrame();
		break;
	default:
		pFrame = new Frame();
	}
	return pFrame;
}
