#include <iostream>
#include <vector>
#include <tuple>
#include <set>

typedef  std::set<std::tuple<uint8_t,uint8_t,uint8_t,uint8_t>> id_set;
typedef  std::tuple<uint8_t,uint8_t,uint8_t,uint8_t> ip_tuple;

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





void out(const id_set &ip_pool) {
    for(auto ip = ip_pool.crbegin();ip != ip_pool.crend();++ip)
    {
        std::cout << (int)std::get<0>(*ip) << "." << (int)std::get<1>(*ip) << "."
                  << (int)std::get<2>(*ip) << "." << (int)std::get<3>(*ip)
                  << std::endl;
    }
}




auto filter_rec(const id_set &set, const std::size_t &N)
{
    return set;
}

template<typename T, typename... Args>
auto filter_rec(const id_set &set, const std::size_t &N, T key, Args ...args)
{
    if (key>255 || key < 0)
        throw std::runtime_error("Error filter key");
    id_set result;
    for (auto it = set.begin();; ++it) {
        it = std::find_if(it, set.cend(), [key,N](ip_tuple value) {
            switch (N - sizeof...(args) - 1) {
                case 0: return (uint8_t)key == std::get<0>(value);
                case 1: return (uint8_t)key == std::get<1>(value);
                case 2: return (uint8_t)key == std::get<2>(value);
                case 3: return (uint8_t)key == std::get<3>(value);
                default: throw std::runtime_error("Error number arguments");
            }
        });

        if (it == set.cend())
            break;

        result.insert(*it);
    }
    return filter_rec(result,N,args...);
}

template<typename... Args>
auto filter(const id_set &set,Args ...args)
{
    return filter_rec(set,sizeof...(args),args...);
}





auto filter_any(const id_set &set, const int &key)
{
    if (key>255 || key < 0)
        throw std::runtime_error("Error filter key");
    id_set result;
    for (auto it = set.begin();; ++it) {
        it = std::find_if(it, set.cend(), [key](ip_tuple value) {
                return  (uint8_t)key == std::get<0>(value) ||
                        (uint8_t)key == std::get<1>(value) ||
                        (uint8_t)key == std::get<2>(value) ||
                        (uint8_t)key == std::get<3>(value);
        });

        if (it == set.cend())
            break;

        result.insert(*it);
    }
    return result;
}