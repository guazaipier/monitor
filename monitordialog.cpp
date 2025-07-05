#include "monitordialog.h"
#include "ui_monitordialog.h"

MonitorDialog::MonitorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MonitorDialog)
    , m_access(new QNetworkAccessManager(this))
    , m_streamReply(Q_NULLPTR)
    , m_face(new Face)
    , m_thread(new QThread(this))
    , m_snapReply(Q_NULLPTR)
    , m_index(0)
{
    ui->setupUi(this);

    // 当前窗口 - recognize - m_face - recognize
    connect(this, &MonitorDialog::recognize, m_face, &Face::recognize);
    // m_face 加入子线程
    m_face->moveToThread(m_thread);
    // 子线程 - 人脸识别
    m_thread->start();// 线程启动 - 事件循环 - 等待信号触发 - 子线程 - 调用对应槽函数

    m_labels[0] = ui->m_labSnap1;
    m_labels[1] = ui->m_labSnap2;
    m_labels[2] = ui->m_labSnap3;
    m_labels[3] = ui->m_labSnap4;
}

MonitorDialog::~MonitorDialog()
{
    m_thread->terminate();
    m_thread->wait();

    delete m_face;
    m_face = Q_NULLPTR;

    delete ui;
}

void MonitorDialog::on_m_btnStream_clicked()
{
    m_streamReply = m_access->get(QNetworkRequest(QUrl("http://127.0.0.1:18080/?action=stream")));
    connect(m_streamReply, &QNetworkReply::readyRead, this, &MonitorDialog::on_m_streamReply_readyRead);
}


void MonitorDialog::on_m_btnSnap_clicked()
{
    m_snapReply = m_access->get(QNetworkRequest(QUrl("http://127.0.0.1:18080/?action=snapshot")));
    connect(m_snapReply, &QNetworkReply::readyRead, this, &MonitorDialog::on_m_snapReply_readyRead);

}

void MonitorDialog::on_m_streamReply_readyRead()
{
    m_streamData += m_streamReply->readAll();

    // jpeg 图像的开始标志 \xff\xd8
    int begin = m_streamData.indexOf("\xff\xd8", 0);
    if (begin == -1)
    {
        m_streamData.clear();
        return;
    }
    // jpeg 图像的开始标志 \xff\xd9
    int end = m_streamData.indexOf("\xff\xd9", begin + 2);
    if (end == -1)
        return;

    QImage frame;
    // m_streamData.mid(begin, end+2) 获取一张完整的图片信息
    if (!frame.loadFromData(m_streamData.mid(begin, end + 2), "JPG"))
    {
        m_streamData.clear();
        return;
    }
    // 将图片加载到 frame 中，清空 m_streamData
    m_streamData.clear();
    // 将图片加载到 m_labStream 中
    ui->m_labStream->setPixmap(QPixmap::fromImage(frame));
    // 视频流监控
    // 触发 recognize 信号 - m_face 的 recognize 槽函数（人脸识别）
    emit recognize(frame);

}

void MonitorDialog::on_m_snapReply_readyRead()
{
    m_snapData += m_snapReply->readAll();

    // jpeg 图像的开始标志 \xff\xd8
    int begin = m_snapData.indexOf("\xff\xd8", 0);
    if (begin == -1)
    {
        m_snapData.clear();
        return;
    }
    // jpeg 图像的开始标志 \xff\xd9
    int end = m_snapData.indexOf("\xff\xd9", begin + 2);
    if (end == -1)
        return;

    QImage frame;
    // m_snapData.mid(begin, end+2) 获取一张完整的图片信息
    if (!frame.loadFromData(m_snapData.mid(begin, end + 2), "JPG"))
    {
        m_snapData.clear();
        return;
    }
    // 将图片加载到 frame 中，清空 m_snapData
    m_snapData.clear();
    // 将图片加载到 m_labStream 中
    m_labels[m_index]->setPixmap(QPixmap::fromImage(frame).scaledToHeight(236));
    m_index = (m_index + 1) % 4;
}
