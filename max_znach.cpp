#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

double maxZnach(ifstream& f) {
    double x, max_ = 0, min_ = 0;
    if (!f.eof()) {
        f >> x;
        cout << x << " ";
        max_ = x;
        min_ = x;
        while (!f.eof()) {
            f >> x;
            cout << x << " ";
            if (x != 0){
                vector<double> v{ min_ + x, min_ - x, min_ * x, min_ / x, max_ + x, max_ - x, max_ * x, max_ / x };
                sort(v.begin(), v.end());
                min_ = v[0];
                max_ = v[7];
            }
            else {
                min_ = min(0., min_);
                max_ = max(0., max_);
            }
           
        }
    }    
    return max_;
}
