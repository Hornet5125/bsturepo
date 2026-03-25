def max_number():
    print('Введите интервал ')
    a = int(input())
    b = int(input())
    max_summ = 0 
    if (a>b):
        for i in range(a, b+1):
            x=0
            for k in range(1,i+1):
                if (i%k==0):
                    x = x + k
                if (max_summ<x):
                    max_summ = x
                    max = i
    print(max,max_summ)
    return 0 