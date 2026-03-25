def numbers():    
    n = int(input())
    p = float(input())
    arr = []
    x = 0
    for i in range(n):
        arr.append(float(input()))
    for k in range(n): 
        if arr[k] > 20.5:
            x = x + arr[k]
    print(x)
    return 0 