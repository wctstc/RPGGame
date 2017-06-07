#include "Player.h"
 
 Player::Player()
 {
 }
 
 
 Player::~Player()
 {
 }
 
 bool Player::Init()
 {
     return m_stPlayerData.Init();
 }

 bool Player::Save(int &iLength, char *csBuffer) const
 {
     int iSize = sizeof(m_stPlayerData);
     if (iLength < iSize)
         return false;
 
     memcpy(csBuffer, &m_stPlayerData, iSize );
 
     iLength = iSize;
     return true;
 }
 
 bool Player::Load(int &iLength, const char *const csBuffer)
 {
     int iSize = sizeof(m_stPlayerData);
     if (iLength < iSize)
         return false;
 
     iLength = iSize;
     return true;
 }
 
 
 bool Player::IsDie()const
 {
     return GetPlayerData().GetHp() <= 0;
 }

void Player::Defance( const int iDamage)
{
    int iRealDamage = iDamage - m_stPlayerData.GetBaseDefance();
    if (iRealDamage <= 0)
        iRealDamage = 1;
}
 
int Player::Attack()
{
    return m_stPlayerData.GetBaseAttack();
}
 
 bool Player::AddMoney(const int iMoney)
 {
     m_stPlayerData.SetMoney(m_stPlayerData.GetMoney() + iMoney);
     return true;
 }
 
 // void Player::AddItemToBagFocus(const int iItemID, const int iNumber)
 // {
 //     m_stPlayerData.oBag.AddForce(iItemID, iNumber);
 // }
 // 
 // bool Player::CanAddItemToBag(const int iItemID, const int iNumber)
 // {
 //     return m_stPlayerData.oBag.CanAdd(iItemID, iNumber);
 // }
 
 bool Player::ReduceMoney(const int iMoney)
 {
     if (m_stPlayerData.GetMoney() < iMoney)
         return false;
 
     m_stPlayerData.SetMoney(m_stPlayerData.GetMoney() - iMoney);
     return true;
 }
 
 
 int Player::GetExtendMaxHp()const
 {
     int iExtendMaxHp = 0;
//      for (int i = 0; i < Equipment::EQUIPMENT_TYPE_MAX; ++i)
//          if (m_ayEquipments[i].bIsEquip)
//              iExtendMaxHp += m_ayEquipments[i].oEquipment.GetMaxHp();
     return iExtendMaxHp;
 }
 
 int Player::GetExtendAttack()const
 {
     int iExtendAttack = 0;
//      for (int i = 0; i < Equipment::EQUIPMENT_TYPE_MAX; ++i)
//          if (m_ayEquipments[i].bIsEquip)
//              iExtendAttack += m_ayEquipments[i].oEquipment.GetAttack();
     return iExtendAttack;
 }
 
 int Player::GetExtendDefance()const
 {
     int iExtendDefance = 0;
//      for (int i = 0; i < Equipment::EQUIPMENT_TYPE_MAX; ++i)
//          if (m_ayEquipments[i].bIsEquip)
//              iExtendDefance += m_ayEquipments[i].oEquipment.GetDefance();
     return iExtendDefance;
 }
 
 // const Bag& Player::GetBag() const
 // {
 //     return m_stBag;
 // }
