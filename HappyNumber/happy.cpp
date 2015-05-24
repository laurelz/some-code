#include<iostream>
#include<vector>
#include<set>

using namespace std;
vector<int> getSingleNum(int n) {
        vector<int>res;
        if (n < 0)
            return res;
        if (n < 10) {
            res.push_back(n);
            return res;
        }
        while (n >= 1) {
            int num = n%10;
            if (num != 0)
                res.push_back(num);
            n = n/10;
        }
        return res;
    }
    bool isHappy(int n) {
        vector<int> tmp = getSingleNum(n);
        if (tmp.size() <= 0)
            return false;
        int res = 0;
        set<int> resset;
        while(tmp.size() > 0) {
            if (tmp.size() == 1 && tmp[0] == 1)
                return true;
            
            res = 0;
            for (int i = 0; i < tmp.size(); ++i) {
                res += tmp[i]*tmp[i];
            }
            if (resset.find(res) != resset.end())
                return false;
            resset.insert(res);
            tmp = getSingleNum(res);
        }
    }
int main() {
	int num = 7;
        if (isHappy(num))
            cout<<"true"<<endl;
        else
            cout<<"false"<<endl;
        return 0;
}
