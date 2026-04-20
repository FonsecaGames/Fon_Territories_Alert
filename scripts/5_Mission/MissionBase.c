modded class MissionGameplay {
    override UIScriptedMenu CreateScriptedMenu(int id)
    {

        UIScriptedMenu menu = super.CreateScriptedMenu(id);

        if (!menu)
        {
            switch (id)
            {
                case CFTMENU.EDIT_WEBHOOK:
                {
                    menu = new CFTWebhookMenu();
                    menu.SetID(id);

                    break;
                }
            }
        }

        return menu;
    }
}