#include "Platform.h"



const std::string platform::UTF_82ASCII(const std::string& sUtf8Code)
{
	wchar_t sWideChar[MAX_STRING_LENGTH];
	char sAsciiChar[MAX_STRING_LENGTH];

	//先把 utf8 转为 unicode  
	::MultiByteToWideChar(CP_UTF8, 0, sUtf8Code.c_str(), -1, sWideChar, MAX_STRING_LENGTH);

	//最后把 unicode 转为 ascii  
	::WideCharToMultiByte(CP_OEMCP, 0, sWideChar, -1, sAsciiChar, MAX_STRING_LENGTH, NULL, NULL);

	return string(sAsciiChar);
}
