modded class TerritoryFlag extends BaseBuildingBase
{
    protected bool m_CanAddWebhook = true;
    protected ref CFTWebhook m_TWebhook = new CFTWebhook;
    
    void TerritoryFlag()
    {
        RegisterNetSyncVariableBool("m_CanAddWebhook");
    }

    bool CanAddWebhook()
    {
        return m_CanAddWebhook;
    }

    CFTWebhook GetTerritoryWebhook()
    {
        return m_TWebhook;
    }

    string GetBaseName()
    {
        return m_TWebhook.GetBaseName();
    }

    string GetWebhook()
    {
        return m_TWebhook.GetWebhook();
    }

    void AddWebhook(string p_base, string p_webhook)
    {
        InternalAddWebhook(p_base, p_webhook);
        ForceSync();
    }

    void RemoveWebhook()
    {
        InternalRemoveWebhook();
        ForceSync();
    }

    override void SetActions() {
        super.SetActions();
        
        AddAction(ActionEditTerritoryWebhook);
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        
        ctx.Write(m_TWebhook.GetBaseName());
        ctx.Write(m_TWebhook.GetWebhook());
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version)) 
            return false;

        string baseName = "";
        string webhook = "";

		if (!ctx.Read(baseName)) 
		{
			return false;
		}

        if (!ctx.Read(webhook)) 
		{
			return false;
		}

        if (webhook != string.Empty && baseName != string.Empty)
        {
            bool added = m_TWebhook.AddWebhook(baseName, webhook);
            m_CanAddWebhook = !added;
        }
        else
        {
            m_CanAddWebhook = m_TWebhook.RemoveWebhook();
        }

        // CFTLog("OnStoreLoad " + GetPosition() + " BaseName:" + m_TWebhook.GetBaseName());

        return true;
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        
        if (GetGame().IsClient())
        {
            // CFTLog("OnVariablesSynchronized " + GetPosition() + " BaseName:'" + m_TWebhook.GetBaseName());
            RPCSingleParam(CFTRPCs.TERRITORY_WEBHOOK_REQUEST, new Param1<bool>(true), true, NULL);
        }
    }

    // =====================================================
    // RPC HANDLER
    // =====================================================
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        Param2<string, string> webhookData;

        // C->S
        if (rpc_type == CFTRPCs.TERRITORY_WEBHOOK_SEND && GetGame().IsServer())
        {
            if (ctx.Read(webhookData))
            {              
                CFTLog("OnRPC [SERVER] WEBHOOK_SEND from client:"+webhookData.param1);
                if (webhookData.param2 == string.Empty)
                {
                    InternalRemoveWebhook();
                }
                else
                {
                    InternalAddWebhook(webhookData.param1, webhookData.param2);
                }
            }
            return;
        }

        // C->S
        if ((rpc_type == CFTRPCs.TERRITORY_WEBHOOK_REQUEST) && GetGame().IsServer())
        {
            CFTLog("OnRPC [SERVER] WEBHOOK_REQUEST from client");
            ForceSync(sender);
        }

        // S->C
        if (rpc_type == CFTRPCs.TERRITORY_WEBHOOK_SEND && GetGame().IsClient())
        {
            if (ctx.Read(webhookData))
            {
                CFTLog("OnRPC [CLIENT] WEBHOOK_SEND from server:" + webhookData.param1);
                if (webhookData.param1 == string.Empty)
                {
                    InternalRemoveWebhook();
                }
                else
                {
                    InternalAddWebhook(webhookData.param1, webhookData.param2);
                }
            }
        }
    }

    // =====================================================
    // PRIVATE FUNCTIONS
    // =====================================================
    private void ForceSync(PlayerIdentity identity = null)
    {
        if (GetGame().IsServer())
        {
            SetSynchDirty();
            RPCSingleParam(CFTRPCs.TERRITORY_WEBHOOK_SEND, new Param2<string, string>(GetBaseName(), GetWebhook()), true, identity);
        }
        else if (GetGame().IsClient())
        {
            RPCSingleParam(CFTRPCs.TERRITORY_WEBHOOK_SEND, new Param2<string, string>(GetBaseName(), GetWebhook()), true, NULL);
        }
        
        CFTLog("ForceSync - BaseName:" + GetBaseName() + " CanAdd:" + m_CanAddWebhook);
    }

    private void InternalAddWebhook(string p_base, string p_webhook)
    {
        m_CanAddWebhook = !m_TWebhook.AddWebhook(p_base, p_webhook);
    }

    private void InternalRemoveWebhook()
    {
        m_CanAddWebhook = m_TWebhook.RemoveWebhook();
    }
}