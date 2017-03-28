#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

bool Player::AddItemToBag(const Item &oItem)
{
	return m_oBag.AddItem(oItem);
}

const Bag& Player::GetBag() const
{
	return m_oBag;
}
