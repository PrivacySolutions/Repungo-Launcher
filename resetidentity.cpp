#include "resetidentity.h"
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include "repugnoapplication.h"

ResetIdentity::ResetIdentity(QObject *parent) :
    QObject(parent)
{
}

void ResetIdentity::resetBrowserIdentity()
{
    QMessageBox areUSure;
    areUSure.setIcon(QMessageBox::Information);
    areUSure.setText(tr("This will delete _all_ your browser data. Including passwords, bookmarks, and other stored."));
    areUSure.setWindowTitle(tr("Are you really sure?"));
    areUSure.setInformativeText(tr("Are you really sure?"));
    areUSure.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    areUSure.setDefaultButton(QMessageBox::No);
    int reply = areUSure.exec();
    if (reply == QMessageBox::No)
    {
        // Cancel
        return;
    }
    // Should be just about deleting the folder.
    QString here = QApplication::instance()->applicationDirPath();
    QDir browserConfig(here + QDir::separator() + "Config" + QDir::separator() + "Browser");
    if (browserConfig.exists())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString("Close all browser windows!!!"));
        msgBox.setText(QString("Please make sure all Abscond browser windows are closed before pressing OK! The repungo launcher will then try to delete the browser config, resulting in Abscond creating a new default identity. However this will fail if Abscond is still open!"));
        msgBox.exec();
        removeDir(browserConfig.absolutePath());
    }
}

void ResetIdentity::resetI2PIdentity()
{
    // Need to bring in zip etc here..
}
