#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfile.h"
#include "QMessageBox"
#include "iostream"
#include "QDebug"
#include "QApplication"
#include "QDir"
#include "QFileInfo"
#include "QThread"
#include "QFileDialog"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    thread.start();
    md5.moveToThread(&thread);

    qRegisterMetaType<QHash<QByteArray,QStringList> >("QHash<QByteArray,QStringList");

    connect(&md5,SIGNAL(getAllFilesMd5Signal(QHash<QByteArray,QStringList>)),
            this,SLOT(on_getAllFilesMd5Signal(QHash<QByteArray, QStringList>)));


    connect(this,SIGNAL(filesmd5(QString)),
            &md5,SLOT(getAllFilesMd5(QString)));


    connect(&md5,SIGNAL(progress(int,int)),
            this,SLOT(on_progress(int,int)));

}

MainWindow::~MainWindow()
{

    thread.exit();
    thread.wait(1000);
    delete ui;
}




void MainWindow::on_pushButton1_clicked()
{

//    QFile file("C:\\Users\\18351\\Desktop\\test.txt");
//    file.open(QIODevice::ReadOnly);
//    QString content = file.readAll();
//    QMessageBox::information(this,"",content);
//    qDebug() << content ;
//    qApp->processEvents();
//    md5.getAllFilesMd5("C:/Users/18351/Desktop/每日总结/");
      QString path = QFileDialog::getExistingDirectory(this,"请选择一个文件夹",".");
      ui->lineEdit->setText(path);
      ui->progressBar->setValue(0);
      emit filesmd5(path);
}

void MainWindow::on_getAllFilesMd5Signal(const QHash<QByteArray, QStringList> &res)
{
    ui->listWidget->clear();
    this->hashmd5 = res;
    for(QHash<QByteArray,QStringList>::const_iterator  itr = res.begin(); itr != res.end(); ++itr){
        //qDebug() <<"file:" << itr.value() << " md5:" << itr.key() << "  count:" << itr.value().count();
        ui->listWidget->addItem(itr.key());


    }
}

void MainWindow::on_progress(int current, int total)
{
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(current);
}




void MainWindow::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->listWidget_2->clear();
    QStringList filenames = this->hashmd5[currentText.toLocal8Bit()];
    ui->listWidget_2->addItems(filenames);
}
