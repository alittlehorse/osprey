//
// Created by alittlehorse on 2/11/21.
//
#include<libserver/aux/Log.hpp>
#include <cassert>
#include <libserver/aux/string_helper.hpp>

int main()
{
    libserver::Log log("avarage/log.txt");
    assert(log.get_path()=="avarage/log.txt");
    log.write_log("Hello");
    //log.write_log("Hello,World");
}



