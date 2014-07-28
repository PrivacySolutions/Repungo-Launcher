#ifndef RESETIDENTITY_H
#define RESETIDENTITY_H

#include <QObject>
#include <QDir>

class ResetIdentity : public QObject
{
    Q_OBJECT
public:
    explicit ResetIdentity(QObject *parent = 0);

    void resetI2PIdentity();
    void resetBrowserIdentity();
    bool removeDir(const QString & dirName)
    {
        bool result = true;
        QDir dir(dirName);

        if (dir.exists(dirName)) {
            Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
                if (info.isDir()) {
                    result = removeDir(info.absoluteFilePath());
                }
                else {
                    result = QFile::remove(info.absoluteFilePath());
                }

                if (!result) {
                    return result;
                }
            }
            result = dir.rmdir(dirName);
        }
        return result;
    }

signals:

public slots:

};

#endif // RESETIDENTITY_H
