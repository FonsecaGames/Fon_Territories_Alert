class CFTerritoryAlarmConfig
{
    private int IntervalInOverload;
    private int MaxHistoryOverload;
    private float MinimumDamageNotify;  // Prevent notify melle damage or punch
    private float IntervalRefreshLink;
    private bool NotifyUnlock;          // for CombinationLocks
    private bool NotifyDamage;
    private bool NotifyDismantle;
    private bool OnlyNonMembers;
    private bool LogAlerts;

    void CFTerritoryAlarmConfig()
    {
        IntervalInOverload = 60;            // When multiple alerts came only will send the next after this time in seconds
        MaxHistoryOverload = 5;             // Will show only the first 5 logs if overload
        IntervalRefreshLink = 60;           // Interval check itens (building and lockers) linked to territory
        MinimumDamageNotify = 0;            // Minimum Hp damage on objects, if 0 will show everything
        NotifyUnlock = true;                // Applied only to CombinationLock, when someone find the correct combination and unlock will alert
        NotifyDamage = true;                // Enable/Disable notify damage on parts
        NotifyDismantle = true;             // Enable/Disable notify dismantle on parts
        OnlyNonMembers = true;              // Allow only non members to alert the territory, otherwise everytbody will alert the territory
        LogAlerts = false;                  // Print the alerts on profile log (recommended when testing)
    }

    void PrintValues()
    {
        CFTLog("IntervalInOverload:" + IntervalInOverload);
        CFTLog("MaxHistoryOverload:" + MaxHistoryOverload);
        CFTLog("IntervalRefreshLink:" + IntervalRefreshLink);
        CFTLog("MinimumDamageNotify:" + MinimumDamageNotify);
        CFTLog("MinimumDamageNotify:" + MinimumDamageNotify);
        CFTLog("NotifyUnlock:" + NotifyUnlock);
        CFTLog("NotifyDamage:" + NotifyDamage);
        CFTLog("NotifyDismantle:" + NotifyDismantle);
        CFTLog("OnlyNonMembers:" + OnlyNonMembers);
        CFTLog("LogAlerts:" + LogAlerts);
    }

    int GetIntervalInOverload()
    {
        return IntervalInOverload;
    }

    int GetMaxHistoryOverload()
    {
        return MaxHistoryOverload;
    }

    float GetMinimumDamageNotify()
    {
        return MinimumDamageNotify;
    }

    float GetIntervalRefreshLink()
    {
        if (IntervalRefreshLink < 10) IntervalRefreshLink = 10;
        return IntervalRefreshLink;
    }

    bool CanNotifyUnlock()
    {
        return NotifyUnlock;
    }

    bool CanNotifyDamage()
    {
        return NotifyDamage;
    }

    bool CanNotifyDismantle()
    {
        return NotifyDismantle;
    }

    bool CanLogAlerts()
    {
        return LogAlerts;
    }
    
    bool CanOnlyNonMembers()
    {
        return OnlyNonMembers;
    }

}