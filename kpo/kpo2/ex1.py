n = int(input("Введите количество элементов: "))
arr = []
for i in range(n):
    decimal_num = int(input(f"Введите десятичное число {i+1}: "))
    binary_num = bin(decimal_num)
    arr.append(binary_num)
print(f"Исходный массив двоичных чисел: {arr}")
sorted_arr = arr.copy()
for k in range(n-1):
    swapped = False
    for j in range(n-1-k):
        num1 = int(sorted_arr[j], 2)
        num2 = int(sorted_arr[j+1], 2)
        if num1 > num2:
            sorted_arr[j], sorted_arr[j+1] = sorted_arr[j+1], sorted_arr[j]
            swapped = True
    if not swapped:
        break
print("Отсортированный массив двоичных чисел: ", sorted_arr)