#include <algorithm>

#include "ip_filter.h"

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::tuple<int,int,int,int>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(split(line, '\t').at(0),'.');
            ip_pool.push_back(std::make_tuple(std::stoi(v.at(0)),std::stoi(v.at(1)),
                                              std::stoi(v.at(2)),std::stoi(v.at(3))));
        }

        // TODO reverse lexicographically sort

        std::sort(ip_pool.rbegin(),ip_pool.rend());
        for(const auto& ip : ip_pool)
            std::cout << ip;

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        for (const auto &ip : ip_pool) {
            if (std::get<0>(ip) == 1)
                std::cout << ip;
        }

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        for (const auto &ip : ip_pool) {
            if (std::get<0>(ip) == 1 && std::get<1>(ip) == 70)
                std::cout << ip;
        }

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output

        for (const auto &ip : ip_pool) {
            if (std::get<0>(ip) == 46 || std::get<1>(ip) == 46 ||
                std::get<2>(ip) == 46 || std::get<3>(ip) == 46)
                std::cout << ip;
        }



        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}