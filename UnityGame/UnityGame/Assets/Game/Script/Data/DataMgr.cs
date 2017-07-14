using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoleData
{
    public static readonly int  MAX_SEQUENCE_NUM = 20;

    public int Health   { get; set; }
    public int Power    { get; set; }
    public int Position { get; set; }
    public int Attack   { get; set; }
    public int Defance  { get; set; }
    public int Magic    { get; set; }

    public string Icon { get; set; }

    public List<int> ActionSequence = new List<int>();
}

public class ActionData
{
    public int    Index    { get; set; }
    public int    Power    { get; set; }
    public int    Movement { get; set; }
    public string Src      { get; set; }
    public string Icon     { get; set; }
    public string Name     { get; set; }
}

public class DataMgr
{
    public static DataMgr Instance = new DataMgr();

    private RoleData g_Player;
    private RoleData g_Enemy;

    private ActionData[] g_ActionData;

    public RoleData Player() { return g_Player; }
    public RoleData Enemy() { return g_Enemy; }
    public ActionData[] AllAction() { return g_ActionData; }

    private DataMgr()
    {
        g_Player = new RoleData();
        g_Player.Health = 100;
        g_Player.Power = 100;
        g_Player.Position = 0;
        g_Player.Attack = 10;
        g_Player.Defance = 5;
        g_Player.Magic = 30;
        g_Player.Icon = "picPlayer5";

        g_Enemy = new RoleData();
        g_Enemy.Health = 100;
        g_Enemy.Power = 100;
        g_Enemy.Position = 5;
        g_Enemy.Attack = 10;
        g_Enemy.Defance = 5;
        g_Enemy.Magic = 30;
        g_Enemy.Icon = "picPlayer1";

        g_ActionData = new ActionData[10];

        g_ActionData[0] = new ActionData();
        g_ActionData[0].Index = 0;
        g_ActionData[0].Power = 0;
        g_ActionData[0].Movement = 1;
        g_ActionData[0].Src = "ActionMoveTmp";
        g_ActionData[0].Name = "移动";

        g_ActionData[1] = new ActionData();
        g_ActionData[1].Index = 1;
        g_ActionData[1].Power = 5;
        g_ActionData[1].Movement = 2;
        g_ActionData[1].Src = "ActionAttackTmp";
        g_ActionData[1].Name = "攻击";

        g_ActionData[2] = new ActionData();
        g_ActionData[2].Index = 2;
        g_ActionData[2].Power = 1;
        g_ActionData[2].Movement = 1;
        g_ActionData[2].Src = "ActionDefanceTmp";
        g_ActionData[2].Name = "防御";

        g_ActionData[3] = new ActionData();
        g_ActionData[3].Index = 0;
        g_ActionData[3].Power = 10;
        g_ActionData[3].Movement = 5;
        g_ActionData[3].Src = "ActionMagicTmp";
        g_ActionData[3].Name = "魔法";
    }
}
