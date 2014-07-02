#include "i2plauncher.h"
#include <QDirIterator>
#include <QDir>
#include <stdio.h>

I2PLauncher::I2PLauncher(QString jrePath, QString i2pPath)
{
    // TODO: Add checks that the directories are correct & exists even they should
    // have been checked by earlier methods in the stack already.
    m_jrePath = jrePath;
    m_i2pPath = i2pPath;
    QString cmd = GenerateLaunchCommand();
    runner = new I2PRunner(cmd);
}

void I2PLauncher::Run()
{
    runner->moveToThread(&workerThread);

    // Setting connections between threads
    connect(&workerThread, &QThread::finished, runner, &QObject::deleteLater);
    connect(this, &I2PLauncher::operate, runner, &I2PRunner::runI2P);
    connect(runner, &I2PRunner::resultReady, this, &I2PLauncher::handleResults);

    workerThread.start();
}

QString I2PLauncher::GenerateLaunchCommand()
{
    // Collect I2P jar files
    QString classPath = "";
    QString compiledString = "";
    QDirIterator it(m_i2pPath+QDir::separator()+"lib", QDirIterator::NoIteratorFlags);
    while (it.hasNext())
    {
        QString tmp = it.next();
        classPath += tmp;
        printf("[+] Added %s to classpath.", qPrintable(tmp));
    }

    QString javaExec =
#ifdef WIN32
    "bin\\java.exe "
#else
    "bin/java "
#endif
    ;

    I2PRunner::i2pCommand = compiledString;
    /*if (Constants::i2pRunCommand == NULL)
    {
        Constants::i2pRunCommand = compiledString;
    }*/
    return "";
}
