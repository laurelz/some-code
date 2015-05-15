
void sortColors(vector<int>& nums) {
        int one = 0, two = 0, three = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) 
                ++one;
            else if (nums[i] == 1)
                ++two;
            else if (nums[i] == 2)
                ++three;
        }
        int count = 0;
        while (one > 0) {
            nums[count++] = 0;
            one--;
        }
        while (two > 0) {
            nums[count++] = 1;
            two--;
        }
        while (three > 0) {
            nums[count++] = 2;
            three--;
        }
    }
