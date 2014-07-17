#define BOOST_TEST_MODULE RomanNumerals
#include <boost/test/included/unit_test.hpp>
#include <string>
#include <map>
#include <iostream>
#include <stdio.h>
#include <sstream>

std::map<std::string, int>  breakByIncrement(int n, int increment){
	std::map<std::string, int> result;
	int rmn = 1;
	int rnd = 1;
	rmn = n % increment; //4 if 14, mod 10
	rnd = n - rmn; //10  if 14
	result["remainder"] = rmn; 
	result["multiplier"] = rnd / increment;
	return result;
}

std::string show_roman(int num)
{
	//Map all of the milestones
	int milestones[7] = {1000, 500, 100, 50, 10, 5, 1}; 
	std::map<int, std::string> RomanMap;
	RomanMap[1]="I";
	RomanMap[5]="V";
	RomanMap[10]="X";
	RomanMap[50]="L";
	RomanMap[100]="C";
	RomanMap[500]="D";
	RomanMap[1000]="M";

	//set up variables
	std::map<std::string, int> iSplit;
	std::string sPayload = "";

	//for debugging
	std::ostringstream stream;

	//build output
	for(int m = 0; m < 7; m++){
		if(num >= milestones[m]) {
			//get the remainder and how many of the current milestone
			iSplit = breakByIncrement(num, milestones[m]);

			//if it's a 4, it prints differently
			if (milestones[m] != 1000 && iSplit["multiplier"] == 4){
				sPayload += RomanMap[milestones[m]];
				sPayload += RomanMap[milestones[m-1]];
			} else{
				//print out a letter for each multiplier
				for (int x = 1;x <= iSplit["multiplier"]; x++) {
					sPayload += RomanMap[milestones[m]]; //D for 500 out of original 567
				}
			}
			
			//set num as the remainder and go through loop again
			num = iSplit["remainder"]; //67 if 567, mod 500
		}
	}

	return sPayload;

}


//Unit Tests
BOOST_AUTO_TEST_SUITE(RomanNumerals);

BOOST_AUTO_TEST_CASE(Single)
{
    BOOST_CHECK_EQUAL(show_roman(1),"I");
    BOOST_CHECK_EQUAL(show_roman(4),"IV");
    BOOST_CHECK_EQUAL(show_roman(6),"VI");
    BOOST_CHECK_EQUAL(show_roman(9),"IX");
}

BOOST_AUTO_TEST_CASE(Tens)
{
	BOOST_CHECK_EQUAL(show_roman(11),"XI");
    BOOST_CHECK_EQUAL(show_roman(14),"XIV");
    BOOST_CHECK_EQUAL(show_roman(40), "XL");
    BOOST_CHECK_EQUAL(show_roman(49),"XLIX");
    BOOST_CHECK_EQUAL(show_roman(67),"LXVII");
    BOOST_CHECK_EQUAL(show_roman(99), "XC");
}

BOOST_AUTO_TEST_CASE(Hundreds)
{
	BOOST_CHECK_EQUAL(show_roman(101), "CI");
	BOOST_CHECK_EQUAL(show_roman(222), "CCXXII");
	BOOST_CHECK_EQUAL(show_roman(400), "CD");
	BOOST_CHECK_EQUAL(show_roman(567), "DLXVII");
	BOOST_CHECK_EQUAL(show_roman(858), "DCCCLVIII");
	BOOST_CHECK_EQUAL(show_roman(999), "CMXCIX");
}

BOOST_AUTO_TEST_CASE(Thousands)
{
	BOOST_CHECK_EQUAL(show_roman(1000), "M");
	BOOST_CHECK_EQUAL(show_roman(1999), "MCMXCIX");
	BOOST_CHECK_EQUAL(show_roman(4567), "MMMMDLXVII");
	BOOST_CHECK_EQUAL(show_roman(9999), "MMMMMMMMMCMXVII");
}

BOOST_AUTO_TEST_SUITE_END()
