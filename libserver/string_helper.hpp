//
// Created by alittlehorse on 2/27/21.
//

#ifndef OSPREY_STRING_HELPER_HPP
#define OSPREY_STRING_HELPER_HPP
#include <string>
#include<vector>
#include<functional>
namespace libserver{
    class string_helper {
    public:
        static void trim(std::string &s) {
            if (s.empty())return;
            s.erase(0, s.find_first_not_of(' '));
            s.erase(s.find_last_not_of(' ') + 1);
        }

        static void replace_all(std::string &str, const std::string &old_value, const std::string &new_value) {
            while (true) {
                if (size_t pos = str.find(old_value); pos != std::string::npos)
                    str.replace(pos, old_value.length(), new_value);
                else { break; }
            }
        };
        static std::vector<std::string> split(std::string source,const std::string &&delim) {
            std::vector <std::string> res;
            if (source.empty()) return std::move(res);
            source += delim;
            size_t pos;
            size_t size = source.size();
            for (int i = 0; i < size; ++i) {
                pos = source.find(delim, i);
                if (pos < size) {
                    std::string&& s = source.substr(i, pos - i);
                    res.push_back(s);
                    i = pos + delim.size() - 1;
                }
            }
            return std::move(res);
        }
        template <typename Iterator>
        static  void advance_all (Iterator & iterator) {
            ++iterator;
        }
        template <typename Iterator, typename ... Iterators>
        static void advance_all (Iterator & iterator, Iterators& ... iterators) {
            ++iterator;
            advance_all(iterators...);
        }
        template <typename Function, typename Iterator, typename ... Iterators>
        static Function zip (Function func, Iterator begin,
                      Iterator end,
                      Iterators ... iterators)
        {
            for(;begin != end; ++begin, advance_all(iterators...))
                func(*begin, *(iterators)... );
            //could also make this a tuple
            return func;
        }
        template <typename... Args>
        static std::string StrFormat(const char *format, Args... args) {
            std::string buffer;
            size_t const size = StringPrint(nullptr, 0, format, args...);
            buffer.resize(size);
            StringPrint(&buffer[0], buffer.size() + 1, format, args...);
            return buffer;
        }
        template <typename T> static T Argument(T value) noexcept { return value; }
        template <typename T>
        static T const *Argument(std::basic_string<T> const &value) noexcept {
            return value.c_str();
        }
        template <typename... Args>
        static int StringPrint(char *const buffer, size_t const bufferCount,
                        char const *const format, Args const &... args) noexcept {
            int const result = snprintf(buffer, bufferCount, format, Argument(args)...);
            return result;
        }
    };
}



#endif //OSPREY_STRING_HELPER_HPP
