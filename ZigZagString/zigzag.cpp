#include<iostream>
#include<string>

using namespace std;

//将输入的一行string转化为按照N行呈zigzag（锯齿型）排列的string，并按行拼接后输出
//eg. input: ABCDEFGHIJKLMN ， NUM = 4
//output:
// A   G     N
// B  F H   M
// C E   I K
// D      J
// output为：AGNBFHMCEIKDJ
string convert(string s, int numRows) {
        if (s.size() <= 0 || numRows <= 1 || numRows > s.size())
            return s;
        string res[numRows];
        for (int i = 0; i < numRows; ++i)
            res[i] = "";
        bool isDown = true;
        int count = 0;
        for (int i = 0; i < s.size(); ++i) {
            res[count] += s[i];
            if (count == 0) {
                isDown = true;
            }
            if (count == numRows-1) {
                isDown = false;
            }
            if (isDown)
                ++count;
            else
                --count;
        }
        if (numRows < 2)
            return res[0];
        string result = "";
        for (int i = 0; i < numRows; ++i)
            result += res[i];
        return result;
    }
int main () {
    string input = "ABCDEFGHIJKLMN";
	int num = 4;
	cout<<convert(input, num)<<endl;
}
