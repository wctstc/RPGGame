
#ifndef __ACTORDATA_H__
#define __ACTORDATA_H__

#include <string>







using std::string;

/**
 * @brief 行动者数据
 */
class ActorData 
{
public:
    ActorData();
    ~ActorData();
public:
    /**
     * @brief 空对象
     */
    static const ActorData &GetNoActorData();
public:

public:
    /**
     * @brief 初始化
     */
    virtual bool Init();
    
    /**
     * @brief 初始化
     */
    virtual bool Init(const ActorData &oActorData);
    
    /**
     * @brief 字符串化
     */
    virtual string ToString()const;
    
    /**
     * @brief 反字符串化
     */
    virtual bool FromString(const string sBuffer);

public:    
    /**
     * @brief 获取编号
     */
    inline const int GetID() const{return m_iID;}
    /**
     * @brief 获取生命值
     */
    inline const int GetHp() const{return m_iHp;}

    /**
     * @brief 设置编号
     */
    inline void SetID(const int iID){m_iID = iID;}
    /**
     * @brief 设置生命值
     */
    inline void SetHp(const int iHp){m_iHp = iHp;}






private:  
    /*<! 编号*/
    int m_iID;
    /*<! 生命值*/
    int m_iHp;


};

#endif //__ACTORDATA_H__
