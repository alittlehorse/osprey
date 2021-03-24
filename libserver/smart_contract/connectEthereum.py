# -*- coding:utf-8 -*-

from web3 import Web3, HTTPProvider

true = True
false = False
contract_addr="0x090cf53dEe2C6ab1B8d5ad02B08e60fcdae728A1" # 合约地址
config = {
    "abi":[
	{
		"inputs": [],
		"name": "transderToContract",
		"outputs": [
			{
				"internalType": "bool",
				"name": "",
				"type": "bool"
			}
		],
		"stateMutability": "payable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "bool",
				"name": "prover",
				"type": "bool"
			},
			{
				"internalType": "address",
				"name": "_to",
				"type": "address"
			}
		],
		"name": "transfer",
		"outputs": [
			{
				"internalType": "bool",
				"name": "",
				"type": "bool"
			}
		],
		"stateMutability": "payable",
		"type": "function"
	},
	{
		"stateMutability": "payable",
		"type": "receive"
	},
	{
		"stateMutability": "payable",
		"type": "fallback"
	},
	{
		"inputs": [
			{
				"internalType": "address",
				"name": "addr",
				"type": "address"
			}
		],
		"name": "getBalance",
		"outputs": [
			{
				"internalType": "uint256",
				"name": "",
				"type": "uint256"
			}
		],
		"stateMutability": "view",
		"type": "function"
	}
],
    "address":contract_addr 
}

INFURA_api = "https://goerli.infura.io/v3/d9651a5bfd4548ba8c331e7723b79232" # INFURA的goerli API地址

web3 = Web3(HTTPProvider(INFURA_api))
contract_instance = web3.eth.contract(address=config['address'], abi=config['abi'])


my_addr = "0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e" # 协议部署方地址

priv_key = "0xfabde6ac6b55fc46677d9453545e699b0cfe3a244a4418e357c97e6a3f56ec9d" # 协议部署方私钥

#print(web3.isConnected())

def SendTxn(txn,priv_key):
    signed_txn = web3.eth.account.signTransaction(txn,private_key=priv_key)
    try:
    	res  = web3.eth.sendRawTransaction(signed_txn.rawTransaction).hex()
    except ValueError:
    	print("insufficient funds for gas * price + value")
    	return "error"
    txn_receipt = web3.eth.waitForTransactionReceipt(res)
    return "success"
 
def SendTxnTransfer(other_addr):
	before_other_addr_balance = web3.eth.getBalance(other_addr)
	before_contract_balance = web3.eth.getBalance(contract_addr)
	txn = contract_instance.functions.transfer(true,other_addr).buildTransaction(
	    {
		'chainId':5,
		'nonce':web3.eth.getTransactionCount(my_addr),
		'gas':76000,
		'value':Web3.toWei(0,'wei'),
		'gasPrice':web3.eth.gasPrice,
	    }
	)
	print(SendTxn(txn,priv_key))
	print("address : "+other_addr+" before : "+str(before_other_addr_balance)+" after : "+str(web3.eth.getBalance(other_addr)))
	print("address : "+contract_addr+" before : "+str(before_contract_balance)+" after : "+str(web3.eth.getBalance(contract_addr)))
	
def SendTxnTransferToContract(my_addr,value,priv_key):
	before_my_addr_balance = web3.eth.getBalance(my_addr)
	before_contract_balance = web3.eth.getBalance(contract_addr)
	txn = contract_instance.functions.transderToContract().buildTransaction(
	    {
	    	'from':my_addr,
		'chainId':5,
		'nonce':web3.eth.getTransactionCount(my_addr),
		'gas':76000,
		'value':Web3.toWei(int(value),'wei'),
		'gasPrice':web3.eth.gasPrice,
	    }
	)
	print(SendTxn(txn,priv_key))
	print("address : "+my_addr+" before : "+str(before_my_addr_balance)+" after : "+str(web3.eth.getBalance(my_addr)))
	print("address : "+contract_addr+" before : "+str(before_contract_balance)+" after : "+str(web3.eth.getBalance(contract_addr)))
	
def SendTxnGetBalance(other_addr):
	print(web3.eth.getBalance(other_addr))
	
