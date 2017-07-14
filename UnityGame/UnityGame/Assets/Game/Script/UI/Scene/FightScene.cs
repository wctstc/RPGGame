using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using FairyGUI;


public class FightScene : MonoBehaviour
{
    private GMovieClip g_TimeNumber;

    private GLoader g_PlayerIcon;
    private GLoader g_EnemyIcon;

    private GTextField g_PlayerActionText;
    private GTextField g_EnemyActionText;

    private GButton g_CurRole;

    private GComponent[] g_SequenceSlot;
    private GComponent[] g_ActionSlot;

    private List<GButton> g_Sequence;
    private List<GButton> g_Action;

    private GTextField g_Health;
    private GTextField g_Power;
    private GTextField g_Movement;

    private void Awake()
    {
        GComponent gComponent = GetComponent<UIPanel>().ui;

        //Movie
        g_TimeNumber = gComponent.GetChild("TimeNumber").asMovieClip;


        //Icon
        g_PlayerIcon = gComponent.GetChild("PlayerIcon").asLoader;
        g_EnemyIcon = gComponent.GetChild("EnemyIcon").asLoader;

        //ActionText
        g_PlayerActionText = gComponent.GetChild("PlayerActionText").asTextField;
        g_EnemyActionText = gComponent.GetChild("EnemyActionText").asTextField;

        //Role
        g_CurRole = gComponent.GetChild("Role1Tmp").asButton;

        g_CurRole.visible = true;
        g_CurRole.selected = true;

        //SequenceSlot
        g_SequenceSlot = new GComponent[7];
        g_SequenceSlot[0] = gComponent.GetChild("SequenceSlot1").asCom;
        g_SequenceSlot[1] = gComponent.GetChild("SequenceSlot2").asCom;
        g_SequenceSlot[2] = gComponent.GetChild("SequenceSlot3").asCom;
        g_SequenceSlot[3] = gComponent.GetChild("SequenceSlot4").asCom;
        g_SequenceSlot[4] = gComponent.GetChild("SequenceSlot5").asCom;
        g_SequenceSlot[5] = gComponent.GetChild("SequenceSlot6").asCom;
        g_SequenceSlot[6] = gComponent.GetChild("SequenceSlot7").asCom;



        //ActionSlot
        g_ActionSlot = new GComponent[10];
        g_ActionSlot[0] = gComponent.GetChild("ActionSlot1").asCom;
        g_ActionSlot[1] = gComponent.GetChild("ActionSlot2").asCom;
        g_ActionSlot[2] = gComponent.GetChild("ActionSlot3").asCom;
        g_ActionSlot[3] = gComponent.GetChild("ActionSlot4").asCom;
        g_ActionSlot[4] = gComponent.GetChild("ActionSlot5").asCom;
        g_ActionSlot[5] = gComponent.GetChild("ActionSlot6").asCom;
        g_ActionSlot[6] = gComponent.GetChild("ActionSlot7").asCom;
        g_ActionSlot[7] = gComponent.GetChild("ActionSlot8").asCom;
        g_ActionSlot[8] = gComponent.GetChild("ActionSlot9").asCom;
        g_ActionSlot[9] = gComponent.GetChild("ActionSlot10").asCom;

        //Sequence
        g_Sequence = new List<GButton>();
        //Action
        g_Action = new List<GButton>();

        g_Health   = gComponent.GetChild("Health").asTextField;
        g_Power    = gComponent.GetChild("Power").asTextField;
        g_Movement = gComponent.GetChild("Movement").asTextField;
    }

    // Use this for initialization
    void Start ()
    {
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    private void OnEnable()
    {
        g_TimeNumber.SetPlaySettings(0, -1, 1, -1);
        g_TimeNumber.onPlayEnd.Add(Balance);

        RoleData playerData = DataMgr.Instance.Player();
        RoleData enemyData = DataMgr.Instance.Enemy();
        
        g_PlayerIcon.url = UIPackage.GetItemURL("Game", playerData.Icon);
        g_EnemyIcon.url = UIPackage.GetItemURL("Game", enemyData.Icon);

        g_PlayerActionText.text = "";
        g_EnemyActionText.text = "";

        for (int i = 0; i < g_SequenceSlot.Length; ++i)
        {
            GObject child = g_SequenceSlot[i].GetChild("Sequence");
            if (child != null)
            {
                g_SequenceSlot[i].RemoveChild(child);
            }
        }
        
        g_Health.text = DataMgr.Instance.Player().Health.ToString();
        g_Power.text = DataMgr.Instance.Player().Power.ToString();
        g_Movement.text = (10).ToString();



        for (int i = 0; i < g_ActionSlot.Length; ++i)
        {
            GObject child = g_ActionSlot[i].GetChild("Action");
            if (child != null)
            {
                g_ActionSlot[i].RemoveChild(child);
            }
        }

        GComponent gComponent= GetComponent<UIPanel>().ui;
        ActionData[] AllActionData = DataMgr.Instance.AllAction();
        for (int i = 0; AllActionData[i] != null; ++i)
        {
            GButton actionButton = gComponent.GetChild(AllActionData[i].Src).asButton;
            actionButton.name = "Action";
            actionButton.SetXY(0, 0);
            actionButton.visible = true;
            actionButton.onClick.Add(AddSequence);
            actionButton.data = AllActionData[i];

            g_Action.Add(actionButton);
            g_ActionSlot[i].AddChild(actionButton);
        }
    }

    void AddSequence(EventContext eventContext)
    {
        GButton btnSequence = UIPackage.CreateObject("Game", "btnSequence").asButton;
        GButton btnAction = eventContext.sender as GButton;
        
        btnSequence.name = "Sequence";
        btnSequence.height = 32;
        btnSequence.width = 32;
        btnSequence.icon = btnAction.icon;
        btnSequence.data = btnAction.data;
        btnSequence.onClick.Add((EventContext context) =>
        {
            GButton sequence = context.sender as GButton;
            sequence = g_Sequence.Find(item => item.icon == sequence.icon);
            g_Sequence.Remove(sequence);

            UpdateUI();
        });


        for (int i = 0; i < g_SequenceSlot.Length; ++i)
        {
            if (g_SequenceSlot[i].numChildren <= 1)
            {
                g_SequenceSlot[i].AddChild(btnSequence);
                break;
            }
        }
        UpdateUI();
    }

    void UpdateUI()
    {
        RoleData playerData = DataMgr.Instance.Player();

        string sActionText = "";

        int usePower = 0;
        int useMovement = 0;
        
        foreach( var item in g_Sequence )
        {
            //item.icon
            ActionData actionData = item.data as ActionData;
            

            if(sActionText.Length > 0)
            {
                sActionText += "\n";
            }

            sActionText += actionData.Name;
            usePower += actionData.Power;
            useMovement += actionData.Movement;
        }

        g_PlayerActionText.text = sActionText;

        g_Power.text = (playerData.Power - usePower).ToString();
        g_Movement.text = (10 - useMovement).ToString();
    }

    void Balance()
    {
        g_TimeNumber.playing = false;


        RoleData playerData = DataMgr.Instance.Player();

        foreach (var item in g_Sequence)
        {
            ActionData actionData = item.data as ActionData;
            for( int i = 0;i < actionData.Movement; ++i )
            {
                playerData.ActionSequence.Add(actionData.Index);
            }
        }

        for (int i = 0; i < RoleData.MAX_SEQUENCE_NUM; ++i)
        {
            DataMgr.Instance.Enemy().ActionSequence[i] = Random.Range(0, 3);
        }
        
        UIMgr.Instance.ShowFightActionScene();
    }
}
