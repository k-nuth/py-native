#ifndef KTH_PY_NATIVE_UTILS_H_
#define KTH_PY_NATIVE_UTILS_H_


#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <kth/capi.h>

#ifdef __cplusplus
extern "C" {
#endif

void* get_ptr(PyObject* obj);
kth_node_t cast_node(PyObject* obj);
int char2int(char input);
void hex2bin(const char* src, uint8_t* target);
PyObject* to_py_obj(void*);

// PyObject* to_py_str(char const* str, size_t n);
PyObject* to_py_str(char const* str);

// return Py_BuildValue("s#", blocks, out_n);

// PyCapsule destructor for *borrowed* child capsules that point into a
// parent's internal storage (e.g. `script.operations()`,
// `block.transaction_nth(i)`, `history_compact.point()`, ...).
//
// The child capsule keeps a strong reference to the parent capsule in
// its PyCapsule context; this destructor decrements that reference
// when Python GC's the child so the parent is free to go. The combo
// prevents the classic dangling-borrow: a caller that released the
// parent while still holding a borrowed child used to get a
// use-after-free on the next access. Generator-driven wrappers that
// return a borrowed view set this destructor and stash the parent
// `py_self` via `PyCapsule_SetContext`.
void kth_py_native_borrowed_parent_dtor(PyObject* capsule);

// The wallet-wrapper stack-scrub helper now lives in the C-API as
// `kth_core_secure_zero` (kth/capi/secure_memory.h). Every high-level
// binding shares the same portable implementation; removing the
// py-native copy avoids drift across bindings.

#ifdef __cplusplus
} //extern "C"
#endif

#endif
