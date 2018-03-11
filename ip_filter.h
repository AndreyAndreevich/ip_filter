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
    for (int i = 0; i < 4; i++) {
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
        for (auto i = ip.cbegin(); i!= ip.cend();i++) {
            if (i != ip.cbegin())
                out << ".";
            out << *i;
        }
        out << std::endl;
    }
}


auto filter_rec(const id_set &ip, const int &N)
{
    return ip;
}

template<typename T, typename... Args>
auto filter_rec(const id_set &ip, const int &N, T key, Args ...args)
{
    if (key>255 || key < 0)
        throw std::runtime_error("Error filter key");

    id_set result;
    for (auto it = ip.begin();; ++it) {
        it = std::find_if(it, ip.end(), [key,N](auto value) {
            return key == atoi(value[N].c_str());
        });

        if (it == ip.end())
            break;

        result.push_back(*it);
    }
    return filter_rec(result,N+1,args...);
}

template<typename... Args>
auto filter(const id_set &ip,Args ...args)
{
    return filter_rec(ip,0,args...);
}

auto filter_any(const id_set &set, const int &key)
{
    if (key>255 || key < 0)
        throw std::runtime_error("Error filter key");

    id_set result;
    for (auto it = set.begin();; ++it) {
        it = std::find_if(it, set.cend(), [key](auto value) {
                return  std::find_if(value.cbegin(),value.cend(),[key](auto value)
                {
                    return key == atoi(value.c_str());
                }) != value.cend();
        });

        if (it == set.cend())
            break;

        result.push_back(*it);
    }
    return result;
}