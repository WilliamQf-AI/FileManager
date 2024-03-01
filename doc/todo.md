如果两个tab指向的路径完全一样，那就没必要刷新
标签页的图标要动态的
contentList记住滚动位置，切换滚动条时要用
icon cache 会持续增长
文件列表，最后一列的排序图标位置不对
content list 第一个clipRect 有的时候没用
title bar tab 画icon时 y的位置可以简化
content list 横向滚动条

content list 获取文件类型就去搞outlook了

AddressBar input text,selected,cursor,enter key change.
back, forward, up path, refresh
鼠标移入窗口，cursor不会改变。
tab页不要盖住最小化按钮

window name

监控文件目录的变化


TitleBar selected index.这要结合拖拽tab页功能一起做
Deskttop翻译成桌面

滚动条应该：SetCapture(root->hwnd);ReleaseCapture();


滚动滚动条还是会内存泄露


在一轮渲染中ICON图标缓存
列表按时间排序

输入框，输入文本
最近使用过的文件

双击标题栏最大化


增加Tab页，关闭Tab页
拖拽Tab页重新排序,延后绘制Tab
定义一个类，存储皮肤需要的颜色
测试以下Layout是否能正确的释放，和智能指针有无冲突

文件窗口也需要钉住窗口
拖拽Tab页时，打开新窗口，
打开一个新应用，进入单进程锁，还是在本应用中打开窗口


filternone


创建一个窗口
添加各种组件（组件属于此窗口）

再创建一个窗口
添加各种组件（组件属于此窗口）

什么时候需要得到组件的父组件