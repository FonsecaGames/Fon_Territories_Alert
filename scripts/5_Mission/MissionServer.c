modded class MissionServer
{
    ref CFTerritoryAlarmConfig m_CFTAlertConfig;
    string m_ConfigFile;

    void MissionServer() 
    {
        m_ConfigFile = CFTConst.MOD_FOLDER + CFTConst.CONFIG_FILE;

        if (!FileExist(CFTConst.MOD_FOLDER)) {
			MakeDirectory(CFTConst.MOD_FOLDER);
		}

        if (!FileExist(m_ConfigFile))
        {
            if (!m_CFTAlertConfig)
            {
                m_CFTAlertConfig = new CFTerritoryAlarmConfig();
            }
            GetDayZGame().SetTerritoriesAlertConfig(m_CFTAlertConfig);
            SaveTerritoriesAlertConfig();
        }
        else
        {
            LoadTerritoriesAlertConfig();
            GetDayZGame().SetTerritoriesAlertConfig(m_CFTAlertConfig);
            SaveTerritoriesAlertConfig();
        }

        m_CFTAlertConfig.PrintValues();
    }

    void SaveTerritoriesAlertConfig()
    {
        JsonFileLoader<CFTerritoryAlarmConfig>.JsonSaveFile(m_ConfigFile, m_CFTAlertConfig);
    }

    void LoadTerritoriesAlertConfig()
    {
        JsonFileLoader<CFTerritoryAlarmConfig>.JsonLoadFile(m_ConfigFile, m_CFTAlertConfig);
    }
}