//
// Created by alittlehorse on 3/19/21.
//

#include "tinyram_precompiler.hpp"
#include <regex>
#include <fstream>
#include <cassert>
#include<functional>
#include <libserver/aux/string_helper.hpp>
namespace libserver{
    bool tinyram_precompiler::complie_tinyram(std::string &&file_path, std::string &&out_name) {
        //turn file content to string and process the information
        //firstly,match the bounds information
        //then delete all comment
        //label the labels
        //transform all instructiontype argument to formal pattern:
        //op immflag des arg arg2

        std::unordered_map<std::string, int> d = {
                {"arg1",    0},
                {"arg2",    0},
                {"immflag", 0},
                {"des",     0}
        };
        std::unordered_map<std::string, int> labels;
        std::string parent_dir, file_name, instr, arg;
        std::string head;

        int w, k, addr = 0;

        std::vector<std::string> lines;

        std::regex head_re("^; TinyRAM V=2.000 M=vn W=([0-9]+) K=([0-9]+)$");
        std::smatch head_match;

        std::function<std::pair<std::string, std::string>()> p = [&file_path]() -> std::pair<std::string, std::string> {
            auto pos = file_path.find_last_of('/');
            std::string filename = file_path.substr(pos + 1);
            string_helper::replace_all(filename, ".s", "");
            std::string parentdir = file_path.substr(0, pos + 1);
            return std::pair<std::string, std::string>(std::move(filename), std::move(parentdir));
        };
        try {
            file_name = p().first;
            parent_dir = p().second;
        }
        catch (std::exception &e) {
            //log->write("cannot parse tinyram file path and name");
            return false;
        }
        log = new Log(parent_dir + file_name + "-complier-log.txt");

        std::ifstream in(file_path);
        std::ofstream out(parent_dir + out_name);

        //-------------------
        //create\open the $1-architecture_params.txt and write the params;
        log->write_log(" parse word size and register number which is located in tinyram file first line \n");
        if (getline(in, head)) {
            if (std::regex_match(head, head_match, head_re)) {
                if (head_match.size() == 3) {
                    std::string w_str = head_match[1].str();
                    std::string k_str = head_match[2].str();
                    try {
                        w = stoi(w_str);
                        k = stoi(k_str);
                    }
                    catch (std::exception &e) {
                        log->write_log(
                                "the compling process fail!\n the word size and register size format is wrong!pealse check!\n");
                        return false;
                    }
                    std::ofstream arch_params_file(parent_dir + file_name + "-architecture_params.txt");
                    arch_params_file << w_str.append(" ");
                    arch_params_file << k_str;
                    arch_params_file.close();
                }
            }

            log->write_log(
                    fmt::format("word size and register number parse processing success!\n word size is {},\n register nunmber is {} \n",w, k)
            );
        } else {
            log->write_log("the compling process fail!\n word size and register number parse processing fail!\n");
            return false;
        }
        // delete the comments
        // write the labels[lale] = addr
        // append the processed-line to lines;
        while (getline(in, head)) {
            if (size_t indx = head.find(';');indx != std::string::npos) {
                head = head.substr(0, indx);
                string_helper::trim(head);
            }
            if (head.empty())continue;
            if (size_t indx = head.find(':');indx != std::string::npos) {
                std::string &&lable = std::move(head.substr(0, indx));
                labels[lable] = addr;
                head = head.substr(indx + 1);
                string_helper::trim(head);
            }
            if (!head.empty()) {
                head.shrink_to_fit();
                lines.push_back(head);
                addr += 2 * (w / 8);
            }
        }
        std::function<int(std::string)> parse_reg = [](const std::string &arg) -> int {
            return stoi(arg.substr(1));
        };
        std::function<std::tuple<int, int>(std::string)> parse_arg2 = [labels, parse_reg](
                std::string arg) -> std::tuple<int, int> {
            if (arg[0] == '_') return std::make_tuple(1, labels.at(arg));
            else if (arg[0] == 'r') {
                return std::make_tuple<int, int>(0, parse_reg(arg));
            }
                //parse immediate value
            else {
                return std::make_tuple<int, int>(1, stoi(arg));
            }
        };
        std::function<void(const std::string &,
                           const std::string &)> process_args = [&d, &labels, &parse_reg, &parse_arg2](
                const std::string &t, const std::string &v) {
            if (t == "arg2") {
                std::tie(d["immflag"], d["arg2"]) = parse_arg2(v);
            } else {
                d[t] = parse_reg(v);
            }
        };

        // complie the tinyram to mechism pattern(formal pattern)
        for (auto l:lines) {
            log->write_log("---------------------------------------------------------\n");
            log->write_log(fmt::format("compling the instruction : {} \n", l));
            string_helper::replace_all(l, ",", " ");
            string_helper::replace_all(l, "  ", " ");
            size_t pos = l.find(' ');
            instr = l.substr(0, pos);
            arg = l.substr(pos + 1);
            auto args = libserver::string_helper::split(arg, " ");
            try {
                assert(instruction_types.at(instr).size() == args.size());
            }
            catch (std::exception &e) {
                log->write_log(fmt::format("the compling process fail!\n the instruction operand size is not right. the erro report is {}\n",
                                           e.what())
                );
                return false;
            }
            //modify the value correponding to key
            for (int i = 0; i < args.size(); i++) {
                process_args(instruction_types.at(instr)[i], args[i]);
            }
            std::string s = fmt::format("{} {} {} {} {}", instr,d["immflag"], d["des"],d["arg1"], d["arg2"]);
            for (auto it = d.begin(); it != d.end(); it++) {
                it->second = 0;
            }
            log->write_log(fmt::format("the complied resualt is: {}\n", s));
            out << s << '\n';
        }

        log->write_log("\n\n complier success!");
        return true;
    }
}

