
#include "UIBase.h"

#include "Frame.h"
#include "Option.h"
#include "App.h"


#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>


using namespace std;

void *thread(void *arg)
{
	cout << (char*)arg << endl;
	return NULL;
}

#include "proto\dataconfig_frame.pb.h"

using dataconfig::FRAME;
using dataconfig::FRAMEArray;

int main()
{
	FRAMEArray aFrames;
//	FILE *file;
	
// 	file = fopen( "proto/data/dataconfig_frame.data", "rb" );
// 	if (file == NULL )
// 		return 0;
// 	char buffer[1024];
// 	int length = fread( buffer, 1, 1024, file );
// 	printf("length:%d", length);
// 
// 	aFrames.ParseFromArray(buffer,length);

	int file;
	file = open("proto/data/dataconfig_frame.data", O_RDONLY|O_BINARY);
	if (file <= 0)
		return 0;
	char buffer[1024];
	//int length = read(file, buffer, 1024);
	//printf("length:%d", length);

	aFrames.ParseFromFileDescriptor(file);
	

	//for (int i = 0; i < aFrames.items().size(); ++i)
	//{
	//	FRAME sFrame = aFrames.items().Get(i);
	//	printf("%d: \n id:%d", i, sFrame.id());
	//	if (sFrame.has_is_exist())
	//		printf("is_exist:%d", sFrame.is_exist());
	//	if (sFrame.has_description())
	//		printf("description:%s", sFrame.description().c_str());
	//	printf("\n");
	//}

	//system("pause");
	//return 0;


	Frame oFrame;
	OptionsArrow option;

	Position postion = {2,4};
	Size size = {20,4};
	string discription = "hello worldhello worldhello worldhello worldhello worldhello world";
	Direction direction = Direction::DIRECTION_VERTICAL;
	int gap = 1;
	vector< OptionData > options;
	OptionData oOptionData;
	string description[] = { "show bag","show author","show hello" };
	int frame_id[] = { 1,2,3 };
	for (int i = 0; i < 3; ++i)
	{
		//oOptionData.index = i;
		oOptionData.sDescription = description[i];
		oOptionData.iFrameID = frame_id[i];
	}



	//oFrame.Init( 0, postion,size,discription,direction,gap,options );

	//frame.Show();

	//option.Init( frame.GetOptionsPosition() );

	//printf( "option:%d", option.SelectOption() );

	App app;
	app.Init();
	app.Start();

	system("pause");
	return 0;
}
