#include "backend.h"

#include <cmath>

#include <QDebug>
#include <QGuiApplication>

#include <inton-core/include/intoncore.h>
#include <inton-core/include/utils.h>

#include "applicationconfig.h"
#include "pcm_recorder.h"
#include "qml/qmlpoint.h"


const int WAVE_LENGTH = 1000;

Backend::Backend(QObject *parent)
    : QObject(parent),
    core(nullptr),
    sound(nullptr)
{
    this->path = "";

    this->initializeRecorder();
    this->initializeAudio();
}

Backend::~Backend()
{
    qDebug() << "~Backend";

    if(this->core != nullptr) delete this->core;
}

bool Backend::isMobile()
{
#ifdef ANDROID
    return false;
#else
    return true;
#endif
}

QVariantList Backend::getWaveData(QString path)
{
    this->initializeRecordCore(path);

    auto storage = this->core->getRecord();

    auto data = storage->getWaveNormalized();
    auto resized_data = IntonCore::resizeVectorByMinMax(data, WAVE_LENGTH);
    qDebug() << "getWaveData: file size: " << data.size();
    qDebug() << "getWaveData: file size: " << resized_data.size();

    QVariantList waveData;

    for (ulong i=0; i<resized_data.size(); i++) {
        waveData.append(QVariant::fromValue(QmlPoint(i, resized_data[i])));
    }

    return waveData;
}

QVariant Backend::getWaveLength(QString path)
{
    this->initializeRecordCore(path);

    auto storage = this->core->getRecord();
    auto wave = storage->getWave();

    return QVariant::fromValue(1.0 * wave.size() / ApplicationConfig::RecordingFrequency);
}

QVariantList Backend::getPitchData(QString path, bool cutted)
{
    this->initializeRecordCore(path);

    this->core->setPitchConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_ALGORITHM).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_OUTPUT_FORMAT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_FRAME_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_RAPT_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SWIPE_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SAMPLING_FREQUENCY).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MINIMUM_F0).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MAXIMUM_F0).toDouble()
    );

    qDebug() << "getPitchData: try getRecord";
    auto storage = this->core->getRecord();
    qDebug() << "getPitchData: try getPitch";
    std::vector<double> data;
    if (cutted)
    {
        data = storage->getPitchCutted();
    } else {
        data = storage->getPitch();
    }
    qDebug() << "getPitchData: try resizeVector";
    auto resized_data = IntonCore::resizeVector(data, WAVE_LENGTH);
    qDebug() << "getPitchData: file size: " << data.size();
    qDebug() << "getPitchData: file size: " << resized_data.size();

    QVariantList pitchData;

    for (ulong i=0; i<resized_data.size(); i++) {
        pitchData.append(QVariant::fromValue(QmlPoint(i, resized_data[i])));
    }

    return pitchData;
}

QVariantList Backend::getPitchOcatavesNormalizedData(QString path, bool cutted)
{
    this->initializeRecordCore(path);

    this->core->setPitchConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_ALGORITHM).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_OUTPUT_FORMAT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_FRAME_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_RAPT_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SWIPE_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SAMPLING_FREQUENCY).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MINIMUM_F0).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MAXIMUM_F0).toDouble()
    );

    this->core->setOctavesConfig(
        this->getOctavesSetting()
    );

    qDebug() << "getPitchNormalizedData: try getTemplate";
    auto storage = this->core->getRecord();
    qDebug() << "getPitchNormalizedData: try getPitch";
    std::vector<double> data;
    if (cutted)
    {
        data = storage->getPitchOctavesNormalizedCutted();
    } else {
        data = storage->getPitchOctavesNormalized();
    }
    qDebug() << "getPitchNormalizedData: try resizeVector";
    auto resized_data = IntonCore::resizeVector(data, WAVE_LENGTH);
    qDebug() << "getPitchNormalizedData: file size: " << data.size();
    qDebug() << "getPitchNormalizedData: file size: " << resized_data.size();

    QVariantList pitchData;

    for (ulong i=0; i<resized_data.size(); i++) {
        pitchData.append(QVariant::fromValue(QmlPoint(i, resized_data[i])));
    }

    return pitchData;
}

QVariantList Backend::getPitchNormalizedData(QString path, bool cutted)
{
    this->initializeRecordCore(path);

    this->core->setPitchConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_ALGORITHM).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_OUTPUT_FORMAT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_FRAME_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_RAPT_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SWIPE_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SAMPLING_FREQUENCY).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MINIMUM_F0).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MAXIMUM_F0).toDouble()
    );

    qDebug() << "getPitchNormalizedData: try getTemplate";
    auto storage = this->core->getRecord();
    qDebug() << "getPitchNormalizedData: try getPitch";
    std::vector<double> data;
    if (cutted)
    {
        data = storage->getPitchNormalizedCutted();
    } else {
        data = storage->getPitchNormalized();
    }
    qDebug() << "getPitchNormalizedData: try resizeVector";
    auto resized_data = IntonCore::resizeVector(data, WAVE_LENGTH);
    qDebug() << "getPitchNormalizedData: file size: " << data.size();
    qDebug() << "getPitchNormalizedData: file size: " << resized_data.size();

    QVariantList pitchData;

    for (ulong i=0; i<resized_data.size(); i++) {
        pitchData.append(QVariant::fromValue(QmlPoint(i, resized_data[i])));
    }

    return pitchData;
}

QVariant Backend::getPitchMinMax()
{
    if (this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_NORMALIZE_BY_OCTAVES).toBool())
    {
        return QVariant::fromValue(QPoint(0,this->getOctavesSetting().size()));
    } else if (this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_NORMALIZED).toBool())
    {
        return QVariant::fromValue(QPoint(0,1));
    } else {
        return QVariant::fromValue(QPoint(
            this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MINIMUM_F0).toDouble(),
            this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MAXIMUM_F0).toDouble()
        ));
    }
}

QVariantList Backend::getPitchFullData(QString path)
{
    QVariantList pitch;

    if (this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_NORMALIZE_BY_OCTAVES).toBool())
    {
        pitch = getPitchOcatavesNormalizedData(path);
    } else if (this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_NORMALIZED).toBool())
    {
        pitch = getPitchNormalizedData(path);
    } else {
        pitch = getPitchData(path);
    }

    return pitch;
}

QVariantList Backend::getPitchDataCutted(QString path)
{
    qDebug() << this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_FRAME);
    qDebug() << this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SHIFT);
    qDebug() << this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME);
    qDebug() << this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SEGMENTS_LENGTH_LIMIT);

    this->core->setIntensityConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt()
    );

    this->core->setSegmentsConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SEGMENTS_LENGTH_LIMIT).toUInt()
    );

    QVariantList pitch;

    if (this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_NORMALIZE_BY_OCTAVES).toBool())
    {
        pitch = getPitchOcatavesNormalizedData(path, true);
    } else if (this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_NORMALIZED).toBool())
    {
        pitch = getPitchNormalizedData(path, true);
    } else {
        pitch = getPitchData(path, true);
    }

    return pitch;
}

QVariantList getDerivativeCount(IntonCore::Storage *storage,
                                bool isNormalizedByOctaves,
                                bool isNormalized,
                                bool isCutted)
{
    qDebug() << "getDerivativeCount " << isCutted;
    std::vector<double> data;

    if (isNormalizedByOctaves && !isCutted)
    {
        qDebug() << "getDerivativeCount: getPitchOctavesNormalizedDerivative";
        data = storage->getPitchOctavesNormalizedDerivative();
    } else if (isNormalized && !isCutted)
    {
        qDebug() << "getDerivativeCount: getPitchNormalizedDerivative";
        data = storage->getPitchNormalizedDerivative();
    } else if (isNormalizedByOctaves && isCutted)
    {
        qDebug() << "getDerivativeCount: getPitchOctavesNormalizedCuttedDerivative";
        data = storage->getPitchOctavesNormalizedCuttedDerivative();
    } else if (isNormalized && isCutted)
    {
        qDebug() << "getDerivativeCount: getPitchNormalizedCuttedDerivative";
        data = storage->getPitchNormalizedCuttedDerivative();
    } else {
        qDebug() << "getDerivativeCount: getPitchDerivative";
        data = storage->getPitchDerivative();
    }

    int less_zero = 0;
    int eq_zero = 0;
    int more_zero = 0;

    for (auto &it: data)
    {
        if (it < 0)
        {
            less_zero++;
        } else if (it > 0)
        {
            more_zero++;
        } else
        {
            eq_zero++;
        }
    }

    double max = (less_zero>eq_zero) ? ((less_zero>more_zero) ? less_zero : more_zero) : ((eq_zero>more_zero) ? eq_zero : more_zero) ;

    qDebug() << "getDerivativeCount less_zero" << less_zero;
    qDebug() << "getDerivativeCount more_zero" << more_zero;
    qDebug() << "getDerivativeCount eq_zero" << eq_zero;
    qDebug() << "getDerivativeCount max" << max;

    QVariantList count;
    count.append(less_zero / max);
    count.append(eq_zero / max);
    count.append(more_zero / max);

    return count;
}

QVariantList Backend::getPitchDerivativeCount(QString path, bool isFull)
{
    this->initializeRecordCore(path);

    this->core->setPitchConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_ALGORITHM).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_OUTPUT_FORMAT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_FRAME_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_RAPT_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SWIPE_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SAMPLING_FREQUENCY).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MINIMUM_F0).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MAXIMUM_F0).toDouble()
    );

    qDebug() << "getPitchNormalizedData: try getTemplate";
    auto storage = this->core->getRecord();

    auto data = getDerivativeCount(storage,
                                   this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_NORMALIZE_BY_OCTAVES).toBool(),
                                   this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_NORMALIZED).toBool(),
                                   !isFull);

    return data;
}

QVariantList Backend::getTemplatePitchDerivativeCount(QString path, bool isFull)
{
    this->initializeTemplateCore(path);

    this->core->setPitchConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_ALGORITHM).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_OUTPUT_FORMAT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_FRAME_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_RAPT_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SWIPE_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SAMPLING_FREQUENCY).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MINIMUM_F0).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MAXIMUM_F0).toDouble()
    );

    qDebug() << "getPitchNormalizedData: try getTemplate";
    auto storage = this->core->getTemplate();

    auto data = getDerivativeCount(storage,
                                   this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_NORMALIZE_BY_OCTAVES).toBool(),
                                   this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_NORMALIZED).toBool(),
                                   !isFull);

    return data;
}

QVariantList calculatePitchSegmentsCount(
        IntonCore::Storage * storage,
        std::list<double> actaves,
        bool cutted,
        bool mean)
{
    auto pitch = storage->getPitch();

    qDebug() << "calculatePitchSegmentsCount: cutted " << cutted;
    if (cutted)
    {
        auto intensity = storage->getIntensity();
        auto data = storage->getAutoSegmentsByIntensitySmoothed();
        qDebug() << "getPitchDataCutted count " << data.size();

        uint32_t pos = 0;
        for (auto &it: data)
        {
            auto to = IntonCore::normalizeValue(it.first, intensity.size(), pitch.size());
            for (auto i = pos; i <= to && i < pitch.size(); i++)
            {
                pitch[i] = 0;
            }
            pos = to + IntonCore::normalizeValue(it.second, intensity.size(), pitch.size());;
            qDebug() << "Segments by intensity pos " << pos;
        }

        for (auto i = pos; i < pitch.size(); i++)
        {
            pitch[i] = 0;
        }
    }

    QMap<int, int> counts;

    int max = 0;

    qDebug() << "calculatePitchSegmentsCount: mean " << mean;
    if (!mean)
    {
        for (ulong i=0; i<pitch.size(); i++)
        {
            int j = 0;
            for (double &actave : actaves)
            {
                if (pitch[i] != 0 && pitch[i] < actave)
                {
                    counts[j] = counts.value(j, 0) + 1;
                    if (max < counts[j]) max = counts[j];
                    break;
                }
                j ++;
            }
        }
    }

    if (mean)
    {
        double min = *min_element(pitch.begin(), pitch.end());
        qDebug() << "calculatePitchSegmentsCount: min " << min;

        int count = 0;
        double sum = 0;

        for (double &element : pitch)
        {
            if (element == min) {
                if (count != 0) {
                    double mean_value = sum / count;
                    sum = 0;
                    //qDebug() << "calculatePitchSegmentsCount: mean_value " << mean_value;
                    int j = 0;
                    for (double &actave : actaves)
                    {
                        if (actave > mean_value)
                        {
                            //qDebug() << "calculatePitchSegmentsCount: actave " << actave;
                            break;
                        }
                        j++;
                    }
                    counts[j] = counts.value(j, 0) + 1;
                    if (max < counts[j]) max = counts[j];
                    count = 0;
                }
            } else {
                sum += element;
                count++;
                //qDebug() << "calculatePitchSegmentsCount: count " << count;
                //qDebug() << "calculatePitchSegmentsCount: sum " << sum;
            }
        }
    }

    QVariantList result;

    for (int i=0; i<actaves.size(); i++)
    {
        result.append(1.0 * counts.value(i, 0) / max);
    }

    result.append(max);

    return result;
}

QVariantList Backend::getTemplatePitchFrequencySegmentsCount(QString path)
{
    this->initializeTemplateCore(path);

    this->core->setPitchConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_ALGORITHM).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_OUTPUT_FORMAT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_FRAME_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_RAPT_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SWIPE_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SAMPLING_FREQUENCY).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MINIMUM_F0).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MAXIMUM_F0).toDouble()
    );

    this->core->setIntensityConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt()
    );

    this->core->setSegmentsConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SEGMENTS_LENGTH_LIMIT).toUInt()
    );

    auto storage = this->core->getTemplate();

    auto actaves = this->getOctavesSetting();

    auto mean = this->getSettingValue(ApplicationConfig::SETTINGS_OCTAVES_HISTOGRAM_MEAN).toBool();

    auto result = calculatePitchSegmentsCount(storage, actaves, true, mean);

    return result;
}

QVariantList Backend::getPitchFrequencySegmentsCount(QString path)
{
    this->initializeRecordCore(path);

    this->core->setPitchConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_ALGORITHM).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_OUTPUT_FORMAT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_FRAME_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_RAPT_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SWIPE_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SAMPLING_FREQUENCY).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MINIMUM_F0).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MAXIMUM_F0).toDouble()
    );

    this->core->setIntensityConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt()
    );

    this->core->setSegmentsConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SEGMENTS_LENGTH_LIMIT).toUInt()
    );

    auto storage = this->core->getRecord();

    auto actaves = this->getOctavesSetting();

    auto mean = this->getSettingValue(ApplicationConfig::SETTINGS_OCTAVES_HISTOGRAM_MEAN).toBool();

    auto result = calculatePitchSegmentsCount(storage, actaves, true, mean);

    return result;
}

QVariantList Backend::getPitchFrequencyCount(QString path)
{
    this->initializeRecordCore(path);

    this->core->setPitchConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_ALGORITHM).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_OUTPUT_FORMAT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_FRAME_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_RAPT_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SWIPE_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SAMPLING_FREQUENCY).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MINIMUM_F0).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MAXIMUM_F0).toDouble()
    );

    this->core->setIntensityConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt()
    );

    this->core->setSegmentsConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SEGMENTS_LENGTH_LIMIT).toUInt()
    );

    auto actavesStr = this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_OCTAVES)
            .toString()
            .split(ApplicationConfig::SETTINGS_TYPE_LIST_DELIMETER);

    auto storage = this->core->getRecord();

    auto actaves = this->getOctavesSetting();

    auto mean = this->getSettingValue(ApplicationConfig::SETTINGS_OCTAVES_HISTOGRAM_MEAN).toBool();

    auto result = calculatePitchSegmentsCount(storage, actaves, false, mean);

    return result;
}

QVariantList Backend::getTemplatePitchFrequencyCount(QString path)
{
    this->initializeTemplateCore(path);

    this->core->setPitchConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_ALGORITHM).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_OUTPUT_FORMAT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_FRAME_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_RAPT_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SWIPE_THRESHOLD).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_SAMPLING_FREQUENCY).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MINIMUM_F0).toDouble(),
        this->getSettingValue(ApplicationConfig::SETTINGS_PITCH_MAXIMUM_F0).toDouble()
    );

    this->core->setIntensityConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt()
    );

    this->core->setSegmentsConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SEGMENTS_LENGTH_LIMIT).toUInt()
    );

    auto storage = this->core->getTemplate();

    auto actaves = this->getOctavesSetting();

    auto mean = this->getSettingValue(ApplicationConfig::SETTINGS_OCTAVES_HISTOGRAM_MEAN).toBool();

    auto result = calculatePitchSegmentsCount(storage, actaves, false, mean);

    return result;
}

QVariantList Backend::getSegmentsByIntensity(QString path)
{
    this->initializeRecordCore(path);

    this->core->setIntensityConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SHIFT).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt(),
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SMOOTH_FRAME).toUInt()
    );

    this->core->setSegmentsConfig(
        this->getSettingValue(ApplicationConfig::SETTINGS_SEGMENTS_SEGMENTS_LENGTH_LIMIT).toUInt()
    );

    auto storage = this->core->getRecord();
    auto intensity = storage->getIntensity();

    auto data = storage->getAutoSegmentsByIntensitySmoothed();
    qDebug() << "Segments by intensity count " << data.size();

    QVariantList segments;

    for (auto &it: data)
    {
        it.first = IntonCore::normalizeValue(it.first, intensity.size(), WAVE_LENGTH);
        it.second = IntonCore::normalizeValue(it.second, intensity.size(), WAVE_LENGTH);
        segments.append(QVariant::fromValue(QmlPoint(it.first, it.first + it.second)));
    }

    return segments;
}

QString Backend::getPath()
{
    return this->path;
}

void Backend::setPath(const QString &path)
{
    qDebug() << "set path: " << path;
    this->path = path;
}

void Backend::initializeCore(bool reinit)
{
    qDebug() << "Backend::initializeCore " << reinit;
    if (this->core != nullptr && !reinit) return;

    if (this->core != nullptr)
    {
        qDebug() << "Backend::initializeCore: Delete core";
        delete this->core;
        this->core = nullptr;
    }

    QString recordsPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QString logPath = QDir(recordsPath).absoluteFilePath("core.log");
    qDebug() << "Backend::initializeCore: logPath: " << logPath;

    //Settings * settings = Settings::getInstance();

    qDebug() << "Backend::initializeCore: Initialize core: " << this->path;
    this->core = new IntonCore::Core(
        this->path.toStdString()//,
        //settings->getConfig()
    );
    qDebug() << "Backend::initializeCore: Initialize core complete";
}

void Backend::initializeRecordCore(const QString& path)
{
    qDebug() << "initializeCore: path" << path;
    if (this->path == path)
    {
        qDebug() << "initializeCore: ok";
        return;
    }
    qDebug() << "initializeCore: old path" << this->path;

    if (!path.isEmpty())
    {
        qDebug() << "initializeCore: initialize core" << path;
        this->initializeCore();
        qDebug() << "initializeCore: load wav file" << path;
        WaveFile * file = IntonCore::Helpers::openWaveFile(path.toStdString());
        qDebug() << "initializeCore: reload record" << path;
        this->core->reloadRecord(file);
    }

    this->setPath(path);
}

void Backend::initializeTemplateCore(const QString& path)
{
    qDebug() << "initializeTemplateCore: path" << path;
    if (this->template_path == path)
    {
        qDebug() << "initializeTemplateCore: ok";
        return;
    }
    qDebug() << "initializeTemplateCore: old path" << this->template_path;

    if (!path.isEmpty())
    {
        qDebug() << "initializeTemplateCore: initialize core" << path;
        this->initializeCore();
        qDebug() << "initializeTemplateCore: load wav file" << path;
        WaveFile * file = IntonCore::Helpers::openWaveFile(path.toStdString());
        qDebug() << "initializeTemplateCore: reload template" << path;
        this->core->reloadTemplate(file);
    }

    this->setPath(path);
}
