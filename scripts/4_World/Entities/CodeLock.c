#ifdef CodeLock
modded class CodeLock extends ItemBase 
{
    ref CFTLink m_Link = new CFTLink;
    static float m_LastHealth = 0;

	void CheckLink()
	{
		if (GetLockState())
        {
            m_Link.CheckLink(GetPosition(), this);
        }
	}

	override void LockServer(ItemBase parent, string passcode)
	{
		super.LockServer(parent, passcode);

		m_Link.ResetLink();
		CheckLink();
	}

	override void NewUnlockServer(EntityAI player, EntityAI parent)
	{
		super.NewUnlockServer(player, parent);

		if (GetHealth() == 0)
		{
			m_Link.SendAlert(CFTDAMAGE.DESTROY, "**Codelock**: Destroyed", 0);
		}
	}

    override float GetSynchronizedHealth()
    {
		float health = super.GetSynchronizedHealth();

        if (m_LastHealth == 0)
            m_LastHealth = health;

        if (m_LastHealth != health)
        {
			float damage = Math.AbsFloat(m_LastHealth - health);
            m_LastHealth = health;

			if (health > 0)
				m_Link.SendAlert(CFTDAMAGE.DAMAGE, "**Codelock**: Damage (" + damage + " hp) (health: " + health + " hp)", damage);
			// else
			// 	m_Link.SendAlert(CFTDAMAGE.DESTROY, "**Codelock**: Destroyed", damage);            
        }

		return health;
    }

}
#endif