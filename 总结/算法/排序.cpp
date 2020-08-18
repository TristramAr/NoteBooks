#include <iostream>
#include <vector>

using namespace std;
//冒泡排序
class BubbleSort
{
public:
    vector<int> bubbleSort(vector<int> nums)
    {
        if (nums.size() == 0 || nums.size() == 1)
        {
            return nums;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            //通过mark避免已经排序成功后的继续循环
            // 如nums[5,1,2,3,4],第一轮交换已经完成排序，后续就无需在继续扫描数组
            bool mark = true;
            for (int j = 0; j < nums.size() - i - 1; j++)
            {
                if (nums[j + 1] < nums[j])
                {
                    // swap(nums[j], nums[j + 1]);
                    int temp = nums[j + 1];
                    nums[j + 1] = nums[j];
                    nums[j] = temp;
                    mark = false;
                }
            }
            if (mark)
            {
                return nums;
            }
        }
    }
};
//选择排序
class SelectSort
{
public:
    //选择排序
    void selectSort(vector<int> &nums)
    {
        if (nums.size() == 0 || nums.size() == 1)
        {
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[j] < nums[minIndex])
                {
                    minIndex = j;
                }
            }
            int temp = nums[i];
            nums[i] = nums[minIndex];
            nums[minIndex] = temp;
        }
    }
};
// 插入排序
class InsertSortSort
{
public:
    void insertSort(vector<int> &nums)
    {
        if (nums.size() == 0 || nums.size() == 1)
        {
            return;
        }
        for (int i = 1; i < nums.size(); i++)
        {
            int temp = nums[i];
            int k = i - 1;
            while (k >= 0 && temp < nums[k])
            {
                nums[k + 1] = nums[k];
                k--;
            }
            nums[k + 1] = temp;
        }
    }
};
// 希尔排序
class SheelSort
{
public:
    void shellSort(vector<int> &nums)
    {
        int len = nums.size();
        int temp, gap = len / 2;
        while (gap > 0)
        {
            for (int i = gap; i < len; i++)
            {
                temp = nums[i];
                int preIndex = i - gap;
                while (preIndex >= 0 && nums[preIndex] > temp)
                {
                    //
                    nums[preIndex + gap] = nums[preIndex];
                    preIndex -= gap;
                }
                nums[preIndex + gap] = temp;
            }
            gap /= 2;
        }
    }
};

//归并排序
class MergeSort
{
public:
    void mergeSort(vector<int> &nums)
    {
        if (nums.size() < 2)
        {
            return;
        }
        int mid = nums.size() / 2;
        //划分为左右两个数组
        vector<int> left;
        vector<int> right;

        for (int i = 0; i < mid; i++)
        {
            left.push_back(nums[i]);
        }
        for (int i = mid; i < nums.size(); i++)
        {
            right.push_back(nums[i]);
        }
        //递归划分
        mergeSort(left);
        mergeSort(right);
        nums.clear();
        merge(left, right, nums);
    }

private:
    void merge(vector<int> &left,
               vector<int> &right,
               vector<int> &result)
    {
        int i = 0;
        int j = 0;
        while (i < left.size() && j < right.size())
        {
            if (left[i] <= right[j])
            {
                result.push_back(left[i]);
                i++;
            }
            else
            {
                result.push_back(right[j]);
                j++;
            }
        }
        while (i < left.size())
        {
            result.push_back(left[i]);
            i++;
        }
        while (j < right.size())
        {
            result.push_back(right[j]);
            j++;
        }
    }
};
//快速排序
class QuickSort
{
public:
    // 写法一， 更好
    void quickSort_1(int left, int right, vector<int> &nums)
    {
        if (left >= right)
        {
            return;
        }
        int mid = nums[left];
        int i = left + 1;
        int j = right;
        while (true)
        {
            while (i <= j && nums[i] <= mid)
            {
                i++;
            }

            while (i <= j && nums[j] >= mid)
            {
                j--;
            }
            if (i >= j)
            {
                break;
            }
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
        nums[left] = nums[j];
        nums[j] = mid;
        quickSort_1(left, j - 1, nums);
        quickSort_1(j + 1, right, nums);
    }
    // 写法二
    void quickSort_2(int left, int right, vector<int> &nums)
    {
        if (left >= right)
        {
            return;
        }
        int i, j, base, temp;
        i = left;
        j = right;
        //选择最左边元素作为基准值
        base = nums[left];
        while (i < j)
        {
            //这里必须先从右向左遍历
            while (nums[j] >= base && i < j)
            {
                j--;
            }
            while (nums[i] <= base && i < j)
            {
                i++;
            }
            if (i < j)
            {
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
        nums[left] = nums[i];
        nums[i] = base;
        quickSort_2(left, i - 1, nums);
        quickSort_2(i + 1, right, nums);
    }
};

//堆排序
class HeapSort
{
public:
    void heapSort(vector<int> &nums, int size)
    {
        // 构建大根堆（从最后一个非叶子节点向上）
        //但是此时虽然满足了最大堆的特性，使得最大值在堆顶，但是并不是有序的
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            adjust(nums, size, i);
        }

        // 调整大根堆
        for (int i = size - 1; i >= 1; i--)
        {
            swap(nums[0], nums[i]); // 将当前最大的放置到数组末尾
            adjust(nums, i, 0);     // 将未完成的n-1个数字排序的部分继续进行堆排序，
                                    //然后将调整好的堆的堆顶再次放置到当前末尾
        }
    }

private:
    //递归方式构建大根堆(len是nums的长度，index是第一个非叶子节点的下标)
    void adjust(vector<int> &nums, int len, int index)
    {
        int left = 2 * index + 1;  //index左子树索引
        int right = 2 * index + 2; //index右子树索引
        int max_index = index;
        //如果当前节点的左子树或者右子树大于根节点，则更新为最大值索引
        if (left < len && nums[left] > nums[max_index])
        {
            max_index = left;
        }
        if (right < len && nums[right] > nums[max_index])
        {
            max_index = right;
        }
        if (index != max_index)
        {
            swap(nums[index], nums[max_index]);
            adjust(nums, len, max_index);
        }
    }
};

//计数排序
class CountSort
{
public:
    void countSort(vector<int> &nums)
    {
        if (nums.size() == 0)
        {
            return;
        }
        int max = nums[0];
        for (auto item : nums)
        {
            if (item > max)
            {
                max = item;
            }
        }
        vector<int> bucket(max + 1);
        for (int i = 0; i < nums.size(); i++)
        {
            bucket[nums[i]]++;
        }
        int index = 0;
        int i = 0;
        while (index < nums.size())
        {
            if (bucket[i] != 0)
            {
                nums[index] = i;
                bucket[i]--;
                index++;
            }
            else
            {
                i++;
            }
        }
    }
    void countSort_1(vector<int> &nums)
    {
        if (nums.size() == 0)
        {
            return;
        }
        int min = nums[0];
        int max = nums[0];
        //找到数组的最大值和最小值
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > max)
            {
                max = nums[i];
            }
            if (nums[i] < min)
            {
                min = nums[i];
            }
        }
        //如果数据不是从0开始的，为了使bucket数组的下标和要排序的数组对应，采用bias变量使原始数据从0开始
        // 这样可以减少内存，例如数据几种在100-150之间，只需要开辟一个size = 51 的计数数组
        // int bias = 0 - min;
        vector<int> bucket(max - min + 1, 0);
        for (int i = 0; i < nums.size(); i++)
        {
            bucket[nums[i] - min]++;
        }
        int index = 0;
        int i = 0;
        while (index < nums.size())
        {
            if (bucket[i] != 0)
            {
                nums[index] = i + min;
                bucket[i]--;
                index++;
            }
            else
            {
                i++;
            }
        }
    }
    vector<int> countSort_3(vector<int> &nums)
    {
        vector<int> result(nums.size(), 0);
        if (nums.size() == 0)
        {
            return nums;
        }
        int min = nums[0];
        int max = nums[0];
        //找到数组的最大值和最小值
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > max)
            {
                max = nums[i];
            }
            if (nums[i] < min)
            {
                min = nums[i];
            }
        }
        //如果数据不是从0开始的，为了使bucket数组的下标和要排序的数组对应，采用bias变量使原始数据从0开始
        // 这样可以减少内存，例如数据几种在100-150之间，只需要开辟一个size = 51 的计数数组
        // int bias = 0 - min;
        vector<int> bucket(max - min + 1, 0);
        for (int i = 0; i < nums.size(); i++)
        {
            bucket[nums[i] - min]++;
        }
        //累加数组
        for (int i = 1; i < bucket.size(); i++)
        {
            bucket[i] = bucket[i] + bucket[i - 1];
        }
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            result[bucket[nums[i] - min] - 1] = nums[i];
            bucket[nums[i] - min]--;
        }
        return result;
    }
};
//基数排序
class RadixSort
{
public:
    void radixSort(vector<int> &nums)
    {
        int max = nums[0];
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > max)
            {
                max = nums[i];
            }
        }
        int maxradix = 0;
        while (max != 0)
        {
            max = max / 10;
            maxradix++;
        }
        vector<vector<int>> bucket;
        // vector<int> result(nums.size(),0);
        for (int i = 0; i < 10; i++)
        {
            bucket.push_back(vector<int>());
        }
        int mod = 10;
        int div = 1;
        for (int i = 0; i < maxradix; i++)
        {
            for (int j = 0; j < nums.size(); j++)
            {
                int num = (nums[j] % mod) / div;
                bucket[num].push_back(nums[j]);
            }
            mod = mod * 10;
            div = div * 10;
            int index = 0;
            for (int i = 0; i < bucket.size(); i++)
            {
                for (int j = 0; j < bucket[i].size(); j++)
                {
                    nums[index] = bucket[i][j];
                    index++;
                }
                bucket[i].clear();
            }
        }
    }
};

int main()
{
    vector<int> nums{4, 0, 8, 5, 9, 5, 2, 12, 32, 14};
    RadixSort sort;
    sort.radixSort(nums);
    for (auto item : nums)
    {
        cout << item << " ";
    }
}