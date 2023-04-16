/*
    Buy and sell stock twice:
        Given an array of numbers which represent the stock prices for a day. Find the
        max gain that can be made by buying a stock and selling that and again doing the same.
    The second stock can be bought only when the first is sold.
    Soltuion:
        The gain will be made when the difference between sold and bought stock is maximum. So we need
        to find the max diff for eack price. But since here we buy another stock after first is sold, so
        for each price we store the max gain that can be made till that price, either by selling at that
        price or if already sold before that price. Next we check the gain that can be made for each price if stock is bought
        at that price and sold later.
        we need to track two things:
        for a given price 'i':
        1. max gain made if bought stock is sold at that price or before
        2. max gain made if stock is bought at this price and sold later: this is the max price that occurs after
            this price.
        We save the results for 1 and do one more traversal to see which price is giving the max gain
        TC: O(n)
        Sc: O(n), for saving the gain results from buying stock once
*/

#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::max;
double BuyAndSellStockTwice(const vector<double>& prices) {
    int min_price_index = 0;
    double current_diff;
    double max_profit = 0;
    int max_price_after_first = prices.size() - 1;
    vector<double> gain_on_this_price(prices.size(),0);
    for (int i = 0; i < prices.size(); i++)
    {
        min_price_index = prices[min_price_index] > prices[i] ? i : min_price_index;
        current_diff = prices[i] - prices[min_price_index];
        max_profit = max(max_profit, current_diff);
        gain_on_this_price[i] = max_profit;
    }
    max_profit = 0;
    /*After completing the first max profit we get the last price assuming we are 
    buying and selling at that price only but this time we trace back  and add
    gain_on_this_price[i] for each index that way max profit wouln't be just first sweep
    max possible but addition of first and second sweep max possible*/
    for (int i = prices.size() - 1; i >= 0; i--)
    {
         max_price_after_first = prices[max_price_after_first] < prices[i] ? i : max_price_after_first;
        current_diff = prices[max_price_after_first] - prices[i];
        max_profit = max(max_profit, current_diff+ gain_on_this_price[i]);
    }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
