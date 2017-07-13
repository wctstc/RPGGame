using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using FairyGUI;

public class UIMgr : MonoBehaviour
{
    //单例模式
    public static UIMgr Instance;

    //场景
    public MainScene g_MainScene;
    public FightScene g_FightScene;
    public FightActionScene g_FightActionScene;

    //所有场景
    private List<MonoBehaviour> g_AllScene;

    // Use this for initialization
    void Start ()
    { 
        GRoot.inst.SetContentScaleFactor(800, 550, UIContentScaler.ScreenMatchMode.MatchWidthOrHeight);
                     
        Instance = this;

//         Instantiate(g_MainScene.gameObject);
//         Instantiate(g_FightScene.gameObject);
//         Instantiate(g_FightActionScene.gameObject);

        g_AllScene = new List<MonoBehaviour>();
        g_AllScene.Add(g_MainScene);
        g_AllScene.Add(g_FightScene);
        g_AllScene.Add(g_FightActionScene);



        foreach( var item in g_AllScene )
        {
            Instantiate(item);
            item.gameObject.SetActive(false);
        }

        g_FightScene.gameObject.SetActive(true);
    }

    // Update is called once per frame
    void Update ()
    {
	}

    void HideAllScene()
    {
        foreach (var item in g_AllScene)
        {
            item.gameObject.SetActive(false);
        }
    }



    public void ShowMainScene()
    {
        HideAllScene();
        g_MainScene.gameObject.SetActive(true);
    }

    public void ShowFightScene()
    {
        HideAllScene();
        g_FightScene.gameObject.SetActive(true);
    }

    public void ShowFightActionScene()
    {
        HideAllScene();
        g_FightActionScene.gameObject.SetActive(true);
    }
}
