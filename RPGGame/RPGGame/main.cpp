
#include "UIBase.h"

#include "Frame.h"
#include "Option.h"
#include "App.h"


#include <conio.h>
int main()
{
	Frame frame;
	OptionsArrow option;

	Position postion = {2,4};
	Size size = {20,4};
	string discription = "hello worldhello worldhello worldhello worldhello worldhello world";
	Direction direction = Direction::Vertical;
	int gap = 1;
	vector< string > options;
	options.push_back("C++");
	options.push_back("Java");
	options.push_back("PHP");


	frame.Init( postion,size,discription,direction,gap,options );

	//frame.Show();

	//option.Init( frame.GetOptionsPosition() );

	//printf( "option:%d", option.SelectOption() );

	App app;
	app.Init();
	app.Start();


	system("pause");
	return 0;
}
