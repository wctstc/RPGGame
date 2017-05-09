#ifndef __MANAGERINSTANCE_H__
#define __MANAGERINSTANCE_H__

#include "ManagerHandler.h"

#include "StrUtil.h"
#include "HomeManager.h"
#include "PlayerManager.h"
#include "ItemManager.h"
#include "ShopManager.h"
#include "MapManager.h"

/*!< 家实例 */
#define g_HomeManager HomeManager::GetInstance()

/*!< 玩家实例 */
#define g_PlayerManger PlayerManager::GetInstance()

/*!< 物品实例 */
#define g_ItemManager  ItemManager::GetInstance()

/*!< 商店实例 */
#define g_ShopManager ShopManager::GetInstance()

#define g_MapManager MapManager::GetInstance()

#endif // __MANAGERINSTANCE_H__
