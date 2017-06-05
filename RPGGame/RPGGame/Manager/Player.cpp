#include "Player.h"
 
 Player::Player()
 {
 }
 
 
 Player::~Player()
 {
 }
 
 bool Player::Init(const Player &oPlayer)
 {
     if (!Actor::Init(oPlayer))
         return false;
 
     m_stPlayerData = oPlayer.m_stPlayerData;
 
     return true;
 }
 bool Player::Init(
     const int iID,
     const string sName,
     const int iHp,
     const int iMaxHp,
     const int iAttack,
     const int iDefance,
     const int iMoney,
     const int iLevel,
     const int iExp,
     const int iTotalExp)
 {
     if (!Actor::Init(iID, sName, iHp, iMaxHp, iAttack, iDefance))
         return false;
 
 
     m_stPlayerData.iMoney    = iMoney;
     m_stPlayerData.iLevel    = iLevel;
     m_stPlayerData.iExp      = iExp;
     m_stPlayerData.iTotalExp = iTotalExp;
 
 
//      for (int i = 0; i < Equipment::EQUIPMENT_TYPE_MAX; ++i)
//          m_ayEquipments[i].bIsEquip = false;
 
     return true;
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
 
 void Player::Reset()
 {
     Actor::SetHp(GetMaxHp() + GetExtendMaxHp());
 }
 
//  Player::EquipmentOperator Player::Equip(
//      const EquipmentOperator eEquipmentOperator,
//      const Equipment &oNewEquipment,
//      Equipment &oOldEuipment)
//  {
//      EquipmentOperator eRet;
//      EquipmentState *oTempEquipment = NULL;
//      if (oNewEquipment.GetType() >= 0
//          && oNewEquipment.GetType() < Equipment::EQUIPMENT_TYPE_MAX)
//      {
//          oTempEquipment = &m_ayEquipments[oNewEquipment.GetType()];
//          switch (eEquipmentOperator)
//          {
//          case EQUIPMENT_OPERATOR_PUTON:
//          case EQUIPMENT_OPERATOR_CHANGE:
//              eRet = EQUIPMENT_OPERATOR_PUTON;
//              if (oTempEquipment->bIsEquip)
//              {
//                  eRet = EQUIPMENT_OPERATOR_CHANGE;
//                  oOldEuipment = oTempEquipment->oEquipment;
//              }
//  
//              oTempEquipment->bIsEquip = true;
//              oTempEquipment->oEquipment = oNewEquipment;
//              break;
//          case EQUIPMENT_OPERATOR_GETOFF:
//              oTempEquipment->bIsEquip = false;
//              oOldEuipment = oTempEquipment->oEquipment;
//              eRet = EQUIPMENT_OPERATOR_GETOFF;
//              break;
//          }
//          oTempEquipment = NULL;
//      }
//  
//      return eEquipmentOperator;
//  }
 
 void Player::Defance( const int iDamage)
 {
     int iRealDamage = iDamage - GetDefance();
     if (iRealDamage <= 0)
         iRealDamage = 1;
 
     Actor::SetPreHp(Actor::GetHp());
     Actor::SetHp(Actor::GetHp()-iRealDamage);
 }
 
 int Player::Attack()
 {
     return GetAttack()+GetExtendAttack();
 }
 
 bool Player::AddMoney(const int iMoney)
 {
     m_stPlayerData.iMoney += iMoney;
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
     if (m_stPlayerData.iMoney < iMoney)
         return false;
 
     m_stPlayerData.iMoney -= iMoney;
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
