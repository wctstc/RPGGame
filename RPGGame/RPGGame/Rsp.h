#ifndef __RSP_H__
#define __RSP_H__

#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;
using std::pair;

#define RSP_FIELD(field)\
const string field = #field

namespace rsp
{
    const string i_RetCode = "i_RetCode";

    const string s_Description        = "s_Description";
    const string v_Option             = "v_Option";
    const string s_Option_Description = "s_Option_Description";
    const string i_Option_FrameID     = "s_Option_FrameID";
    const string i_Option_Notify      = "i_Option_Notify";
    const string i_Option_Data      = "i_Option_Data";

    const string v_ShopItem          = "v_ShopItem";

    const string i_ShopItem_ItemID   = "i_ShopItem_ItemID";
    const string i_ShopItem_Price    = "i_ShopItem_Price";
    const string i_ShopItem_Amount   = "i_ShopItem_Amount";


    const string i_ItemID          = "i_ItemID";
    const string s_ItemDescription = "s_ItemDescription";



    /**
    * @brief 响应类
    */
    class Rsp
    {
    public:
        /**
        * @brief 响应码枚举
        */
        enum RetCode
        {
            RETCODE_SUCCEED = 0,
            RETCODE_NO_INDEX = 1000001,
            RETCODE_ERROR_INDEX = 1000002,
            RETCODE_NO_DATAID = 1000003,
            RETCODE_ERROR_DATAID = 1000004,

            RETCODE_NO_ITEM = 2000002,
        };

    public:
	    Rsp();
	    ~Rsp();
    public:
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
	    void Add(string sKey, vector<Rsp> vValue);

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
	    const vector<Rsp> GetVector(string sKey)const;

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
	    /*!< 整型参数映射 */
	    map<string, int> m_mapIntArg;
	    /*!< 字符串参数映射 */
	    map<string, string> m_mapStringArg;
	    /*!< 数组参数映射 */
	    map<string, vector<Rsp>> m_mapVectorArg;


    };

}
#endif // __RSP_H__
