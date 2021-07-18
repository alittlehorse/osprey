/** @file
 *****************************************************************************

 Declaration of interfaces for Log system

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/


#ifndef OSPREY_LOG_H
#define OSPREY_LOG_H

#include <utility>
#include <fstream>
#include <libserver/aux_struct/string_helper.hpp>

#include<fmt/format.h>
#include<fmt/ostream.h>

//TODO:refactoring the log system.
namespace libserver{
    class Log{
    private:
        std::string _path;
        std::ofstream log_file;

    public:
        explicit Log(const std::string& path):_path(path){
            log_file.open(path);
        }
        std::string  get_path(){return _path;};
        void write_log(const std::string&& content)
        {
            fmt::print(content);
            fmt::print(log_file,content);
        }
        void close(){
            log_file.close();
        }
    };

}
#endif //OSPREY_LOG_H