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
    bool TestPointer();
    bool TestFrame();
};


#endif // __TESTUNIT_H__
