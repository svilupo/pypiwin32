// This file declares the IPropertyStorage Interface and Gateway for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration

class PyIPropertyStorage : public PyIEnumProvider
{
public:
	MAKE_PYCOM_CTOR(PyIPropertyStorage);
	static IPropertyStorage *GetI(PyObject *self);
	static PyComEnumProviderTypeObject type;

	// The Python methods
	static PyObject *ReadMultiple(PyObject *self, PyObject *args);
	static PyObject *WriteMultiple(PyObject *self, PyObject *args);
	static PyObject *DeleteMultiple(PyObject *self, PyObject *args);
	static PyObject *ReadPropertyNames(PyObject *self, PyObject *args);
	static PyObject *WritePropertyNames(PyObject *self, PyObject *args);
	static PyObject *DeletePropertyNames(PyObject *self, PyObject *args);
	static PyObject *Commit(PyObject *self, PyObject *args);
	static PyObject *Revert(PyObject *self, PyObject *args);
	static PyObject *Enum(PyObject *self, PyObject *args);
	static PyObject *SetTimes(PyObject *self, PyObject *args);
	static PyObject *SetClass(PyObject *self, PyObject *args);
	static PyObject *Stat(PyObject *self, PyObject *args);

protected:
	PyIPropertyStorage(IUnknown *pdisp);
	~PyIPropertyStorage();
};
