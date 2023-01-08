#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>

int kthLargest(std::vector<int>& arr, int k){
  std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  
  for(int i = 0; i < k; ++i){
    pq.push(arr[i]);
  }
  
  size_t arrSize = arr.size();
  for(size_t i=k; i < arrSize; ++i){
    int kMax = pq.top();
    if(kMax < arr[i]){
        pq.pop();
        pq.push(arr[i]);
    }
  }
  return pq.top();
}

int main(){
  std::vector<int> arr = {4,7,3,5,8,1,12,6,9};
  int kth = 3;    // 8
  // int kth = 4; // 7
  
  int getElem = kthLargest(arr, kth);
  printf("%dth largest:%d", kth, getElem);
}

//struct LinkList{
//  int* value;
//  LinkList* next;
//  LinkList()
//    :value(nullptr), LinkList(nullptr)
//  {}
//};
//
//int kthLargest(int k, int* array, int len){
//  LinkList list[k]
//  LinkList* head = list;
//  for(int i = 1; i < k; ++i){
//     list[i-1].next = list[i];
//  }
//  
//  list[0].value = &array[0]
//  LinkList* start = list + 1;
//  LinkList* end   = list + k;
//  
//  int* currElemPtr = array + 1;
//  
//  // sort the 1st kth element into the box
//  // in ascending order
//  while(start != end){
//    *start = currElemPtr;
//    
//    // sorting
//    if(start > *currElemPtr){
//      
//      int** tmp = moveBox;
//      
//      while(tmp != box){
//        if(*tmp < )
//        int *swap = *(tmp-1)
//        *(tmp-1) = currElemPtr
//        *tmp = swap;
//
//        --tmp
//      }
//      
//    } else {
//      
//    }
//    
//    
//    ++moveBox;
//    ++currElemPtr;
//  }
//
//  // maintain kth elemnt, if the 1st element is smaller
//  
//  return 0;
//  
//}
//
//int main(){
//  int kth = 3;
//  int testA[9] = {4,7,3,5,8,1,12,6,9};
//  
//  int getElem = kthLargest(kth, testA, sizeof(testA)/sizeof(testA[0]));
//  printf("%dth largest:%d", kth, getElem);
//}
