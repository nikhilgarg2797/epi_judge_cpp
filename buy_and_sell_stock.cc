#include <vector>
#include <limits>
#include "test_framework/generic_test.h"
using std::vector;
using std::numeric_limits;
using std::max;
using std::min;

double BuyAndSellStockOnce(const vector<double>& prices) {
    int min_price_index  = 0;
    double current_diff;
    double max_profit = 0;
    for (int i = 0; i< prices.size();i++)
    {   // minimum price index is inedx value of the minimum price of the array
        min_price_index = prices[min_price_index] > prices[i] ? i : min_price_index;
        // current difference is price difference of ith price with minimum price
        current_diff = prices[i] - prices[min_price_index];
        // max profit is max(current differences so far)
        max_profit = max(max_profit, current_diff); 
    }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
