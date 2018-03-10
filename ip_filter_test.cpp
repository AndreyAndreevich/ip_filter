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
                std::make_tuple((uint8_t)1,(uint8_t)70,(uint8_t)44,(uint8_t)170),
                std::make_tuple((uint8_t)1,(uint8_t)29,(uint8_t)168,(uint8_t)152),
                std::make_tuple((uint8_t)1,(uint8_t)1,(uint8_t)234,(uint8_t)8),
                std::make_tuple((uint8_t)46,(uint8_t)70,(uint8_t)225,(uint8_t)39),
                std::make_tuple((uint8_t)46,(uint8_t)70,(uint8_t)147,(uint8_t)26),
        };
        BOOST_CHECK_THROW(filter(set,256),std::exception);
        BOOST_CHECK_THROW(filter(set,-1),std::exception);
        BOOST_CHECK_THROW(filter(set,1,1,234,8,1).size(),std::exception);

        BOOST_CHECK_EQUAL(filter(set,1).size(),3);
        BOOST_CHECK_EQUAL(filter(set,2).size(),0);
        BOOST_CHECK_EQUAL(filter(set,46,70).size(),2);
        BOOST_CHECK_EQUAL(filter(set,46,70,225).size(),1);
        BOOST_CHECK_EQUAL(filter(set,1,1,234,8).size(),1);
    }

    BOOST_AUTO_TEST_CASE(test_filter_any)
    {
        id_set set = {
                std::make_tuple((uint8_t)1,(uint8_t)70,(uint8_t)44,(uint8_t)170),
                std::make_tuple((uint8_t)1,(uint8_t)29,(uint8_t)168,(uint8_t)152),
                std::make_tuple((uint8_t)1,(uint8_t)1,(uint8_t)234,(uint8_t)8),
                std::make_tuple((uint8_t)46,(uint8_t)70,(uint8_t)225,(uint8_t)39),
                std::make_tuple((uint8_t)46,(uint8_t)70,(uint8_t)147,(uint8_t)26),
        };
        BOOST_CHECK_THROW(filter_any(set,256),std::exception);
        BOOST_CHECK_THROW(filter_any(set,-1),std::exception);

        BOOST_CHECK_EQUAL(filter_any(set,70).size(),3);
        BOOST_CHECK_EQUAL(filter_any(set,39).size(),1);
        BOOST_CHECK_EQUAL(filter_any(set,22).size(),0);
    }

BOOST_AUTO_TEST_SUITE_END()