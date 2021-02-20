/** @file
 *****************************************************************************

 Declaration of interfaces for compling the proof program which source langrauge is tinyram

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef OSPREY_TINYRAM_COMPLIER_SERVER_H
#define OSPREY_TINYRAM_COMPLIER_SERVER_H


namespace libserver{
    class tinyram_comlier_server{
        //input the assemble file and process the file ,like a complier
    public:
        bool complie_tinyram(std::string&& file_path);
    };

    bool tinyram_comlier_server::complie_tinyram(std::string &&file_path) {
        return false;
    }
}
#endif //OSPREY_TINYRAM_COMPLIER_SERVER_H
