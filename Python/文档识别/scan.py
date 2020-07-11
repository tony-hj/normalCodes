import numpy as np
import cv2
import argparse

def cv_show(name ,img):
    cv2.imshow(name,img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
img = cv2.imread("page.jpg")
#img.shape[0]得到的是图片的高,img.shape[1]得到的是图片的宽 
ratio = img.shape[0] / 500.0

img = cv2.resize(img, (500,500))

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray = cv2.resize(gray, (500,500))
cv_show("grat",gray)
gray = cv2.GaussianBlur(gray, (5,5), 0)

cv_show("grat",gray)

edged = cv2.Canny(gray, 75, 200)
cv_show("canny算子",edged)

cnts,hierarchy = cv2.findContours(edged.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

cnts = sorted(cnts,key = cv2.contourArea,reverse = True)[:1]
cv2.drawContours(img, cnts, -1, (0,0,255),3)
 
# cnt = cnts[3]
# cv2.drawContours(img, [cnt], 0, (0,0,255))

cv_show("finish",img)

