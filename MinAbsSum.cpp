// https://codility.com/media/train/15-DynamicProgramming.pdf
// https://codility.com/media/train/solution-min-abs-sum.pdf
#include <numeric>

int solution(vector<int>& A) {
    const int N = A.size();
    if (N == 0)
        return 0;
   
    int MaxVal = 0;
    for (int i = 0; i < N; i++) {
        A[i] = abs(A[i]);
        MaxVal = max(MaxVal, A[i]);
    }

    const int Sum = std::accumulate(A.begin(), A.end(), 0);
    vector<int> count(MaxVal + 1, 0);
    for (int i = 0; i < N; i++)
        count[A[i]]++;

    // for (int i =0; i <= MaxVal; i++)
    // {
    //     cout << count[i] << " ";
    // }
    // cout << endl;

    // Dynamic Programming
    // dpj = -1 if we cannot get the sum j,
    // dpj ­>= 0 if we can get sum j.
    // dpj denotes how many values a remain (maximally) after achieving sum j.
    vector<int> dp(Sum + 1, -1);
    dp[0] = 0;
    for (int a = 1; a <= MaxVal; a++) {
        if (count[a]>0) {
            for (int j = 0; j < Sum; j++) {
                if (dp[j] >= 0)
                // as no value a is needed to obtain the sum j.
                    dp[j] = count[a];
                else if (j >= a && dp[j - a] > 0)
                    dp[j] = dp[j - a] - 1;
            }
            // for (int i =0; i <= Sum; i++)
            // {
            //     cout << dp[i] << " ";
            // }
            // cout << endl;
        }
    }
    // Using this algorithm, we can mark all
    // the sum values and choose the best
    // one (closest to half of S).

    int result = Sum;
    for (int i = 0; i < Sum / 2 + 1; i++) {
        if (dp[i] >= 0)
            result = min(result, Sum - 2 * i);
    }

    return result;
}
