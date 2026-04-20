modded class PluginManager {
	override void Init() {
		super.Init();

		RegisterPlugin("CFTUIManager", true, false);
	}
}