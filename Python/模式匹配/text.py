# -*- coding: utf-8 -*-
"""
Created on Fri Jun 26 10:25:39 2020

@author: 花祭
"""
import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt#Matplotlib是RGB
#%matplotlib inline 
def cv_show(name,img):  
    cv.imshow(name, img)
    cv.waitKey(0)
    cv.destroyAllWindows()

org = cv.imread("text.jpg")
img = cv.cvtColor(org, cv.COLOR_BGR2GRAY) 
temp = cv.imread("text_head.jpg",0)

h, w = temp.shape[:2] 

res = cv.matchTemplate(img, temp, cv.TM_SQDIFF)
min_val, max_val, min_loc, max_loc = cv.minMaxLoc(res)

img2 = img.copy()
top_left = min_loc
bottom_right = (top_left[0] + w, top_left[1] + h)
cv.rectangle(org, top_left, bottom_right, 255, 5)

cv_show("img", org)
plt.show()