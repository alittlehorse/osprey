pragma solidity  ^0.7.0;
 
contract Payable {
    uint256 value;
	// 向合约账户转账 
	function transderToContract() payable public returns(bool){
		if(msg.sender.balance <= msg.value){
		    return false;
		}
        value = msg.value;
		payable(address(this)).transfer(msg.value);
		return true;
	}


	function transfer(bool prover,address _to) public payable returns(bool){
		if(address(this).balance <= msg.value){
			    return false;
			}
		if(prover == true){
			payable(address(uint160(_to))).transfer(value);
		}
		return true;
	}
		function getBalance(address addr) public view returns (uint256){
		return addr.balance;
	}

	fallback() external payable {}

	receive() external payable {}

}
