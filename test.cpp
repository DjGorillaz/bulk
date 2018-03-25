
#include "bulk.h"
#define BOOST_TEST_MODULE test_bulk

#include <ostream>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

BOOST_AUTO_TEST_SUITE(Writing)

bool testApp(const std::string& input, const std::string& output)
{
    std::ofstream test("testCase.log");
    test << input;
    test.close();

    std::ifstream test1("testCase.log");
    App app(5, test1);

    std::stringstream ss;
    app.exporters.emplace_back(std::make_unique<Console>(ss));

    app.start();
    test1.close();
    remove("testCase.log");
    
    return ss.str() == output;
}

BOOST_AUTO_TEST_CASE(console)
{
    std::string input = "1\n2\n3\n4\n5\n{\n1\n{\n{\n2\n}\n}\n3\n}\n1\n2\n";
    std::string output = "bulk: 1, 2, 3, 4, 5\n"
                        "bulk: 1, 2, 3\n"
                        "bulk: 1, 2\n";
    BOOST_REQUIRE(testApp(input, output));
}

BOOST_AUTO_TEST_SUITE_END()