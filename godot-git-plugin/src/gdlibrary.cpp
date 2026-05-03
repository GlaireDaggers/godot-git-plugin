#include "git_plugin.h"

#include "godot_cpp/classes/project_settings.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/godot.hpp"

void initialize_git_plugin_module(godot::ModuleInitializationLevel p_level) {
	if (p_level != godot::MODULE_INITIALIZATION_LEVEL_EDITOR) {
		return;
	}

	// register custom settings
	godot::ProjectSettings *settings = godot::ProjectSettings::get_singleton();

	if (!settings->has_setting(SETTING_ENABLE_LFS)) {
		settings->set_setting(SETTING_ENABLE_LFS, SETTING_ENABLE_LFS_DEFAULT);
		settings->set_initial_value(SETTING_ENABLE_LFS, SETTING_ENABLE_LFS_DEFAULT);
		settings->set_as_basic(SETTING_ENABLE_LFS, true);
	}

	if (!settings->has_setting(SETTING_GIT_BIN_PATH)) {
		settings->set_setting(SETTING_GIT_BIN_PATH, SETTING_GIT_BIN_PATH_DEFAULT);
		settings->set_initial_value(SETTING_GIT_BIN_PATH, SETTING_GIT_BIN_PATH_DEFAULT);
		settings->set_as_basic(SETTING_GIT_BIN_PATH, true);
	}

	godot::ClassDB::register_class<GitPlugin>();
}

void uninitialize_git_plugin_module(godot::ModuleInitializationLevel p_level) {
	if (p_level != godot::MODULE_INITIALIZATION_LEVEL_EDITOR) {
		return;
	}
}

extern "C" {

GDExtensionBool GDE_EXPORT git_plugin_init(const GDExtensionInterfaceGetProcAddress p_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_git_plugin_module);
	init_obj.register_terminator(uninitialize_git_plugin_module);
	init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_EDITOR);

	return init_obj.init();
}
}
