#include "main.h"

// -- Embeds --

//go:build ignore

#include <switch.h>
#include "internal/mod/mod.h"

SWITCH_MODULE_LOAD_FUNCTION(mod_solod_load);
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_solod_shutdown);
SWITCH_MODULE_DEFINITION(mod_solod, mod_solod_load, mod_solod_shutdown, NULL);

SWITCH_MODULE_LOAD_FUNCTION(mod_solod_load)
{
	/* connect my internal structure to the blank pointer passed to me */
	*module_interface = switch_loadable_module_create_module_interface(pool, modname);
	mod_OnLoad(module_interface);

	/* indicate that the module should continue to be loaded */
	return SWITCH_STATUS_SUCCESS;
}

/*
  Called when the system shuts down
*/
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_solod_shutdown)
{
	return SWITCH_STATUS_SUCCESS;
}

// -- Variables and constants --

// -- Implementation --

int main(void) {
    freeswitch_Init();
}
