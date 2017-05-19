
#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <string>







using std::string;

/**
 * @brief 行动者
 */
class Actor 
{
public:
    Actor();
    ~Actor();
public:
    /**
     * @brief 空对象
     */
    static const Actor &GetNoActor();
public:

public:
    /**
     * @brief 初始化
     */
    virtual bool Init();
    
    /**
     * @brief 初始化
     */
    virtual bool Init(const Actor &oActor);
    
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
     * @brief 获取名字
     */
    inline const string GetName() const{return m_sName;}
    /**
     * @brief 获取上一次生命值
     */
    inline const int GetPreHp() const{return m_iPreHp;}
    /**
     * @brief 获取生命值
     */
    inline const int GetHp() const{return m_iHp;}
    /**
     * @brief 获取基础生命值上限
     */
    inline const int GetBaseMaxHp() const{return m_iBaseMaxHp;}
    /**
     * @brief 获取基础攻击力
     */
    inline const int GetBaseAttack() const{return m_iBaseAttack;}
    /**
     * @brief 获取基础防御力
     */
    inline const int GetBaseDefance() const{return m_iBaseDefance;}

    /**
     * @brief 设置编号
     */
    inline void SetID(const int iID){m_iID = iID;}
    /**
     * @brief 设置名字
     */
    inline void SetName(const string sName){m_sName = sName;}
    /**
     * @brief 设置上一次生命值
     */
    inline void SetPreHp(const int iPreHp){m_iPreHp = iPreHp;}
    /**
     * @brief 设置生命值
     */
    inline void SetHp(const int iHp){m_iHp = iHp;}
    /**
     * @brief 设置基础生命值上限
     */
    inline void SetBaseMaxHp(const int iBaseMaxHp){m_iBaseMaxHp = iBaseMaxHp;}
    /**
     * @brief 设置基础攻击力
     */
    inline void SetBaseAttack(const int iBaseAttack){m_iBaseAttack = iBaseAttack;}
    /**
     * @brief 设置基础防御力
     */
    inline void SetBaseDefance(const int iBaseDefance){m_iBaseDefance = iBaseDefance;}





private:  
    /*<! 编号*/
    int m_iID;
    /*<! 名字*/
    string m_sName;
    /*<! 上一次生命值*/
    int m_iPreHp;
    /*<! 生命值*/
    int m_iHp;
    /*<! 基础生命值上限*/
    int m_iBaseMaxHp;
    /*<! 基础攻击力*/
    int m_iBaseAttack;
    /*<! 基础防御力*/
    int m_iBaseDefance;


};

#endif //__ACTOR_H__
