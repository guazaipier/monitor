# 简介 监控摄像头，捕捉人物
## 模块
    1. 服务端推流
    2. 客户端拉流并获取快照
## 平台
### 服务端： vbox 虚拟机内安装的 24.04.1-Ubuntu 系统
### 客户端： windows 主机
## 构建
### 服务端
#### 安装 mjpg-stream
[mjpg-stream 详细步骤见 github](https://github.com/jacksonliam/mjpg-streamer)
```bash
sudo apt-get install cmake libjpeg8-dev
sudo apt-get install gcc g++
cd mjpg-streamer-experimental
make
sudo make install
```
#### 开启推流
```bash
./mjpg_streamer -i "input_uvc.so -n -f 60 -d /dev/video0" -o "output_http.so -w www"
```

#### 浏览器中获取流
ubuntu 虚拟机: http://127.0.0.1:8080/stream   
windows 主机: http://127.0.0.1:18080/stream    
其中虚拟机的 8080 端口映射到主机的 18080 端口     
### 客户端
使用 qt creator 编译并运行 monotor  
点击视频，即可获取到拉到的流信息，显示在左侧视频框中；  
点击快照，即可获取到当前视频快照，根据点击顺序显示在右侧四个图像框中。  
