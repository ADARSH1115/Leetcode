class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        if(n<=2){
            return nums[0]==0?0:1;

        }
        bool increasing = true,decreasing = true;

        int zeroPos=0;

        for(int i =0;i<n;i++){
            if(nums[i]==0) zeroPos=i;

            int next=nums[(i+1)%n];

            if(next!= (nums[i]+1)%n){
                increasing =false;
            }
            if(next!=(nums[i]+n-1)%n){
                decreasing = false;
            }
        }
        if(increasing){
            return min(zeroPos,n-zeroPos+2);
        }
        if(decreasing){
            return 1+min(n-1-zeroPos,(zeroPos+1)%n);
        }
        return -1;
    }
};