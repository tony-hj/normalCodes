import urllib.request
response = urllib.request.urlopen('https://movie.douban.com/subject/1292052/')
img = response.read()

with open('img.jpg','wb') as f:
    f.write(img)
