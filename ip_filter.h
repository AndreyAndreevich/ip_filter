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

std::ostream& operator<<(std::ostream &out, const std::tuple<int,int,int,int> &ip) {
    out << std::get<0>(ip) << "." << std::get<1>(ip) << "."
        << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
}



void process(std::istream &in, std::ostream &out) {

    std::vector<std::tuple<int,int,int,int>> ip_pool;


    /// перебираем входные данные и собираем вектор ip адрессов
    for(std::string line; std::getline(in, line);)
    {
        auto v = split(split(line, '\t').at(0),'.');

        if (v.size() != 4)
            throw std::runtime_error("Error IP size");

        std::vector<int> check_int_vector;

        for (const auto &item : v) {
            int num = std::stoi(item);
            if (num < 0 || num > 255)
                throw std::runtime_error("Incorrect IP");
            check_int_vector.push_back(num);
        }

        ip_pool.push_back(std::make_tuple(check_int_vector.at(0),check_int_vector.at(1),
                                          check_int_vector.at(2),check_int_vector.at(3)));
    }

    // TODO reverse lexicographically sort

    std::sort(ip_pool.rbegin(),ip_pool.rend());
    for(const auto& ip : ip_pool)
        out << ip;

    // 222.173.235.246
    // 222.130.177.64
    // 222.82.198.61
    // ...
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first byte and output

    for (const auto &ip : ip_pool) {
        if (std::get<0>(ip) == 1)
            out << ip;
    }

    // 1.231.69.33
    // 1.87.203.225
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first and second bytes and output

    for (const auto &ip : ip_pool) {
        if (std::get<0>(ip) == 46 && std::get<1>(ip) == 70)
            out << ip;
    }

    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    // TODO filter by any byte and output

    for (const auto &ip : ip_pool) {
        if (std::get<0>(ip) == 46 || std::get<1>(ip) == 46 ||
            std::get<2>(ip) == 46 || std::get<3>(ip) == 46)
            out << ip;
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