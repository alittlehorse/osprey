
#include<libserver/aux_struct/params_config.hpp>
#include <cassert>
#include<memory>

int main(){
  std::unique_ptr<params_config> p(new params_config());
  p->init("../../libserver/tutorial/avarage/avarage.json");
  assert(p->get_register_count()==16);
  size_t a = p->get_time_bound();
  assert(p->get_time_bound() == 64);
  assert(p->get_program()=="import sys; .....");
  assert(p->get_verify_program()=="store.w 1 0 0 0\nmov 1 0 0 32768\nread 1 1 0 0\ncjmp 1 0 0 28\nadd 1 0 0 2\nstore.w 0 1 0 0\njmp 1 0 0 8\nstore.w 1 0 0 32768\nmov 1 3 0 0\nmov 1 4 0 0\nread 1 2 0 1\ncjmp 1 0 0 60\nadd 1 3 3 1\nadd 0 4 4 2\njmp 1 0 0 40\nudiv 0 4 4 3\nload.w 0 1 0 0\nsub 0 4 4 1\nanswer 0 0 0 4\n");
  assert(p->get_tinyram_input_size_bound()== 25);
  assert(p->get_tinyram_program_size_bound() == 20);
  return 0;
}