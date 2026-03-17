def binary_search(arr, target):
    left = 0
    right = len(arr) - 1

    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid  # Элемент найден
        elif arr[mid] < target:
            left = mid + 1  # Ищем в правой половине
        else:
            right = mid - 1  # Ищем в левой половине
        
    return -1  # Элемент не найден

my_list = [1, 3, 5, 7, 9, 11, 13]
target = 7
result = binary_search(my_list, target)
print(f"Индекс элемента: {result}")