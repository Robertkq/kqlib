#ifndef kqformat_
#define kqformat_

#include "string.h"
#include "vector.h"
//#include <iostream>

namespace kq
{
    namespace format_details
    {

        inline char getAlign(kq::string& str)
        {
            if (!str.empty() && !(str[0] >= 48 && str[0] <= 57)) {
                char c = str[0];
                str.erase(str.begin());
                if (c != 'r' && c != 'c')
                {
                    return 'l';
                }
                return c;
            }
            return 'l';
        }

        inline int stoi(const kq::string& str)
        {
            int ret = 0;
            for (size_t i = 0; i < str.size(); ++i)
            {
                ret = ret * 10 + int(str[i] - 48);
            }
            return ret;
        }

        inline kq::string to_string(const kq::string& str)
        {
            return str;
        }

        inline kq::string to_string(const char* ptr)
        {
            return ptr;
        }

        inline kq::string to_string(char c)
        {
            kq::string ret;
            ret.push_back(c);
            return ret;
        }

        inline kq::string to_string(int i)
        {
            kq::string ret;
            while (i != 0)
            {
                ret.insert(ret.begin(), char(48 + i % 10));
                i /= 10;
            }
            return ret;
        }

        template<typename T>
        void format_args_add(kq::vector<kq::string>& v, T t)
        {
            v.push_back(to_string(t));
        }

        template<typename T, typename... Args>
        void format_args_add(kq::vector<kq::string>& v, T t, Args... Rest)
        {
            v.push_back(to_string(t));
            format_args_add(v, Rest...);
        }

        template<typename... Args>
        kq::vector<kq::string> format_args(Args... args)
        {
            kq::vector<kq::string> ret;
            format_args_add(ret, args...);
            return ret;
        }

    } // end of format_details::


    template<typename... Args>
    kq::string format(const char* fmt, Args... args)
    {
        kq::vector<kq::string> f_list = format_details::format_args(args...);

        //for (size_t i = 0; i < f_list.size(); ++i) { std::cout << "Arg " << i << ". " << f_list[i] << "\n"; }

        kq::string str(fmt);

        //std::cout << str << "\n\n";

        char argalign;

        unsigned int    argid,
            defargid = 0,
            argatr;

        unsigned int    start_arg_pos,
            end_arg_pos;

        for (size_t i = 0; i < str.size(); ++i)
        {
            if (str[i] == '{')
            {
                start_arg_pos = i + 1;
            }
            else if (str[i] == '}')
            {
                end_arg_pos = i;
                unsigned int difference = (end_arg_pos - start_arg_pos) + 2;
                argid = -1;
                argatr = -1;
                kq::string str_arg(str.substr(start_arg_pos, difference - 2));

                //std::cout << start_arg_pos << " " << end_arg_pos << "\n";
                //std::cout << "Current Arg: " << str_arg << "\n";

                kq::string str_argid = str_arg;
                kq::string str_argatr;

                unsigned int colon_pos = str_arg.find(':');
                if (colon_pos != str_arg.size()) {
                    str_argid = str_arg.substr(0, colon_pos);
                    str_argatr = str_arg.substr(colon_pos + 1, str_arg.size());
                }

                argalign = format_details::getAlign(str_argatr);

                //std::cout << "str_argid: " << str_argid << "\n"
                //"str_argatr: " << str_argatr << "\n";

                if (!str_argid.empty()) {
                    argid = format_details::stoi(str_argid);
                }

                if (!str_argatr.empty()) {
                    argatr = format_details::stoi(str_argatr);
                }

                //std::cout << "argid: " << argid << "\nargatr: " << argatr << "\nargalign: " << argalign << '\n';

                for (size_t j = 0; j < difference; ++j) {
                    str.erase(str.begin() + start_arg_pos - 1);
                }

                if (argid == int(-1)) {
                    argid = defargid++;
                }

                int space_difference;
                if (argatr != int(-1)) {
                    space_difference = argatr - f_list[argid].size();
                }

                if (argalign == 'l' && argatr != int(-1)) {
                    int space_difference = argatr - f_list[argid].size();
                    while (space_difference-- > 0) {
                        str.insert(str.begin() + start_arg_pos - 1, ' ');
                    }
                }

                unsigned int first_half, second_half;
                if (argalign == 'c' && argatr != int(-1)) {
                    first_half = second_half = (argatr - f_list[argid].size()) / 2;
                    if ((argatr - f_list[argid].size()) % 2 == 1) { ++first_half; }
                    while (first_half-- > 0) {
                        str.insert(str.begin() + start_arg_pos - 1, ' ');
                    }
                }


                for (kq::string::reverse_iterator it = f_list[argid].rbegin(); it != f_list[argid].rend(); ++it) {
                    str.insert(str.begin() + start_arg_pos - 1, *it);
                }

                if (argalign == 'c' && argatr != int(-1)) {
                    while (second_half-- > 0) {
                        str.insert(str.begin() + start_arg_pos - 1, ' ');
                    }
                }

                if (argalign == 'r' && argatr != int(-1)) {
                    int space_difference = argatr - f_list[argid].size();
                    while (space_difference-- > 0) {
                        str.insert(str.begin() + start_arg_pos - 1, ' ');
                    }
                }


                //std::cout << "NEW:" << str << " << i=" << i << "\n";

                i = i - difference;
            }


        }
        str.shrink_to_fit();
        return str;
    }
} // end of kq::

#endif