#include <iostream>
#include <string>
#include <Python.h>
using namespace std;
namespace libserver{
    class smart_contract{
    public:
        smart_contract();
        // args:addr, priv_key，value
        void SendTxnTransferToContract(string addr,string priv_key,int value);

        // args:addr
        void SendTxnTransfer(string addr);
        int connectEthereum(char const *functionName,char const *args[]);

    private:
        char const *pName_char;
        PyObject *pName, *pModule, *pFunc;
        PyObject *pArgs,*pValue;
        int i;
    };

}

