#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "configdialog.h"
#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDebug>
#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QMessageBox>
#include <QTime>
#include <QDesktopServices>
#include <QClipboard>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openConfig();

private:
    Ui::MainWindow *ui;
    ConfigDialog confDialog;

    QString currentFile;
    QClipboard *clipboard;

    void uploadReady();
    void upload();
    QString getRandomString();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // MAINWINDOW_H
