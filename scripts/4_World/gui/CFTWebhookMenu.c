class CFTWebhookMenu : UIScriptedMenu 
{
    static const string LAYOUT_FILE = "CFTerritoriesAlert/gui/layouts/CFTDiscordWebHookEnter.layout";
	
    protected TerritoryFlag m_Flag;

	protected ref EditBoxWidget m_EdBaseName;
    protected ref EditBoxWidget m_EdWebhook;
	protected ref TextWidget m_TxtError;
    protected ref ButtonWidget m_BtnSave;
    protected ref ButtonWidget m_BtnReset;
    protected ref ButtonWidget m_BtnClose;

    protected string m_LastBaseName = "";
    protected string m_LastWebhook = "";

	override Widget Init() 
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets(LAYOUT_FILE);

        m_EdBaseName    = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("edtBaseName"));
        m_EdWebhook     = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("edtWebhook"));
        m_TxtError      = TextWidget.Cast(layoutRoot.FindAnyWidget("txtError"));
        m_BtnSave       = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnSave"));
        m_BtnReset      = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnReset"));
        m_BtnClose      = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnClose"));

        if (!m_EdBaseName || !m_EdWebhook || !m_TxtError || !m_BtnSave || !m_BtnReset || !m_BtnClose)
        {
            string wigetInvalid = " m_EdBaseName: " + (m_EdBaseName != null);
            wigetInvalid += " m_EdWebhook: " + (m_EdWebhook != null);
            wigetInvalid += " m_TxtError: " + (m_TxtError != null);
            wigetInvalid += " m_BtnSave: " + (m_BtnSave != null);
            wigetInvalid += " m_BtnReset: " + (m_BtnReset != null);
            wigetInvalid += " m_BtnClose: " + (m_BtnClose != null);
            CFTLog("Some Widget is invalid! " + wigetInvalid);

            GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(Close, 10);
            return layoutRoot;
        }

        // RefreshUI();
		return layoutRoot;
	}

	void SetTarget(ItemBase targetObject) 
    {
        m_Flag = TerritoryFlag.Cast(targetObject);
        CFTLog("SetTarget :" + m_Flag.GetPosition() + " Name:" + m_Flag.GetBaseName());
	}

    void RefreshUI()
    {
        if (!m_Flag)
            return ;

        if (!m_EdBaseName || !m_EdWebhook || !m_BtnSave || !m_BtnSave || !m_BtnReset || !m_TxtError)
            return ;

        string baseName = m_Flag.GetBaseName();
        string webhook = m_Flag.GetWebhook();
        bool isEnabled = m_Flag.CanAddWebhook();

        m_EdBaseName.SetText(baseName);
        m_EdWebhook.SetText(webhook);

        m_EdBaseName.Enable(isEnabled);
        m_EdWebhook.Enable(isEnabled);
        m_BtnSave.Enable(isEnabled);
        m_BtnReset.Enable(!isEnabled);

        m_TxtError.SetText("");

        m_EdBaseName.Update();
        m_EdWebhook.Update();
    }

    bool ReadFromUI()
    {
        if (!m_EdBaseName || !m_EdWebhook)
            return false;
        
        string baseName = m_EdBaseName.GetText();
        string webhook = m_EdWebhook.GetText();

        if ((baseName == string.Empty) || (webhook == string.Empty))
        {
            m_TxtError.SetText("Empty Field!");
            return false;
        }
        else
        {
            m_Flag.AddWebhook(baseName, webhook)
            string error = m_Flag.GetTerritoryWebhook().GetError();
            if (error == string.Empty)
            {
                RefreshUI();
            }
            else
            {
                m_TxtError.SetText(error);
            }
            return true;
        }
    }

	override bool OnClick(Widget w, int x, int y, int button) {
		bool canContinue = super.OnClick(w, x, y, button);

        m_TxtError.SetText("");
        if (w == m_BtnSave)
        {
            return ReadFromUI();
        }

        if (w == m_BtnReset)
        {
            m_Flag.RemoveWebhook();
            RefreshUI();
            return true;
        }

        if (w == m_BtnClose)
        {
            Close();
            return true;
        }

		return false;
	}

	override void OnShow()
    {
		super.OnShow();

        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
		GetGame().GetUIManager().ShowCursor(true);
		GetGame().GetMission().GetHud().Show(false);

        RefreshUI();
	}

	override void OnHide() {
		super.OnHide();

        GetGame().GetUIManager().ShowCursor(false);
		GetGame().GetMission().PlayerControlEnable(1);
		GetGame().GetMission().GetHud().Show(true);
	}

    override void Update(float timeslice)
    {
        super.Update(timeslice);

        if (!GetGame())
            return ;
        

        if ((m_LastBaseName != m_Flag.GetBaseName()) || (m_LastWebhook != m_Flag.GetWebhook()))
        {
            m_LastBaseName = m_Flag.GetBaseName();
            m_LastWebhook = m_Flag.GetWebhook();
            CFTLog("Changed " + m_Flag.GetPosition() + " BaseName:" + m_LastBaseName + " Webhook:" + m_LastWebhook);
            RefreshUI();
        }

        if (KeyState(KeyCode.KC_ESCAPE) == 1)
		{
			Close();
			return;
		}
    }
}