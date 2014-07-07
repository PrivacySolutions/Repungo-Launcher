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

    // Environment overriding
    QStringList env = QProcess::systemEnvironment();
    env << RepugnoApplication::applicationDirPath() +QDir::separator()+ "tmp";
    env << "_JAVA_OPTIONS=-Xmx"+QString(DEFAULT_MEMORY)+"M"; // This is required for a JRE to start.
    env << "JAVA_HOME="+m_jrePath;
    qDebug() << "JAVA_HOME="+m_jrePath;
    p.setEnvironment(env);

    // TODO: Add optional?
    QDir *logDir = new QDir(RepugnoApplication::applicationDirPath() +QDir::separator()+"log");
    if (!logDir->exists()) logDir->mkdir(logDir->absolutePath());

    p.setStandardErrorFile(logDir->absolutePath()+QDir::separator()+"i2p.stderr.log",QIODevice::Append);
    p.setStandardOutputFile(logDir->absolutePath()+QDir::separator()+"i2p.stdout.log",QIODevice::Append);

    //TODO: Check if location is different from i2psnark.config and change in case it is.


    // Running
    qDebug() << "CMD for I2P is: " << cmd;
    p.startDetached(cmd);
#if QT_VERSION < 0x050300
    qint64 i2pPid = p.pid();
    //ProcessId first added in Qt 5.3
#else
    qint64 i2pPid = p.processId();
#endif
    qDebug() << "I2P should have started now. With process id: " << QString::number(i2pPid);
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
        classPath +=
#ifdef WIN32
                ";"
#else
                ":"
#endif
                +tmp;
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
    compiledString += javaExec + " -cp ." + classPath;
    compiledString += " -Di2p.dir.base="+m_i2pPath +
            " -Dorg.mortbay.util.FileResource.checkAliases=false -DloggerFilenameOverride="+
            QCoreApplication::applicationDirPath() + QDir::separator() +"log"+ QDir::separator() +"i2p-log-router-@.txt " +
            "-Djava.library.path=."+ QDir::separator() + QCoreApplication::applicationDirPath() + QDir::separator() +"lib "+
            "-Dorg.mortbay.http.Version.paranoid=true -Di2p.dir.config="+ i2p_config + " " + mainClass;
    qDebug() << "CMD so far: " << compiledString;

    //I2PRunner::i2pCommand = compiledString;
    /*if (Constants::i2pRunCommand == NULL)
    {
        Constants::i2pRunCommand = compiledString;
    }*/
    return compiledString;
}
