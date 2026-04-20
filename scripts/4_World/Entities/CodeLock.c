#ifdef CodeLock
modded class CodeLock extends ItemBase 
{
    protected TerritoryFlag m_Flag;
    static float m_LastHealth = 0;

    override float GetSynchronizedHealth()
    {
        float health = super.GetSynchronizedHealth();

        if (m_LastHealth == 0)
            m_LastHealth = health;

        if (m_LastHealth != health)
        {
            CFTLog("CodeLock health diff:" + (m_LastHealth - health)+ " health:" + health + " last:" + m_LastHealth);
            m_LastHealth = health;
            SendAlarm();
        }

        return health;
    }


    bool SetTerritory(TerritoryFlag p_flag)
	{
		if (!p_flag)
		{
			CFTLog("CLSetTerritory: NoTerritory");
			return false;
		}

		if (!m_Flag)
		{
			m_Flag = TerritoryFlag.Cast(p_flag);
			CFTLog("CLSetTerritory: " + m_Flag.GetBaseName());
			return true;
		}

		CFTLog("CLSetTerritory: Already applied");
		return false;
	}

    bool SendAlarm()
	{
		if (!m_Flag)
		{
			return false;
		}
		// return m_Flag.TriggerAlarm();
		CFTLog("CLALARM!!!!!");
		return true;
	}	
}
#endif