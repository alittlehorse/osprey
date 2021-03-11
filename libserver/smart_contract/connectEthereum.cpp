#define PY_SSIZE_T_CLEAN
#include <Python.h>

int connectEthereum(char const *functionName,char const *args[])
{
    char const *pName_char = "connectEthereum";
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs,*pValue;
    int i,count=0;
    
    Py_Initialize();
    //判断初始化是否成功
    if(!Py_IsInitialized())
    {
        printf("Python init failed!\n");
        return -1;
    }
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('../')");
    pName = PyUnicode_DecodeFSDefault(pName_char);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, functionName);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            char const **temp = args;
            	
            while(*temp != NULL){
               count++;
               temp++;
            }
            pArgs = PyTuple_New(count-1);
            for (i = 0; i < count-1; ++i) {
                pValue = PyUnicode_FromString(args[i]);
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", functionName);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", pName_char);
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}
