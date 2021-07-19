//
// Created by alittlehorse on 4/25/21.
//
#include <libserver/analysis_program/analysis_program.cpp>
using namespace std;
int main(){
  string program_str = "def fun(data):\n        return 2";
  analysis_program ana;
  cout << ana.execute(program_str);
  program_str = "def fun(data):\n"
                "        return 2";
  return 0;
}

