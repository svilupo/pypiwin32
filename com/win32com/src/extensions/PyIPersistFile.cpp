// This file implements the IPersistFile Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "PyIPersist.h"
#include "PyIPersistFile.h"

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIPersistFile::PyIPersistFile(IUnknown *pdisp):
	PyIPersist(pdisp)
{
	ob_type = &type;
}

PyIPersistFile::~PyIPersistFile()
{
}

/* static */ IPersistFile *PyIPersistFile::GetI(PyObject *self)
{
	return (IPersistFile *)PyIPersist::GetI(self);
}

// @pymethod |PyIPersistFile|IsDirty|Checks an object for changes since it was last saved to its current file.
PyObject *PyIPersistFile::IsDirty(PyObject *self, PyObject *args)
{
	IPersistFile *pIPF = GetI(self);
	if ( pIPF == NULL )
		return NULL;
	if ( !PyArg_ParseTuple(args, ":IsDirty") )
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIPF->IsDirty( );
	PY_INTERFACE_POSTCALL;

	// @rdesc This method returns the raw COM error code without raising the normal COM exception.
	// You should treat any error return codes as an indication that the object has changed. 
	// Unless this method explicitly returns S_FALSE, assume that the object must be saved.
	return PyInt_FromLong(hr);
}

// @pymethod |PyIPersistFile|Load|Opens the specified file and initializes an object from the file contents.
PyObject *PyIPersistFile::Load(PyObject *self, PyObject *args)
{
	IPersistFile *pIPF = GetI(self);
	if ( pIPF == NULL )
		return NULL;
	// @pyparm <o unicode>|pszFileName||Absolute path of the file to open
	// @pyparm int|dwMode|STGM_READ|Specifies the access mode from the STGM enumeration.
	PyObject *obpszFileName;
	LPOLESTR pszFileName;
	DWORD dwMode = STGM_READ;
	if ( !PyArg_ParseTuple(args, "O|l:Load", &obpszFileName, &dwMode) )
		return NULL;
	BOOL bPythonIsHappy = TRUE;
	if (!PyWinObject_AsBstr(obpszFileName, &pszFileName)) bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIPF->Load( pszFileName, dwMode );
	PY_INTERFACE_POSTCALL;
	SysFreeString(pszFileName);

	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIPF, IID_IPersistFile);
	Py_INCREF(Py_None);
	return Py_None;

}

// @pymethod |PyIPersistFile|Save|Saves the object into the specified file.
PyObject *PyIPersistFile::Save(PyObject *self, PyObject *args)
{
	IPersistFile *pIPF = GetI(self);
	if ( pIPF == NULL )
		return NULL;
	// @pyparm <o unicode>|pszFileName||absolute path of the file where the object is saved.
	// @pyparm int|fRemember||Specifies whether the file is to be the current working file or not.
	PyObject *obpszFileName;
	LPOLESTR pszFileName;
	BOOL fRemember;
	if ( !PyArg_ParseTuple(args, "Oi:Save", &obpszFileName, &fRemember) )
		return NULL;
	BOOL bPythonIsHappy = TRUE;
	if (!PyWinObject_AsBstr(obpszFileName, &pszFileName, TRUE)) bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIPF->Save( pszFileName, fRemember );
	PY_INTERFACE_POSTCALL;
	SysFreeString(pszFileName);

	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIPF, IID_IPersistFile);
	Py_INCREF(Py_None);
	return Py_None;

}

// @pymethod |PyIPersistFile|SaveCompleted|Notifies the object that it can revert from NoScribble mode to Normal mode.
PyObject *PyIPersistFile::SaveCompleted(PyObject *self, PyObject *args)
{
	IPersistFile *pIPF = GetI(self);
	if ( pIPF == NULL )
		return NULL;
	// @pyparm <o unicode>|pszFileName||Absolute path of the file where the object was saved.
	PyObject *obpszFileName;
	LPOLESTR pszFileName;
	if ( !PyArg_ParseTuple(args, "O:SaveCompleted", &obpszFileName) )
		return NULL;
	BOOL bPythonIsHappy = TRUE;
	if (!PyWinObject_AsBstr(obpszFileName, &pszFileName)) bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIPF->SaveCompleted( pszFileName );
	PY_INTERFACE_POSTCALL;
	SysFreeString(pszFileName);

	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIPF, IID_IPersistFile);
	Py_INCREF(Py_None);
	return Py_None;

}

// @pymethod <o unicode>|PyIPersistFile|GetCurFile|Gets the current name of the file associated with the object.
PyObject *PyIPersistFile::GetCurFile(PyObject *self, PyObject *args)
{
	IPersistFile *pIPF = GetI(self);
	if ( pIPF == NULL )
		return NULL;
	LPOLESTR ppszFileName;
	if ( !PyArg_ParseTuple(args, ":GetCurFile") )
		return NULL;
	HRESULT hr;
	PY_INTERFACE_PRECALL;
	hr = pIPF->GetCurFile( &ppszFileName );
	PY_INTERFACE_POSTCALL;

	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, pIPF, IID_IPersistFile);
	PyObject *obppszFileName;

	obppszFileName = MakeOLECHARToObj(ppszFileName);
	PyObject *pyretval = Py_BuildValue("O", obppszFileName);
	Py_XDECREF(obppszFileName);
	CoTaskMemFree(ppszFileName);
	return pyretval;
}

// @object PyIPersistFile|Description of the interface
static struct PyMethodDef PyIPersistFile_methods[] =
{
	{ "IsDirty", PyIPersistFile::IsDirty, 1 }, // @pymeth IsDirty|Checks an object for changes since it was last saved to its current file.
	{ "Load", PyIPersistFile::Load, 1 }, // @pymeth Load|Opens the specified file and initializes an object from the file contents.
	{ "Save", PyIPersistFile::Save, 1 }, // @pymeth Save|Saves the object into the specified file.
	{ "SaveCompleted", PyIPersistFile::SaveCompleted, 1 }, // @pymeth SaveCompleted|Notifies the object that it can revert from NoScribble mode to Normal mode.
	{ "GetCurFile", PyIPersistFile::GetCurFile, 1 }, // @pymeth GetCurFile|Gets the current name of the file associated with the object.
	{ NULL }
};

PyComTypeObject PyIPersistFile::type("PyIPersistFile",
		&PyIPersist::type,
		sizeof(PyIPersistFile),
		PyIPersistFile_methods,
		GET_PYCOM_CTOR(PyIPersistFile));
// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGPersistFile::IsDirty(
		void)
{
	PY_GATEWAY_METHOD;
	HRESULT hr=InvokeViaPolicy("IsDirty", NULL);
	return hr;
}

STDMETHODIMP PyGPersistFile::Load(
		/* [in] */ LPCOLESTR pszFileName,
		/* [in] */ DWORD dwMode)
{
	PY_GATEWAY_METHOD;
	PyObject *obpszFileName;
	obpszFileName = MakeOLECHARToObj(pszFileName);
	HRESULT hr=InvokeViaPolicy("Load", NULL, "Ol", obpszFileName, dwMode);
	Py_XDECREF(obpszFileName);
	return hr;
}

STDMETHODIMP PyGPersistFile::Save(
		/* [unique][in] */ LPCOLESTR pszFileName,
		/* [in] */ BOOL fRemember)
{
	PY_GATEWAY_METHOD;
	PyObject *obpszFileName;
	obpszFileName = MakeOLECHARToObj(pszFileName);
	HRESULT hr=InvokeViaPolicy("Save", NULL, "Oi", obpszFileName, fRemember);
	Py_XDECREF(obpszFileName);
	return hr;
}

STDMETHODIMP PyGPersistFile::SaveCompleted(
		/* [unique][in] */ LPCOLESTR pszFileName)
{
	PY_GATEWAY_METHOD;
	PyObject *obpszFileName;
	obpszFileName = MakeOLECHARToObj(pszFileName);
	HRESULT hr=InvokeViaPolicy("SaveCompleted", NULL, "O", obpszFileName);
	Py_XDECREF(obpszFileName);
	return hr;
}

STDMETHODIMP PyGPersistFile::GetCurFile(
		/* [out] */ LPOLESTR __RPC_FAR * ppszFileName)
{
	PY_GATEWAY_METHOD;
	PyObject *result;
	HRESULT hr=InvokeViaPolicy("GetCurFile", &result);
	if (FAILED(hr)) return hr;
	// Process the Python results, and convert back to the real params
	PyObject *obppszFileName;
	if (!PyArg_Parse(result, "O" , &obppszFileName)) return PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
	BOOL bPythonIsHappy = TRUE;
	if (!PyWinObject_AsBstr(obppszFileName, ppszFileName)) bPythonIsHappy = FALSE;
	if (!bPythonIsHappy) hr = PyCom_HandlePythonFailureToCOM(/*pexcepinfo*/);
	Py_DECREF(result);
	return hr;
}

