def bubble_sort():
    n = input("Введите количество элементов ")
    arr = [input() for i in range(n)]
    sorted_arr = arr.copy()
    for k in range(n-1):
        swapped = False
        for j in range(n-1-k):
            num1 = int(sorted_arr[j], 2)
            num2 = int(sorted_arr[j + 1], 2)
            if num1>num2:
                sorted_arr[j], sorted_arr[j+1] = sorted_arr[j+1], sorted_arr[j]
                swapped = True
        if not swapped: 
            break
    return sorted_arr
print (bubble_sort)