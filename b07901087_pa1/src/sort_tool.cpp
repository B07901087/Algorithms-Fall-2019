// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i=1;i<data.size();i++)
	{
        int key = data[i];
        
        int j = i - 1;
        while(j>=0 && key<data[j])
        {
            data[j+1] = data[j];
            
            j--;
        }
        data[j + 1] = key;
	}
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if (low<high)
    {
        int p=Partition(data, low, high);
        QuickSortSubVector(data, low, p);
        QuickSortSubVector(data, p+1, high);
        
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int pivot = data[low+(high-low)/2];
    int prev = low - 1;
    int after = high + 1;
    
    while (true)
    {
        
        while (true)
        {
            prev += 1;
            if (data[prev] >= pivot)
            {
                break;
            }
        }
        while (true)
        {
            after -= 1;
            if(data[after] <= pivot)
            {
                break;
            }
        }
        if(prev<after)
        {
            int temp=data[prev];
            data[prev] = data[after];
            data[after] = temp;
        }
        else
        {
            return after;
        
        }
    }
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low<high)
    {
    int mid = int((low + high) / 2);
    MergeSortSubVector( data,low,mid);
    MergeSortSubVector( data,mid+1,high);
    SortTool::Merge(data,low,mid,mid+1,high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int data_index = low;
    vector<int> lsubvector(& data[low], & data[middle1+1] );
    vector<int> rsubvector(& data[middle2],& data[high+1]);
    

    int left_index = 0;
    int right_index = 0;
    int llength = middle1 - low +1;
    int rlength = high - middle2 +1;
    
    
    
    while (left_index <= llength-1 || right_index <= rlength-1)
    {
        
        
        if ( (lsubvector[left_index] <= rsubvector[right_index] || right_index > rlength-1) && left_index <= llength-1)
        {
            
            data[data_index]=lsubvector[left_index];
            left_index++;
            
        }
        else
        {
            if(right_index <= rlength-1)
            {
                data[data_index] = rsubvector[right_index];
                right_index++;
            }
        }
        data_index++;
        
    }

}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    
    int L=(root+1)*2-1; 
    int R=(root+1)*2;
    int max = root;
    if (L<heapSize || R<heapSize)
    {
        
        if(data[root]<data[L] && L<heapSize)
        {
            max = L;
        }
        if (data[max]<data[R] && R<heapSize)
        {
            max = R;
            
        }
        if (max==root)
        {
            
        }
        else
        {
            int temp = data[root];
            data[root]= data[max];
            data[max] = temp;
            
            MaxHeapify(data, max);
            
        }
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = heapSize/2; i >= 0;i--)
    {
        MaxHeapify(data, i);
    }
}
