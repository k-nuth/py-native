// Copyright (c) 2016-present Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/py-native/chain/double_spend_proof.h>

#include <string.h>
#include <kth/capi.h>
#include <kth/capi/chain/double_spend_proof.h>
#include <kth/py-native/capsule_names.h>
#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// PyCapsule destructor — released by GC when the capsule is
// collected. Explicit `destruct` calls set the capsule name to
// "kth.destroyed", so PyCapsule_IsValid returns false and this
// destructor becomes a no-op (no double-free).
void kth_py_native_chain_double_spend_proof_capsule_dtor(PyObject* capsule) {
    if ( ! PyCapsule_IsValid(capsule, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF)) return;
    kth_double_spend_proof_mut_t handle = (kth_double_spend_proof_mut_t)PyCapsule_GetPointer(capsule, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (handle != NULL) kth_chain_double_spend_proof_destruct(handle);
}

PyObject*
kth_py_native_chain_double_spend_proof_construct_default(PyObject* self, PyObject* Py_UNUSED(args)) {
    auto const result = kth_chain_double_spend_proof_construct_default();
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF, kth_py_native_chain_double_spend_proof_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_double_spend_proof_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_double_spend_proof_construct_from_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"reader", (char*)"version", NULL};
    char const* reader_buf = NULL;
    Py_ssize_t reader_size = 0;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "y#I", kwlist, &reader_buf, &reader_size, &version)) {
        return NULL;
    }
    kth_double_spend_proof_mut_t out = NULL;
    kth_error_code_t result = kth_chain_double_spend_proof_construct_from_data((uint8_t const*)reader_buf, (kth_size_t)reader_size, (uint32_t)version, &out);
    if (result != kth_ec_success) {
        PyErr_Format(PyExc_RuntimeError, "kth error code %d", (int)result);
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)out, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF, kth_py_native_chain_double_spend_proof_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_double_spend_proof_destruct(out);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_double_spend_proof_construct(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"out_point", (char*)"spender1", (char*)"spender2", NULL};
    PyObject* py_out_point = NULL;
    PyObject* py_spender1 = NULL;
    PyObject* py_spender2 = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OOO", kwlist, &py_out_point, &py_spender1, &py_spender2)) {
        return NULL;
    }
    kth_output_point_const_t out_point_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_out_point, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (out_point_handle == NULL) return NULL;
    kth_double_spend_proof_spender_const_t spender1_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_spender1, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (spender1_handle == NULL) return NULL;
    kth_double_spend_proof_spender_const_t spender2_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_spender2, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (spender2_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_construct(out_point_handle, spender1_handle, spender2_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF, kth_py_native_chain_double_spend_proof_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_double_spend_proof_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_double_spend_proof_copy(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_const_t self_handle = (kth_double_spend_proof_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_copy(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_MemoryError, "kth: allocation failed");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF, kth_py_native_chain_double_spend_proof_capsule_dtor);
    if (capsule == NULL) {
        kth_chain_double_spend_proof_destruct(result);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_double_spend_proof_destruct(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_mut_t self_handle = (kth_double_spend_proof_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    kth_chain_double_spend_proof_destruct(self_handle);
    PyCapsule_SetName(py_self, "kth.destroyed");
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_equals(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"other", NULL};
    PyObject* py_self = NULL;
    PyObject* py_other = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_other)) {
        return NULL;
    }
    kth_double_spend_proof_const_t self_handle = (kth_double_spend_proof_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    kth_double_spend_proof_const_t other_handle = (kth_double_spend_proof_const_t)PyCapsule_GetPointer(py_other, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (other_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_equals(self_handle, other_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_double_spend_proof_out_point(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_const_t self_handle = (kth_double_spend_proof_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_out_point(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT, kth_py_native_borrowed_parent_dtor);
    if (capsule == NULL) return NULL;
    Py_INCREF(py_self);
    if (PyCapsule_SetContext(capsule, py_self) != 0) {
        Py_DECREF(py_self);
        Py_DECREF(capsule);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_double_spend_proof_set_out_point(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_double_spend_proof_mut_t self_handle = (kth_double_spend_proof_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    kth_output_point_const_t x_handle = (kth_output_point_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_CHAIN_OUTPUT_POINT);
    if (x_handle == NULL) return NULL;
    kth_chain_double_spend_proof_set_out_point(self_handle, x_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender1(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_const_t self_handle = (kth_double_spend_proof_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender1(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER, kth_py_native_borrowed_parent_dtor);
    if (capsule == NULL) return NULL;
    Py_INCREF(py_self);
    if (PyCapsule_SetContext(capsule, py_self) != 0) {
        Py_DECREF(py_self);
        Py_DECREF(capsule);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_double_spend_proof_set_spender1(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_double_spend_proof_mut_t self_handle = (kth_double_spend_proof_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    kth_double_spend_proof_spender_const_t x_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (x_handle == NULL) return NULL;
    kth_chain_double_spend_proof_set_spender1(self_handle, x_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_spender2(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_const_t self_handle = (kth_double_spend_proof_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_spender2(self_handle);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: NULL handle returned");
        return NULL;
    }
    PyObject* capsule = PyCapsule_New((void*)result, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER, kth_py_native_borrowed_parent_dtor);
    if (capsule == NULL) return NULL;
    Py_INCREF(py_self);
    if (PyCapsule_SetContext(capsule, py_self) != 0) {
        Py_DECREF(py_self);
        Py_DECREF(capsule);
        return NULL;
    }
    return capsule;
}

PyObject*
kth_py_native_chain_double_spend_proof_set_spender2(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"x", NULL};
    PyObject* py_self = NULL;
    PyObject* py_x = NULL;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_self, &py_x)) {
        return NULL;
    }
    kth_double_spend_proof_mut_t self_handle = (kth_double_spend_proof_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    kth_double_spend_proof_spender_const_t x_handle = (kth_double_spend_proof_spender_const_t)PyCapsule_GetPointer(py_x, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF_SPENDER);
    if (x_handle == NULL) return NULL;
    kth_chain_double_spend_proof_set_spender2(self_handle, x_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_to_data(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_double_spend_proof_const_t self_handle = (kth_double_spend_proof_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    kth_size_t out_size = 0;
    auto const result = kth_chain_double_spend_proof_to_data(self_handle, (uint32_t)version, &out_size);
    if (result == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "kth: serialization failed");
        return NULL;
    }
    PyObject* py_result = Py_BuildValue("y#", result, (Py_ssize_t)out_size);
    kth_core_destruct_array(result);
    return py_result;
}

PyObject*
kth_py_native_chain_double_spend_proof_is_valid(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_const_t self_handle = (kth_double_spend_proof_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_is_valid(self_handle);
    return PyBool_FromLong((long)result);
}

PyObject*
kth_py_native_chain_double_spend_proof_reset(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_mut_t self_handle = (kth_double_spend_proof_mut_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    kth_chain_double_spend_proof_reset(self_handle);
    Py_RETURN_NONE;
}

PyObject*
kth_py_native_chain_double_spend_proof_serialized_size(PyObject* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {(char*)"self", (char*)"version", NULL};
    PyObject* py_self = NULL;
    unsigned int version = 0;
    if ( ! PyArg_ParseTupleAndKeywords(args, kwds, "OI", kwlist, &py_self, &version)) {
        return NULL;
    }
    kth_double_spend_proof_const_t self_handle = (kth_double_spend_proof_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_serialized_size(self_handle, (uint32_t)version);
    return PyLong_FromSize_t((size_t)result);
}

PyObject*
kth_py_native_chain_double_spend_proof_hash(PyObject* self, PyObject* py_arg0) {
    PyObject* py_self = py_arg0;
    kth_double_spend_proof_const_t self_handle = (kth_double_spend_proof_const_t)PyCapsule_GetPointer(py_self, KTH_PY_CAPSULE_CHAIN_DOUBLE_SPEND_PROOF);
    if (self_handle == NULL) return NULL;
    auto const result = kth_chain_double_spend_proof_hash(self_handle);
    return Py_BuildValue("y#", result.hash, (Py_ssize_t)KTH_BITCOIN_HASH_SIZE);
}

PyMethodDef kth_py_native_chain_double_spend_proof_methods[] = {
    {"chain_double_spend_proof_construct_default", (PyCFunction)kth_py_native_chain_double_spend_proof_construct_default, METH_NOARGS, NULL},
    {"chain_double_spend_proof_construct_from_data", (PyCFunction)kth_py_native_chain_double_spend_proof_construct_from_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_construct", (PyCFunction)kth_py_native_chain_double_spend_proof_construct, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_copy", (PyCFunction)kth_py_native_chain_double_spend_proof_copy, METH_O, NULL},
    {"chain_double_spend_proof_destruct", (PyCFunction)kth_py_native_chain_double_spend_proof_destruct, METH_O, NULL},
    {"chain_double_spend_proof_equals", (PyCFunction)kth_py_native_chain_double_spend_proof_equals, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_out_point", (PyCFunction)kth_py_native_chain_double_spend_proof_out_point, METH_O, NULL},
    {"chain_double_spend_proof_set_out_point", (PyCFunction)kth_py_native_chain_double_spend_proof_set_out_point, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender1", (PyCFunction)kth_py_native_chain_double_spend_proof_spender1, METH_O, NULL},
    {"chain_double_spend_proof_set_spender1", (PyCFunction)kth_py_native_chain_double_spend_proof_set_spender1, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_spender2", (PyCFunction)kth_py_native_chain_double_spend_proof_spender2, METH_O, NULL},
    {"chain_double_spend_proof_set_spender2", (PyCFunction)kth_py_native_chain_double_spend_proof_set_spender2, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_to_data", (PyCFunction)kth_py_native_chain_double_spend_proof_to_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_is_valid", (PyCFunction)kth_py_native_chain_double_spend_proof_is_valid, METH_O, NULL},
    {"chain_double_spend_proof_reset", (PyCFunction)kth_py_native_chain_double_spend_proof_reset, METH_O, NULL},
    {"chain_double_spend_proof_serialized_size", (PyCFunction)kth_py_native_chain_double_spend_proof_serialized_size, METH_VARARGS | METH_KEYWORDS, NULL},
    {"chain_double_spend_proof_hash", (PyCFunction)kth_py_native_chain_double_spend_proof_hash, METH_O, NULL},
    {NULL, NULL, 0, NULL}  // sentinel
};

#ifdef __cplusplus
} // extern "C"
#endif
