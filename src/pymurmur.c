#ifndef PYMURMUR_MODULE_VERSION
#define PYMURMUR_MODULE_VERSION "v0.1.0"
#endif // PYMURMUR_MODULE_VERSION

#define Py_LIMITED_API 0x030700F0L
#define PY_SSIZE_T_CLEAN

#include "Python.h"

#include "MurmurHash1.h"
#include "endian.h"

/**
 * 使用MurmurHash1算法计算哈希值
 *
 * 该函数通过Python接口调用，用于计算给定数据的MurmurHash1哈希值它接受数据和长度作为输入参数，
 * 并返回计算得到的哈希值
 *
 * @param self Python扩展函数的自我引用，未使用
 * @param args 包含调用参数的元组
 * @return 返回一个包含计算结果的PyObject对象，出错则返回NULL
 */
static PyObject *pymurmur_murmur1(PyObject *self, PyObject *args) {
    // 提取输入参数data和length，分别表示要哈希的数据和数据长度
    char *data;
    int length;
    if (!PyArg_ParseTuple(args, "y#", &data, &length)) {
        return NULL;
    }

    // 使用MurmurHash1算法计算哈希值，传入数据、长度和种子值0
    uint32_t value = MurmurHash1(data, length, 0);
    // 将计算得到的哈希值转换为小端字节序
    value = htole32(value);
    // 创建一个包含计算结果的Python字节对象，并返回
    PyObject *ret = PyBytes_FromStringAndSize((const char *)&value, sizeof(value));
    if (NULL == ret) {
        return NULL;
    }
    return ret;
}

static PyMethodDef pymurmur_methods[] = {
    {
        .ml_name = "murmur1",
        .ml_meth = pymurmur_murmur1,
        .ml_flags = METH_VARARGS,
        .ml_doc = "MurmurHash1 algorithm implementation",
    },
    {NULL, NULL, 0, NULL},
};

static struct PyModuleDef pymurmur_module_def = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "pymurmur",
    .m_doc = "Python binding to murmur hash algorithms",
    .m_size = -1,
    .m_methods = pymurmur_methods,
};

PyMODINIT_FUNC PyInit_pymurmur(void) {
    PyObject *module = PyModule_Create(&pymurmur_module_def);
    if (NULL == module) {
        PyErr_SetString(PyExc_Exception, "Failed to create pymurmur module");
        return NULL;
    }

    PyObject *version = PyUnicode_FromString(PYMURMUR_MODULE_VERSION);
    if (NULL == version) {
        PyErr_SetString(PyExc_Exception, "Failed to create version string");
        return NULL;
    }

    if (PyObject_SetAttrString(module, "__version__", version)) {
        PyErr_SetString(PyExc_Exception, "Failed to set __version__ attribute for module");
        return NULL;
    }

    Py_DECREF(version);
    return module;
}
