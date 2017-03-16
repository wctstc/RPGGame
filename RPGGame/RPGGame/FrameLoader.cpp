#include "FrameLoader.h"



bool FrameLoader::Init()
{

	Frame frame;

	Position postion = { 2,4 };
	Size size = { 20,4 };
	string discription = "hello worldhello worldhello worldhello worldhello worldhello world";
	Direction direction = Direction::Vertical;
	int gap = 1;
	vector< string > options;
	options.push_back("C++");
	options.push_back("Java");
	options.push_back("PHP");


	frame.Init(postion, size, discription, direction, gap, options);

	m_frame_data.insert(pair<int, Frame>(0, frame));

	return true;
}

Frame *FrameLoader::GetFrameByID(int iID)
{
	map<int, Frame>::iterator it = m_frame_data.find(iID);
	if (it == m_frame_data.end())
		return nullptr;
	return &(it->second);
}
