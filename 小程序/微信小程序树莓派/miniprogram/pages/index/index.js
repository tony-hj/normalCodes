//index.js
//获取应用实例
const app = getApp()
 
Page({
  data: {
    logo: "/res/rasp-logo.png",
    welcome: "欢迎使用树莓小车",
    enterBtn: "进入",
    PromoteMsg: "Please enter the server address (eg: http://x.x.x.x:8080)",
    reqURL: ""
  },
  // 从输入框中获取用户输入的服务器地址信息
  getURL: function (e) {
    this.setData({
      reqURL: e.detail.value
    })
  },
  enterClicked: function (e) {
    /*
     * 当按下进入按钮，需要做以下事情：
     * 1. 首先判断用户是否已经在输入框中输入完整的服务器地址
     * 2. 发起一个到服务器的GET请求，并分析服务器的响应结果
     * 3. 跳转到小车控制界面
    */
    console.log(this.data.reqURL)
 
    if (this.data.reqURL == '') {
      wx.showModal({
        title: '提示',
        content: '请先输入正确的服务器地址！',
      })
      return
    }
 
    // 发起到服务器的GET请求
    wx.request({
      url: this.data.reqURL,
      success: function (res) {
        // 在这里获取POST请求地址，以及视频流地址，然后赋值给全局变量，供control页面调用
        console.log(res.data.match(/url = \"(\S*)\"/)[1])
        console.log(res.data.match(/src=\"(\S*)\"/)[1])
        app.globalData.postURL = res.data.match(/url = \"(\S*)\"/)[1]
        app.globalData.cameraURL = res.data.match(/src=\"(\S*)\"/)[1]
 
        // 跳转到control页面
        wx.navigateTo({
          url: '/pages/control/control',
        })
      },
      fail: function(res) {
        wx.showModal({
          title: '提示',
          content: '请检查输入的服务器地址！',
        })
      }
    })
  }
})