#include "PlayerManager.h"
#include "PlayerLoader.h"


PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}

bool PlayerManager::Init()
{
	//PlayerLoader::GetInstance().Init();

	m_oActor.Init(10, 10, 10, 1, 1);
	Item item;
	item.SetDescription("swoker");
	item.SetID(3);
	m_oActor.AddItemToBag(item);

	return true;
}

const Bag & PlayerManager::GetBag()
{
	return m_oActor.GetBag();
}

