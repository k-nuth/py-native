#include <kth/py-native/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

// inline
void* get_ptr(PyObject* obj) {
#if PY_MAJOR_VERSION >= 3
    return PyCapsule_GetPointer(obj, NULL);
#else /* PY_MAJOR_VERSION >= 3 */
    return PyCObject_AsVoidPtr(obj);
#endif /* PY_MAJOR_VERSION >= 3 */
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
#if PY_MAJOR_VERSION >= 3
    return PyCapsule_New(obj, NULL, NULL);
#else /* PY_MAJOR_VERSION >= 3 */
    return PyCObject_FromVoidPtr(obj, NULL);
#endif /* PY_MAJOR_VERSION >= 3 */
}

//inline
// PyObject* to_py_str(char const* str, size_t n) {
PyObject* to_py_str(char const* str) {
    return Py_BuildValue("s", str);

// return Py_BuildValue("y#", str, n);
// return Py_BuildValue("s#", blocks, out_n);
// #if PY_MAJOR_VERSION >= 3
//     return Py_BuildValue("y#", blocks, out_n);
// #else
//     return Py_BuildValue("s#", blocks, out_n);
// #endif

}





#ifdef __cplusplus
} //extern "C"
#endif
