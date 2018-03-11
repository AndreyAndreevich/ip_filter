#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>

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

    BOOST_AUTO_TEST_CASE(test_filter)
    {
        id_set set = {
                {"1","70","44","170"},
                {"1","29","168","152"},
                {"1","1","234","8"},
                {"46","70","225","39"},
                {"46","70","147","26"},
        };
        BOOST_CHECK_THROW(filter(set,256),std::exception);
        BOOST_CHECK_THROW(filter(set,-1),std::exception);

        BOOST_CHECK_EQUAL(filter(set,1).size(),3);
        BOOST_CHECK_EQUAL(filter(set,2).size(),0);
        BOOST_CHECK_EQUAL(filter(set,46,70).size(),2);
        BOOST_CHECK_EQUAL(filter(set,46,70,225).size(),1);
        BOOST_CHECK_EQUAL(filter(set,1,1,234,8).size(),1);
    }

    BOOST_AUTO_TEST_CASE(test_filter_any)
    {
        id_set set = {
                {"1","70","44","170"},
                {"1","29","168","152"},
                {"1","1","234","8"},
                {"46","70","225","39"},
                {"46","70","147","26"},
        };
        BOOST_CHECK_THROW(filter_any(set,256),std::exception);
        BOOST_CHECK_THROW(filter_any(set,-1),std::exception);

        BOOST_CHECK_EQUAL(filter_any(set,70).size(),3);
        BOOST_CHECK_EQUAL(filter_any(set,39).size(),1);
        BOOST_CHECK_EQUAL(filter_any(set,22).size(),0);
    }

BOOST_AUTO_TEST_SUITE_END()