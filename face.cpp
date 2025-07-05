#include "face.h"
#include <opencv2/opencv.hpp>
using namespace cv;

#include <QImage>
#include <QDebug>
#include <vector>
using namespace std;

Face::Face(QObject *parent)
    : QObject{parent}
{

}

// frame 传递过来的图片
void Face::recognize(QImage const& frame)
{
    // 将一个帧图片转换为 rgb888 格式的 QImage 类型
    QImage rgb888 = frame.convertToFormat(QImage::Format_RGB888);
    // QImage 转换为 mat 矩阵格式
    Mat image = Mat(rgb888.height(), rgb888.width(), CV_8UC3, rgb888.bits(), rgb888.bytesPerLine());

    CascadeClassifier faceClassifier;
    faceClassifier.load("D:\\3party\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_default.xml");

    Mat gray;
    cvtColor(image, gray, COLOR_RGB2GRAY);  // 将图像从彩色转换为灰色，降低颜色噪声干扰 公式为： gray = 0.299*R + 0.587*G + 0.114*B
    equalizeHist(gray, gray); //将图像的灰度直方图从集中的区域拉伸到整个灰度范围（0-255）

    vector<Rect> faces;
    faceClassifier.detectMultiScale(gray, faces); // 检测人脸

    if (faces.empty())
        qDebug() << "没有人进入监控区";
    else
        qDebug() << QString("%1 个人进入监控区").arg(faces.size());
}
