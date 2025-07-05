#ifndef MONITORDIALOG_H
#define MONITORDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>
#include <QLabel>
#include "face.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MonitorDialog;
}
QT_END_NAMESPACE

class MonitorDialog : public QDialog
{
    Q_OBJECT

public:
    MonitorDialog(QWidget *parent = nullptr);
    ~MonitorDialog();

signals:
    // 识别人脸
    void recognize(QImage const& frame);

private slots:
    // 获取视频流并显示
    void on_m_btnStream_clicked();
    // 获取快照并显示
    void on_m_btnSnap_clicked();

    // 处理收到的视频流
    void on_m_streamReply_readyRead();
    // 处理收到的快照图片
    void on_m_snapReply_readyRead();

private:
    Ui::MonitorDialog *ui;

    QNetworkAccessManager *m_access;
    QNetworkReply *m_streamReply;
    QByteArray m_streamData;

    // 人脸识别的工作对象
    Face *m_face;
    // 构建的子线程
    QThread *m_thread;

    // 快照
    QNetworkReply *m_snapReply;
    // 快照数据
    QByteArray m_snapData;

    QLabel *m_labels[4];
    int m_index;
};
#endif // MONITORDIALOG_H
