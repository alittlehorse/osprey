//
// Created by alittlehorse on 2/9/21.
//

#ifndef OSPREY_LOG_H
#define OSPREY_LOG_H
#include <iostream>
#include <utility>
#include <fstream>
#include <libserver/aux/string_helper.hpp>

namespace libserver{
    class Log{
    private:
        std::string _path;
        std::ofstream  outfile;

    public:
        explicit Log(std::string path){_path = std::move(path);}
        std::string  get_path(){return _path;};
        template<typename... Args>
        void write_log(const char *format, Args... args)
        {
            std::string content =  libserver::string_helper::StrFormat(format,args...);
            outfile.open(_path, std::ios::app);
            outfile<<content;
            outfile.close();
            std::string s = "World";
        }
    };

}
#endif //OSPREY_LOG_H