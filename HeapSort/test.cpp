#include"HeapSort.h"
#include<vector>
#include <iostream>
#include <cstring>
#include <cmath>
#include <chrono>
#include<algorithm>
#include <random>
#include <iterator>
using namespace std;

template <typename Comparable>
bool check(vector<Comparable> &arr)//检查排序是否正确
{
    for(size_t i = 0; i < arr.size()-1; ++i)
    {
        if(arr[i] > arr[i+1])
            return false;
    }
    return true;
}

void SortedVector(vector<int> &arr, int N)//构造有序序列
{
    for(int i = 1; i <= N; ++i)
        arr.emplace_back(i);//emplace_back函数在容器的末尾就地构造一个新元素
}

void RandomVector(vector<int> &arr, int N)//构造随机序列
{
    random_device seed;//生成随机种子
    mt19937 rnd(seed());//使用seed作为种子初始化mt19937随机数生成器
    for(int i = 0; i <= N; ++i)
    {
        arr.emplace_back(rnd());
    }
}

void ReverseVector(vector<int> &arr, int N)//构造逆序序列
{
    for(int i=N; i >= 1; --i)
        arr.emplace_back(i);
}

void RepeatedVector(vector<int> &arr, int N)//构造有重复元素的序列
{
    int count = 0;
    for(int i = 1; count <= N; ++i)
    {
        for(int j=1; j <= i; ++j)
        {
            arr.emplace_back(i);
            ++count;
        }
    }
    random_device seed; //生成随机种子
    mt19937 rnd(seed()); // 以seed作为种子生成随机数
    shuffle(arr.begin(), arr.end(),rnd);//打乱序列
}

void testHeapSort(vector<int> &arr)//测试HeapSort
{
    auto start = std::chrono::high_resolution_clock::now();//开始时间
    HeapSort(arr);
    auto end = std::chrono::high_resolution_clock::now();//结束时间
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    if(check(arr))//检查排序正确性
        std::cout << "Correct!" << std::endl;
    else
        throw invalid_argument("Wrong!");
    std::cout << "HeapSort time: " << duration.count() << "ms" << std::endl;
    arr.clear();
}

void testSTL(vector<int> &arr)//测试std::sort_heap
{
    auto start = std::chrono::high_resolution_clock::now();//开始时间
    make_heap(arr.begin(),arr.end());//建堆
    sort_heap(arr.begin(),arr.end());//堆排序
    auto end = std::chrono::high_resolution_clock::now();//结束时间
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    if(check(arr))//检查排序正确性
        std::cout << "Correct!" << std::endl;
    else
        throw invalid_argument("Wrong!");
    std::cout << "std::sort_heap time: " << duration.count() << "ms" << std::endl;
    arr.clear();
}

int main()
{
    vector<int> a={};//a用来测试HeapSort
    vector<int> b={};//b用来测试std::sort_heap
    
    std::cout << "test RandomVector" << std::endl;//测试随机序列
    RandomVector(a, 1000000);
    b=a;
    testHeapSort(a);
    testSTL(b);

    std::cout << "test SortedVector" << std::endl;//测试有序序列
    SortedVector(a, 1000000);
    b=a;
    testHeapSort(a);
    testSTL(b);

    std::cout << "test ReverseVector" << std::endl;//测试逆序序列
    ReverseVector(a, 1000000);
    b=a;
    testHeapSort(a);
    testSTL(b);

    std::cout << "test RepeatedVector" << std::endl;//测试重复元素的序列
    RepeatedVector(a, 1000000);
    b=a;
    testHeapSort(a);
    testSTL(b);
}