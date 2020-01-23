# Snake

贪吃蛇怎么翻比较好听呢？

## 说明

- 因为本人贼菜还不会写前端也不知道怎么做动画，所以只能在控制台里一帧一帧显示，此即snake.cpp
- 后面去了解了一下关于控制台的一些内容，所以新写了一个newsnake.cpp

## 项目背景

贪吃蛇是带伙的老朋友了就8用多说了8

## 开发环境

- Windows 10 64位 ( DirectX 12 )

## 功能

snake.cpp：

- 逐帧显示游戏界面以实现动画
- 单次运行程序可以连续玩多局游戏
- 为了提高可玩性，蛇向上下左右移动时棋盘颜色分别显示白青紫黄四种不同颜色

newsnake.cpp：

- 终于不用一帧一帧显示了，呵护视力从我做起！
- 固定了游戏界面的位置，改进了游戏界面的设计，把游戏说明放在了游戏界面右侧
- 隐藏了光标，优化游戏体验
- 使用了一个队列和一个二维数组来判断蛇是否存活，代码较复杂但时间效率较高
- 目前存在的问题是游戏界面最左边边框不能正常起到限制作用

newnewsnake.cpp:

- 限定游戏开始时蛇头位置为游戏界面正中心，果实位置仍是随机生成
- 基本框架和newsnake.cpp相同，改用用向量来储存蛇的位置和判断是否存活，时间效率较差但是代码更简洁

## 贡献者

- [Jiaqi Dai](https://github.com/jqdai) - Fudan University

## 一些参考

- [别人做的“帧正的”贪吃蛇](https://blog.csdn.net/timerzip/article/details/83719740)
- [别人做的“真正的”贪吃蛇](https://blog.csdn.net/ganyonjie/article/details/91387649)
- [在控制台中输出不同颜色](https://blog.csdn.net/shinef/article/details/95026723)
- [清空队列（queue，不是deque）](https://www.cnblogs.com/zhonghuasong/p/7524624.html)
- [getchar，getch，getche的异同](https://blog.csdn.net/qq_28311415/article/details/81167211)
- [控制台界面控制](https://blog.csdn.net/bnb45/article/details/7934840)
- [控制台相关的API的用法](https://www.cnblogs.com/lanhaicode/p/10498497.html)
- [枚举类型](https://www.runoob.com/w3cnote/cpp-enum-intro.html)
