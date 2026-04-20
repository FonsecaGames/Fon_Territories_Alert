class CFTUIManager : PluginBase {
    void ShowMenu(int menuId, ItemBase target) {
        if (GetGame().IsServer()) { return; }
        if (GetGame().GetUIManager().GetMenu()) {
            return;
        }
        GetGame().GetUIManager().EnterScriptedMenu(menuId, null);

        CFTWebhookMenu menu = CFTWebhookMenu.Cast(GetGame().GetUIManager().GetMenu());
        menu.SetTarget(target);

        TerritoryFlag flag = TerritoryFlag.Cast(target);
    }

    void ExitMenus() {
        CFTWebhookMenu menu = CFTWebhookMenu.Cast(GetGame().GetUIManager().GetMenu());

        if (menu)
        {
            menu.Close();
        }
    }
}
CFTUIManager GetCFTUIManager() {
    return CFTUIManager.Cast(GetPlugin(CFTUIManager));
}