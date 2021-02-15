//
// Created by alittlehorse on 2/11/21.
//
#include<libserver/Log.hpp>
#include <cassert>

int main()
{
    libserver::Log log("avarage/log.txt");
    assert(log.get_path()=="avarage/log.txt");
    size_t a = 1;
    assert(log.StrFormat("Hello,World%zu",a)=="Hello,World1");
    //log.write_log("Hello,World");
}



