Osprey
============
---------------------------
### Author and Contract

osprey is developed by alittlehorse and is released under the MIT license.

------------------------------
**NOTE**:this project is a Big data PaaS(Processing as a Server) trading platform based on zero-knowledge proof and blockchain with the protection of data privacy and functional privacy.
I modified source code of libsnark developed by the SCIPR Lab and contributors to archieve the tinyram_snark module.

----------------------------------
## Overview
This platform implements pp-zkSNARK schemes(Groth16), which are a cryptographic method for proving/verifying, in zero knowledge, the integrity of computations.  
This platform implements fair-swap using smart contract.  
This platform implements network transmission between buyer and provider.

A computation can be expressed as an NP statement in form:  
*"The Tinyram program foo, when executed, returns answer 0 if given the input bar and some additional input qux."*

A prover who knows the witness for the NP statement (i.e., a satisfying input/assignment) can produce a short proof attesting to the truth of the NP statement. This proof can be verified by anyone, and offers the following properties.

+ Zero knowledge: the verifier learns nothing from the proof beside the truth of the statement (i.e., the value qux, in the above examples, remains secret).
+ Succinctness: the proof is short and easy to verify.
+ Non-interactivity: the proof is a string (i.e. it does not require back-and-forth interaction between the prover and the verifier).
+ Soundness: the proof is computationally sound (i.e., it is infeasible to fake a proof of a false NP statement). Such a proof system is also called an argument.
+ Proof of knowledge: the proof attests not just that the NP statement is true, but also that the prover knows why (e.g., knows a valid qux).

--------------------------------
## Security
This code is a research-quality proof of concept, and has not yet undergone extensive review or testing. It is thus not suitable, as is, for use in critical or production systems

-------------------------------
## Build instructions

### Dependencies
The libsnark library relies on the following:

+ C++ build environment
+ CMake build infrastructure
+ GMP for certain bit-integer arithmetic
+ libprocps for reporting memory usage
+ Boost for command lines usage
+ libevent for network

So far we have tested these only on Linux. On Debian 10 (buster), Ubuntu 18.04 LTS, Ubuntu 20.04 LTS:
```asm
  $ sudo apt install build-essential cmake git libgmp3-dev libprocps-dev python3-markdown libboost-program-options-dev libssl-dev python3 pkg-config
```

### Building
Create the Makefile:
```asm
$ mkdir build && cd build && cmake ..
```
then, to compile the library, tests, and profiling harness, run this within the build directory:
```asm
$ make
```
To compile and run the tests for this library, run:
```asm
$ make check
```
----------------------------------------
## References
+ libsnark developed by SCIPR: https://github.com/scipr-lab/libsnark
+ [BCTV14a] Succinct non-interactive zero knowledge for a von Neumann architecture , Eli Ben-Sasson, Alessandro Chiesa, Eran Tromer, Madars Virza, USENIX Security 2014
+ [ate-pairing] High-Speed Software Implementation of the Optimal Ate Pairing over Barreto-Naehrig Curves , MITSUNARI Shigeo, TERUYA Tadanori
+ [Groth16] On the Size of Pairing-based Non-interactive Arguments , Jens Groth, EUROCRYPT 2016

