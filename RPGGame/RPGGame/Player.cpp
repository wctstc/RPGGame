#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

bool Player::Init(int iID, int iHp, int iMaxHp, int iAttack, int iDefance)
{
    m_stPlayerData.stActorData.iID      = iID;
    m_stPlayerData.stActorData.iHp      = iHp;
    m_stPlayerData.stActorData.iMaxHp   = iMaxHp;
    m_stPlayerData.stActorData.iAttack  = iAttack;
    m_stPlayerData.stActorData.iDefance = iDefance;

    m_oBag.Init(1, 20);

    for (int i = 0; i < EquipmentType::EQUIPMENT_TYPE_MAX; ++i)
        m_ayEquipments[i].bIsEquip = false;

    return true;
}

void Player::Reset()
{
    m_stPlayerData.stActorData.iHp = GetMaxHp();
}

Player::EquipmentOperator Player::Equip(
    const EquipmentOperator eEquipmentOperator,
    const Equipment &oNewEquipment,
    Equipment &oOldEuipment)
{
    EquipmentOperator eRet;
    EquipmentState *oTempEquipment = NULL;
    if (oNewEquipment.GetType() >= 0
        && oNewEquipment.GetType() < data::EQUIPMENT_TYPE_MAX)
    {
        oTempEquipment = &m_ayEquipments[oNewEquipment.GetType()];
        switch (eEquipmentOperator)
        {
        case EQUIPMENT_OPERATOR_PUTON:
        case EQUIPMENT_OPERATOR_CHANGE:
            eRet = EQUIPMENT_OPERATOR_PUTON;
            if (oTempEquipment->bIsEquip)
            {
                eRet = EQUIPMENT_OPERATOR_CHANGE;
                oOldEuipment = oTempEquipment->oEquipment;
            }

            oTempEquipment->bIsEquip = true;
            oTempEquipment->oEquipment = oNewEquipment;
            break;
        case EQUIPMENT_OPERATOR_GETOFF:
            oTempEquipment->bIsEquip = false;
            oOldEuipment = oTempEquipment->oEquipment;
            eRet = EQUIPMENT_OPERATOR_GETOFF;
            break;
        }
        oTempEquipment = NULL;
    }

    return eEquipmentOperator;
}

void Player::Defance(int iDamage)
{
    int iRealDamage = iDamage - GetDefance();
    if (iRealDamage <= 0)
        iRealDamage = 1;
    m_stPlayerData.stActorData.iHp -= iRealDamage;
}

int Player::Attack()
{
    return GetAttack();
}

bool Player::IsDie()
{
    return m_stPlayerData.stActorData.iHp <= 0;
}

bool Player::AddItemToBag(const int iItemID, const int iNumber)
{
    return m_oBag.Add(iItemID, iNumber);
}

void Player::AddItemToBagFocus(const int iItemID, const int iNumber)
{
    m_oBag.AddForce(iItemID, iNumber);
}

bool Player::CanAddItemToBag(const int iItemID, const int iNumber)
{
    return m_oBag.CanAdd(iItemID, iNumber);
}

bool Player::Pay(const int iMoney)
{
    if (m_stPlayerData.stActorExternData.iMoney < iMoney)
        return false;

    m_stPlayerData.stActorExternData.iMoney -= iMoney;
    return true;
}


bool Player::Buy(const Goods &oGoods)
{
    int iItemID = oGoods.GetItemID();
    int iNumber = oGoods.GetAmount();
    int iPrice  = oGoods.GetPrice();

    if (!m_oBag.CanAdd(iItemID, iNumber))
        return false;

    if (Pay(iPrice))
        return false;

    m_oBag.AddForce(iItemID, iNumber);

    return true;
}

int Player::GetHp()const
{
    return m_stPlayerData.stActorData.iHp;
}

int Player::GetMaxHp()const
{
    int iTotalMaxHp = m_stPlayerData.stActorData.iMaxHp;

    for (int i = 0; i < data::EQUIPMENT_TYPE_MAX; ++i)
        if (m_ayEquipments[i].bIsEquip)
            iTotalMaxHp += m_ayEquipments[i].oEquipment.GetMaxHp();

    return iTotalMaxHp;
}

int Player::GetAttack()const
{
    int iTotalAttack = m_stPlayerData.stActorData.iAttack;

    for (int i = 0; i < data::EQUIPMENT_TYPE_MAX; ++i)
        if (m_ayEquipments[i].bIsEquip)
            iTotalAttack += m_ayEquipments[i].oEquipment.GetAttack();

    return iTotalAttack;
}

int Player::GetDefance()const
{
    int iTotalDefance = m_stPlayerData.stActorData.iDefance;

    for (int i = 0; i < data::EQUIPMENT_TYPE_MAX; ++i)
        if (m_ayEquipments[i].bIsEquip)
            iTotalDefance += m_ayEquipments[i].oEquipment.GetDefance();

    return iTotalDefance;
}

int Player::GetExtendMaxHp()const
{
    int iExtendMaxHp = 0;
    for (int i = 0; i < data::EQUIPMENT_TYPE_MAX; ++i)
        if (m_ayEquipments[i].bIsEquip)
            iExtendMaxHp += m_ayEquipments[i].oEquipment.GetMaxHp();
    return iExtendMaxHp;
}

int Player::GetExtendAttack()const
{
    int iExtendAttack = 0;
    for (int i = 0; i < data::EQUIPMENT_TYPE_MAX; ++i)
        if (m_ayEquipments[i].bIsEquip)
            iExtendAttack += m_ayEquipments[i].oEquipment.GetAttack();
    return iExtendAttack;
}

int Player::GetExtendDefance()const
{
    int iExtendDefance = 0;
    for (int i = 0; i < data::EQUIPMENT_TYPE_MAX; ++i)
        if (m_ayEquipments[i].bIsEquip)
            iExtendDefance += m_ayEquipments[i].oEquipment.GetDefance();
    return iExtendDefance;
}

const Container& Player::GetBag() const
{
    return m_oBag;
}
