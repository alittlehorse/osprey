/** @file
 *****************************************************************************

 Declaration of interfaces for compling the proof program which source langrauge is tinyram

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#include <libserver/tinyram_complier_server.hpp>
#include<regex>
#include <fstream>

namespace libserver{
    bool tinyram_comlier_server::complie_tinyram(std::string &&file_path) {
        //turn file content to string and process the information
        //firstly,match the bounds information
        //then delete all comment;
        //relpace all instruction type;
        std::string parent_dir = parent_dir();
        const std::string file_name = file_name();
        std::regex head_re("^; TinyRAM V=2.000 M=vn W=([0-9]+) K=([0-9]+)$");
        std:smatch head_match;
        std::ifstream in(file_path);
        std::string head;
        if(getline(in,head)){
            if(std::regex_match(head,head_match,head_re)){
                if (head_match.size() == 3){
                    std::string&& w = head_match[1].str();
                    std::string&& k = head_match[2].str();
                    std::ofstream arch_params_file(.append("-architecture_params.txt"));

                }
            }
        }
        //regex_match(getline(assemble_file),tinyram_comment_re);

    }
}
