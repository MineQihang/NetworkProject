# NetworkProject
重庆大学《计算机网络》课程项目——网络协议的封装与解封装

## 编译运行

Windows / Linux

### Windows

可以使用Clion/VS Code等IDE打开项目，直接build然后run起来即可（或者自己去下载CMake然后命令行运行）

### Linux

在项目同目录下创建build文件夹并进入

```shell
mkdir build
```

CMake编译

```shell
cmake ..
```

make编译

```shell
make
```

运行

```shell
./Chat
```

## 项目参数

如果不需要显示中间结果，请进入`./src/utils/common.h`中修改`show_proc`为0.
