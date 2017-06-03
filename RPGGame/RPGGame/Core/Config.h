#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
using std::string;


/**
* @brief 配置类
*/
class Config
{
public:
	Config();
	~Config();
public:
	/**
	* @brief 加载配置文件
	*/
	void Load(string file_name);

	/**
	* @brief 保存配置文件
	*/
	void Save(string file_name = "");
public:
	/**
	* @brief 获取配置信息
	*/
	string GetValue(string key);

	/**
	* @brief 设置配置信息
	*/
	void SetValue(string key, string value);
private:

};



#endif // __CONFIG_H__
