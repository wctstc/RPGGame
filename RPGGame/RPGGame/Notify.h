#ifndef __NOTIFY_H__
#define __NOTIFY_H__

#include <map>
#include <string>
#include <vector>

#include "Cmd.h"

using std::map;
using std::vector;
using std::string;
using std::pair;

/**
* @brief 通知命名空间
*/
namespace notify
{

    const string i_Index = "i_Index";



    const string i_PropertyFrame_Hp = "i_PropertyFrame_Hp";
    const string i_PropertyFrame_MaxHp = "i_PropertyFrame_MaxHp";
    const string i_PropertyFrame_Money = "i_PropertyFrame_Money";
    const string i_PropertyFrame_Level = "i_PropertyFrame_Level";
    const string i_PropertyFrame_Exp = "i_PropertyFrame_Exp";
    const string i_PropertyFrame_TotalExp = "i_PropertyFrame_TotalExp";
    const string i_PropertyFrame_Bag = "i_PropertyFrame_Bag";
    const string i_PropertyFrame_TotalBag = "i_PropertyFrame_TotalBag";

    const string s_TipsFrame_Description = "s_TipsFrame_Description";


    /**
     * @brief 通知类
     */
    class Notify
    {
    public:
        Notify();
        ~Notify();
    public:
        /**
        * @brief 初始化
        */
        virtual bool Init(cmd::Command eCmd);

        /**
        * @brief 获取指令
        */
        cmd::Command GetCmd();

        /**
        * @brief 添加整型参数
        */
        void Add(string sKey, int iValue);

        /**
        * @brief 添加字符串参数
        */
        void Add(string sKey, string sValue);

        /**
        * @brief 添加数组参数
        */
        void Add(string sKey, vector<Notify> vValue);

        /**
        * @brief 获取指定整型参数
        */
        const int GetInt(string sKey)const;

        /**
        * @brief 获取指定字符串参数
        */
        const string GetString(string sKey)const;

        /**
        * @brief 获取指定数组参数
        */
        const vector<Notify> GetVector(string sKey)const;

        /**
        * @brief 是否有指定整型参数
        */
        const bool HasInt(string sKey)const;

        /**
        * @brief 是否有指定字符串参数
        */
        const bool HasString(string sKey)const;

        /**
        * @brief 是否有指定数组参数
        */
        const bool HasVector(string sKey)const;
    private:
        /*!< 指令 */
        cmd::Command m_eCmd;
        /*!< 整型参数映射 */
        map<string, int> m_mapIntArg;
        /*!< 字符串参数映射 */
        map<string, string> m_mapStringArg;
        /*!< 数组参数映射 */
        map<string, vector<Notify>> m_mapVectorArg;

    };
};

#endif // __NOTIFY_H__
