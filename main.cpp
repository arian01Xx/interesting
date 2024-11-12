#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        int n=flowers.size();
        sort(flowers.begin(), flowers.end());
        if(n==0) return 0;

        vector<long long> pre(n+1,0);
        for(int i=1; i<=n; i++){
            pre[i]=pre[i-1]+(long long)flowers[i-1];
        }
        long long res=LLONG_MIN;

        for(int t=n; t>=0; t--){ //de derecha a izquierda
            long long fullCost=0;
            long long partialCost=0;
            if(t<n){
                if(flowers[t]<target){
                    long long need=(long long)target-(long long)flowers[t];
                    if(need>newFlowers) break;
                    newFlowers-=need; //actualiza las flores que quedan
                }
            }
            fullCost=(long long)(n-t)*full;
            int l=0;
            int r=target-1;

            while(l<=r){
                int mid=l+(r-l)/2;
                int idx=upper_bound(flowers.begin(), flowers.begin()+t, mid)-flowers.begin();
                if(idx==0) l=mid+1;
                else{
                    long long needToPlant=((long long)mid*(long long)idx-pre[idx]);
                    if(needToPlant>newFlowers) r=mid-1;
                    else{
                        l=mid+1;
                        partialCost=(long long)mid*partial;
                    }
                }
            }
            res=max(res, fullCost+partialCost);
        }
        return res;
    }
};

int main(){
    return 0;
}