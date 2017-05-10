
#include "UIBase.h"

#include "FrameWithOption.h"
#include "ArrowManager.h"
#include "App.h"


#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include "Pointer.h"

using namespace std;

#include "StrUtil.h"
#include "proto\dataconfig_frame.pb.h"

#include "TestUnit.h"

using dataconfig::FRAME;
using dataconfig::FRAMEArray;

int main()
{
    TestUnit test;
    test.Run();


//     App &app = App::GetInstance();
//     app.Init();
//     app.Start();

    system("pause");



    return 0;
}
