#include "MapHandler.h"

#include "ManagerInstance.h"

MapHandler::MapHandler()
{
}


MapHandler::~MapHandler()
{
}

int MapHandler::HandlerShowMap(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    int iNum = g_MapManager.GetMapTotalNum();
    
    vector<rsp::Rsp> vOptions;
    for (int i = 0; i < iNum; ++i)
    {
        rsp::Rsp oOption;
        const Map &oMap = g_MapManager.GetMapByID(i);

        oOption.Add(rsp::s_Option_Description,oMap.GetName());
        oOption.Add(rsp::i_Option_Data, oMap.GetID());
        oOption.Add(rsp::i_Option_FrameID, 3100000);
        oOption.Add(rsp::i_Option_Notify, cmd::NOTIFY_IDLE);
        
        vOptions.push_back(oOption);
    }

    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::v_Option,  vOptions);
    
    return 0;
}

int MapHandler::HandlerShowMapAction(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    if (!g_ManagerHandler.CheckReqIndex(g_MapManager.GetMapTotalNum(), oReq, oRsp))
        return 0;

    int iIndex = oReq.GetInt(req::i_Index);

    const Map &oMap = g_MapManager.GetMapByID(iIndex);
    if (&oMap == &Map::GetNoMap())
    {
        g_ManagerHandler.RspWithNoOption("无地图", oRsp);
        return 0;
    }

    const vector<int>& vMapActionIDs = oMap.GetMapActionID();
    if (vMapActionIDs.size() <= 0)
    {
        g_ManagerHandler.RspWithNoOption("无地图动作",oRsp);
        return 0;
    }

    vector<rsp::Rsp> vOptions;
    int iSize = vMapActionIDs.size();
    for (int i = 0;i < iSize; ++i)
    {
        rsp::Rsp oOption;
        const MapAction &oMapAction = g_MapManager.GetMapActionByID(vMapActionIDs[i]);
        int iFrameID = -2;

        switch (oMapAction.GetType())
        {
        case MapAction::MAPACTION_TYPE_RESOURCE:
            iFrameID = 3110000;
            break;
        case MapAction::MAPACTION_TYPE_MONSTER:
            iFrameID = 3120000;
            break;
        }

        oOption.Add(rsp::s_Option_Description, oMapAction.GetName());
        oOption.Add(rsp::i_Option_FrameID,     iFrameID);
        oOption.Add(rsp::i_Option_Data,        oMapAction.GetID());
        oOption.Add(rsp::i_Option_Notify,      cmd::NOTIFY_IDLE);

        vOptions.push_back(oOption);
    }

    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::v_Option,  vOptions);

    return 0;
}

int MapHandler::HandlerShowMonster(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    if (!g_ManagerHandler.CheckReqData(oReq, oRsp))
        return 0;

    int iMapActionID = oReq.GetInt(req::i_Data);
    const MapAction &oMapAction = g_MapManager.GetMapActionByID(iMapActionID);
    if (&oMapAction == &MapAction::GetNoMapAction())
    {
        g_ManagerHandler.RspWithNoOption("无地图动作",oRsp);
        return 0;
    }

    const Monster &oMonster = g_MapManager.GetCurrentMonster(iMapActionID);
    if (oMonster.GetID() == Monster::GetNoMonster().GetID())
    {
        oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
        oRsp.Add(rsp::i_State, 1);
        return 0;
    }
    else
    {
        oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
        oRsp.Add(
            rsp::s_Description,
            StrUtil::Format(
                "名字：%s\n描述：%s\n血量：%d/%d\n攻击力：%d\n防御力：%d",
                oMonster.GetName().c_str(),
                oMonster.GetDescription().c_str(),
                oMonster.GetHp(),
                oMonster.GetMaxHp(),
                oMonster.GetAttack(),
                oMonster.GetDefance()));
    }

    return 0;
}

int MapHandler::HandleMapAttack(const cmd::NotifyCommand eNotifyCommand, const notify::Notify &oNotify)
{
    string sTips;
    Monster &oCurrentMonst = g_MapManager.GetCurrentMonster();
    const Player &oPlayer = g_PlayerManger.GetPlayer();

    g_PlayerManger.Attack(oCurrentMonst);


    if (oPlayer.IsDie())
    {
        sTips = "你死翘翘了~~";
    }

    if (oCurrentMonst.IsDie())
    {
        const vector<int>& vDrops = oCurrentMonst.GetDrop();
        string sDropInfo;

        for (unsigned int i = 0; i < vDrops.size(); ++i)
        {
            const Drop &oDrop = g_MapManager.GetDropByID(vDrops[i]);
            g_PlayerManger.AddToBag(oDrop.GetItemID(), oDrop.GetItemNum());

            //生成提示
            if (!sDropInfo.empty())
                sDropInfo.append(",");

            sDropInfo.append(
                StrUtil::Format(
                    "%s*%d",
                    g_ItemManager.GetNameByID(oDrop.GetItemID()).c_str(),
                    oDrop.GetItemNum()));
        }

        sTips = StrUtil::Format("恭喜，击杀%s获得%s",oCurrentMonst.GetName().c_str(),sDropInfo.c_str());
    }
    else
    {
        sTips = StrUtil::Format("你攻击%s,%s收到%d伤害\n%s攻击你，你受到%d伤害",
            oCurrentMonst.GetName().c_str(),
            oCurrentMonst.GetName().c_str(),
            oCurrentMonst.GetPreHp()-oCurrentMonst.GetHp(),
            oCurrentMonst.GetName().c_str(),
            oPlayer.GetPreHp()-oPlayer.GetHp());
    }


    g_ManagerHandler.UpdateTipsFrame(sTips);
    g_ManagerHandler.UpdatePropertyFrame();
    return 0;
}

int MapHandler::HandleMapRun(const cmd::NotifyCommand eNotifyCommand, const notify::Notify &oNotify)
{
    if (g_MapManager.Escape())
    {
        g_ManagerHandler.UpdateTipsFrame("逃跑成功");
    }
    return 0;
}
