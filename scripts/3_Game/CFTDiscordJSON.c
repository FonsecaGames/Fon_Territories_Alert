class CFTDiscordJSON
{
	/*
		Source of discord hook help:
			https://discord.com/developers/docs/resources/channel#embed-object
	*/
	ref CFTDiscordObject_Body m_body;
	ref CFTDiscordObject_Footer m_footer;
	ref CFTDiscordObject_Image m_image;
	ref CFTDiscordObject_Thumbnail m_thumbnail;
	ref CFTDiscordObject_Video m_video;
	ref CFTDiscordObject_Provider m_provider;
	ref CFTDiscordObject_Author m_author;

	/*
		Description:
			It convert an unformated data to a JSON to send through
			DiscordHook class.
	*/
	string GetJSON()
	{
		string jsonData = "{";
		
		jsonData += GetModuleJSON(m_body);
		jsonData += GetModuleJSON(m_footer);
		jsonData += GetModuleJSON(m_image);
		jsonData += GetModuleJSON(m_thumbnail);
		jsonData += GetModuleJSON(m_video);
		jsonData += GetModuleJSON(m_provider);
		jsonData += GetModuleJSON(m_author);
		jsonData += "}";
		jsonData = CFTDiscordHelper.RemoveExtraCommasJSON(jsonData);
		return jsonData;
	}
	
	string GetModuleJSON(ref CFTDiscordObject module)
	{
		if (module)
		{
			return module.DefaultJSONConvert();
		}
		return "";
	}
};