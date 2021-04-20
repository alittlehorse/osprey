/** @file
 *****************************************************************************

 Declaration of interfaces for compiling tinyram(source language) to immediate language.


 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/


#ifndef OSPREY_TINYRAM_PRECOMPILER_HPP
#define OSPREY_TINYRAM_PRECOMPILER_HPP
#include <string>
#include <unordered_map>
#include<vector>
#include<libserver/aux_struct/Log.hpp>
namespace libserver{
    class tinyram_precompiler {
    public:
        /// complie the tinyram file to immediate format.
        /// \arg:: file_path:std::string&&
        /// \return: bool and write the immediate format to the same path

        bool complie_tinyram(std::string &&file_path,std::string&& out_name);

    private:
        Log* log;
        const std::unordered_map<std::string,std::vector<std::string>> instruction_types=
                {       {"and",{"des","arg1","arg2"}},
                        {"or",{"des","arg1","arg2"}},
                        {"xor",{"des","arg1","arg2"}},
                        {"not",{"des","arg2"}},
                        {"add",{"des","arg1","arg2"}},
                        {"sub",{"des","arg1","arg2"}},
                        {"mull",{"des","arg1","arg2"}},
                        {"umulh",{"des","arg1","arg2"}},
                        {"smulh",{"des","arg1","arg2"}},
                        {"udiv",{"des","arg1","arg2"}},
                        {"umod",{"des","arg1","arg2"}},
                        {"shl",{"des","arg1","arg2"}},
                        {"shr",{"des","arg1","arg2"}},
                        {"cmpe",{"arg1","arg2"}},
                        {"cmpa",{"arg1","arg2"}},
                        {"cmpae",{"arg1","arg2"}},
                        {"cmpg",{"arg1","arg2"}},
                        {"cmpge",{"arg1","arg2"}},
                        {"mov",{"des","arg2"}},
                        {"cmov",{"des","arg2"}},
                        {"jmp",{"arg2"}},
                        {"cjmp",{"arg2"}},
                        {"cnjmp",{"arg2"}},
                        {"opcode_10111",{}},
                        {"opcode_11000",{}},
                        {"opcode_11001",{}},
                        {"store.b",{"arg2","des"}},
                        {"load.b",{"des","arg2"}},
                        {"store.w",{"arg2","des"}},
                        {"load.w",{"des","arg2"}},
                        {"read",{"des","arg2"}},
                        {"answer",{"arg2"}}};

    };

}




#endif //OSPREY_TINYRAM_PRECOMPILER_HPP
