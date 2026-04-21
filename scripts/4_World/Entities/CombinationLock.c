modded class CombinationLock extends ItemBase
{
    private bool m_LastLocked = false;
    protected TerritoryFlag m_Flag;

    override bool IsLocked()
    {
        bool isLocked = super.IsLocked();

        if (m_LastLocked && !isLocked)
        {
            string alert = "";
            alert += "**Combination**: Unlocked\\n";
            if (m_Flag)
                m_Flag.GetTerritoryWebhook().SendAlert(CFTDAMAGE.DISMANTLE, alert, 0);
        }
        m_LastLocked = isLocked;

        return isLocked;
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
}