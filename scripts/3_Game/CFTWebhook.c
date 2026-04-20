class CFTWebhook
{
    static const string DISCORD_API = "/api/webhooks/";
    static const int HISTORY_MAX = 5;

    private string m_BaseName;
    private string m_Webhook;
    private string m_ErrorMsg = "";
    private bool m_HasWebhook = false;
    private bool m_EnableHook = false;

    private ref array<string> m_DamageHistory;
    private int m_TotalHistoryCount = 0;
    private float m_AcumulatedDamage = 0;
    private bool m_LockedHook = false;      // Lock to prevent multiple msgs

    void CFTWebhook()
    {
        m_BaseName = "";
        m_Webhook = "";

        m_DamageHistory = new array<string>;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SetEnableHook, 5000);
    }

    bool AddWebhook(string p_base_name, string p_webhook)
    {
        m_ErrorMsg = "";

        if (p_base_name == string.Empty)
        {
            m_ErrorMsg = "Empty Base Name";
            return false;
        }

        if (!p_webhook.Contains(DISCORD_API))
        {
            m_ErrorMsg = "Invalid Discord Api";
            return false;
        }
        
        m_BaseName = p_base_name;
        m_Webhook = p_webhook;
        m_HasWebhook = true;

        SendHello();

        return true;
    }

    bool RemoveWebhook()
    {
        SendGoodbye();

        m_BaseName = "";
        m_Webhook = "";
        m_HasWebhook = false;
        
        return true;
    }

    bool HasWebhook()
    {
        return m_HasWebhook;
    }

    string GetBaseName()
    {
        return m_BaseName;
    }

    string GetWebhook()
    {
        return m_Webhook;
    }

    string GetError()
    {
        return m_ErrorMsg;
    }

    void SendAlert(CFTDAMAGE p_type, string msg, float dmg = 0)
    {
        if (m_LockedHook)
        {
            AddDamageHistory(p_type, msg, dmg);
        }
        else
        {
            SendRaidAlert(msg);
            LockHook();
        }
    }

    bool SendRaidAlert(string p_description)
    {
        ref CFTDiscordJSON dataJSON = new CFTDiscordJSON();
        ref CFTDiscordObject_Body dataBody = new CFTDiscordObject_Body(0xd70202);

        dataBody.SetField("title", "Territory Alarm");

        string desc =   "**Territory**: "+ m_BaseName + "\\n";
		dataBody.SetField("description", desc +  p_description);

        dataJSON.m_body = dataBody;

        return SendHook(dataJSON);
    }

    bool SendHello()
    {
        if (!HasWebhook())
            return false;

        ref CFTDiscordJSON dataJSON = new CFTDiscordJSON();
        ref CFTDiscordObject_Body dataBody = new CFTDiscordObject_Body(5019904);

        dataBody.SetField("title", "Territory Alarm");
		dataBody.SetField("description", "The webhook has been added to the territory "+ m_BaseName);

        dataJSON.m_body = dataBody;

        return SendHook(dataJSON);
    }

    private bool SendGoodbye()
    {
        if (!HasWebhook())
            return false;

        ref CFTDiscordJSON dataJSON = new CFTDiscordJSON();
        ref CFTDiscordObject_Body dataBody = new CFTDiscordObject_Body(0xd6a102);

        dataBody.SetField("title", "Territory Alarm");
		dataBody.SetField("description", "The webhook has been removed from territory "+ m_BaseName);

        dataJSON.m_body = dataBody;

        return SendHook(dataJSON);
    }

    private bool SendHook(CFTDiscordJSON p_json)
    {
        if (!HasWebhook())
            return false;
        
        // Only server send msg
        if (GetGame().IsClient())
            return false;
        
        if (!m_EnableHook)
            return false;
        
        ref CFTDiscordHook hook = new CFTDiscordHook;

        if (!hook)
            return false;

        hook.SetUrl(m_Webhook);
        hook.SendHook(p_json);

        return true;
    }

    private void SetEnableHook()
    {
        m_EnableHook = true;
    }

    private void LockHook()
    {
        m_LockedHook = true;
        // Only Send 1 Alarm each 60Sec, but keep the total damage
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UnlockHook, 60 * 1000);
    }

    private void UnlockHook()
    {
        m_LockedHook = false;
        SendDamageHistory();
    }

    private void AddDamageHistory(CFTDAMAGE p_type, string msg, float dmg)
    {
        if (!m_DamageHistory)
            return;

        if (dmg != 0)
            m_AcumulatedDamage += dmg;

        m_TotalHistoryCount += 1;
        if (m_DamageHistory.Count() > HISTORY_MAX)
            return ;
        
        m_DamageHistory.Insert(msg);
    }

    private void SendDamageHistory()
    {
        if (m_DamageHistory.Count() == 0)
			return;

		string singleMsg = "";
		foreach(string msg : m_DamageHistory)
		{
			singleMsg += msg;
		}

        int diffCount = m_TotalHistoryCount - m_DamageHistory.Count();
        if (diffCount)
            singleMsg += "\\nMore " + diffCount + " alerts";

        singleMsg += "\\n**Acumulated Damage**:" + m_AcumulatedDamage;
        m_AcumulatedDamage = 0;

		m_DamageHistory.Clear();
		SendRaidAlert(singleMsg);
    }
}