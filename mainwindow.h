#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <filemd5.h>
#include <QThread>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void filesmd5(const QString &path);

private slots:


    void on_pushButton1_clicked();
    void on_getAllFilesMd5Signal(const QHash<QByteArray,QStringList> &res);
    void on_progress(int current,int total);//显示进度条


    void on_listWidget_currentTextChanged(const QString &currentText);

private:
    Ui::MainWindow *ui;

    FileMd5 md5;
    QThread thread;
    QHash<QByteArray, QStringList> hashmd5;
};
#endif // MAINWINDOW_H
