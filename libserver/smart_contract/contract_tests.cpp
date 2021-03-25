#include "connectEthereum.h"


int main(){
    smart_contract::smart_contract::init();
    smart_contract::smart_contract::SendTxnTransferToContract("0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e","0xfabde6ac6b55fc46677d9453545e699b0cfe3a244a4418e357c97e6a3f56ec9d",1000000);

    smart_contract::smart_contract::SendTxnTransfer("0x57128a8c478B3fEab65866a9c39d06408c243ce9");
	return 0;
}

