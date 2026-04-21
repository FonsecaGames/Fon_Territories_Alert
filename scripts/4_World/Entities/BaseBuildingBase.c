modded class BaseBuildingBase extends ItemBase
{
	protected TerritoryFlag m_Flag;
	private bool m_AlarmLocked = false;

	override void EEInit()
	{
		super.EEInit();

		FindFlag();
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
		
		FindFlag();

		PlayerBase playerSource;
		if ( source.IsPlayer() )// Fists
			playerSource = PlayerBase.Cast( source );
		else
			playerSource = PlayerBase.Cast( source.GetHierarchyParent() );
		
		if (IsTerritoryMember(playerSource))
			return;

		float damage = damageResult.GetHighestDamage("");
		string alert = "";
		alert += "**Hit By**:" + dmgType + " (" + damage + " hp)\\n";		
		if (m_Flag)
			m_Flag.GetTerritoryWebhook().SendAlert(CFTDAMAGE.HIT_BY, alert, damage);
	}

	// override void OnPartDestroyedServer( Man player, string part_name, int action_id, bool destroyed_by_connected_part = false )
	// {
	// 	super.OnPartDestroyedServer( player, part_name, action_id, destroyed_by_connected_part );
		
	// 	if (IsTerritoryMember(PlayerBase.Cast(player)))
	// 		return;

	// 	string alert = "";
	// 	alert += "**Destroyed**:" + part_name + "\\n";
	// 	if (m_Flag)
	// 		m_Flag.GetTerritoryWebhook().SendAlert(CFTDAMAGE.DESTROY, alert, 0);
	// }

	override void OnPartDismantledServer(notnull Man player, string part_name, int action_id)
	{
		super.OnPartDismantledServer(player, part_name, action_id);

		FindFlag();

		if (IsTerritoryMember(PlayerBase.Cast(player)))
			return;

		string alert = "";
		alert += "**Dismantled**:" + part_name + "\\n";
		if (m_Flag)
			m_Flag.GetTerritoryWebhook().SendAlert(CFTDAMAGE.DISMANTLE, alert, 0);
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

	bool IsTerritoryMember(PlayerBase player)
	{
		if (!m_Flag)
			return false;

		PlayerIdentity ident = PlayerIdentity.Cast(player.GetIdentity());
		if (m_Flag.IsTerritoryMember(ident.GetId()))
		{
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
