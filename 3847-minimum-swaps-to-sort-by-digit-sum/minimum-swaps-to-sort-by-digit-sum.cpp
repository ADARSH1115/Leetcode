class Solution {
public:
    int digitalSum(int num){
        int sum=0;
        while(num>0){
            sum+=num%10;
            num/=10;
        }
        return sum;
    }
    int minSwaps(vector<int>& nums) {
        int n=nums.size();
        vector<pair<int ,int>>arr;

        for(int num:nums){
            arr.push_back({digitalSum(num),num});
        }
        sort(arr.begin(),arr.end());

        unordered_map<int,int>pos;

        for(int i=0;i<n;i++){
            pos[arr[i].second] =i;
        }

        vector<bool>visited(n,false);
        int swaps=0;

        for(int i=0;i<n;i++){
            if(visited[i]){
                continue;
            }
            int j=i;

            int cycleSize=0;
            while(!visited[j]){
                visited[j]=true;
                cycleSize++;

                j=pos[nums[j]];
            }
            if(cycleSize>1){
                swaps+=cycleSize-1;
            }
        }
        return swaps;
    }
};