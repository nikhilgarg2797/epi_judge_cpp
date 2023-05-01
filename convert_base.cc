#include <string>
#include<iostream>
#include<vector>
#include "test_framework/generic_test.h"

using std::string;
using namespace std;
/*
    Problem:
        Given a number in base 'b1', convert the number to base 'b2'
        0 <= b1, b2 <= 16
        For numbers >= 10, use A for 10, B, ... F for 15
    Input:
        num: (string)num in b1 for conversion
        b1: base 1
        b2: base 2
    Output:
        number in base b2
    For this first we will convert the number to base 10. After that convert it to b2.
    TC: O( n * log_b2(b1) ) +  O(n), n = no. of characters in string num.
*/

int convertToDecimal(const string& num, int base)
{
    int num_10 = 0;
    // check if negative
    bool negative = num[0] == '-' ? true : false;

    for (int i = negative ? 1 : 0; i < num.size(); i++) {
        // multiply by base value
        num_10 = num_10 * base;
        // take out the digit from the number
        // in case the position is occupied by A, B.. F we convert it to
        // their values 10, 11,... 15
        if (isdigit(num[i])) {
            num_10 = num_10 + num[i] - '0';
        }
        else {   // If b1 >= 10 then it can have A, B .. occupy positions
            // since each charc from A onwards is atleast >= 10
            num_10 = num_10 + num[i] - 'A' + 10;
        }
    }
    return negative ? -num_10 : num_10;
}

string convertToBase(int num, int base)
{
    if (num == 0)
        return "";
    // now the remainder can be single or multiple digit long
    return convertToBase(num / base, base) +
        (char)(num % base < 10 ? num % base + '0' : (num % base) - 10 + 'A');

}

string ConvertBase(const string& num_as_string, int b1, int b2) {
    // converts the number from given base to decimal
    int num10 = convertToDecimal(num_as_string,b1);
    // convert the number from decimal to given base
    string num_b2 = convertToBase(num10, b2);

    return num_b2;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
