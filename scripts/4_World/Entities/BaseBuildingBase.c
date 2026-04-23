modded class BaseBuildingBase extends ItemBase
{
	ref CFTLink m_Link = new CFTLink;
	private bool m_AlarmLocked = false;

	void CheckLink()
	{
		m_Link.CheckLink(GetPosition(), this);
	}
	
	override void EEInit()
	{
		super.EEInit();
		CheckLink();
	}

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{		
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		string dmgType = "";
		if (damageType == DT_CLOSE_COMBAT) dmgType = "Combat";
		else if (damageType == DT_FIRE_ARM) dmgType = "Fire Arm";
		else if (damageType == DT_EXPLOSION) dmgType = "Explosion";
		else if (damageType == DT_CUSTOM) dmgType = "Custom";

		if (GetGame().IsClient())
			return;
		
		PlayerBase playerSource;
		if ( source.IsPlayer() )// Fists
			playerSource = PlayerBase.Cast( source );
		else
			playerSource = PlayerBase.Cast( source.GetHierarchyParent() );
		
		if (m_Link.IsTerritoryMember(playerSource))
			return;

		float damage = damageResult.GetHighestDamage("");
		m_Link.SendAlert(CFTDAMAGE.DAMAGE, "**Hit By**:" + dmgType + " (" + damage + " hp)", damage);
	}

	override void OnPartDestroyedServer( Man player, string part_name, int action_id, bool destroyed_by_connected_part = false )
	{
		super.OnPartDestroyedServer( player, part_name, action_id, destroyed_by_connected_part );
		
		if (m_Link.IsTerritoryMember(PlayerBase.Cast(player)))
			return;

		m_Link.SendAlert(CFTDAMAGE.DESTROY, "**Destroyed**:" + part_name, 0);
	}

	override void OnPartDismantledServer(notnull Man player, string part_name, int action_id)
	{
		super.OnPartDismantledServer(player, part_name, action_id);

		if (m_Link.IsTerritoryMember(PlayerBase.Cast(player)))
			return;

		m_Link.SendAlert(CFTDAMAGE.DISMANTLE, "**Dismantled**:" + part_name, 0);
	}

}
