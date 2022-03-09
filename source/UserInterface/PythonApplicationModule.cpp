// search for:
#ifdef USE_OPENID
	PyModule_AddIntConstant(poModule, "USE_OPENID",	1);
	if (openid_test)
		PyModule_AddIntConstant(poModule, "OPENID_TEST",	1);
	else
		PyModule_AddIntConstant(poModule, "OPENID_TEST",	0);
#else
	PyModule_AddIntConstant(poModule, "USE_OPENID",	0);
	PyModule_AddIntConstant(poModule, "OPENID_TEST",	0);
#endif /* USE_OPENID */

// add under:
#ifdef ENABLE_CPP_PSM
	PyModule_AddIntConstant(poModule, "ENABLE_CPP_PSM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_CPP_PSM", 0);
#endif