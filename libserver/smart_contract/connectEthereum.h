/** @file
 *****************************************************************************
smart contract module
 provide smart contract to libserver.
 The contract address embedded in the platform

 *****************************************************************************
 * @author     This file is part of libserver, developed by xu chen
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#include <iostream>
#include <string>
using namespace std;
namespace smart_contract{
    class smart_contract{
    public:
        static void init();
        // args:addr, priv_key，value
        static void SendTxnTransferToContract(string addr,string priv_key,int value);

        // args:addr
        static void SendTxnTransfer(string addr);
        static int connectEthereum(char const *functionName,char const *args[]);

    };

}

