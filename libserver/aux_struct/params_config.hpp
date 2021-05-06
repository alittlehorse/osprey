//
// Created by alittlehorse on 5/1/21.
//

#ifndef OSPREY_LIBSERVER_AUX_STRUCT_PARAMS_CONFIG_HPP_
#define OSPREY_LIBSERVER_AUX_STRUCT_PARAMS_CONFIG_HPP_
#include <string>
#include <libserver/ram_compiler/tinyram_precompiler.hpp>


class params_config {
 public:
  params_config()=default;
  bool init(const std::string& config_path);
  [[nodiscard]] const size_t get_register_count() const;
  [[nodiscard]] const size_t get_word_size() const;
  [[nodiscard]] const size_t get_tinyram_input_size_bound() const;
  [[nodiscard]] const size_t get_time_bound() const;
  [[nodiscard]] const size_t get_tinyram_program_size_bound() const;
  [[nodiscard]] const std::string& get_program() const;
  [[nodiscard]] const std::string& get_verify_program() const;
  bool precompiler(const std::string& tinyram_program);
 private:
  size_t register_count;
  size_t word_size;
  size_t tinyram_input_size_bound;
  size_t time_bound;
  size_t tinyram_program_size_bound;
  std::string program;
  std::string verify_program;

};

#endif //OSPREY_LIBSERVER_AUX_STRUCT_PARAMS_CONFIG_HPP_
