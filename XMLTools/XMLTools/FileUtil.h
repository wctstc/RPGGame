#ifndef __FILEUTIL_H__
#define __FILEUTIL_H__

#include <string>

using std::string;

/**
 * @brief 文件工具类
 */
class FileUtil
{
private:
    FileUtil();
    ~FileUtil();

public:
    /**
     * @brief 二进制格式读取文件
     */
    static int LoadFileWithBinary(const string sFile, char *const csBuffer, const int iSize );

    /**
     * @brief 二进制格式保存文件
     */
    static int SaveFileWithBinary(const string sFile, const char *const csBuffer, const int iLength);

    /**
    * @brief 字符格式读取文件
    */
    static int LoadFileWithChar(const string sFile, char *const csBuffer, const int iSize);

    /**
    * @brief 字符格式保存文件
    */
    static int SaveFileWithChar(const string sFile, const char *const csBuffer, const int iLength);
};

#endif // __FILEUTIL_H__


