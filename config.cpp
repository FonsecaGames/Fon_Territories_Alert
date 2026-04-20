class CfgPatches
{
    class CFTerritoriesAlert
    {
        units[]          = {};
        weapons[]        = {};
        requiredVersion  = 0.1;
        requiredAddons[] = { "DZ_Data", "DZ_Scripts", "ZenTerritories" };
    };
};

class CfgMods
{
    class CFTerritoriesAlert
    {
        dir         = "CFTerritoriesAlert";
        picture     = "";
        action      = "";
        hideName    = 0;
        hidePicture = 0;
        name        = "Territories Alert";
        credits     = "Fonseca";
        author      = "Fonseca";
        authorID    = "76561198172055119";
        version     = "1.0.0";
        extra       = 0;
        type        = "mod";

        dependencies[] = { "Game", "World", "Mission" };

        class defs
        {
            class gameScriptModule
            {
                value  = "";
                files[] = { "CFTerritoriesAlert/scripts/3_Game" };
            };
            class worldScriptModule
            {
                value  = "";
                files[] = { "CFTerritoriesAlert/scripts/4_World" };
            };
            class missionScriptModule
            {
                value  = "";
                files[] = { "CFTerritoriesAlert/scripts/5_Mission" };
            };
        };
    };
};
