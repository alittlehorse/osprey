//
// Created by alittlehorse on 5/1/21.
//

#include "params_config.hpp"
#include <boost/json.hpp>
#include <fstream>
bool params_config::init(const std::string& config_path) {
  std::ifstream f(config_path);
  std::string content((std::istreambuf_iterator<char>(f)),
                      std::istreambuf_iterator<char>());
  const char *cstr = content.c_str();
  boost::json::parser parser;
  boost::json::error_code ec;
  parser.write(cstr,content.size(),ec);
  if(ec)return false;
  boost::json::value value = parser.release();
  if(!value.is_object())return false;
  boost::json::object object = value.as_object();
  program = value_to<std::string>(object.at("program"));

  tinyram_input_size_bound = value_to<size_t>(object.at("tinyram_input_size_bound"));
  time_bound = value_to<size_t>(object.at("time_bound"));
  tinyram_program_size_bound = value_to<size_t>(object.at("tinyram_program_size_bound"));
  register_count = value_to<size_t>(object.at("register_count"));
  word_size = value_to<size_t>(object.at("word_size"));
  verify_program =  value_to<std::string>(object.at("verify_program"));
  return true;
}
const size_t params_config::get_register_count() const {
  return register_count;
}
const size_t params_config::get_word_size() const {
  return word_size;
}
const size_t params_config::get_tinyram_input_size_bound() const {
  return tinyram_input_size_bound;
}
const size_t params_config::get_time_bound() const {
  return time_bound;
}
const size_t params_config::get_tinyram_program_size_bound() const {
  return tinyram_program_size_bound;
}
const std::string &params_config::get_program() const {
  return program;
}
const std::string &params_config::get_verify_program() const {
  return verify_program;
}
bool params_config::precompiler(const std::string &tinyram_program) {
  libserver::tinyram_precompiler c;
  std::string s;
  c.compile_tinyram(this->verify_program,&s);
  this->verify_program = s;
}






