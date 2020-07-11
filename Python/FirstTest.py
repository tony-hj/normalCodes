def fun(n):
    if n==1:
        return 1
    else:
        return n*fun(n-1)
       
temp = input("输入其数值：")
temp = int(temp)
print(fun(temp))
