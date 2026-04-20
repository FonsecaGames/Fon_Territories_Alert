class CFTDiscordHook
{
    private string m_Url = "";

    void CFTDiscordHook()
    {
    }

    bool SetUrl(string p_webhook)
    {
        if (!p_webhook)
            return false;

        m_Url = p_webhook;

        return true;
    }

    bool SendHook(ref CFTDiscordJSON data)
    {
        if (m_Url == string.Empty)
            return false;
        
        RestCallback cbx1 = new SilentCallBack;
        RestContext ctx = GetRestApi().GetRestContext(m_Url);
        ctx.SetHeader("application/json");
        ctx.POST(cbx1, "", WrapData(data));

        return true;
    }

    private string WrapData(ref CFTDiscordJSON data)
	{
		string json = "{\"embeds\":[";
		
		json += data.GetJSON();
		json += "]}";
		return json;
	}

}

class SilentCallBack : RestCallback
{
	override void OnError(int errorCode) {};
	override void OnTimeout() {};
	override void OnSuccess(string data, int dataSize) {};
};
