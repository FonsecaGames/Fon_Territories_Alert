modded class CombinationLock extends ItemBase
{
    ref CFTLink m_Link = new CFTLink;

    void CheckLink()
    {
        if (IsLockAttached())
        {
            m_Link.CheckLink(GetPosition(), this);
        }
    }

    override void LockServer( EntityAI parent, bool ignore_combination = false )
    {
        super.LockServer(parent, ignore_combination);
        m_Link.ResetLink();
        CheckLink();
    }

    override void UnlockOnServer(EntityAI player, EntityAI parent, bool isInsideLock = false)
    {
        super.UnlockOnServer(player, parent, isInsideLock);

        PlayerBase playerSource = PlayerBase.Cast(player);
        if(m_Link.IsTerritoryMember(playerSource))
            return;

        m_Link.SendAlert(CFTDAMAGE.UNLOCK, "**Combination**: Unlocked", 0);
    }
}