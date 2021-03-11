#include "connectEthereum.h"


int main(){
	// SendTxnGetBalance 获取账户余额  args:to_addr
	char const *functionName = "SendTxnGetBalance";
	char const *args[] = {"0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e"};
	
	// SendTxnTransferToContract 买方转账   args:from_addr,value,from_addr_priv_key
	//char const *functionName = "SendTxnTransferToContract";
	//char const *args[] = {"0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e","1000000","0xfabde6ac6b55fc46677d9453545e699b0cfe3a244a4418e357c97e6a3f56ec9d"};
	
	// SendTxnTransfer 转账给卖方
	//char const *functionName = "SendTxnTransfer";   args:addr
	//char const *args[] = {"0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e"};


	libserver::connectEthereum(functionName,args);
	return 0;
}

