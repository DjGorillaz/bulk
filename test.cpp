
#include "bulk.h"
#define BOOST_TEST_MODULE test_bulk

#include <ostream>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

BOOST_AUTO_TEST_SUITE(Writing)

bool testApp(const std::string& input, const std::string& output, int N)
{
    std::ofstream test("testCase.log");
    test << input;
    test.close();

    std::ifstream test1("testCase.log");
    App app(N, test1);

    std::stringstream ss;
    app.exporters.emplace_back(std::make_unique<Console>(ss));

    app.start();
    test1.close();
    remove("testCase.log");
    
    return ss.str() == output;
}

BOOST_AUTO_TEST_CASE(test1)
{
    std::string input = "1\n2\n3\n4\n5\n";
    std::string output = "bulk: 1, 2, 3\n"
                        "bulk: 4, 5\n";
    BOOST_REQUIRE(testApp(input, output, 3));
}

BOOST_AUTO_TEST_CASE(test2)
{
    std::string input = "1\n2\n3\n{\n4\n5\n6\n7\n}\n";
    std::string output = "bulk: 1, 2, 3\n"
                        "bulk: 4, 5, 6, 7\n";
    BOOST_REQUIRE(testApp(input, output, 3));
}

BOOST_AUTO_TEST_CASE(test3)
{
    std::string input = "{\n1\n2\n{\n3\n4\n}\n5\n6\n}\n";
    std::string output = "bulk: 1, 2, 3, 4, 5, 6\n";
    BOOST_REQUIRE(testApp(input, output, 3));
}

BOOST_AUTO_TEST_CASE(test4)
{
    std::string input = "1\n2\n3\n{\n4\n5\n6\n7\n";
    std::string output = "bulk: 1, 2, 3\n";
    BOOST_REQUIRE(testApp(input, output,3));
}

BOOST_AUTO_TEST_SUITE_END()