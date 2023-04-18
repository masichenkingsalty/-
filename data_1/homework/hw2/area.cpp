#include"../../stack/stack.h"
#include"../../../vector/vector.h"
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
        
        //��midΪ�е�left��right�ֱ������������ҵ� left - 1 < height[mid] �� right + 1 < height[mid] ֹͣ
    	//�����Ļ�left �� right֮��ĸ߶Ⱦ�height[mid]��С��
        //���þ���ȥ�������
    //ö�ٸ�mid ��heights������±�;
        for (int mid = 0; mid < n; ++mid) {
            
            int left = mid, right = mid;
    
            // ȷ�����ұ߽�
            while (left - 1 >= 0 && heights[left - 1] >= heights[mid]) --left;
            
            while (right + 1 < n && heights[right + 1] >= heights[mid]) ++right;
            
            // �������
            area = max(area, (right - left + 1) * heights[mid]);
        }
        
        	cout<<"��������Ϊ��"; 
        	for (int i = 0; i < heights.size(); i++)
		{
			myprint(heights[i]);
		}
			cout<<endl;
			cout<<"������Ϊ��"; 
        	cout<<area<<endl;
        return 0;
}
