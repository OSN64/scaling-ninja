#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionPreference,
                SIGNAL(triggered()),
                this,
                SLOT(openConfig()));

    clipboard = QApplication::clipboard();

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openConfig(){
    confDialog.show();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
        if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        currentFile = urlList.at(0).path(); // for now only suport one file
        uploadReady();
    } else {
        ui->urlLineEdit->setText(tr("Unable to read data"));
    }
    event->acceptProposedAction();
}
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}
void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}
void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}
void MainWindow::uploadReady(){
   bool autoUp =  confDialog.getBool("autoUpload"); // auto upload setting

   if(autoUp)
       upload();
   else
       qDebug() << "no auto upload";
}
void MainWindow::upload(){
    // copy file to the set server directory
    bool autoOpen = confDialog.getBool("autoOpen");
    QString urlPath = confDialog.getString("urlPath");
    QString servDir = confDialog.getString("webServerLoc");
    QFileInfo fInfo(currentFile);
    QString fileName = getRandomString() + "." + fInfo.suffix();
    QFile file(currentFile);

    if (!file.copy(servDir + fileName)){ // could not open file
        QMessageBox::critical(this,tr("Error"),tr("Could not copy file"));
        return;
    }
    file.close();

    QUrl url(urlPath + fileName);
    ui->urlLineEdit->setText(url.toString());
    clipboard->setText(url.toString());

    if (autoOpen)
        QDesktopServices::openUrl(url);
}
QString MainWindow::getRandomString()
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 12; // assuming you want random strings of 12 characters
   QTime now = QTime::currentTime();

   QString randomString;
   qsrand(now.msec());
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}
