#include "FrameLoader.h"


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
	Frame *pFrame;
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
// 
// 	Frame frame;
// 
// 	Position postion = { 2,4 };
// 	Size size = { 20,4 };
// 	string discription = "hello worldhello worldhello worldhello worldhello worldhello world";
// 	Direction direction = Direction::DIRECTION_VERTICAL;
// 	int gap = 1;
// 	vector< OptionData > options;
// 	OptionData oOptionData;
// 	FrameData oFrameData;
// 	//frame 0
// 	string description[] = { "show bag","show author","show hello" };
// 	int frame_id[] = { 1,2,3 };
// 	for (int i = 0; i < 3; ++i)
// 	{
// 	//	oOptionData.index = i;
// 		oOptionData.sDescription = description[i];
// 		oOptionData.ulFrameID = frame_id[i];
// 		options.push_back(oOptionData);
// 	}
// 	oFrameData.iID = 0;
// 	oFrameData.eDirection = direction;
// 	oFrameData.oPosition = postion;
// 	oFrameData.oSize = size;
// 	oFrameData.sDiscription = discription;
// 	oFrameData.vOptions = options;
// 	frame.Init(oFrameData);
// 	m_frame_data.insert(pair<int, Frame>(0, frame));
// 
// 	//frame 1show bag
// 	options.clear();
// 	postion = { 2,4 };
// 	size = { 20,4 };
// 	discription = "1:food  2:weapon";
// 	direction = Direction::DIRECTION_VERTICAL;
// 	string description1[] = { "OK" };
// 	int frame_id1[] = { -1 };
// 	for (int i = 0; i < 1; ++i)
// 	{
// 	//	oOptionData.index = i;
// 		oOptionData.sDescription = description1[i];
// 		oOptionData.ulFrameID = frame_id1[i];
// 		options.push_back(oOptionData);
// 	}
// 	oFrameData.iID = 1;
// 	oFrameData.eDirection = direction;
// 	oFrameData.oPosition = postion;
// 	oFrameData.oSize = size;
// 	oFrameData.sDiscription = discription;
// 	oFrameData.vOptions = options;
// 	frame.Init(oFrameData);
// 	m_frame_data.insert(pair<int, Frame>(1, frame));
// 
// 	//frame 2show author
// 	options.clear();
// 	postion = { 2,4 };
// 	size = { 20,4 };
// 	discription = "lost wang";
// 	direction = Direction::DIRECTION_VERTICAL;
// 	string description2[] = { "OK" };
// 	int frame_id2[] = { -1 };
// 	for (int i = 0; i < sizeof(frame_id2)/sizeof(frame_id2[0]); ++i)
// 	{
// 	//	oOptionData.index = i;
// 		oOptionData.sDescription = description2[i];
// 		oOptionData.ulFrameID = frame_id2[i];
// 		options.push_back(oOptionData);
// 	}
// 	oFrameData.iID = 2;
// 	oFrameData.eDirection = direction;
// 	oFrameData.oPosition = postion;
// 	oFrameData.oSize = size;
// 	oFrameData.sDiscription = discription;
// 	oFrameData.vOptions = options;
// 	frame.Init(oFrameData);
// 	m_frame_data.insert(pair<int, Frame>(2, frame));
// 
// 
// 	//frame 3show show hello
// 	options.clear();
// 	postion = { 2,4 };
// 	size = { 20,4 };
// 	discription = "hello world,welcome to now country!";
// 	direction = Direction::DIRECTION_HORIZONTAL;
// 	gap = 8;
// 	string description3[] = { "OK", "Cancel" };
// 	int frame_id3[] = { 2, -1 };
// 	for (int i = 0; i < sizeof(frame_id3) / sizeof(frame_id3[0]); ++i)
// 	{
// 	//	oOptionData.index = i;
// 		oOptionData.sDescription = description3[i];
// 		oOptionData.ulFrameID = frame_id3[i];
// 		options.push_back(oOptionData);
// 	}
// 	oFrameData.iID = 3;
// 	oFrameData.eDirection = direction;
// 	oFrameData.oPosition = postion;
// 	oFrameData.oSize = size;
// 	oFrameData.sDiscription = discription;
// 	oFrameData.vOptions = options;
// 	frame.Init(oFrameData);
// 	m_frame_data.insert(pair<int, Frame>(3, frame));

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
	case 4:
		break;
	default:
		pFrame = new Frame();
	}
	return pFrame;
}
