#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


std::ostream& operator<<(std::ostream &out,
                         const std::tuple<int,int,int,int> &ip) {
    out << std::get<0>(ip) << "." << std::get<1>(ip) << "."
            << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
}
/*
///реализую функцию фильра с переменным числом аргументов (вдруг понадобится)))
///использую магический трюк
template<typename... Args>
auto filter(const id_set &ip,Args ...args)
{
    std::vector<std::string> sKey = {(1,std::to_string(args))...};
    const size_t N = sizeof...(args);
    id_set result;
    auto it = ip.cbegin();
    while (it != ip.cend()) {
        it = std::find_if(it, ip.cend(), [sKey] (auto value) mutable {
            value.resize(N);
            return sKey == value;
        });

        if (it != ip.cend()) {
            result.push_back(*it);
            it++;
        }
    }

    return result;
}



auto filter_any(const id_set &ip, const size_t &key)
{
    const std::string sKey = std::to_string(key);
    id_set result;

    auto it = ip.cbegin();
    while (it != ip.cend()) {
        it = std::find_if(it, ip.cend(), [sKey](auto value) {

                return  std::find_if(value.cbegin(),value.cend(),[sKey](auto value)
                {
                    return sKey == value;
                }) != value.cend();

        });

        if (it != ip.cend()) {
            result.push_back(*it);
            it++;
        }
    }
    return result;
}

*/