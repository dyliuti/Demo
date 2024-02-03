#ifndef FILEUTIL_H
#define FILEUTIL_H
#include <QString>

class FileUtil
{
public:
    static QString getErrorFileDir();
    static QString getClassroomImagePath();
    static bool exist(const QString &path);
    static bool makePath(const QString &strDirPath, bool skipExistingPath = true);
    static bool deleteRecursively(const QString &path);
    static bool copyRecursively(const QString &srcFilePath, const QString &tgtFilePath, bool overwrite);
    static QStringList getTypicalFiles(const QString &strDirPath, const QStringList &strSuffixes, bool bRecursively);
    static QString getName(const QString &path);
};

#endif // FILEUTIL_H
