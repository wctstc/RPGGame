using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using FairyGUI;

public class FightActionScene : MonoBehaviour {

    private GMovieClip g_Time;

    private GImage[] g_Road;
    private GImage[] g_Action;

    private GImage g_Player;
    private GImage g_Enemy;
    private GTextField g_PlayerText;
    private GTextField g_EnemyText;

    private int[] g_PlayerAction;
    private int[] g_EnemyAction;

    private int g_TimeDuring;
	// Use this for initialization
	void Start () {
        GComponent gComponent = GetComponent<UIPanel>().ui;
        
        //Movie
        g_Time = gComponent.GetChild("Time").asMovieClip;
        g_Time.playing = false;

        //Road
        g_Road = new GImage[6];
        g_Road[0] = gComponent.GetChild("Road1").asImage;
        g_Road[1] = gComponent.GetChild("Road2").asImage;
        g_Road[2] = gComponent.GetChild("Road3").asImage;
        g_Road[3] = gComponent.GetChild("Road4").asImage;
        g_Road[4] = gComponent.GetChild("Road5").asImage;
        g_Road[5] = gComponent.GetChild("Road6").asImage;

        //Role
        g_Player = gComponent.GetChild("PlayerRole").asImage;
        g_Enemy = gComponent.GetChild("EnemyRole").asImage;
        g_PlayerText = gComponent.GetChild("PlayerText").asTextField;
        g_EnemyText = gComponent.GetChild("EnemyText").asTextField;
        

        //Action
        g_Action = new GImage[8];
        g_Action[0] = UIPackage.CreateObject("Game", "picMove").asImage;
        g_Action[1] = UIPackage.CreateObject("Game", "picAttack").asImage;
        g_Action[2] = UIPackage.CreateObject("Game", "picDefance").asImage;
        g_Action[3] = UIPackage.CreateObject("Game", "picMagic").asImage;
        g_Action[4] = UIPackage.CreateObject("Game", "picMove").asImage;
        g_Action[5] = UIPackage.CreateObject("Game", "picAttack").asImage;
        g_Action[6] = UIPackage.CreateObject("Game", "picDefance").asImage;
        g_Action[7] = UIPackage.CreateObject("Game", "picMagic").asImage;

        for ( int i = 0; i < 8; ++i)
        {
            g_Action[i].height = 32;
            g_Action[i].width = 32;
            g_Action[i].visible = false;
            gComponent.AddChild(g_Action[i]);
        }

        //RoleAction
        g_PlayerAction = new int[10];
        g_EnemyAction = new int[10];
        
    }
    public void Play()
    {
        g_Time.SetPlaySettings(0, -1, 1, -1);
        g_Time.playing = true;
        g_TimeDuring = 0;

        for (int i = 0; i < 10; ++i)
        {
            g_PlayerAction[i] = -1;
            g_EnemyAction[i] = -1;
        }
        
        //SequenceAction(DataMgr.Instance.Player().ActionSequence, g_PlayerAction);
        
        //SequenceAction(DataMgr.Instance.Enemy().ActionSequence, g_EnemyAction);

        InvokeRepeating("DoAction",0, 1.0f);
    }
    // Update is called once per frame
    void Update () {
	}

    void DoAction()
    {
        for (int i = 0; i < 4; ++i)
        {
            g_Action[i].x = g_Player.x + 34;
            g_Action[i].y = g_Player.y + 40;
            g_Action[i].visible = false;
        }
        switch (DataMgr.Instance.Player().ActionSequence[g_TimeDuring])
        {
            case 0:
                g_Player.x += 40;
                g_Player.y -= 40;
                g_Action[0].visible = true;
                g_Action[0].x = g_Player.x + 34;
                g_Action[0].y = g_Player.y + 40;
                break;
            case 1:
                g_Action[1].visible = true;
                break;
            case 2:
                g_Action[2].visible = true;
                break;
            case 3:
                g_Action[3].visible = true;
                break;
        }

        for (int i = 0; i < 4; ++i)
        {
            g_Action[4 + i].x = g_Enemy.x + 34;
            g_Action[4 + i].y = g_Enemy.y + 40;
            g_Action[4 + i].visible = false;
        }
        switch (DataMgr.Instance.Enemy().ActionSequence[g_TimeDuring])
        {
            case 0:
                g_Enemy.x -= 40;
                g_Enemy.y += 40;
                g_Action[4].visible = true;
                g_Action[4].x = g_Enemy.x + 34;
                g_Action[4].y = g_Enemy.y + 40;
                break;
            case 1:
                g_Action[5].visible = true;
                break;
            case 2:
                g_Action[6].visible = true;
                break;
            case 3:
                g_Action[7].visible = true;
                break;
        }
        ++g_TimeDuring;

        if(g_TimeDuring >= 10)
        {
            GetComponent<UIPanel>().ui.visible = false;
            CancelInvoke("DoAction");
        }
    }

    void SequenceAction(int[]sequence, int[] action)
    {
        int index = 0;
        for( int i = 0; i < sequence.Length; ++i)
        {
            switch(sequence[i])
            {
                case 0:
                    action[index++] = 0;
                    break;
                case 1:
                    action[index++] = -1;
                    action[index++] = 1;
                    break;
                case 2:
                    action[index++] = 2;
                    action[index++] = 2;
                    break;
                case 3:
                    action[index++] = -1;
                    action[index++] = -1;
                    action[index++] = -1;
                    action[index++] = 3;
                    break;
            }
        }
    }
}
