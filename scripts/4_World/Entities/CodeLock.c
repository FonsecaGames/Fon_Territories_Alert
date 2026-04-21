#ifdef CodeLock
modded class CodeLock extends ItemBase 
{
    protected TerritoryFlag m_Flag;
    static float m_LastHealth = 0;

	// NOTE: For now the player how damaged isn't tracked
    override float GetSynchronizedHealth()
    {
		float health = super.GetSynchronizedHealth();

		FindFlag();

        if (m_LastHealth == 0)
            m_LastHealth = health;

        if (m_LastHealth != health)
        {
			float damage = Math.AbsFloat(m_LastHealth - health);
            m_LastHealth = health;

			string alert = "";

			if (health > 0)
				alert += "**Codelock**: Damage (" + damage + " hp)\\n";
			else
				alert += "**Codelock**: Destroyed\\n";

            if (m_Flag)
				m_Flag.GetTerritoryWebhook().SendAlert(CFTDAMAGE.DAMAGE, alert, damage);
        }

		return health;
    }

    bool SetTerritory(TerritoryFlag p_flag)
	{
		if (!p_flag)
		{
			return false;
		}

		if (!m_Flag)
		{
			m_Flag = TerritoryFlag.Cast(p_flag);
			return true;
		}
		return false;
	}

	// TODO: Find a common place to call this, for now keep local
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
#endif