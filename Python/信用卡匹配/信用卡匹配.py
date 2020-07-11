from imutils import contours
import numpy as np
import argparse
import cv2
import myutils
def cv_show(name,img):
 	cv2.imshow(name, img)
 	cv2.waitKey(0)
 	cv2.destroyAllWindows()

# 指定信用卡类型
FIRST_NUMBER = {
 	"3": "American Express",
 	"4": "Visa",
 	"5": "MasterCard",
 	"6": "Discover Card"
}

#导入原始图片并显示     
img = cv2.imread("ocr_a_reference.png")
#cv_show("img",img)   
#将原视图片转换为灰度图并显示 
ref = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
#cv_show("gray",ref)
#二值图像
ref = cv2.threshold(ref, 175, 255, cv2.THRESH_BINARY_INV)[1]
#cv_show("ref",ref)
#计算轮廓 
#cv2.findContours()函数接受的参数为二值图，即黑白的（不是灰度图）,cv2.RETR_EXTERNAL只检测外轮廓，cv2.CHAIN_APPROX_SIMPLE只保留终点坐标
#返回的list中每个元素都是图像中的一个轮廓
#ref_, refCnts,hierarchy = cv2.findContours(ref.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
refCnts,hierarchy = cv2.findContours(ref.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cv2.drawContours(img, refCnts,-1, (0,0,255),3)
#cv_show("img",img)
#显示目前一共有多少轮廓
print(np.array(refCnts).shape)
refCnts = myutils.sort_contours(refCnts, method="left-to-right")[0] #排序，从左到右，从上到下
#字典 
digits = {}
for (i,c) in enumerate(refCnts):
    #计算外接矩形，并通过resize函数调整为合适大小
    #cv2.boundingRect(img) 函数返回4个参数x,y,w,h  x，y是矩阵左上点的坐标，w，h是矩阵的宽和高，img为输入的二值图
    (x,y,w,h) = cv2.boundingRect(c)
    roi = ref[y:y+h,x:x+w]
    roi = cv2.resize(roi, (57,88))
    
    #每个数字对应一个模板 
    digits[i] = roi
#print (digits)
#初始化卷积核 
rectKernel = cv2.getStructuringElement(cv2.MORPH_RECT, (9,3))
sqKernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5,5))

#读取输入图像
image = cv2.imread("credit_card_01.png")
#cv_show("image",image)
image = myutils.resize(image,width=300)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#cv_show("image_gray",gray) 
#顶帽操作，突出更明亮的区域
tophat = cv2.morphologyEx(gray, cv2.MORPH_TOPHAT, rectKernel)
#cv_show("tophat", tophat)
#Sobel算子,找到边缘，用算法对其进行处理
gradX = cv2.Sobel(tophat, ddepth=cv2.CV_32F, dx=1, dy=0)
gradX = np.absolute(gradX)
(minVal,maxVal) = (np.min(gradX),np.max(gradX))
gradX = (255 * ((gradX - minVal) / (maxVal - minVal)))
gradX = gradX.astype("uint8")
#cv_show("gradX",gradX)

#通过闭操作（先膨胀，再腐蚀）将数字连在一起(方便将其分成块) 
gradX = cv2.morphologyEx(gradX, cv2.MORPH_CLOSE, rectKernel) 
#cv_show('gradX',gradX)    
#结合OTSU方法自动进行判断阈值 
thresh = cv2.threshold(gradX, 0,255, cv2.THRESH_BINARY|cv2.THRESH_OTSU)[1] 
#cv_show("thresh", thresh)

#再来一个闭操作
thresh = cv2.morphologyEx(thresh, cv2.MORPH_CLOSE, sqKernel) #再来一个闭操作
#cv_show('thresh',thresh)

threshCnts, hierarchy = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
cnts = threshCnts
cur_img = image.copy()
cv2.drawContours(cur_img, cnts, -1, (0,0,255),3)
#cv_show("cur_img",cur_img)
locs = []

#遍历轮廓
for (i,c) in enumerate(cnts):
    (x,y,w,h) = cv2.boundingRect(c)
    ar = w / float(h)
     
    if ar > 1.5 and ar < 4.0:
        if(w>40 and w<55) and (h>10 and h<20):
            locs.append((x,y,w,h))
            
locs = sorted(locs, key=lambda x:x[0])
output = []

for (i,(gX,gY,gW,gH)) in enumerate(locs):
    groupOutput = []   
    # 根据坐标提取每一个组
    group = gray[gY - 5:gY + gH + 5, gX - 5:gX + gW + 5]
    #cv_show('group',group)     
    # group = gray[gY:gY + gH + 5, gX:gX + gW + 5]
    # cv_show('group',group) 
    #预处理
    group = cv2.threshold(group, 0,255,cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
    #cv_show("group_t",group) 
    # group = cv2.threshold(group, 175,255,cv2.THRESH_BINARY)[1]
    # cv_show("group_t",group) 
    #计算每一个轮廓
    digitCnts,hierarchy = cv2.findContours(group.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    digitCnts = contours.sort_contours(digitCnts,method = "left-to-right")[0]
    #计算每一组中的每一个数值
    for c in digitCnts:
        #找到当前数值的轮廓，resize成合适的大小
        
        (x,y,w,h) = cv2.boundingRect(c)
        roi = group[y:y+h,x:x+w]
        roi = cv2.resize(roi, (57,88))
        #cv_show("roi",roi)
        #计算匹配得分
        scores = []
        #在模板中计算每一个得分
        for (digit,digitROI) in digits.items():
            result = cv2.matchTemplate(roi,digitROI,cv2.TM_CCOEFF)
            (_,score,_,_) = cv2.minMaxLoc(result)
            scores.append(score)
            
        #得到最合适的数字
        groupOutput.append(str(np.argmax(scores)))
        
        #画
        cv2.rectangle(image,(gX-5,gY-5),(gX + gW + 5,gY + gH + 5),(0,0,255),1)
        cv2.putText(image,"".join(groupOutput),(gX,gY-15),cv2.FONT_HERSHEY_SIMPLEX,0.65,(0,0,255),2)
        
        #结果
        output.extend(groupOutput)

print("Credit Card Type: {}".format(FIRST_NUMBER[output[0]]))
print("Credit Card #:{}".format("".join(output)))
cv2.imshow("Image", image)
cv2.waitKey(0)
        
