// replace:
PyObject * chrmgrRegisterCacheMotionData(PyObject* poSelf, PyObject* poArgs)
{
	[...]
}

PyObject * chrmgrRegisterMotionData(PyObject* poSelf, PyObject* poArgs)
{
	[...]
}

// with:
#ifndef ENABLE_CPP_PSM
PyObject * chrmgrRegisterCacheMotionData(PyObject* poSelf, PyObject* poArgs)
{
	[...]
}

PyObject * chrmgrRegisterMotionData(PyObject* poSelf, PyObject* poArgs)
{
	[...]
}
#endif

// replace:
		{ "RegisterMotionData",			chrmgrRegisterMotionData,				METH_VARARGS },

// with:
#ifndef ENABLE_CPP_PSM
		{ "RegisterMotionData",			chrmgrRegisterMotionData,				METH_VARARGS },
#endif

// replace:
		{ "RegisterCacheMotionData",	chrmgrRegisterCacheMotionData,			METH_VARARGS },

// with:
#ifndef ENABLE_CPP_PSM
		{ "RegisterCacheMotionData",	chrmgrRegisterCacheMotionData,			METH_VARARGS },
#endif