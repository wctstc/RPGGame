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

	const FRAME *pFrame;
	Frame oFrame;
	FrameData oFrameData;
	Option oOptionData;
	vector<Option> vOptions;
	for (int i = 0; i < ayFrames.items_size(); ++i)
	{
		vOptions.clear();
		pFrame = &(ayFrames.items(i));
		oFrameData.iID = pFrame->id();
		oFrameData.eDirection = static_cast<Direction>(pFrame->direction());
		oFrameData.oPosition.iX = pFrame->x();
		oFrameData.oPosition.iY = pFrame->y();
		oFrameData.oSize.iWidth = pFrame->width();
		oFrameData.oSize.iHeigth = pFrame->height();
		oFrameData.sDescription = pFrame->description().c_str();
		if (pFrame->has_handle_id())
			oFrameData.iHandlerID = pFrame->handle_id();
		else
			oFrameData.iHandlerID = 0;
		for (int j = 0; j < pFrame->option().size(); ++j )
		{
			oOptionData.sDescription = pFrame->option(j).description();
			oOptionData.iFrameID = pFrame->option(j).frame_id();
			vOptions.push_back(oOptionData);
		}
		oFrameData.vOptions = vOptions;
		oFrame.Init(oFrameData);
		m_frame_data.insert(pair<int, Frame>(oFrame.GetID(), oFrame));
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
	map<int, Frame>::iterator it = m_frame_data.find(iID);
	if (it == m_frame_data.end())
		return nullptr;
	return &(it->second);
}
