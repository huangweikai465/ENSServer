[TOC]

# Easy Net Service Server

| 版本 | 更新时间   | 说明 |
| ---- | ---------- | ---- |
| V1.0 | 2020/10/23 | 初版 |

## 项目说明

该项目主要解决局域网下，服务器处于动态IP网络下的问题，该项目能够动态获取服务器地址，并支持使用系统默认工具打开链接。这里是服务端代码，兼容Windows、MacOS、Linux平台，项目环境依赖少,文件体积小，从嵌入式arm设备到大型服务器均适用。目前使用的是明文传输，后续会更新加密传输功能。

## 编译安装

### Linux/MacOS

需要安装 gcc、g++、make、cmake等编译工具。

使用如下指令编译安装指令如下：

``` bash
#创建编译文件夹
mkdir build
cd build
#编译
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
#安装
sudo make install
```

如果需要开机自启，需要执行如下指令：

``` bash
sudo cp ./shell/ens.service /lib/systemd/system/
sudo systemctl daemon-reload
#启动服务
sudo systemctl ens start
#开机自启
sudo systemctl enable ens
```

### Windows

1. 新建build文件夹

2. 在build文件夹下，如下命令行生成VS工程：

   ``` bash
   cmake ..
   ```

3. 使用VS打开EasyNetService.sln，编译。编译成功后会在 build/bin下生成Debug或者Release文件夹分别存放对应的可执行文件

## 启动服务端程序

在命令行中执行如下命令即可：

``` bash
ensserver
```

默认使用4657端口作为UDP通信端口，如果需要修改可以执行如下指令：

``` bash
#例如使用5678作为UDP通信端口
ensserver -u 5678
```

## 管理服务

可通过ensmanager配置当前服务，默认ssh和ftp服务示例。

服务管理操作如下：

``` bash
#列出当前服务
ensmanager ls
#删除服务
#删除某端口上的服务
ensmanager rm -p 3456
#删除名称为ExampleFTP的服务
ensmanager rm -n ExampleFTP
#将ExampleFTP重命名为MyFTP
ensmanager rn ExampleFTP MyFTP
#新增服务，例如在80端口新增一个名为MyWeb的web服务
ensmanager add -p 80 -t web -n MyWeb
```

## 新增类型

新增一个类型操作如下（以新增samba服务为例）：

1. 在服务端新增smb类型的服务，如下：

   ``` bash
   ensmanager add -p 0 -t smb -n MySamba
   ```

2. 在<font color=orange>客户端右键单击后，在“应用配置”下新增打开smb服务的命令行指令</font>，例如：

   ``` bash
   #windows客户端上：
   start \\$(IP)
   #Mac客户端上：
   open smb://$(IP)
   ```