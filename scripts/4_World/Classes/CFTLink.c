class CFTLink 
{
    const int m_IntervalOverload = 5 * 1000;

    private TerritoryFlag m_Flag;
    private bool m_IsOverloaded = false;

    void SendAlert(CFTDAMAGE p_type, string msg, float dmg = 0)
    {
        if (!m_Flag)
            return;

        m_Flag.GetTerritoryWebhook().SendAlert(p_type, msg, dmg);
    }

    bool CheckLink(vector pos, ItemBase target)
	{
        if (m_Flag)
            return false;

		array<Object> objects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;

        GetGame().GetObjectsAtPosition(pos, GameConstants.REFRESHER_RADIUS, objects, proxyCargos);

        TerritoryFlag flag;
        for (int i = 0; i < objects.Count(); i++)
        {
            if (Class.CastTo(flag, objects.Get(i)))
            {
                SetTerritory(flag, target);
				return true;
            }
        }

        if (!m_Flag)
            SetOverload();

        return false;
	}

    void ResetLink()
    {
        if (m_Flag)
        {
            m_Flag = null;
        }
    }

    bool IsTerritoryMember(PlayerBase player)
    {
        if (!GetGame().GetTerritoriesAlertConfig().CanOnlyNonMembers())
            return false;

        if (!m_Flag || !player)
			return false;

		PlayerIdentity ident = PlayerIdentity.Cast(player.GetIdentity());
		if (m_Flag.IsTerritoryMember(ident.GetId()))
		{
			return true;
		}

		return false;
    }

    private bool SetTerritory(TerritoryFlag p_flag, ItemBase p_target)
	{
		if (!p_flag)
			return false;

		if (!m_Flag)
		{
			m_Flag = TerritoryFlag.Cast(p_flag);
            CFTLog("SetTerritory: '" + m_Flag.GetBaseName() + "' -> item: " + p_target.GetType() + " (" + p_target.GetID() + ")");
			return true;
		}

		return false;
	}

    private void SetOverload()
    {
        if (m_IsOverloaded)
            return;
        m_IsOverloaded = true;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ResetOverload, m_IntervalOverload);
    }

    private void ResetOverload()
    {
        m_IsOverloaded = false;
    }
}