//
// Created by alittlehorse on 4/25/21.
//
#include <libserver/analysis_program/analysis_program.cpp>
using namespace std;
int main(){
  string program_str = "def fun(data):\n"
      "    return 2";
  string primary_input_path = "./primary_input.txt";
  analysis_program ana;
  ana.execute(program_str,primary_input_path);
  program_str = "def fun(data):\n"
                "return 2";
  return 0;
}

