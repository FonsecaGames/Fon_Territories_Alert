class CFTerritoryAlarmConfig
{
    private int IntervalInOverload;
    private int MaxHistoryOverload;
    private int IntervalCheckTerritoryObjects;
    private float MinimumDamageNotify;  // Prevent notify melle damage or punch
    private bool NotifyUnlock;          // for CombinationLocks
    private bool LogAlerts;

    void CFTerritoryAlarmConfig()
    {
        IntervalInOverload = 60;            // When multiple alerts came only will send the next after this time in seconds
        MaxHistoryOverload = 5;             // Will show only the first 5 logs if overload
        IntervalCheckTerritoryObjects = 60; // The territory flag will scan inside it radius to assign the territory to objects, don't set to low can cause server starvation
        MinimumDamageNotify = 0;            // Minimum Hp damage on objects, if 0 will show everything
        NotifyUnlock = true;                // Applied only to CombinationLock, when someone find the correct combination and unlock will alert
        LogAlerts = false;                  // Print the alerts on profile log (recommended when testing)
    }

    void PrintValues()
    {
        CFTLog("IntervalInOverload:" + IntervalInOverload);
        CFTLog("MaxHistoryOverload:" + MaxHistoryOverload);
        CFTLog("IntervalCheckTerritoryObjects:" + IntervalCheckTerritoryObjects);
        CFTLog("MinimumDamageNotify:" + MinimumDamageNotify);
        CFTLog("MinimumDamageNotify:" + MinimumDamageNotify);
        CFTLog("NotifyUnlock:" + NotifyUnlock);
    }

    int GetIntervalInOverload()
    {
        return IntervalInOverload;
    }

    int GetMaxHistoryOverload()
    {
        return MaxHistoryOverload;
    }

    int GetIntervalCheckTerritoryObjects()
    {
        return IntervalCheckTerritoryObjects;
    }

    float GetMinimumDamageNotify()
    {
        return MinimumDamageNotify;
    }

    bool CanNotifyUnlock()
    {
        return NotifyUnlock;
    }

    bool CanLogAlerts()
    {
        return LogAlerts;
    }
    
}