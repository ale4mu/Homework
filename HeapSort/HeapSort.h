#include <vector>
using namespace std;

template <typename Comparable>
void Heapify( vector<Comparable> &arr,int i,int n )//使parent>child
{
    int parent = i;
    while(true)//递归可能导致栈溢出
    {   
        int theMax=parent; //默认parent是最大元
        int leftchild = 2*theMax + 1;
        int rightchild = 2*theMax + 2;
        //比较parent与child的大小
        if( leftchild < n && arr[ theMax ] < arr[ leftchild ] )
            theMax = leftchild;
        if( rightchild < n && arr[ theMax ] < arr[ rightchild ] )
            theMax = rightchild;
        if(theMax != parent)//parent不是最大的
        {
            swap( arr[ parent ], arr[ theMax ]);//交换最大元到parent的位置
            parent=theMax;//交换后到下一级维护堆
        }
        else
            break;
    }
}

template <typename Comparable>
void BuildHeap(vector<Comparable> &arr)//建立最大堆
{
    int size=arr.size();
    for(int i = size/2-1;i >= 0; --i)//从最后一个非叶子节点开始，向上建堆
    {
        Heapify(arr, i, size);
    }
}

template <typename Comparable>
void DeleteMax(vector<Comparable> &arr, int i)
{
    swap(arr[0], arr[i]);//将根节点即最大元素与数组末尾的元素交换
    Heapify(arr, 0, i);//重建堆维持最大堆的性质
}

template <typename Comparable>
void HeapSort(vector<Comparable> &arr)
{
    BuildHeap(arr);//构建最大堆
    for(int i = arr.size()-1; i > 0; --i)//不断将当前最大元素交换到数组末尾
        DeleteMax(arr, i);
}