using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using FairyGUI;

public class MainScene : MonoBehaviour
{
    private GButton g_Country;
    private GButton g_Field;
    private GButton g_Forst;
    private GButton g_River;
    private GButton g_Mine;

    private GButton g_Info;
    private GButton g_Bag;
    private GButton g_Skill;
    private GButton g_Achievement;

	// Use this for initialization
	void Start () {
        GComponent gComponent = GetComponent<UIPanel>().ui;

        g_Country = gComponent.GetChild("MenuCountry").asButton;
        g_Field   = gComponent.GetChild("MenuField").asButton;
        g_Forst   = gComponent.GetChild("MenuForst").asButton;
        g_River   = gComponent.GetChild("MenuRiver").asButton;
        g_Mine    = gComponent.GetChild("MenuMine").asButton;
         
        g_Info        = gComponent.GetChild("PlayerRole").asButton;
        g_Bag         = gComponent.GetChild("PlayerBag").asButton;
        g_Skill       = gComponent.GetChild("PlayerSkill").asButton;
        g_Achievement = gComponent.GetChild("PlayerAchievement").asButton;


        g_Country.onClick.Add(() =>
        {
            UIMgr.Instance.ShowFightScene();
        });
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
