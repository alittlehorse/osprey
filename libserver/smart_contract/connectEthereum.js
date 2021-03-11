let Web3 = require("web3");
let Tx = require("ethereumjs-tx");

//合约地址
let contractAddr = "0xa446b9aBBC394C5c41D4C46FACf18CDd8A64bc11";
//创建web3对象
let web3 = new Web3;

//连接到ropsten
let INFURA_api = "https://goerli.infura.io/v3/d9651a5bfd4548ba8c331e7723b79232";
web3.setProvider(new Web3.providers.HttpProvider(INFURA_api));

//账户地址
let fromAddr = "0x57128a8c478B3fEab65866a9c39d06408c243ce9";

let count = web3.eth.getTransactionCount(fromAddr);
let gasPrice = web3.eth.gasPrice;
let gasLimit = 90000;

let rawTransaction = {
    "from": fromAddr,
    "nonce": web3.toHex(count),
    "gasPrice": web3.toHex(gasPrice),
    "gasLimit": web3.toHex(gasLimit),
    "to": contractAddr, 
    "value": "0x10000", 
    "data": "0x460968dd" //函数名callme取keccak后的bytes4
};

//账户私钥，不包含'0x'字符
let priv_key = new Buffer.from("0a09c8a1913273f24f7c7d610d1a11b0440885300801226c4d39222a32419b9f", "hex");
let tx = new Tx(rawTransaction);

//用私钥签名交易信息
tx.sign(priv_key);
let serializedTx = tx.serialize();

//发送交易
web3.eth.sendRawTransaction('0x'+serializedTx.toString('hex'),
    function(err, hash) {
        if (!err)
            console.log(hash);
        else
            console.log(err);
    });

