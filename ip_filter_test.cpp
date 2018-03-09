#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "ip_filter.h"


BOOST_AUTO_TEST_SUITE(test_suite_ip_filter)

    BOOST_AUTO_TEST_CASE(test_split)
    {
        BOOST_CHECK(split("",  '.') == std::vector<std::string>({""}));
        BOOST_CHECK(split("11", '.') == std::vector<std::string>({"11"}));
        BOOST_CHECK(split("..", '.') == std::vector<std::string>({"", "", ""}));
        BOOST_CHECK(split("11.", '.') == std::vector<std::string>({"11", ""}));
        BOOST_CHECK(split(".11", '.') == std::vector<std::string>({"", "11"}));
        BOOST_CHECK(split("11.22", '.') == std::vector<std::string>({"11", "22"}));
    }

BOOST_AUTO_TEST_SUITE_END()