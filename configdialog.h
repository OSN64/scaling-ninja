#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QApplication>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGridLayout>
#include <QSettings>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDir>
#include <QStringList>

#include "mylineedit.h"

class ConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigDialog();
    ~ConfigDialog();

    QString getString(QString);
    bool getBool(QString);
signals:

private slots:
    void save();
    void getServDir();
    void openServDir();
    void rmServDir();

private:
    void initWidgets();
    void initLayouts();
    void initConnect();

    void loadSettings();
    void saveSettings();

    void setAvailExitButtons(bool);

    QString settingsFile;

    QGroupBox *packagesGroup;
    QLabel *urlLabel;
    QLabel *servDirLabel;
    MyLineEdit *servDirLineEdit;
    QLineEdit *urlEdit;
    QPushButton *closeButton;
    QPushButton *saveButton;
    QPushButton *eraseButton;
    QPushButton *openDirButton;
    QCheckBox *autoUpCheckBox;
    QCheckBox *autoOpenCheckBox;
    QGridLayout *packagesLayout;
    QHBoxLayout *buttonsLayout;
    QVBoxLayout *mainLayout;

};

#endif // CONFIGDIALOG_H
