// This file implements the IEnumFORMATETC Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "PyIEnumFORMATETC.h"

extern BOOL PyObject_AsFORMATETC(PyObject *ob, FORMATETC *petc);
extern PyObject *PyObject_FromFORMATETC(FORMATETC *petc);

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyIEnumFORMATETC::PyIEnumFORMATETC(IUnknown *pdisp):
	PyIUnknown(pdisp)
{
	ob_type = &type;
}

PyIEnumFORMATETC::~PyIEnumFORMATETC()
{
}

/* static */ IEnumFORMATETC *PyIEnumFORMATETC::GetI(PyObject *self)
{
	return (IEnumFORMATETC *)PyIUnknown::GetI(self);
}

PyObject *
PyIEnumFORMATETC::iter()
{
	Py_INCREF(this);
	return this;
}

PyObject *
PyIEnumFORMATETC::iternext()
{
	ULONG celtFetched = 0;
	FORMATETC ret;;
	IEnumFORMATETC *peidl = GetI(this);
	if ( peidl == NULL )
		return NULL;
	PY_INTERFACE_PRECALL;
	HRESULT hr = peidl->Next(1, &ret, &celtFetched);
	PY_INTERFACE_POSTCALL;
	if (  HRESULT_CODE(hr) != ERROR_NO_MORE_ITEMS && FAILED(hr) )
		return PyCom_BuildPyException(hr,peidl, IID_IEnumFORMATETC);
	if (celtFetched==0) {
		PyErr_SetNone(PyExc_StopIteration);
		return NULL;
	}
	return PyObject_FromFORMATETC(&ret);
}

// @pymethod object|PyIEnumFORMATETC|Next|Retrieves a specified number of items in the enumeration sequence.
PyObject *PyIEnumFORMATETC::Next(PyObject *self, PyObject *args)
{
	long celt = 1;
	// @pyparm int|num|1|Number of items to retrieve.
	if ( !PyArg_ParseTuple(args, "|l:Next", &celt) )
		return NULL;

	IEnumFORMATETC *peidl = GetI(self);
	if ( peidl == NULL )
		return NULL;

	FORMATETC *rgVar = new FORMATETC[celt];
	if ( rgVar == NULL ) {
		PyErr_SetString(PyExc_MemoryError, "allocating result FORMATETCs");
		return NULL;
	}

	memset(rgVar, 0, sizeof(FORMATETC)*celt);
	ULONG celtFetched = 0;
	PY_INTERFACE_PRECALL;
	HRESULT hr = peidl->Next(celt, rgVar, &celtFetched);
	PY_INTERFACE_POSTCALL;
	if (  HRESULT_CODE(hr) != ERROR_NO_MORE_ITEMS && FAILED(hr) )
	{
		delete [] rgVar;
		return PyCom_BuildPyException(hr,peidl, IID_IEnumFORMATETC);
	}

	PyObject *result = PyList_New(celtFetched);
	int i;
	if ( result != NULL )
	{
		for ( i = celtFetched; i--; )
		{
			PyObject *ob = PyObject_FromFORMATETC(rgVar+i);
			if ( ob == NULL )
			{
				Py_DECREF(result);
				result = NULL;
				break;
			}
			PyList_SET_ITEM(result, i, ob);
		}
	}
	delete [] rgVar;
	return result;
}

// @pymethod |PyIEnumFORMATETC|Skip|Skips over the next specified elementes.
PyObject *PyIEnumFORMATETC::Skip(PyObject *self, PyObject *args)
{
	long celt;
	if ( !PyArg_ParseTuple(args, "l:Skip", &celt) )
		return NULL;

	IEnumFORMATETC *peidl = GetI(self);
	if ( peidl == NULL )
		return NULL;

	PY_INTERFACE_PRECALL;
	HRESULT hr = peidl->Skip(celt);
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, peidl, IID_IEnumFORMATETC);

	Py_INCREF(Py_None);
	return Py_None;
}

// @pymethod |PyIEnumFORMATETC|Reset|Resets the enumeration sequence to the beginning.
PyObject *PyIEnumFORMATETC::Reset(PyObject *self, PyObject *args)
{
	if ( !PyArg_ParseTuple(args, ":Reset") )
		return NULL;

	IEnumFORMATETC *peidl = GetI(self);
	if ( peidl == NULL )
		return NULL;

	PY_INTERFACE_PRECALL;
	HRESULT hr = peidl->Reset();
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, peidl, IID_IEnumFORMATETC);

	Py_INCREF(Py_None);
	return Py_None;
}

// @pymethod <o PyIEnumFORMATETC>|PyIEnumFORMATETC|Clone|Creates another enumerator that contains the same enumeration state as the current one
PyObject *PyIEnumFORMATETC::Clone(PyObject *self, PyObject *args)
{
	if ( !PyArg_ParseTuple(args, ":Clone") )
		return NULL;

	IEnumFORMATETC *peidl = GetI(self);
	if ( peidl == NULL )
		return NULL;

	IEnumFORMATETC *pClone;
	PY_INTERFACE_PRECALL;
	HRESULT hr = peidl->Clone(&pClone);
	PY_INTERFACE_POSTCALL;
	if ( FAILED(hr) )
		return PyCom_BuildPyException(hr, peidl, IID_IEnumFORMATETC);

	return PyCom_PyObjectFromIUnknown(pClone, IID_IEnumFORMATETC, FALSE);
}

// @object PyIEnumFORMATETC|A Python interface to IEnumFORMATETC
static struct PyMethodDef PyIEnumFORMATETC_methods[] =
{
	{ "Next", PyIEnumFORMATETC::Next, 1 },    // @pymeth Next|Retrieves a specified number of items in the enumeration sequence.
	{ "Skip", PyIEnumFORMATETC::Skip, 1 },	// @pymeth Skip|Skips over the next specified elementes.
	{ "Reset", PyIEnumFORMATETC::Reset, 1 },	// @pymeth Reset|Resets the enumeration sequence to the beginning.
	{ "Clone", PyIEnumFORMATETC::Clone, 1 },	// @pymeth Clone|Creates another enumerator that contains the same enumeration state as the current one.
	{ NULL }
};

PyComTypeObject PyIEnumFORMATETC::type("PyIEnumFORMATETC",
		&PyIUnknown::type,
		sizeof(PyIEnumFORMATETC),
		PyIEnumFORMATETC_methods,
		GET_PYCOM_CTOR(PyIEnumFORMATETC));

// ---------------------------------------------------
//
// Gateway Implementation

STDMETHODIMP PyGEnumFORMATETC::Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ FORMATETC *pi,
            /* [out] */ ULONG __RPC_FAR *pCeltFetched)
{
	PY_GATEWAY_METHOD;
	PyObject *result;
	HRESULT hr = InvokeViaPolicy("Next", &result, "i", celt);
	if ( FAILED(hr) )
		return hr;

	if ( !PySequence_Check(result) )
		goto error;
	int len;
	len = PyObject_Length(result);
	if ( len == -1 )
		goto error;
	if ( len > (int)celt)
		len = celt;

	if ( pCeltFetched )
		*pCeltFetched = len;

	int i;
	for ( i = 0; i < len; ++i )
	{
		PyObject *ob = PySequence_GetItem(result, i);
		if ( ob == NULL )
			goto error;

		if ( !PyObject_AsFORMATETC(ob, &pi[i] ))
		{
			Py_DECREF(result);
			return PyCom_SetCOMErrorFromPyException(IID_IEnumFORMATETC);
		}
	}

	Py_DECREF(result);
	return len < (int)celt ? S_FALSE : S_OK;

  error:
	PyErr_Clear();	// just in case
	Py_DECREF(result);
	return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumFORMATETC, "Next() did not return a sequence of objects");
}

STDMETHODIMP PyGEnumFORMATETC::Skip( 
            /* [in] */ ULONG celt)
{
	PY_GATEWAY_METHOD;
	return InvokeViaPolicy("Skip", NULL, "i", celt);
}

STDMETHODIMP PyGEnumFORMATETC::Reset(void)
{
	PY_GATEWAY_METHOD;
	return InvokeViaPolicy("Reset");
}

STDMETHODIMP PyGEnumFORMATETC::Clone( 
            /* [out] */ IEnumFORMATETC __RPC_FAR *__RPC_FAR *ppEnum)
{
	PY_GATEWAY_METHOD;
	PyObject * result;
	HRESULT hr = InvokeViaPolicy("Clone", &result);
	if ( FAILED(hr) )
		return hr;

	/*
	** Make sure we have the right kind of object: we should have some kind
	** of IUnknown subclass wrapped into a PyIUnknown instance.
	*/
	if ( !PyIBase::is_object(result, &PyIUnknown::type) )
	{
		/* the wrong kind of object was returned to us */
		Py_DECREF(result);
		return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumFORMATETC);
	}

	/*
	** Get the IUnknown out of the thing. note that the Python ob maintains
	** a reference, so we don't have to explicitly AddRef() here.
	*/
	IUnknown *punk = ((PyIUnknown *)result)->m_obj;
	if ( !punk )
	{
		/* damn. the object was released. */
		Py_DECREF(result);
		return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumFORMATETC);
	}

	/*
	** Get the interface we want. note it is returned with a refcount.
	** This QI is actually going to instantiate a PyGEnumFORMATETC.
	*/
	Py_BEGIN_ALLOW_THREADS
	hr = punk->QueryInterface(IID_IEnumFORMATETC, (LPVOID *)ppEnum);
	Py_END_ALLOW_THREADS

	/* done with the result; this DECREF is also for <punk> */
	Py_DECREF(result);

	return PyCom_SetCOMErrorFromSimple(hr, IID_IEnumFORMATETC, "Python could not convert the result from Next() into the required COM interface");
}
