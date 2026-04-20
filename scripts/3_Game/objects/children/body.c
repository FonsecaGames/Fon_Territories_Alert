class CFTDiscordObject_Body : CFTDiscordObject
{
	/*
		https://discord.com/developers/docs/resources/channel#embed-object
	
		Fields:
			color - int
			title - string
			description - string
			url - string
			timpestamp - string (ISO8601 timestamp)
			fields - array of Field object
		Note:
			We don't include field for type, cause by default it use the "rich" type,
			that mean we can use any type of media.
	*/
	private int m_color;
	private ref array<ref CFTDiscordObject_Fields> m_otherFields;

	void CFTDiscordObject_Body(int color = -1)
	{
		m_color = color;
		m_otherFields = new array<ref CFTDiscordObject_Fields>;
	}
	
	override protected string ConvertSpecialFields()
	{
		string addedFieldsToJson = "";
		
		addedFieldsToJson += GetColorField();
		addedFieldsToJson += GetOtherFields();
		return addedFieldsToJson;
	}
	
	private string GetColorField()
	{
		if (m_color > -1)
		{
			return CFTDiscordHelper.GetJSONLineOthers("color", m_color.ToString());
		}
		return "";
	}
	
	private string GetOtherFields()
	{
		string dataFields = "";

		if (m_otherFields.Count() > 0)
		{
			dataFields += "[";
			foreach (auto otherField : m_otherFields)
			{
				dataFields += otherField.DefaultJSONConvert();
			}
			dataFields += "],";
		}
		return dataFields;
	}

	private void AddNewField(string name, string value, bool inline = false)
	{
		m_otherFields.Insert(new CFTDiscordObject_Fields(name, value, inline));
	}

	override protected bool CanSetKey(string key)
	{
		switch (key)
		{
			case "title":
				return true;
			case "description":
				return true;
			case "url":
				return true;
			case "timestamp":
				return true;
		}
		return false;
	}
};