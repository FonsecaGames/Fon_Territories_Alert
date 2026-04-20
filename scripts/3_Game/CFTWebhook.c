class CFTWebhook
{
    static const string DISCORD_API = "/api/webhooks/";

    private string m_BaseName;
    private string m_Webhook;
    private string m_ErrorMsg = "";

    void CFTWebhook()
    {
        m_BaseName = "";
        m_Webhook = "";
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

        return true;
    }

    bool RemoveWebhook()
    {
        m_BaseName = "";
        m_Webhook = "";
        
        return true;
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
}