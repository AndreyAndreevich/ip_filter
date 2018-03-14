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

    BOOST_AUTO_TEST_CASE(test_process_correct) {

        std::string correct_in_data = std::string() +
                                      "219.102.120.135\t486\t0\n" +
                                      "67.232.81.208\t1\t0\n" +
                                      "185.46.85.78\t5\t4\n" +
                                      "1.70.44.170\t4665\t0\n" +
                                      "85.254.10.197\t0\n" +
                                      "23.240.215.189\t6\t0\n" +
                                      "46.70.113.73\t3\t6\n" +
                                      "1.29.168.152\t17\t0\n" +
                                      "185.69.186.168\t1\n" +
                                      "46.70.29.76\t3\6\n" +
                                      "110.152.103.161\t0\t1\n";

        std::string correct_out_data = std::string() +
                                       "219.102.120.135\n" +
                                       "185.69.186.168\n" +
                                       "185.46.85.78\n" +
                                       "110.152.103.161\n" +
                                       "85.254.10.197\n" +
                                       "67.232.81.208\n" +
                                       "46.70.113.73\n" +
                                       "46.70.29.76\n" +
                                       "23.240.215.189\n" +
                                       "1.70.44.170\n" +
                                       "1.29.168.152\n" +
                                       "1.70.44.170\n" +
                                       "1.29.168.152\n" +
                                       "46.70.113.73\n" +
                                       "46.70.29.76\n" +
                                       "185.46.85.78\n" +
                                       "46.70.113.73\n" +
                                       "46.70.29.76\n";


        std::stringbuf in_buffer(correct_in_data);
        std::stringbuf out_buffer;
        std::istream in_stream(&in_buffer);
        std::ostream out_stream(&out_buffer);

        BOOST_CHECK_NO_THROW(process(in_stream, out_stream));

        BOOST_CHECK_EQUAL(out_buffer.str(), correct_out_data);

    }
    BOOST_AUTO_TEST_CASE(test_process_incorrect) {

        std::stringbuf out_buffer;
        std::ostream out_stream(&out_buffer);


        std::string incorrect_in_data1 = std::string() +
                                        "67.232.81.208\t2\t1\n" +
                                        "1.29.168.152\t2\t2\n" +
                                        "123.125.223\t3\t4\n" +     ///incorrect
                                        "185.46.85.78\t5\n";

        std::stringbuf in_buffer(incorrect_in_data1);
        std::istream in_stream(&in_buffer);

        BOOST_CHECK_THROW(process(in_stream, out_stream), std::exception);
        in_stream.clear();

        /////////////////////////////////////////////////////////////////////////

        std::string incorrect_in_data2 = std::string() +
                                         "67.232.81.208\t2\t1\n" +
                                         "1.29.168.152\t2\t2\n" +
                                         "123.125.223.23.31\t3\t4\n" +  ///incorrect
                                         "185.46.85.78\t5\n";

        in_buffer.str(incorrect_in_data2);
        BOOST_CHECK_THROW(process(in_stream, out_stream), std::exception);
        in_stream.clear();

        /////////////////////////////////////////////////////////////////////////

        std::string incorrect_in_data3 = std::string() +
                                         "67.232.81.208\t2\t1\n" +
                                         "1.29.168.152\t2\t2\n" +
                                         "123.125.a.23\t3\t4\n" +  ///incorrect
                                         "185.46.85.78\t5\n";

        in_buffer.str(incorrect_in_data3);
        BOOST_CHECK_THROW(process(in_stream, out_stream), std::exception);
        in_stream.clear();

        /////////////////////////////////////////////////////////////////////////

        std::string incorrect_in_data4 = std::string() +
                                         "67.232.81.208\t2\t1\n" +
                                         "1.29.168.152\t2\t2\n" +
                                         "123.125.256.23\t3\t4\n" +  ///incorrect
                                         "185.46.85.78\t5\n";

        in_buffer.str(incorrect_in_data4);
        BOOST_CHECK_THROW(process(in_stream, out_stream), std::exception);
        in_stream.clear();

        /////////////////////////////////////////////////////////////////////////

        std::string incorrect_in_data5 = std::string() +
                                         "67.232.81.208\t2\t1\n" +
                                         "1.29.168.152\t2\t2\n" +
                                         "123.125.-1.23.31\t3\t4\n" +  ///incorrect
                                         "185.46.85.78\t5\n";

        in_buffer.str(incorrect_in_data5);
        BOOST_CHECK_THROW(process(in_stream, out_stream), std::exception);
        /////////////////////////////////////////////////////////////////////////
    }

BOOST_AUTO_TEST_SUITE_END()