#include "PlayerHandler.h"

#include "ManagerInstance.h"

PlayerHandler::PlayerHandler()
{
}


PlayerHandler::~PlayerHandler()
{
}


int PlayerHandler::HandleShowBag(const cmd::Command eCmd, const  req::Req &oReq, rsp::Rsp &oRsp)
{
	const ContainerData *pBag = g_PlayerManger.GetBag().GetContainerData();

    //背包为空
    if (pBag == NULL || pBag->GetCellNum() <= 0)
    {
        g_ManagerHandler.RspWithNoOption("无物品",oRsp);
        return 0;
    }

    //获取背包物品信息
    vector<rsp::Rsp> vRspOption;
    for (int i = 0; i < pBag->GetCellNum(); ++i)
    {
		CellData stCellData;
		if (pBag->GetCell(i, stCellData))
        if (pBag->GetCell(i, stCellData) && stCellData.GetItemID() > 0 && stCellData.GetItemNum() >= 0)
        {
            string sDescription = StrUtil::Format(
                "%s*%d",
                g_ItemManager.GetNameByID(stCellData.GetItemID()).c_str(),
				stCellData.GetItemNum());

            rsp::Rsp oRspOption;
            oRspOption.Add(rsp::s_Option_Description, sDescription);
            oRspOption.Add(rsp::i_Option_FrameID, 2110000);
            oRspOption.Add(rsp::i_Option_Notify, cmd::NOTIFY_IDLE);
            oRspOption.Add(rsp::i_Option_Data, stCellData.GetItemID());
            vRspOption.push_back(oRspOption);
        }
    }

    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::v_Option, vRspOption);

    return 0;
}

int PlayerHandler::HandleShowBagItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    const Container &oBag = g_PlayerManger.GetBag();
    if (!g_ManagerHandler.CheckReqIndex(oBag.GetUsedCapacity(), oReq, oRsp))
        return 0;

	CellData stCellData;

	const ContainerData *pBagData = oBag.GetContainerData();

	if (pBagData == 0 || pBagData->GetCell(oReq.GetInt(req::i_Index), stCellData))
	{
		return 0;
	}

    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::s_Description, g_ItemManager.GetDescriptionByID(stCellData.GetItemID()));

    return 0;
}

