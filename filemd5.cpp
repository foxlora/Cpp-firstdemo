#include "filemd5.h"
#include "qfile.h"
#include "QMessageBox"
#include "iostream"
#include "QDebug"
#include "QApplication"
#include "QDir"
#include "QFileInfo"
#include "QCryptographicHash"
#include "QHash"



FileMd5::FileMd5(QObject *parent) : QObject(parent)
{

}

void FileMd5::getAllFilesMd5(const QString &path)
//获取所有文件的md5
{
    QHash<QByteArray,QStringList> res;
    QStringList files = getFiles(path);
    for(int i=0;i<files.count();++i){

        QString filename = files.at(i);
        QByteArray md5 = getFileMd5(filename);

        res[md5].append(filename);
        emit progress(i+1,files.count());
    }



    emit getAllFilesMd5Signal(res);
}

QStringList FileMd5::getFiles(const QString &path)
{
    QStringList res;
    QDir dir(path);
    QFileInfoList infolist = dir.entryInfoList(QDir::Files|QDir::Dirs| QDir::NoDotAndDotDot);//可添加过滤信息

    for (QFileInfo info : infolist) {
        //如果是文件夹，则继续遍历文件夹
        if (info.isDir()){
            QString subdir = info.absoluteFilePath();
            QStringList files = getFiles(subdir);
            res.append(files);
        }
        else {
            //如果是文件，直接加入res
            QString filename = info.absoluteFilePath();
            res.append(filename);
        }

    }
    return res;
}

QByteArray FileMd5::getFileMd5(const QString &filename)
{
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly)){
        QCryptographicHash hash(QCryptographicHash::Md5);
        while(!file.atEnd()){
            QByteArray content = file.read(100 * 1024 * 1024);
            hash.addData(content);
            qApp->processEvents();
        }

        QByteArray md5 = hash.result().toHex();

        return md5;
    }



}
