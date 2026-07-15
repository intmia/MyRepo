def quick_sort(arr):
    """
    快速排序（Quick Sort）
    使用分治法，选基准元素，将数组分为小于、等于、大于三部分，递归排序。
    """
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]          # 选择中间元素作为基准
    left = [x for x in arr if x < pivot]    # 小于基准的部分
    middle = [x for x in arr if x == pivot]  # 等于基准的部分
    right = [x for x in arr if x > pivot]   # 大于基准的部分
    return quick_sort(left) + middle + quick_sort(right)


if __name__ == "__main__":
    import sys

    if len(sys.argv) > 1:
        arr = [int(x) for x in sys.argv[1:]]
    else:
        arr = [3, 6, 8, 10, 1, 2, 1]

    print(f"原始数组: {arr}")
    sorted_arr = quick_sort(arr)
    print(f"排序结果: {sorted_arr}")
