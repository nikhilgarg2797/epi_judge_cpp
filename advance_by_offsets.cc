#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::min;
using std::max;
bool CanReachEnd(const vector<int>& max_advance_steps) {
    int n = max_advance_steps.size();
    vector<int> minimum_jump_array(n, INFINITY);
    minimum_jump_array[0] = 0;
    vector<int> jump_path_array;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (i <= j + max_advance_steps[j])
            {
                if (minimum_jump_array[j] + 1 < minimum_jump_array[i])
                {
                    jump_path_array.push_back(j);
                } 
                minimum_jump_array[i] = min(minimum_jump_array[j]+1, minimum_jump_array[i]);
            }
        }
    }

  return jump_path_array.size()>=n-1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
