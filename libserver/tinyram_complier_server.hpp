/** @file
 *****************************************************************************

 Declaration of interfaces for compling the proof program which source langrauge is tinyram

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <unordered_map>
#include <vector>
#include<tuple>
#ifndef OSPREY_TINYRAM_COMPLIER_SERVER_H
#define OSPREY_TINYRAM_COMPLIER_SERVER_H

using namespace std;
namespace libserver{
    [[maybe_unused]] static const std::unordered_map<std::string,std::vector<std::string>> instruction_types=
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
    class tinyram_comlier_server {
        //input the assemble file and process the file ,like a complier
    public:
        bool complie_tinyram(std::string &&file_path);
        int parse_reg(std::string);
        std::tuple<int,int> parse_arg2(std::string);

    private:
        std::string&& parent_dir();
        std::string&& file_name();
        std::unordered_map<std::string,int> labels;
    };

}
#endif //OSPREY_TINYRAM_COMPLIER_SERVER_H
