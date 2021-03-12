# -*- coding:utf-8 -*-

from web3 import Web3, HTTPProvider

true = True
false = False
config = {
    "abi":[
	{
		"inputs": [],
		"name": "transderToContract",
		"outputs": [],
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
		"outputs": [],
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
    "address":"0xa446b9aBBC394C5c41D4C46FACf18CDd8A64bc11" # 合约地址
}

INFURA_api = "https://goerli.infura.io/v3/d9651a5bfd4548ba8c331e7723b79232" # INFURA的goerli API地址

web3 = Web3(HTTPProvider(INFURA_api))
contract_instance = web3.eth.contract(address=config['address'], abi=config['abi'])

my_addr = "0x57128a8c478B3fEab65866a9c39d06408c243ce9" # 买方地址
#other_addr = "0xAa3d7608ed56FCbE7aA5c75a5af180eB9Fd0133e" # 卖方地址
#value = 1000000 # 费用(wei)
priv_key = "0x0a09c8a1913273f24f7c7d610d1a11b0440885300801226c4d39222a32419b9f" # 买方账户私钥
print(web3.isConnected())
def SendTxn(txn,priv_key):
    signed_txn = web3.eth.account.signTransaction(txn,private_key=priv_key)
    res  = web3.eth.sendRawTransaction(signed_txn.rawTransaction).hex()
    txn_receipt = web3.eth.waitForTransactionReceipt(res)

    print(res)
    return txn_receipt
 
def SendTxnTransfer(other_addr):
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
	
def SendTxnTransferToContract(my_addr,value,priv_key):
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
	
def SendTxnGetBalance(other_addr):
	txn = contract_instance.functions.getBalance(other_addr).buildTransaction(
	    {
		'chainId':5,
		'nonce':web3.eth.getTransactionCount(my_addr),
		'gas':76000,
		'value':Web3.toWei(0,'wei'),
		'gasPrice':web3.eth.gasPrice,
	    }
	) 
	print(SendTxn(txn,priv_key))
