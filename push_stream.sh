#!/bin/bash
# 使用 mjpg_streamer 作为推流服务端
# platform: vbox虚拟机 24.04.1-Ubuntu
# download && install: https://github.com/jacksonliam/mjpg-streamer.git

# 开始推流 （摄像头插件： input_uvc.so 输出插件： output_http.so）
./mjpg_streamer -i "input_uvc.so -n -f 60 -d /dev/video0" -o "output_http.so -w www"

# 虚拟机 24.04.1-Ubuntu 内部拉流 （output_http.so 默认使用端口 8080）
# http://127.0.0.1:8080/stream.html
# 本地 windows 浏览器 （端口映射 8080 -> 18080）
# http://127.0.0.1:18080/stream.html
# 拉流
# http://127.0.0.1:18080/?action=stream
# 快照
# http://127.0.0.1:18080/?action=snapshot


