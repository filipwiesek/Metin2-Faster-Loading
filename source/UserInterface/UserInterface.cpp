// search for:
#include "CheckLatestFiles.h"

// add under:
#ifdef ENABLE_CPP_PSM
#include "PythonPlayerSettingsModule.h"
#endif

// search for:
initServerStateChecker();

// add under:
#ifdef ENABLE_CPP_PSM
	initplayersettingsmodule();
#endif