class ActionEditTerritoryWebhook extends ActionInteractBase
{
    private TerritoryFlag m_Flag;

	void ActionEditTerritoryWebhook()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
	}
	
	override string GetText()
	{
        if (m_Flag.CanAddWebhook())
        {
            return "Add Webhook";
        }
        return "Remove Webhook";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
        PlayerIdentity ident = PlayerIdentity.Cast(player.GetIdentity());
        m_Flag = TerritoryFlag.Cast(target.GetObject());
        if (!m_Flag)
        {
            return false;
        }

		if (ident && m_Flag)
		{
			float state = m_Flag.GetAnimationPhase("flag_mast");
			if ((m_Flag.FindAttachmentBySlotName("Material_FPole_Flag")) && (state < TerritoryConst.FLAGUPSTATE))
			{
				return m_Flag.CheckPlayerPermission(ident.GetId(), TerritoryPerm.ADDMEMBER);
			}
		}

		return false;
	}

    override void OnStartClient(ActionData action_data) 
    {
        super.OnStartClient(action_data);

        m_Flag = TerritoryFlag.Cast(action_data.m_Target.GetObject());
        if (m_Flag)
        {
            GetCFTUIManager().ShowMenu(CFTMENU.EDIT_WEBHOOK, ItemBase.Cast(action_data.m_Target.GetObject()));
        }
    }
};