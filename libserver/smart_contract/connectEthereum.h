#include <iostream>
#include <string>
using namespace std;
namespace libserver{
	// args:addr, priv_key，value
	void SendTxnTransferToContract(string addr,string priv_key,int value);

	// args:addr
	void SendTxnTransfer(string addr);
}

