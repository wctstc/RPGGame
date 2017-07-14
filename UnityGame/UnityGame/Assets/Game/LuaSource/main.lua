--主入口函数。从这里开始lua逻辑

require("fairygui")

function Main()					
	print("lua start!")
	local UIPackage = FairyGUI.UIPackage
	local GRoot = FairyGUI.GRoot
	local packageName = "Start"
	local componentName = "PageStart"
	UIPackage.AddPackage("UIProject/"..packageName)
	--适配
	GRoot.inst:SetContentScaleFactor(1366, 768)
	local panel = UIPackage.CreateObject(packageName, componentName)
	local btn = panel:GetChild("Btn")
	btn.onClick:Add(function()
		print("----------------------------------------------------")
	end)
	print("btn", btn)

	local uiWindow = FairyGUI.Window.New()
	uiWindow.contentPane = panel
	--show
	uiWindow:Show()
end

--场景切换通知
function OnLevelWasLoaded(level)

end