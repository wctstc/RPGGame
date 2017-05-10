#ifndef __TESTUNIT_H__
#define __TESTUNIT_H__

#define TEST( func )\
{\
    if(!func())\
    {\
        cout << #func << " Test Fail!" << endl;\
    }\
}

class TestUnit
{
public:
    TestUnit();
    ~TestUnit();
public:
    void Run();
private:
    bool TestStrUtilSplit();
    bool TestStrUtilFormat();
    bool TestPointer();
    bool TestFrame();
    bool TestPropertyFrame();
    bool TestProtobuf();
    bool TestLog();
    bool TestMapConfig();
    bool TestMacro();
};


#endif // __TESTUNIT_H__
