//
// Created by alittlehorse on 2/27/21.
//
#include<string>
#include<vector>
#include <cassert>
#include<libserver/string_helper.hpp>
#include<iostream>

int main(){
    std::string s = " i am james ";
    libserver::string_helper::trim(s);
    assert(s=="i am james");
    libserver::string_helper::replace_all(s," ",",");
    assert(s=="i,am,james");
    std::string a = "122";
    libserver::string_helper::replace_all(a,"12","21");
    assert(a=="221");
    auto b = libserver::string_helper::split(s,",");

    assert(b.size()==3);
    assert(b[0] == "i");
    assert(b[1] == "am");
    assert(b[2]=="james");
    std::vector<int> v1{1,2,3};
    std::vector<int> v2{3,2,1};
    std::vector<float> v3{1.2,2.4,9.0};
    std::vector<float> v4{1.2,2.4,9.0};
    libserver::string_helper::zip (
            [](int i,int j,float k,float l){
                std::cout << i << " " << j << " " << k << " " << l << std::endl;
            },
            v1.begin(),v1.end(),v2.begin(),v3.begin(),v4.begin());
}

