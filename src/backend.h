#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include <QList>
#include <QVariant>
#include <QVariantList>

namespace IntonCore {
class Core;
}

class Recorder;
class PcmRecorder;
class Settings;

class QSound;

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    virtual ~Backend();

    Q_PROPERTY(QString path READ getPath WRITE setPath)

    Q_INVOKABLE bool isMobile();

    // Settings API
    Q_INVOKABLE QVariant getSettingValue(QString id);
    Q_INVOKABLE QVariantList getSettings();
    Q_INVOKABLE QString setSettings(QString id, QString value);
    Q_INVOKABLE bool validateSettings(QString id, QString value);

    std::list<double> getOctavesSetting();

    // Files API
    Q_INVOKABLE QVariantList getWaveFilesList();
    Q_INVOKABLE void deleteWaveFile(QString path);
    Q_INVOKABLE void playWaveFile(QString path, bool stop);
    Q_INVOKABLE QString startStopRecordWaveFile();
    Q_INVOKABLE QString openFileDialog();

    Q_INVOKABLE QString loadResult();
    Q_INVOKABLE void saveResult(
        QString startTime,
        QString endTime,
        QString speechRate,
        QString articulationRate,
        QString phrasePause,
        QString speechDuration,
        QString fillerSounds
    );

    // WAVE file API
    Q_INVOKABLE QVariantList getWaveData(QString path);
    Q_INVOKABLE QVariant getWaveLength(QString path);

    // Pitch API
    Q_INVOKABLE QVariantList getPitchData(QString path, bool cutted = false);
    Q_INVOKABLE QVariantList getPitchNormalizedData(QString path, bool cutted = false);
    Q_INVOKABLE QVariantList getPitchOcatavesNormalizedData(QString path, bool cutted = false);
    Q_INVOKABLE QVariantList getPitchFullData(QString path);
    Q_INVOKABLE QVariantList getPitchDataCutted(QString path);
    Q_INVOKABLE QVariant getPitchMinMax();

    Q_INVOKABLE QVariantList getPitchFrequencySegmentsCount(QString path);
    Q_INVOKABLE QVariantList getTemplatePitchFrequencySegmentsCount(QString path);
    Q_INVOKABLE QVariantList getPitchFrequencyCount(QString path);
    Q_INVOKABLE QVariantList getTemplatePitchFrequencyCount(QString path);

    Q_INVOKABLE QVariantList getPitchOcavesMetrics(QString path, bool isFull);
    Q_INVOKABLE QVariantList getTemplateOcavesMetrics(QString path, bool isFull);

    Q_INVOKABLE QVariantList getPitchDerivativeCount(QString path, bool isFull);
    Q_INVOKABLE QVariantList getTemplatePitchDerivativeCount(QString path, bool isFull);

    // Segments API
    Q_INVOKABLE QVariantList getSegmentsByIntensity(QString path);

public:
    QString getPath();
    void setPath(const QString& path);

private:
    IntonCore::Core *core;

    QString path;
    QString template_path;

    QSound *sound;

    PcmRecorder *recorder;

private:
    void initializeCore(bool reinit = false);
    void initializeRecordCore(const QString& path);
    void initializeTemplateCore(const QString& path);

    void initializeRecorder();
    void initializeAudio();

signals:

};

#endif // BACKEND_H
