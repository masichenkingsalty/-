#include"../../stack/stack.h"
#include"../../vector/vector.h"
#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<time.h> 
using namespace std;
void myprint(int x) {
	printf("%d ", x);
}

int main(){
		srand(time(0));
		Vector<int> heights;
		int a=0;
		for (int i = 0; i < 6; i++)
		{	
			a=(rand() % 10 + 1);
			heights.insert(0,a);
		}
        int n = heights.size();
        int area = 0;
        
        //以mid为中点left和right分别向左右引伸找到 left - 1 < height[mid] 和 right + 1 < height[mid] 停止
    	//这样的话left 和 right之间的高度就height[mid]最小了
        //不用经常去算面积了
    //枚举高mid 是heights数组的下标;
        for (int mid = 0; mid < n; ++mid) {
            
            int left = mid, right = mid;
    
            // 确定左右边界
            while (left - 1 >= 0 && heights[left - 1] >= heights[mid]) --left;
            
            while (right + 1 < n && heights[right + 1] >= heights[mid]) ++right;
            
            // 计算面积
            area = max(area, (right - left + 1) * heights[mid]);
        }
        
        	cout<<"数组数据为："; 
        	for (int i = 0; i < heights.size(); i++)
		{
			myprint(heights[i]);
		}
			cout<<endl;
			cout<<"最大面积为："; 
        	cout<<area<<endl;
        return 0;
}
