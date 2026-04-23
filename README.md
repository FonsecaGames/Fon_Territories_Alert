# CFTerritoriesAlert

DayZ server mod that adds Discord webhook alerts for ZenTerritories base events.

When a territory is attacked, dismantled, unlocked, or damaged, this mod sends structured Discord embed notifications so territory members can react quickly.

## Features

- Per-territory Discord webhook configuration through in-game UI.
- Webhook is stored with the territory flag and persisted across restarts.
- Automatic item-to-territory linking via `CFTLink` (building parts and locks).
- Periodic territory resync for linked objects and lock attachments.
- Alert events include:
  - Building hit (combat, firearm, explosion, custom)
  - Building part destroyed
  - Building part dismantled
  - Combination lock and codelock damage/destroy
  - Lock unlock event (optional)
- Member filtering option to alert only when attacker is not from the same territory.
- Anti-spam overload handling:
  - Buffers repeated alerts during cooldown.
  - Sends a merged summary with accumulated damage.
- Optional server-side alert logging for debugging.

## Requirements

- DayZ server environment
- ZenTerritories (required addon in config)
- Optional CodeLock integration (auto-detected with preprocessor flag)

## Installation

1. Copy the mod folder (example: `@CFTerritoriesAlert`) to your DayZ server root.
2. Copy the `.bikey` file to the server `keys` folder.
3. Add the mod in the server startup parameter `-mod`, keeping `ZenTerritories` before this mod.
4. Restart the server and confirm both mods are loaded in the startup log.
5. After first boot, check generated config at `$profile:\CFTerritoriesAlert\AlertsConfig.json`.

Example startup parameters:

```bat
-mod=@ZenTerritories;@CFTerritoriesAlert
```

If you use a launcher/panel, add the same mods in this order in the server mod list.

## Configuration

The config is created automatically on first server start:

- Path: $profile:\CFTerritoriesAlert\AlertsConfig.json

Default values are initialized in the script and then saved to JSON.

Example config:

```json
{
  "IntervalInOverload": 60,
  "MaxHistoryOverload": 5,
  "IntervalRefreshLink": 60,
  "MinimumDamageNotify": 0,
  "NotifyUnlock": true,
  "NotifyDamage": true,
  "NotifyDismantle": true,
  "OnlyNonMembers": true,
  "LogAlerts": false
}
```

### Config fields

- IntervalInOverload: Seconds to wait before sending the next alert batch when spam is detected.
- MaxHistoryOverload: Maximum number of buffered messages kept during overload.
- IntervalRefreshLink: Seconds between periodic territory link refresh (minimum enforced: 10 seconds).
- MinimumDamageNotify: Minimum damage threshold for notifications.
- NotifyUnlock: Enables/disables unlock notifications.
- NotifyDamage: Enables/disables damage notifications for structures and locks.
- NotifyDismantle: Enables/disables dismantle notifications.
- OnlyNonMembers: If true, only non-members trigger alerts.
- LogAlerts: Writes alert messages to profile logs for debugging.

## In-Game Usage

1. Go to a territory flag.
2. Use the action Add Webhook (or Remove Webhook if already configured).
3. Enter:
   - Base Name
   - Discord webhook URL (must contain /api/webhooks/)
4. Save.

Only players with territory member-management permission can access this action.

## Discord Payload

Alerts are sent as Discord embeds using REST POST requests to the configured webhook URL.

- Title: Territory Alarm
- Thumbnail: alert icon
- Description: territory name + event details

## Known Notes

- Webhook sending is server-side only.
- There is a short startup delay before webhook delivery is enabled.
- If no webhook is set for a territory, no alerts are sent for that territory.

## Credits

- Author: [Fonseca](https://steamcommunity.com/profiles/76561198172055119/)
- Mod: [Basic Territories Alert](https://steamcommunity.com/sharedfiles/filedetails/?id=3712735166)

## Support me
Consider a donation if you are liking this mod
[PayPal](https://www.paypal.com/donate/?hosted_button_id=SNRA7FRFUVWVW)

## Repack

I higly recommend don't repack this mod, any future update/fix will not be covered and I'll not provide support. You are allowed to repack since you give me the credits and mark my steam user [Fonseca](https://steamcommunity.com/profiles/76561198172055119/) and this mod as original. This follow the Mozilla Public License Version 2.0.
