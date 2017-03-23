#include "FrameLoader.h"



bool FrameLoader::Init()
{

	Frame frame;

	Position postion = { 2,4 };
	Size size = { 20,4 };
	string discription = "hello worldhello worldhello worldhello worldhello worldhello world";
	Direction direction = Direction::DIRECTION_VERTICAL;
	int gap = 1;
	vector< OptionData > options;
	OptionData oOptionData;
	//frame 0
	string description[] = { "show bag","show author","show hello" };
	int frame_id[] = { 1,2,3 };
	for (int i = 0; i < 3; ++i)
	{
		oOptionData.index = i;
		oOptionData.description = description[i];
		oOptionData.frame_id = frame_id[i];
		options.push_back(oOptionData);
	}
	frame.Init( 0,postion, size, discription, direction, gap, options);
	m_frame_data.insert(pair<int, Frame>(0, frame));

	//frame 1show bag
	options.clear();
	postion = { 2,4 };
	size = { 20,4 };
	discription = "1:food  2:weapon";
	direction = Direction::DIRECTION_VERTICAL;
	string description1[] = { "OK" };
	int frame_id1[] = { -1 };
	for (int i = 0; i < 1; ++i)
	{
		oOptionData.index = i;
		oOptionData.description = description1[i];
		oOptionData.frame_id = frame_id1[i];
		options.push_back(oOptionData);
	}
	frame.Init(1,postion, size, discription, direction, gap, options);
	m_frame_data.insert(pair<int, Frame>(1, frame));

	//frame 2show author
	options.clear();
	postion = { 2,4 };
	size = { 20,4 };
	discription = "lost wang";
	direction = Direction::DIRECTION_VERTICAL;
	string description2[] = { "OK" };
	int frame_id2[] = { -1 };
	for (int i = 0; i < sizeof(frame_id2)/sizeof(frame_id2[0]); ++i)
	{
		oOptionData.index = i;
		oOptionData.description = description2[i];
		oOptionData.frame_id = frame_id2[i];
		options.push_back(oOptionData);
	}
	frame.Init(2,postion, size, discription, direction, gap, options);
	m_frame_data.insert(pair<int, Frame>(2, frame));


	//frame 3show show hello
	options.clear();
	postion = { 2,4 };
	size = { 20,4 };
	discription = "hello world,welcome to now country!";
	direction = Direction::DIRECTION_HORIZONTAL;
	gap = 8;
	string description3[] = { "OK", "Cancel" };
	int frame_id3[] = { 2, -1 };
	for (int i = 0; i < sizeof(frame_id3) / sizeof(frame_id3[0]); ++i)
	{
		oOptionData.index = i;
		oOptionData.description = description3[i];
		oOptionData.frame_id = frame_id3[i];
		options.push_back(oOptionData);
	}
	frame.Init(3,postion, size, discription, direction, gap, options);
	m_frame_data.insert(pair<int, Frame>(3, frame));

	return true;
}

Frame *FrameLoader::GetFrameByID(int iID)
{
	map<int, Frame>::iterator it = m_frame_data.find(iID);
	if (it == m_frame_data.end())
		return nullptr;
	return &(it->second);
}
