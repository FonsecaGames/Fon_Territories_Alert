modded class CombinationLock extends ItemBase
{
    protected TerritoryFlag m_Flag;

    override void UnlockServer( EntityAI player, EntityAI parent )
    {
        super.UnlockServer(player, parent);

        FindFlag();

        PlayerBase playerSource = PlayerBase.Cast(player);
        PlayerIdentity ident = PlayerIdentity.Cast(playerSource.GetIdentity());
        if(m_Flag.IsTerritoryMember(ident.GetId()))
            return;

        string alert = "";
        alert += "**Combination**: Unlocked\\n";
        m_Flag.GetTerritoryWebhook().SendAlert(CFTDAMAGE.UNLOCK, alert, 0);
    }

    bool SetTerritory(TerritoryFlag p_flag)
	{
		if (!p_flag)
			return false;

		if (!m_Flag)
		{
			m_Flag = TerritoryFlag.Cast(p_flag);
			return true;
		}

		return false;
	}

    void FindFlag()
	{
        if (!m_Flag)
            return;

		array<Object> objects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;

        GetGame().GetObjectsAtPosition(GetPosition(), GameConstants.REFRESHER_RADIUS, objects, proxyCargos);

        TerritoryFlag flag;
        for (int i = 0; i < objects.Count(); i++)
        {
            if (Class.CastTo(flag, objects.Get(i)))
            {
                SetTerritory(flag);
				break;
            }
        }
	}
}