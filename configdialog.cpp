#include "configdialog.h"
#include <QDebug>

ConfigDialog::ConfigDialog()
{
    settingsFile = QApplication::applicationDirPath()
            + "/scaling.ini";

    initWidgets();
    initConnect();
    initLayouts();
    loadSettings();

    setWindowTitle(tr("Config Dialog"));
}
ConfigDialog::~ConfigDialog()
{

}

// initialising all objects
void ConfigDialog::initWidgets(){
    packagesGroup = new QGroupBox(tr("Server Config"));

    urlLabel = new QLabel(tr("Url Path:"));
    urlEdit = new QLineEdit;

    servDirLabel = new QLabel(tr("Server Directory:"));
    servDirLineEdit = new MyLineEdit;

    closeButton = new QPushButton(tr("Close"));
    saveButton = new QPushButton(tr("Save"));

    autoUpCheckBox = new QCheckBox(tr("Automatic upload"));
    autoOpenCheckBox = new QCheckBox(tr("Open file in browser when finished"));

    eraseButton = new QPushButton("Erase Server Directory");
    openDirButton = new QPushButton("Open Server Directory");

    // set colour of the above buttons
    QPalette lp = palette();
    lp.setBrush(QPalette::Button,Qt::red);
    eraseButton->setPalette(lp);

    QPalette rp = palette();
    rp.setBrush(QPalette::Button,Qt::green);
    openDirButton->setPalette(rp);
}
// set all the widget layouts
void ConfigDialog::initLayouts(){
    packagesLayout = new QGridLayout;
    packagesLayout->addWidget(urlLabel, 0, 0);
    packagesLayout->addWidget(urlEdit, 0, 1);

    packagesLayout->addWidget(servDirLabel, 1, 0);
    packagesLayout->addWidget(servDirLineEdit, 1, 1);

    packagesLayout->addWidget(autoUpCheckBox, 2, 0);
    packagesLayout->addWidget(autoOpenCheckBox, 3, 0);

    packagesLayout->addWidget(eraseButton, 4, 0);
    packagesLayout->addWidget(openDirButton, 4, 1);

    packagesGroup->setLayout(packagesLayout);

    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);
    buttonsLayout->addWidget(saveButton);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
}
// initalise all the user events
void ConfigDialog::initConnect(){
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));

    connect(servDirLineEdit,SIGNAL(focussed(bool)),this,SLOT(getServDir()));
    connect(eraseButton, SIGNAL(clicked()), this, SLOT(rmServDir()));
    connect(openDirButton, SIGNAL(clicked()), this, SLOT(openServDir()));

}
void ConfigDialog::loadSettings(){
    QSettings settings(settingsFile, QSettings::IniFormat);
    QString urlPath = settings.value("urlPath").toString();
    QString webServerLoc = settings.value("webServerLoc").toString();
    bool autoUpload = settings.value("autoUpload").toBool();
    bool autoOpen = settings.value("autoOpen").toBool();

    // set view object values
    urlEdit->setText(urlPath);
    servDirLineEdit->setText(webServerLoc);
    autoUpCheckBox->setChecked(autoUpload);
    autoOpenCheckBox->setChecked(autoOpen);

}
void ConfigDialog::saveSettings(){
    QSettings settings(settingsFile, QSettings::IniFormat);

    settings.setValue("urlPath",urlEdit->text());
    settings.setValue("webServerLoc",servDirLineEdit->text() + "/");
    settings.setValue("autoUpload",autoUpCheckBox->isChecked());
    settings.setValue("autoOpen",autoOpenCheckBox->isChecked());
}
void ConfigDialog::save(){
    saveSettings();
    close();
}
void ConfigDialog::getServDir(){
    servDirLabel->setFocus(); // workaround for constant focus signals
    QString directory = QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory"),
                servDirLineEdit->text(), // directory to start from
                QFileDialog::ShowDirsOnly
                );
    if (directory != ""){ // if file is not nothing
        servDirLineEdit->setText(directory);
    }else{
        qWarning() << "Error reading geting server directory";
    }
}
void ConfigDialog::openServDir(){
    QDesktopServices::openUrl(servDirLineEdit->text());
}
void ConfigDialog::rmServDir(){
    setAvailExitButtons(false);
    // do checks here
    QDir dir(servDirLineEdit->text());
    if(dir.isRoot() || !dir.exists()){
        setAvailExitButtons(false);
        return qWarning("Unable to remove directory contents");
    }
    dir.setNameFilters(QStringList() << "*.*");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList())
    {
        dir.remove(dirFile);
    }
    setAvailExitButtons(true);
}
void ConfigDialog::setAvailExitButtons(bool enabled){
    closeButton->setEnabled(enabled);
    saveButton->setEnabled(enabled);
}
QString ConfigDialog::getString(QString key){
    QSettings settings(settingsFile, QSettings::IniFormat);
    return settings.value(key).toString();
}
bool ConfigDialog::getBool(QString key){
    QSettings settings(settingsFile, QSettings::IniFormat);
    return settings.value(key).toBool();
}
