#include "i2plauncher.h"
#include "repugnoapplication.h"
#include <QDirIterator>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <stdio.h>

I2PLauncher::I2PLauncher(QString jrePath, QString i2pPath)
{
    // TODO: Add checks that the directories are correct & exists even they should
    // have been checked by earlier methods in the stack already.
    m_jrePath = jrePath;
    m_i2pPath = i2pPath;
    //runner = new I2PRunner();
}

void I2PLauncher::Run()
{
    /*
    runner->moveToThread(&workerThread);

    // Setting connections between threads
    connect(&workerThread, &QThread::finished, runner, &QObject::deleteLater);
    connect(this, &I2PLauncher::operate, runner, &I2PRunner::runI2P);
    connect(runner, &I2PRunner::resultReady, this, &I2PLauncher::handleResults);

    workerThread.start();*/
    QProcess p;
    QString cmd = I2PLauncher::GenerateLaunchCommand();
    printf ("[+] Starting I2P with command: %s", qPrintable(cmd));

    // Environment overriding
    QStringList env = QProcess::systemEnvironment();
    env << RepugnoApplication::applicationDirPath() +QDir::separator()+ "tmp";
    env << "JAVA_HOME="+m_jrePath;
    qDebug() << "JAVA_HOME="+m_jrePath;
    p.setEnvironment(env);

    // Running
    qDebug() << "CMD for I2P is: " << cmd;
    p.start(cmd);
    qDebug() << "I2P should have started now.";
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
        QFileInfo *fTest = new QFileInfo(tmp);
        if ( fTest->isDir() ) continue; // Only allow jars for now
        classPath += ":"+tmp;
        qDebug() << "[+] Added "<< tmp << " to classpath.";
    }
    qDebug() << "[+] Classpath looks like: " << classPath;

    QString javaExec =
#ifdef WIN32
    "\\bin\\java.exe "
#else
    "/bin/java "
#endif
    ;
    QString i2p_config = QCoreApplication::applicationDirPath() + QDir::separator() + "conf";
    QString mainClass = I2PMAINCLASS;
    compiledString += m_jrePath;
    compiledString += javaExec + " -cp" + classPath;
    compiledString += " -Di2p.dir.base="+m_i2pPath + " -Di2p.dir.config="+ i2p_config + " " + mainClass;
    qDebug() << "CMD so far: " << compiledString;

    //I2PRunner::i2pCommand = compiledString;
    /*if (Constants::i2pRunCommand == NULL)
    {
        Constants::i2pRunCommand = compiledString;
    }*/
    return compiledString;
}
