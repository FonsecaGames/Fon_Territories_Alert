modded class DayZGame 
{
    protected ref CFTerritoryAlarmConfig m_CFTAlertConfig;

    void SetTerritoriesAlertConfig(CFTerritoryAlarmConfig p_config)
    {
        m_CFTAlertConfig = p_config;
    }

    ref CFTerritoryAlarmConfig GetTerritoriesAlertConfig()
    {
        return m_CFTAlertConfig;
    }
}