#define BOOST_TEST_MODULE RomanNumerals
#include <boost/test/included/unit_test.hpp>

std::string show_roman(int num)
{
	return "";
}

//Unit Tests
BOOST_AUTO_TEST_SUITE(RomanNumerals);

BOOST_AUTO_TEST_CASE(SingleDigit)
{
    BOOST_CHECK_EQUAL(show_roman(1),"I");
}

BOOST_AUTO_TEST_SUITE_END()
