
#ifndef __PLAYERDATA_H__
#define __PLAYERDATA_H__

#include <string>







using std::string;

/**
 * @brief 玩家数据
 */
class PlayerData 
{
public:
    PlayerData();
    ~PlayerData();
public:
    /**
     * @brief 空对象
     */
    static const PlayerData &GetNoPlayerData();
public:

public:
    /**
     * @brief 初始化
     */
    virtual bool Init();
    
    /**
     * @brief 初始化
     */
    virtual bool Init(const PlayerData &oPlayerData);
    
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
     * @brief 获取生命值
     */
    inline const int GetHp() const{return m_iHp;}
    /**
     * @brief 获取生命值
     */
    inline const int GetHp() const{return m_iHp;}
    /**
     * @brief 获取生命值
     */
    inline const int GetHp() const{return m_iHp;}
    /**
     * @brief 获取生命值
     */
    inline const int GetHp() const{return m_iHp;}
    /**
     * @brief 获取生命值
     */
    inline const int GetHp() const{return m_iHp;}
    /**
     * @brief 获取生命值
     */
    inline const int GetHp() const{return m_iHp;}

    /**
     * @brief 设置生命值
     */
    inline void SetHp(const int iHp){m_iHp = iHp;}
    /**
     * @brief 设置生命值
     */
    inline void SetHp(const int iHp){m_iHp = iHp;}
    /**
     * @brief 设置生命值
     */
    inline void SetHp(const int iHp){m_iHp = iHp;}
    /**
     * @brief 设置生命值
     */
    inline void SetHp(const int iHp){m_iHp = iHp;}
    /**
     * @brief 设置生命值
     */
    inline void SetHp(const int iHp){m_iHp = iHp;}
    /**
     * @brief 设置生命值
     */
    inline void SetHp(const int iHp){m_iHp = iHp;}






private:  
    /*<! 生命值*/
    int m_iHp;
    /*<! 生命值*/
    int m_iHp;
    /*<! 生命值*/
    int m_iHp;
    /*<! 生命值*/
    int m_iHp;
    /*<! 生命值*/
    int m_iHp;
    /*<! 生命值*/
    int m_iHp;


};

#endif //__PLAYERDATA_H__
