#ifndef FILEMD5_H
#define FILEMD5_H

#include <QObject>

class FileMd5 : public QObject
{
    Q_OBJECT
public:
    explicit FileMd5(QObject *parent = nullptr);

signals:
    void getAllFilesMd5Signal(const QHash<QByteArray,QStringList> &res);
    void progress(int current,int total);

public slots:
    void getAllFilesMd5(const QString &path);

private:
    QStringList getFiles(const QString &path);//获取指定文件夹下所有文件
    QByteArray getFileMd5(const QString &filename);//获取某一文件名md5
};

#endif // FILEMD5_H
