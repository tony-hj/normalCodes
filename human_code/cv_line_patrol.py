#!/usr/bin/python3
# -*- coding: UTF-8 -*-
# 小球颜色识别后执行动作组
import sys
if sys.version_info.major == 2:
    print('Please run this program with python3!')
    sys.exit(0)
import cv2
import numpy as np
import time
import threading
from config import *
from cv_ImgAddText import *
import Serial_Servo_Running as SSR
import PWMServo
import math
import RPi.GPIO as GPIO

print('''
**********************************************************
*****巡线：通过摄像头检测黑线，使机器人沿着黑线运动*******
**********************************************************
----------------------------------------------------------
Official website:http://www.lobot-robot.com/pc/index/index
Online mall:https://lobot-zone.taobao.com/
----------------------------------------------------------
Version: --V1.1  2020/04/08
----------------------------------------------------------
''')

debug = True

servo1_ = servo1

#寻迹时摄像头舵机朝下看
PWMServo.setServo(1, servo1, 500)
PWMServo.setServo(2, servo2, 500)
#PWMServo.setServo(1, 1250, 500)
#PWMServo.setServo(2, 1000, 500)

#蜂鸣器io口初始化
buzzer_pin = 11
GPIO.setmode(GPIO.BCM)
GPIO.setup(buzzer_pin, GPIO.OUT)

#使用到的动作组，存储在/home/human_code/ActionGroups/
go_straight = 'go_straight_fast'
go_straight_trace_fast = 'go_straight_fast'
go_straight_trace_slow = 'go_straight_slow'
go_straight_kick = 'go_straight_slow'
turn_right = 'turn_right'
turn_left  = 'turn_left'

#寻迹时，画出的线框颜色
line_color = (255, 0, 0)
#寻迹时，画出的线框的粗细
line_thickness = 2         

orgFrame = None
orgframe = None
Running = True
#图像分辨率
ori_width, ori_height = 160, 120
#调用摄像头
stream = "http://127.0.0.1:8080/?action=stream?dummy=param.mjpg"
cap = cv2.VideoCapture(stream)
def get_img():
    global orgFrame
    while True:
        if cap.isOpened():
            #读取图片
            ret, orgframe = cap.read()          
            #将摄像头画面缩小以便处理
            orgFrame = cv2.resize(orgframe, (ori_width, ori_height), interpolation = cv2.INTER_CUBIC)
        else:
            time.sleep(0.01)

th1 = threading.Thread(target=get_img)
th1.setDaemon(True)     # 设置为后台线程，这里默认是False，设置为True之后则主线程不用等待子线程
th1.start()  

#映射函数
def leMap(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

#获取最大轮廓以及它的面积
def getAreaMax_contour(contours, area_min = 75):
        contour_area_temp = 0
        contour_area_max = 0
        area_max_contour = None

        for c in contours : #历遍所有轮廓
            contour_area_temp = math.fabs(cv2.contourArea(c)) #计算轮廓面积
            if contour_area_temp > contour_area_max :
                contour_area_max = contour_area_temp
                if contour_area_temp > area_min:  #只有在面积大于300时，最大面积的轮廓才是有效的，以过滤干扰
                    area_max_contour = c

        return area_max_contour, contour_area_max#返回最大的轮廓

roi = [ # [ROI, weight]
        (0,  20,  0, 160, 0.3), 
        (40, 60,  0, 160, 0.6), 
        (80, 100,  0, 160, 0.1)
       ]

black_line_centerx = 80
cross_line = 0
get_black_line = False
start_get_cross_line = False
get_cross_line = False
print_status = True
recode_line = 0
recode_center = 0
#寻迹主体程序，颜色为黑色
def Tracing(orgimage, r_w, r_h, r = roi, l_c = line_color, l_t = line_thickness):
    global black_line_centerx
    global cross_line, get_black_line, start_get_cross_line, count_go_straight, start_count
    global get_cross_line, print_status, go_straight, bridge_up, recode_line, recode_center
    
    Frame = cv2.GaussianBlur(orgimage, (3, 3), 0)#高斯模糊
    Frame = cv2.cvtColor(Frame, cv2.COLOR_BGR2LAB) #将图像转换到LAB空间
    Frame = cv2.inRange(Frame, color_range['black'][0], color_range['black'][1]) #根据lab值对图片进行二值化 
    opened = cv2.morphologyEx(Frame, cv2.MORPH_OPEN, np.ones((3,3),np.uint8))#开运算
    closed = cv2.morphologyEx(opened, cv2.MORPH_CLOSE, np.ones((3,3),np.uint8))#闭运算
           
    centroid_x_sum = 0
    area_sum = 0
    n = 0
    weight_sum = 0
    center_ = []
    max_area = 0
    #将图像分割成上中下三个部分，这样处理速度会更快，更精确
    for r in roi:
        n += 1
        blobs = closed[r[0]:r[1], r[2]:r[3]]
        cnts = cv2.findContours(blobs , cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_TC89_L1)[-2]#找出所有轮廓
        cnt_large, area = getAreaMax_contour(cnts)#找到最大面积的轮廓
        if cnt_large is not None:#如果轮廓不为空
            rect = cv2.minAreaRect(cnt_large)#最小外接矩形
            box = np.int0(cv2.boxPoints(rect))#最小外接矩形的四个顶点
            box[0, 1], box[1, 1], box[2, 1], box[3, 1] = box[0, 1] + (n - 1)*40, box[1, 1] + (n - 1)*40, box[2, 1] + (n - 1)*40, box[3, 1] + (n - 1)*40#对获取的点做处理
            
            #获取矩形的对角点
            pt1_x, pt1_y = box[0, 0], box[0, 1]
            pt3_x, pt3_y = box[2, 0], box[2, 1]

            cv2.drawContours(orgframe, [box], -1, (0,0,255,255), 2)#画出四个点组成的矩形
            center_x, center_y = (pt1_x + pt3_x) / 2, (pt1_y + pt3_y) / 2#中心点
            
            if n == 1:
                recode_line = 1
            elif n == 2 and recode_line == 0:
                recode_line = 2
            elif n == 2 and recode_line == 1:
                recode_line = 3
            elif n == 3 and recode_line == 0:
                recode_line = 4
                recode_center = center_x
            elif n == 3 and recode_line == 1:
                recode_line = 5 
            elif n == 3 and recode_line == 2:
                recode_line = 6
                recode_center = center_x
            elif n == 3 and recode_line == 3:
                recode_line = 7

            #cv2.circle(orgframe, (int(pt1_x), int(pt1_y)), 5, (0,0,255), -1)#画出中心点
            #根据面积来判断是否为十字交叉口
            if area > 1000:
                #当上部分检测到十字交叉口时，我们认为开始检测到十字交叉口
                if n == 1:
                    if (cross_line == 4 and count_go_straight > 20) or (cross_line == 6 and count_go_straight >= 25) or (cross_line == 8 and count_go_straight >= 10):
                        count_go_straight = 0
                        start_count = False
                        count_go_straight = 0
                        if print_status:
                            print_status = False
                            print('检测到黑色标识线')
                        start_get_cross_line = True
                    elif cross_line != 4 and cross_line != 6:
                        if print_status:
                            print_status = False
                            print('检测到黑色标识线')
                        start_get_cross_line = True
                elif n == 2 and ((cross_line == 4 and count_go_straight >= 20) or (cross_line == 6 and count_go_straight >= 25) or (cross_line == 8 and count_go_straight >= 10) or cross_line == 5) and bridge_up:
                    count_go_straight = 0
                    start_get_cross_line = True
                    start_count = False
                    if print_status:
                        print_status = False
                        print('检测到黑色标识线')
                    if cross_line == 7:
                        go_straight = go_straight_trace_slow
                elif n == 3:#当下部分检测到十字交叉口时，我们认为现在处于离十字交叉口最近的地发，且处于十字交叉口前方 
                    if start_get_cross_line:      
                        start_get_cross_line = False
                        #累计检测到的十字路口
                        cross_line += 1
                        get_cross_line = True
                        if not print_status and cross_line <= 9:
                            print_status = True
                            print('当前处于第' + str(cross_line) + '条标识线')
            else:
                center_.append([center_x,center_y])            
                cv2.circle(orgframe, (int(center_x), int(center_y)), 5, (0,0,255), -1)#画出中心点
                #按权重不同对上中下三个中心点进行求和
                centroid_x_sum += center_x * r[4]
                weight_sum += r[4]

    if weight_sum is not 0:
        #求最终得到的中心点
        black_line_centerx = int(centroid_x_sum / weight_sum)  
        if (recode_line == 4 or recode_line == 6) and abs(recode_center - 80) > 50 :
            black_line_centerx = 160 - black_line_centerx
            recode_line = 0
            recode_center = 0
        #print(black_line_centerx)
        get_black_line = True
    else:
        get_black_line = False

range_rgb = {'red': (0, 0, 255),
              'blue': (255, 0,0),
              'green': (0, 255, 0),
              'black': (0, 0, 0),
              'yellow':(255, 255, 0),
              }

color_list = []
COLOR = 'None'
cylinder_red_finish = False
cylinder_green_finish = False
cylinder_blue_finish = False
#颜色识别，主要用来识别红绿蓝三种颜色
def colors_identify(img):  
    global color_list, COLOR
    global cylinder_red_finish, cylinder_green_finish, cylinder_blue_finish

    GaussianBlur_img = cv2.GaussianBlur(img, (3,3), 0)#高斯模糊
    LAB_img = cv2.cvtColor(GaussianBlur_img, cv2.COLOR_BGR2LAB)#将图片转换到LAB空间
    
    rad = 0
    areaMax_contour = 0
    max_area = 0
    area_max = 0
    black_line_centerx = 0
    centerY = 0 
    #根据红绿蓝三种颜色的lab值进行处理
    for i in color_range:
        #去除黑色和黄色，防止干扰，提高速度
        if i != 'black' and i != 'yellow':
            #如果前面已经识别过其中的某种颜色，则此次不再识别，提高速度
            if (cylinder_red_finish == False and i == 'red') or (cylinder_green_finish == False and i == 'green') or (cylinder_blue_finish == False and i == 'blue'): 
                frame = cv2.inRange(LAB_img, color_range[i][0], color_range[i][1])#对原图像和掩模进行位运算
                opened = cv2.morphologyEx(frame, cv2.MORPH_OPEN, np.ones((3,3),np.uint8))#开运算
                closed = cv2.morphologyEx(opened, cv2.MORPH_CLOSE, np.ones((3,3),np.uint8))#闭运算
                contours = cv2.findContours(closed, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)[-2]#找出轮廓
                areaMax_contour, area_max = getAreaMax_contour(contours)#找出最大轮廓
                if areaMax_contour is not None:
                    if area_max > max_area:#找最大面积
                        max_area = area_max
                        color_max = i
                        areaMax_contour_max = areaMax_contour
    if max_area != 0:
        ((black_line_centerx, centerY), rad) = cv2.minEnclosingCircle(areaMax_contour_max)  # 获取最小外接圆
        black_line_centerx, centerY, rad = int(black_line_centerx), int(centerY), int(rad)#获取圆心，半径
        cv2.circle(orgframe, (black_line_centerx, centerY), rad, (0, 255, 0), 2)#画圆
        if color_max == 'red':  #红色最大
            color = 1
        elif color_max == 'green':  #绿色最大
            color = 2
        elif color_max == 'blue':  #蓝色最大
            color = 3
        else: 
            color = 0
        #获取最近10次的值
        color_list.append(color)
        if len(color_list) == 10:
            #取平均
            color = int(round(np.mean(color_list)))
            color_list = []
            if color == 1:
                COLOR = 'red'
            elif color == 2:
                COLOR = 'green'
            elif color == 3:
                COLOR = 'blue'
            else:
                return None
                color_max = 'None'
            return COLOR
        else:
            return None
    else:
        COLOR = "None"
        return None

X = 0
Y = 0 
get_ball = False
#区别与上一个，这个函数是识别特定的颜色，根据输入的颜色来识别
def color_identify(img, target_color = 'yellow'):
    global X, Y, get_ball
    
    GaussianBlur_img = cv2.GaussianBlur(img, (3, 3), 0)#高斯模糊
    LAB_img = cv2.cvtColor(GaussianBlur_img, cv2.COLOR_BGR2LAB) #将图像转换到LAB空间
    inRange_img = cv2.inRange(LAB_img, color_range[target_color][0], color_range[target_color][1]) #根据lab值对图片进行二值化 
    opened = cv2.morphologyEx(inRange_img, cv2.MORPH_OPEN, np.ones((3,3),np.uint8))#开运算
    closed = cv2.morphologyEx(opened, cv2.MORPH_CLOSE, np.ones((3,3),np.uint8))#闭运算
    contours = cv2.findContours(closed, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)[-2] #找出所有外轮廓
    areaMax_contour = getAreaMax_contour(contours, area_min = 3)[0] #找到最大的轮廓
    
    X = 999
    Y = 999
    radius = 0
    if areaMax_contour is not None:  #有找到最大面积
        if target_color != 'black':
            (X, Y), radius = cv2.minEnclosingCircle(areaMax_contour) #获取最小外接圆
            X = int(X)
            Y = int(Y)
            radius = int(radius)
            cv2.circle(orgframe, (X, Y), radius, range_rgb[target_color], 2) 
            #防干扰
            #print(X, Y)
            if radius > 5:
                get_ball = True       
                return True
        else:
            rect = cv2.minAreaRect(areaMax_contour)#最小外接矩形
            box = np.int0(cv2.boxPoints(rect))#最小外接矩形的四个顶点
            
            pt2_x, pt2_y = box[1, 0], box[1, 1]
            pt3_x, pt3_y = box[2, 0], box[2, 1]
            cv2.drawContours(orgframe, [box], -1, (0,0,255,255), 2)#画出四个点组成的矩形
            if pt2_x != pt3_x:
                line_angle = int((math.atan((pt2_y - pt3_y)/(pt2_x - pt3_x))/math.pi)*180)
            else:
                line_angle = 90
            print(line_angle)
            if 5 < abs(line_angle) < 50:
                #print('turn_left')
                return 'turn_left'
            elif 50 < abs(line_angle) < 85 or 95 < abs(line_angle):
                #print('turn_right')
                return 'turn_right'
            else:
                #print('center')
                return 'center'
    else:
        X, Y = -999, -999
        return False
        
cylinder_color = None
cylinder_start = True
get_cylinder = False
#每个圆柱对应的动作
def action(color, start = True):
    global go_straight, turn_left, turn_right, go_straight_trace_fast, go_straight_trace_slow, cylinder_color
    global cylinder_red_finish, cylinder_green_finish, cylinder_blue_finish, cylinder_start, get_cylinder, cross_line
    #每个动作只会执行一遍，例如红色圆柱的动作执行完，即使下次再识别到红色也不会执行，防止干扰
    if color == 'red' and cylinder_red_finish is False and cylinder_start:
        if start:
            print('执行red圆柱对应动作，蜂鸣器响')
            GPIO.output(buzzer_pin, 1)
            cylinder_color = color
            cylinder_start = False
            get_cylinder = False
            SSR.runAction('stand_fast')
            time.sleep(0.1)
            if cross_line == 5:
                SSR.runAction(go_straight)
                SSR.runAction(go_straight)
            SSR.runAction(go_straight)
            SSR.runAction(go_straight)
            SSR.runAction(go_straight)
            SSR.runAction(go_straight)
        else:
            print('停止red圆柱对应动作\n')
            GPIO.output(buzzer_pin, 0)
            cylinder_start = False
            SSR.runAction('stand_fast')
            time.sleep(0.1)
            cylinder_red_finish = True
    elif color == 'green' and cylinder_green_finish is False and cylinder_start:
        if start:
            print('执行green圆柱对应动作, 举起左手')
            cylinder_color = color
            cylinder_start = False
            get_cylinder = False
            #切换动作
            go_straight = 'left_hand_g'
            turn_left = 'left_hand_tl'
            turn_right = 'left_hand_tr'
            SSR.runAction('left_hand')
            time.sleep(0.1)
            if cross_line == 5:
                SSR.runAction('left_hand_g')
                SSR.runAction('left_hand_g')
            SSR.runAction('left_hand_g')
            SSR.runAction('left_hand_g')
            SSR.runAction('left_hand_g')
        else:
            print('停止green圆柱对应动作\n')
            cylinder_start = False
            #切换回动作
            go_straight = go_straight_trace_fast
            turn_left = 'turn_left'
            turn_right = 'turn_right'
            SSR.runAction('stand_fast')
            time.sleep(0.1)
            cylinder_green_finish = True
    elif color == 'blue' and cylinder_blue_finish is False and cylinder_start:
        if start:
            print('执行blue圆柱对应动作，举起右手')
            cylinder_color = color
            cylinder_start = False
            get_cylinder = False
            go_straight = 'right_hand_g'
            turn_left = 'right_hand_tl'
            turn_right = 'right_hand_tr'
            SSR.runAction('right_hand')
            time.sleep(0.1)
            if cross_line == 5:
                SSR.runAction('right_hand_g')
                SSR.runAction('right_hand_g')
            SSR.runAction('right_hand_g')
            SSR.runAction('right_hand_g')
            SSR.runAction('right_hand_g')
        else:
            print('停止blue圆柱对应动作\n')
            cylinder_start = False
            go_straight = go_straight_trace_fast
            turn_left = 'turn_left'
            turn_right = 'turn_right'
            SSR.runAction('stand_fast')
            time.sleep(0.1)
            cylinder_blue_finish = True
            
step = 1

kick = False
count = 0
find_ball = False

get_yellow_line = False

ready_trace = True
trace = True
count_go_straight = 0
start_count = False
set_black_line_centerx = centerx
go = turn_l = turn_r  = False
line_status = 3
find_goal = False
#寻迹，踢球逻辑动作处理部分，涉及到动作，所以单独作为一个线程运行，防止卡顿过长
def move():
    global get_black_line, black_line_centerx, set_black_line_centerx
    global go_straight, turn_left,turn_right,go_straight_kick
    global cross_line, get_cross_line, get_cylinder
    global cylinder_color, kick, ready_trace, trace
    global get_ball
    global X, Y
    global step 
    global find_ball
    global count, count_go_straight, start_count
    global get_yellow_line
    global cylinder_start 
    global go, turn_l, turn_r
    global line_status
    global find_goal
    global servo1_
    
    status = 1
    while True:
        if kick:
            if get_ball:
                count = 0
                if find_ball:
                    PWMServo.setServo(1, servo1, 100)
                    PWMServo.setServo(2, servo2, 100)
                    time.sleep(0.1)
                    find_ball = False
                    if status == 1:
                        get_ball = False
                        SSR.runAction('turn_right')
                        get_ball = False
                        status = 5
                    elif status == 2:  
                        get_ball = False
                        SSR.runAction('turn_left')
                        get_ball = False
                        status = 1
                    elif status == 3:
                        get_ball = False
                        SSR.runAction('turn_left')
                        SSR.runAction(go_straight_kick)
                        get_ball = False
                        status = 2
                    elif status == 4:
                        get_ball = False
                        SSR.runAction('turn_right')
                        SSR.runAction(go_straight_kick)
                        get_ball = False
                        status = 3

                elif step == 1:
                    print('进入步骤1')
                    if X - centerx > 50:#不在中心
                        print('X:' + str(X) + ' centerx:' + str(centerx) + '\n' + '球在右边-->>向右移动一步')
                        SSR.runAction('turn_right')
                        time.sleep(0.2)
                    elif X - centerx < -50:#不在中心
                        print('X:' + str(X) + ' centerx:' + str(centerx) + '\n' + '球在左边-->>向左移动一步')     
                        SSR.runAction('turn_left')
                        time.sleep(0.2)
                    else:#在中心
                        print('X:' + str(X) + ' centerx:' + str(centerx) + '\n' + '球在中心-->>转到步骤2')
                        step = 2
                elif step == 2:
                    print('进入步骤2')
                    if 60 < Y <= 110:
                        print('Y:' + str(Y) + '\n' + '球在最近处-->>转到步骤3')
                        step = 3
                    elif 0 <= Y <= 60:
                        print('Y:' + str(Y) + '\n' + '球在远处-->>向前走一步-->>回到步骤1')
                        SSR.runAction(go_straight_kick)
                        step = 1 
                    else:
                        step = 1            
                elif step == 3:
                    print('进入步骤3')
                    if X - centerx > 50 or -15 <  X - centerx < 15:#不在中心，根据方向让机器人转向一步
                        print('X:' + str(X) + ' centerx:' + str(centerx) + '\n' + '球偏右-->>站立-->>右移一步')
                        SSR.runAction('stand_fast')
                        SSR.runAction('right_move_one_step')
                        time.sleep(0.2)
                    elif X - centerx < -50:
                        print('X:' + str(X) + ' centerx:' + str(centerx) + '\n' + '球偏左-->>站立-->>左移一步')
                        SSR.runAction('stand_fast')
                        SSR.runAction('left_move_one_step')
                        time.sleep(0.2)
                    else:
                        print('X:' + str(X) + ' centerx:' + str(centerx) + '\n' + '球在中心-->>转到步骤4')
                        step = 4                   
                elif step == 4:
                    print('进入步骤4')
                    if X - centerx >= 0:
                        print('X:' + str(X) + ' centerx:' + str(centerx) + '\n' + '球在右-->>右脚射门')
                        SSR.runAction('shot_right')                      
                    elif X - centerx < 0:
                        print('X:' + str(X) + ' centerx:' + str(centerx) + '\n' + '球在左-->>左脚射门')
                        SSR.runAction('shot_left')
                    step = 1
                    print('回到步骤1')
                get_ball = False
            else:
                if step != 3 and step != 4:
                    count += 1
                    if count >= 20:
                        count = 0
                        if not find_ball:                       
                            find_ball = True
                            get_ball = False
                        if status == 1:
                            status = 2
                            get_ball = False
                            PWMServo.setServo(1, servo1 + 120, 100)
                            PWMServo.setServo(2, servo2 + 300, 100)
                            time.sleep(0.1)
                        elif status == 2:
                            status = 3
                            get_ball = False
                            PWMServo.setServo(1, servo1 + 250, 100)
                            PWMServo.setServo(2, servo2 + 300, 100)
                            time.sleep(0.1)
                        elif status == 3:
                            status = 4
                            get_ball = False
                            PWMServo.setServo(1, servo1 + 250, 100)
                            PWMServo.setServo(2, servo2 - 300, 100)
                            time.sleep(0.1)
                        elif status == 4:
                            status = 1
                            get_ball = False
                            PWMServo.setServo(1, servo1 + 120, 100)
                            PWMServo.setServo(2, servo2 - 300, 100)
                            time.sleep(0.1)
                    else:
                        time.sleep(0.01)
                else:
                    time.sleep(0.01)
        else:
            if get_cross_line:   
                if cross_line == 2 or cross_line == 5 or cross_line == 7:
                    #print('1111')
                    trace = False
                    get_black_line = False
                    get_cross_line = False
                    if cross_line == 7:
                        cylinder_start = True
                        if cylinder_blue_finish is False:
                            print('识别到blue圆柱')
                            action('blue', start = True)
                        elif cylinder_green_finish is False:
                            print('识别到green圆柱')
                            action('green', start = True)
                        elif cylinder_red_finish is False:
                            print('识别到red圆柱')
                            action('red', start = True)
                        trace = True
                    else:
                        SSR.runAction('stand_fast')
                        PWMServo.setServo(1, servo1 + 400, 500)
                        PWMServo.setServo(2, servo2 - 600, 500)
                        time.sleep(0.5)
                        ready_trace = False
                elif cross_line == 4 or cross_line == 6 or cross_line == 8:
                    get_cross_line = False
                    cylinder_start = True
                    print('完全进入缓冲区')
                    action(cylinder_color, start = False)
                    start_count = True
                    count_go_straight = 0
                elif cross_line >= 9:
                    get_cross_line = False
                    #print('go', go)
                    #if go:
                    print('停止寻线')
                    trace = False
                    get_black_line = False
                    time.sleep(1)
                    for i in range(7):
                        SSR.runAction('go_straight_fast')
                    kick = True
                    print('开始执行踢球程序')                    
            if get_cylinder:
                ready_trace = True
                get_cylinder = False
                get_cross_line = False
                cylinder_start = True
                print('识别到' + cylinder_color + '圆柱')
                PWMServo.setServo(1, servo1, 500)
                PWMServo.setServo(2, servo2, 500)
                time.sleep(0.5)
                action(cylinder_color, start = True)
                trace = True
            elif get_black_line and trace:
                get_black_line = False
                
                if cross_line == 5:
                    set_black_line_centerx = centerx
                elif cross_line == 6:
                    set_black_line_centerx = centerx + 12
                elif cross_line == 7:
                    set_black_line_centerx = centerx - 40
                elif cross_line == 8:
                    set_black_line_centerx = centerx
                    
                if line_status == 1:
                    PWMServo.setServo(1, servo1_, 100)
                    PWMServo.setServo(2, servo2, 100)
                    time.sleep(0.1)
                    SSR.runAction(turn_left)
                    turn_l = True
                    line_status = 0                     
                elif line_status == 2:
                    PWMServo.setServo(1, servo1_, 100)
                    PWMServo.setServo(2, servo2, 100)
                    time.sleep(0.1)
                    SSR.runAction(turn_right)
                    turn_r = True
                    line_status = 0                     
                elif abs(black_line_centerx - set_black_line_centerx) <= 23:
                    if turn_r or turn_l:
                        turn_r = turn_l = False
                        time.sleep(0.3)
                    SSR.runAction(go_straight)     
                    if start_count:
                        count_go_straight += 1
                    go = True
                elif black_line_centerx - set_black_line_centerx > 23:
                    if go:
                        go = False
                        time.sleep(0.5)
                    SSR.runAction(turn_right)
                    turn_r = True
                elif black_line_centerx - set_black_line_centerx < -23:
                    if go:
                        go = False
                        time.sleep(0.5)
                    SSR.runAction(turn_left)
                    turn_l = True
                line_status = 0
            else:
                if get_black_line is False and trace:
                    if line_status == 0:
                        line_status = 1
                        PWMServo.setServo(1, servo1_ + 120, 100)
                        PWMServo.setServo(2, servo2 + 300, 100)
                        time.sleep(0.1) 
                    elif line_status == 1:
                        line_status = 2
                        PWMServo.setServo(1, servo1_ + 120, 100)
                        PWMServo.setServo(2, servo2 - 300, 100)
                        time.sleep(0.1)
                time.sleep(0.01)

SSR.runAction('0')    
th2 = threading.Thread(target=move)
th2.setDaemon(True)     # 设置为后台线程，这里默认是False，设置为True之后则主线程不用等待子线程
th2.start()  

#cross_line = 3
bridge_up = False
#kick = True
yellow_line_y1 = 60
yellow_line_y2 = 100
get_yellow = False
while True:
    #获取一帧图像
    if orgFrame is not None:
        if Running:
            #对原图像不做任何处理，只作为显示，防止出错
            orgframe = orgFrame.copy()
            frame = orgFrame.copy()
            frame_width  = frame.shape[:2][1]
            frame_height = frame.shape[:2][0]
            #如果到了踢球环节            
            if kick:
                color_identify(frame, target_color = 'blue')                
            else:
                #在第三个交叉路口后就是上下桥环节，所以此时需要开启识别黄色程序
                if cross_line == 3:
                    get_bridge_color = color_identify(frame)
                    #只有识别到黄色且黄色处于图像的上部分，我们就切换为平稳步态，为了更稳定的识别黄色消失
                    if get_bridge_color and yellow_line_y2 >= Y > yellow_line_y1:
                        if get_yellow is False:
                            get_yellow = True
                            if bridge_up is False:
                                servo1_ = servo1 - 50
                                PWMServo.setServo(1, servo1_, 100)
                                time.sleep(0.2)
                            else:
                                servo1_ = servo1
                                PWMServo.setServo(1, servo1_, 100)
                                time.sleep(0.2)
                            go_straight = go_straight_trace_slow
                            print('开始检测到黄线，切换步态')
                    #当黄色处于下部分时
                    elif get_bridge_color and Y > yellow_line_y2:

                            #再次识别到黄色时，如果上桥标志为真，则执行下桥动作
                        if bridge_up:
                            if go:
                                print('开始执行下桥动作')
                                trace = False
                                get_black_line = False
                                time.sleep(1)#必要延时，让寻迹暂时停止
                                SSR.runAction('stand_fast')#立正，稳定
                                SSR.runAction('xia')#下桥
                                SSR.runAction('stand_fast')#立正，稳定
                                print('下桥完成')
                                go_straight = go_straight_trace_fast#步态切换回快
                                set_black_line_centerx = centerx - 20#寻迹中心点偏移
                                trace = True#寻迹恢复
                                count_go_straight = 0
                                start_count = True
                                cross_line = 4
                        get_yellow_line = True
                    else:
                        #当检测不到黄色时，且此前检测到过黄色，我们就开始计数前进的步数
                        if bridge_up is False:
                            if get_yellow_line:
                                if go:
                                    print('开始执行上桥动作')
                                    start_count = False
                                    count_go_straight = 0
                                    go = False
                                    get_yellow_line = False
                                    trace = False#寻迹暂停标志位
                                    get_black_line = False                                
                                    time.sleep(1)#必要的延时让寻迹暂时停止
                                    yellow_line_y1 = 40
                                    yellow_line_y2 = 90
                                    servo1_ = servo1 + 100
                                    PWMServo.setServo(1, servo1_, 100)
                                    time.sleep(0.2)
                                    go_straight = go_straight_trace_fast#寻迹步态改回快速
                                    SSR.runAction(go_straight_trace_slow)
                                    SSR.runAction(go_straight_trace_slow)
                                    SSR.runAction('stand_fast')#立正，稳定
                                    SSR.runAction('shang')#上桥
                                    print('上桥完成')
                                    time.sleep(0.2)
                                    bridge_up = True#标记一下上桥完成，防止下桥时识别成上桥
                                    trace = True#寻迹恢复
                if ready_trace:
                    if trace:
                        Tracing(frame, frame_width, frame_height)
                else:
                    #检测圆柱颜色
                    cylinders_color = colors_identify(frame)
                    if cylinders_color is not None:
                        cylinder_color = cylinders_color
                        get_cylinder = True
            if debug == 1:#调试模式下
                cv2.namedWindow('orgframe', cv2.WINDOW_AUTOSIZE)#显示框命名
                cv2.imshow('orgframe', orgframe) #显示图像
                cv2.waitKey(1)
        else:
            time.sleep(0.01)
    else:
        time.sleep(0.01)
cv2.destroyAllWindows()
