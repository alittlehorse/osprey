/** @file
 *****************************************************************************
smart contract module
 provide smart contract to libserver.
 The contract address embedded in the platform

 *****************************************************************************
 * @author     This file is part of libserver, developed by xu chen
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>
#include "connectEthereum.h"

using namespace std;
namespace smart_contract{
	int smart_contract::connectEthereum(char const *functionName,char const *args[])
		{
            char const *pName_char;
            PyObject *pName, *pModule, *pFunc;
            PyObject *pArgs,*pValue;
            int i;
            Py_Initialize();
            //判断初始化是否成功
            if(!Py_IsInitialized())
            {
                printf("Python init failed!\n");
            }
            pName_char = "connectEthereum";

            pName = PyUnicode_DecodeFSDefault(pName_char);
            /* Error checking of pName left out */
            pModule = PyImport_Import(pName);
            //Py_DECREF(pName);
		if (pModule != NULL) {
		    pFunc = PyObject_GetAttrString(pModule, functionName);
		    /* pFunc is a new reference */
		    if (pFunc && PyCallable_Check(pFunc)) {
		    	char const **temp_args = args;
			int count = 0;
			while(strcmp(*temp_args,"null")){
				count++;
				temp_args++;
			}
			pArgs = PyTuple_New(count);
			for (i = 0; i < count; ++i) {
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
			    //printf("Result of call: %ld\n", PyLong_AsLong(pValue));
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
		//if (Py_FinalizeEx() < 0) {
		 //   return 120;
		//}
		return 0;
	}
	void smart_contract::SendTxnTransferToContract(string addr,string priv_key,int value){
		char const *args[4];
		args[0] = addr.c_str();
		args[1] = to_string(value).c_str();
		args[2] = priv_key.c_str();
		args[3] = "null";
		connectEthereum("SendTxnTransferToContract",args);
	}
	void smart_contract::SendTxnTransfer(string addr){
		char const *args[2];
		args[0] = addr.c_str();
		args[1] = "null";
		connectEthereum("SendTxnTransfer",args);
	}

    void smart_contract::init() {
        Py_Initialize();
        //判断初始化是否成功
        if(!Py_IsInitialized())
        {
            printf("Python init failed!\n");
        }
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('../../libserver/smart_contract')");
    }
}
