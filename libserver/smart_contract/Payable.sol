pragma solidity  ^0.7.0;
 
contract Payable {
 
	uint256 value;
	function getBalance(address addr) public view returns (uint256){
		return addr.balance;
	}

	// 向合约账户转账 
	function transderToContract() payable public {
		value = msg.value;
		payable(address(this)).transfer(msg.value);
	}


	function transfer(bool prover,address _to) public payable{
		if(prover == true){
			payable(address(uint160(_to))).transfer(value);
		}
	}

	fallback() external payable {}

	receive() external payable {}

}
