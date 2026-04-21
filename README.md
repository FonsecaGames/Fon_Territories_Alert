# CFTerritoriesAlert

DayZ server mod that adds Discord webhook alerts for ZenTerritories base events.

When a territory is attacked, dismantled, unlocked, or damaged, this mod sends structured Discord embed notifications so territory members can react quickly.

## Features

- Per-territory Discord webhook configuration through in-game UI.
- Webhook is stored with the territory flag and persisted across restarts.
- Alert events include:
  - Building hit (combat, firearm, explosion, custom)
  - Building part dismantled
  - Combination lock and codelock damage/destroy
  - Lock unlock event (optional)
- Anti-spam overload handling:
  - Buffers repeated alerts during cooldown.
  - Sends a merged summary with accumulated damage.
- Optional server-side alert logging for debugging.

## Requirements

- DayZ server environment
- ZenTerritories (required addon in config)
- Optional CodeLock integration (auto-detected with preprocessor flag)

## Installation

1. Build/sign the mod package with your existing build pipeline.
2. Deploy the generated PBO(s) to your server mod folder.
3. Add the mod to server startup parameters.
4. Ensure ZenTerritories is loaded before this mod.
5. Start the server once to generate the config file.

## Configuration

The config is created automatically on first server start:

- Path: $profile:\CFTerritoriesAlert\AlertsConfig.json

Default values are initialized in the script and then saved to JSON.

Example config:

```json
{
  "IntervalInOverload": 60,
  "MaxHistoryOverload": 5,
  "IntervalCheckTerritoryObjects": 60,
  "MinimumDamageNotify": 0,
  "NotifyUnlock": true,
  "LogAlerts": false
}
```

### Config fields

- IntervalInOverload: Seconds to wait before sending the next alert batch when spam is detected.
- MaxHistoryOverload: Maximum number of buffered messages kept during overload.
- IntervalCheckTerritoryObjects: Interval (seconds) for territory scan and object assignment.
- MinimumDamageNotify: Minimum damage threshold for notifications.
- NotifyUnlock: Enables/disables unlock notifications.
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

## Development

### Project structure

- scripts/3_Game: shared logic, Discord payload builder, webhook sender, config model
- scripts/4_World: gameplay hooks, actions, UI plugin/menu, territory/object linkage
- scripts/5_Mission: server config load/save bootstrap
- tools: local development scripts (build, run, log monitor)

### Log monitor script

A Python helper is included to monitor rotating DayZ logs and auto-switch to the newest file.

Run:

```bash
python tools/monitor_dayz_log.py /path/to/log/folder
```

File pattern watched:

- script_YYYY-MM-DD_HH-MM-SS.log

Behavior:

- Tails the current newest file
- Clears the terminal when a newer log file appears
- Continues printing only the newest file contents

## Known Notes

- Webhook sending is server-side only.
- There is a short startup delay before webhook delivery is enabled.
- If no webhook is set for a territory, no alerts are sent for that territory.

## Credits

- Author: Fonseca
- Mod: Territories Alert

## License

See LICENSE.txt.
