'''number = 7
guess = 2
print("数字猜谜游戏！")
while guess != number:
    guess = int(input("请输入你猜的数字："))
    if guess == number:
        print("恭喜，猜对了！")
    elif guess < number:
        print("猜的数字小了，，，，")
    elif guess > number:
        print("猜的数字大了，，，，")'''

        

'''num = int(input("请输入一个数字："))
if num%2==0:
    if num%3==0:
        print("你输入的数字可以整除2和3！")
    else:
        print("你输入的数字可以整除2，不能整除3！")
else:
    if num%3==0:
        print("你输入的数字可以整除3，不能整除2")
    else:
        print("你输入的数字不能整除2和3")'''


'''n = 100
counter = 1
sum = 0
while counter <= n:
    sum = counter + sum
    counter += 1
print("1到100之间数字的和为%d"%(n,sum))'''

'''var = 1
while var == 1:
    num = int(input("输入一个数字 :"))
    print ("你输入的数字是: ", num)
    print ("Good bye!")'''

'''flag = 1
while (flag): print("十年生死两茫茫")'''

'''sites = ["baidu","google","runoob","taobao"]
for site in sites:
    if site == "runoob":
        print("菜鸟教程！")
        break
    print("循环数据" + site)
else:
        print("没有循环数据!")
        print("没有循环！")

for letter in 'runoob':
    if letter == 'b':
        break
    print('当前字母为：',letter)'''

'''var = 10
while var > 0:
    print("当期变量值为：",var)
    var -= 1
    if var == 5:
        break
    print("Good bye!")'''

'''for n in range(2, 10):
    for x in range(2, n):
        if n % x == 0:
            print(n, '等于' , x ,'*' ,n//x)
            break
    else:
        print(n, '是质数')'''


'''for n in range(2, 10):
    for x in range(2, n):
        if n % x == 0:
            print(n, '等于', x, '*', n//x)
            break
    else:
        print(n, ' 是质数')'''

'''for n in range(2, 10):
    for x in range(2, n):
        if n % x == 0:
            print(n, '等于', x, '*', n//x)
            break
    else:
        print(n, '是质数')'''

'''for letter in 'Runoob':
    if letter ==  'o':
        pass
        print("执行pass块")
    print("当前字母:",letter)
    
print("Good bye")'''

'''list=[1,2,3,4]
it = iter(list)
for x in it:
    print(x," ")'''


'''import sys

list=[1,2,3,4]
it = iter(list)

while True:
    try:
        print (next(it))
    except StopIteration:
        sys.exit()'''






