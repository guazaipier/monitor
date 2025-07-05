#ifndef FACE_H
#define FACE_H

#include <QObject>


class Face : public QObject
{
    Q_OBJECT
public:
    explicit Face(QObject *parent = nullptr);

signals:

public slots:
    void recognize(QImage const& frame);
};

#endif // FACE_H
