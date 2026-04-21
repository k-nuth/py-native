#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// inline
void* get_ptr(PyObject* obj) {
    return PyCapsule_GetPointer(obj, NULL);
}

// inline
kth_node_t cast_node(PyObject* obj) {
    return (kth_node_t)get_ptr(obj);
}

int char2int(char input) {
    if (input >= '0' && input <= '9')
        return input - '0';
    if (input >= 'A' && input <= 'F')
        return input - 'A' + 10;
    if (input >= 'a' && input <= 'f')
        return input - 'a' + 10;
    return 0;
}

void hex2bin(const char* src, uint8_t* target) {
    int i=0;
    while (*src && src[1]) {
        *(target--) = char2int(*src) * 16 + char2int(src[1]);
        src += 2;
        i++;
    }
}

// inline
PyObject* to_py_obj(void* obj) {
    return PyCapsule_New(obj, NULL, NULL);
}

//inline
PyObject* to_py_str(char const* str) {
    return Py_BuildValue("s", str);
}

void kth_py_native_borrowed_parent_dtor(PyObject* capsule) {
    // The child capsule holds a strong reference to its parent in the
    // PyCapsule context (not the pointer — that's the borrowed handle).
    // Release the parent reference on GC so the parent can finally be
    // collected once every child view of it is gone. Borrowed children
    // never own the native payload, so there's nothing to `destruct()`
    // on the capsule pointer itself.
    PyObject* parent = (PyObject*)PyCapsule_GetContext(capsule);
    Py_XDECREF(parent);
}

#ifdef __cplusplus
} //extern "C"
#endif
