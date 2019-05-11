#include <string>
#include <cstdlib>
#include <sstream>
#include "util/Utility.hpp"
using namespace std;

namespace PARASProgram
{
	namespace Convert
	{
		/**
		 * Converts the given double to a string
		 */
        std::string *doubleToString(double dbl)
		{
			ostringstream convert;
			convert << dbl;
            std::string *ret = new string(convert.str());
			return ret;
		}


		/**
		 * Converts the given int to a string
		 */
        std::string *intToString(int in)
		{
			stringstream convert;
			convert << in;
            std::string *ret = new string(convert.str());
			return ret;
		}


		/**
		 * Converts the given long to a string
		 */
        std::string *longToString(long long in)
		{
			stringstream convert;
			convert << in;
            std::string *ret = new string(convert.str());
			return ret;
		}


		/**
		 * Converts the given string to an int
		 */
        int stringToInt(std::string* str)
		{
			return atoi(str->c_str());
		}

		/**
		 * Converts the given string to a double
		 */
        double stringToDouble(std::string* str)
		{
			stringstream convert;
			double dbl;
			convert << *str;
			convert >> dbl;

			return dbl;
		}

		/**
		 * Converts the given string to a bool
		 */
		bool stringToBool(string* str)
		{
			return Utility::bothTrim(str)->compare("true") == 0;
		}
	}

}
