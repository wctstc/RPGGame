using UnityEngine;

public static class LuaConst
{
    public static string luaDir = Application.dataPath + "/Game/LuaSource";
    public static string toluaDir = Application.dataPath + "/3rdParty/Tolua/ToLua/Lua";
    public static string zbsDir = "D:/ZeroBraneStudio/lualibs/mobdebug";

    public static bool openLuaSocket = true;        //是否打开Lua Socket库
}