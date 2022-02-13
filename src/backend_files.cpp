#include "backend.h"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>

#include "qml/qmlfileinfo.h"
#include "applicationconfig.h"

QVariantList Backend::getWaveFilesList()
{
    QDir dataDir(ApplicationConfig::GetFullDataPath());
    QStringList allFiles = dataDir.entryList(ApplicationConfig::WaveFileFilter, QDir::NoDotAndDotDot | QDir::Files);
    qDebug() << "Found files: " << allFiles;

    QVariantList fileList;

    foreach(auto file, allFiles)
    {
        QmlFileInfo info(dataDir.absoluteFilePath(file));
        qDebug() << "File: " << info.getName() << " : " << info.getPath();

        fileList.append(QVariant::fromValue(info));
    }

    return fileList;
}

void Backend::deleteWaveFile(QString path)
{
    qDebug() << "deleteWaveFile " << path;
    QFile file (path.toLocal8Bit());
    file.remove();
}

QString Backend::openFileDialog()
{
#ifdef ANDROID
    auto fileUrl = QFileDialog::getOpenFileUrl(nullptr,
                                tr("Open File"),
                                ApplicationConfig::GetFullTestsPath(),
                                tr("Wave (*.wav)"));
    qDebug() << "openFileDialog: " << fileUrl;
    auto fileName = fileUrl.toString();
#else
    auto fileName = QFileDialog::getOpenFileName(nullptr,
        tr("Open File"),
        ApplicationConfig::GetFullTestsPath(),
        tr("Wave (*.wav)"));
#endif
    qDebug() << "openFileDialog: " << fileName;

    return fileName;
}

QString Backend::loadResult()
{
    QFile file(ApplicationConfig::GetFullResultsPath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    QString results = "";

    while(!in.atEnd()) {
        results += in.readLine().replace("|","\n");
        results += "\n\n";
    }

    file.close();

    return results;
}

void Backend::saveResult(QString startTime,
                         QString endTime,
                         QString speechRate,
                         QString articulationRate,
                         QString phrasePause,
                         QString speechDuration,
                         QString fillerSounds)
{
    qDebug() << "startTime: " << startTime;
    qDebug() << "endTime: " << endTime;
    qDebug() << "speechRate: " << speechRate;
    qDebug() << "articulationRate: " << articulationRate;
    qDebug() << "phrasePause: " << phrasePause;
    qDebug() << "speechDuration: " << speechDuration;
    qDebug() << "fillerSounds: " << fillerSounds;
    QFile results(ApplicationConfig::GetFullResultsPath());
    if (!results.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;
    QTextStream out(&results);
    out << "Star DateTime - " << startTime << "|" <<
           "End DateTime - " << endTime << "|" <<
           "Speech Rate - " << speechRate << "|"
           "Articulation Rate - " << articulationRate << "|"
           "Phrase Pause - " << phrasePause << "|"
           "Speech Duration - " << speechDuration << "|"
           "Filler Sounds - " << fillerSounds << "\n";
    results.close();
}
