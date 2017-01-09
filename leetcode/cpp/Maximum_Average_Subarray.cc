#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

/**
 * http://www.lintcode.com/zh-cn/problem/maximum-average-subarray/
 * Given an array with positive and negative numbers, find the maximum average subarray 
 * which length should be greater or equal to given length k.
 
 * Sample:
 * Given nums = [1, 12, -5, -6, 50, 3], k = 3
 * Return 15.667 // (-6 + 50 + 3) / 3 = 15.667
 *
 * tips:
 * bi-seperate to find(hit) the average, sum(an) - n * avg > 0, means avg(an) larger than avg
**/

class MaximumAverageSubarray{
public:
    double maxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        double *sum = new double[n+1];
        double l = INT_MAX*1.0, r = INT_MIN*1.0;

        for(int i = 0 ; i < n ; ++i) {
            if (nums[i] < l)
                l = nums[i];
            if (nums[i] > r)
                r = nums[i];
        }

        sum [0] = 0;
        while(r - l >= 1e-6) {
            double mid = (l + r)/2.0;
            double min_pre = 0;
            bool check = false;
            for(int i = 1 ; i <= n ; ++i) {
                sum[i] = sum[i-1] + nums[i-1] - mid;
                if (i >= k && sum[i] >= min_pre) {
                    check = true;
                    break;
                }
                if (i >=k) {
                    min_pre = (min_pre < sum[i-k+1]) ? min_pre : sum[i-k+1];
                }
            }
            if (check) l = mid;
            else r = mid;
        }
        return l;
    }
};


int main()
{
    MaximumAverageSubarray mas;
    int x[] = {1, 12, -5, -6, 50, 3};
    vector<int> a (x, x + sizeof(x)/sizeof(x[0]));
    cout<<mas.maxAverage(a, 3)<<endl;  // expected 15.667   
}

