modded class BaseBuildingBase extends ItemBase
{
	protected TerritoryFlag m_Flag;
	private bool m_AlarmLocked = false;	
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{		
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		string dmgType = "";
		if (damageType == DT_CLOSE_COMBAT) dmgType = "Combat";
		if (damageType == DT_FIRE_ARM) dmgType = "Fire Arm";
		if (damageType == DT_EXPLOSION) dmgType = "Explosion";
		if (damageType == DT_CUSTOM) dmgType = "Custom";

		if (GetGame().IsClient())
			return;

		float damage = damageResult.GetHighestDamage("");
		string alert = "";
		alert += "**Hit By**:" + dmgType + " (" + damage + ")\\n";		
		if (m_Flag)
			m_Flag.GetTerritoryWebhook().SendAlert(CFTDAMAGE.HIT_BY, alert, damage);
	}

	override void OnPartDestroyedServer( Man player, string part_name, int action_id, bool destroyed_by_connected_part = false )
	{
		super.OnPartDestroyedServer( player, part_name, action_id, destroyed_by_connected_part );
		
		string alert = "";
		alert += "**Destroyed**:" + part_name + "\\n";
		if (m_Flag)
			m_Flag.GetTerritoryWebhook().SendAlert(CFTDAMAGE.DESTROY, alert, 0);
	}
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		string alert = "";
		alert += "**Object**:" + item.GetType() + "\\n";
		alert += "**Damage**:";
		if (item.IsRuined())
		{
			alert += "ruined\n";
		}
		else
		{
			alert += "detached\n";
		}
		if (m_Flag)
			m_Flag.GetTerritoryWebhook().SendAlert(CFTDAMAGE.DETACH, alert, 0);
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
