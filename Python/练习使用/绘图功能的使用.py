import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt

# img = cv2.imread("text.jpg")
# print(img.shape)
# img = cv2.resize(img,(900,500))

#直线（图像，起始坐标，终点坐标，颜色）
#cv2.line(img, (0,0), (900,500), (255,0,0))
#矩形
#cv2.rectangle(img, (20,20), (300,500), (132,132,0),5)
#在图像上显示文字
# font = cv2.FONT_HERSHEY_SIMPLEX
# cv2.putText(img, "IRONMAN", (200,200), cv2.LINE_AA, 0.5, (0,0,255))

#鼠标指令 
# def draw_circle(event,x,y,flags,param):
#     if event == cv2.EVENT_MOUSEMOVE:
#         cv2.circle(img,(x,y),20,(255,0,0),-1)
# # 创建一个黑色的图像，一个窗口，并绑定到窗口的功能 
# cv2.namedWindow('image')
# cv2.setMouseCallback('image',draw_circle)
# while(1):
#     cv2.imshow('image',img)
#     #按下Esc退出 
#     if cv2.waitKey(20) & 0xFF == 27:
#         break
# cv2.destroyAllWindows()



# cv2.imshow("img",img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()

# cap = cv.VideoCapture(0)
# while(1):
#     # 读取帧
#     _, frame = cap.read()
#     # 转换颜色空间 BGR 到 HSV
#     hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
#     # 定义HSV中蓝色的范围
#     lower_blue = np.array([50,50,80])
#     upper_blue = np.array([255,255,200])
#     # 设置HSV的阈值使得只取蓝色
#     mask = cv.inRange(hsv, lower_blue, upper_blue)
#     # 将掩膜和图像逐像素相加
#     res = cv.bitwise_and(frame,frame, mask= mask)
#     cv.imshow('frame',frame)
#     cv.imshow('mask',mask)
#     cv.imshow('res',res)
#     k = cv.waitKey(5) & 0xFF
#     if k == 27:
#         break
# cv.destroyAllWindows()
# img = cv.imread('snow.jpeg')
# img = cv.resize(img, (900,500))
# cv.imshow("img",img)

# hist,bins = np.histogram(img.flatten(),256,[0,256])
# cdf = hist.cumsum()
# cdf_normalized = cdf * float(hist.max()) / cdf.max()
# plt.plot(cdf_normalized, color = 'b')
# plt.hist(img.flatten(),256,[0,256], color = 'r')
# plt.xlim([0,256])
# plt.legend(('cdf','histogram'), loc = 'upper left')
# plt.show()
# cdf_m = np.ma.masked_equal(cdf,0)
# cdf_m = (cdf_m - cdf_m.min())*255/(cdf_m.max()-cdf_m.min())
# cdf = np.ma.filled(cdf_m,0).astype('uint8')
# img2 = cdf[img] 
# img2 = cv.resize(img2, (900,500))
# cv.imshow("img2",img2)

# cv.waitKey(0)
# cv.destroyAllWindows()

# print(hist)
# cv.imshow("img",hist)
# cv.waitKey(0)
# cv.destroyAllWindows()


img = cv.imread('snow.jpeg',0)
# create a CLAHE object (Arguments are optional).
clahe = cv.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))
cl1 = clahe.apply(img)
cv.imwrite('clahe_2.jpg',cl1)


