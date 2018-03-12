#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>

typedef  std::vector<std::vector<std::string>> id_set;

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

bool cmp(std::vector<std::string> &vL,std::vector<std::string> &vR)
{
    for (auto i = 0; i < 4; i++) {
        if (vL[i].size() != vR[i].size())
            return  vL[i].size() > vR[i].size();
        if (vL[i] != vR[i])
            return vL[i] > vR[i];
    }
    return true;
}


std::ostream& operator<<(std::ostream &out, const id_set &ip_pool) {
    for(auto ip : ip_pool)
    {
        for (auto &i : ip) {
            if (&i != &ip.front())
                out << ".";
            out << i;
        }
        out << std::endl;
    }
}

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

