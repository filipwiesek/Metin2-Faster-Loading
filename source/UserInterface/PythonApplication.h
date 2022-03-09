// search for:
#include "MovieMan.h"

// add under:
#ifdef ENABLE_CPP_PSM
#include "PythonPlayerSettingsModule.h"
#endif

// search for:
		CPythonSystem				m_pySystem;

// add under:
#ifdef ENABLE_CPP_PSM
		CPlayerSettingsModule		m_pyPlayerSettingsModule;
#endif