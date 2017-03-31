#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Bag.h"


class Player
{
public:
	Player();
	~Player();
public:
	bool Init();
	bool AddItemToBag( const Item &oItem );
public:
	const Bag& GetBag()const;
private:
	Bag m_oBag;
};


#endif // __PLAYER_H__
