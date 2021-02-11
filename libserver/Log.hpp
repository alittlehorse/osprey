//
// Created by alittlehorse on 2/9/21.
//

#ifndef OSPREY_LOG_H
#define OSPREY_LOG_H
#include <iostream>
#include <utility>
#include <fstream>

namespace libserver{
    class Log{
    private:
        std::string _path;
        std::ofstream  outfile;
        template <typename T> T Argument(T value) noexcept { return value; }
        template <typename T>
        T const *Argument(std::basic_string<T> const &value) noexcept {
            return value.c_str();
        }
        template <typename... Args>
        int StringPrint(char *const buffer, size_t const bufferCount,
                        char const *const format, Args const &... args) noexcept {
            int const result = snprintf(buffer, bufferCount, format, Argument(args)...);
            return result;
        }



    public:
        explicit Log(std::string path){_path = std::move(path);}
        std::string  get_path(){return _path;};
        template<typename... Args>
        void write_log(const char *format, Args... args)
        {
            std::string content =  StrFormat(format,args...);
            outfile.open(_path, std::ios::app);
            outfile<<content;
            outfile.close();
        }
        template <typename... Args>
        std::string StrFormat(const char *format, Args... args) {
            std::string buffer;
            size_t const size = StringPrint(nullptr, 0, format, args...);
            buffer.resize(size);
            StringPrint(&buffer[0], buffer.size() + 1, format, args...);
            return buffer;
        }
    };

}
#endif //OSPREY_LOG_H