#ifndef APPLICATIONCONFIG_H
#define APPLICATIONCONFIG_H

#include <QString>
#include <QStringList>
#include <QGuiApplication>
#include <QDir>
#include <QStandardPaths>

namespace ApplicationConfig {
    static const QString DataPath = "data";
    static const QString RecordsPath = "records";
    static const QString TestsPath = "tests";

    static QString GetFullDataPath()
    {
#ifdef ANDROID
        QString recordsPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
//        QString recordsPath = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
#else
        QString appPath = QGuiApplication::applicationDirPath();
        QString dataPath = QDir(appPath).absoluteFilePath(ApplicationConfig::DataPath);
        QString recordsPath = QDir(dataPath).absoluteFilePath(ApplicationConfig::RecordsPath);
#endif
        return recordsPath;
    }

    static QString GetFullTestsPath()
    {
#ifdef ANDROID
        QString testsPath = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
#else
        QString appPath = QGuiApplication::applicationDirPath();
        QString dataPath = QDir(appPath).absoluteFilePath(ApplicationConfig::DataPath);
        QString testsPath = QDir(dataPath).absoluteFilePath(ApplicationConfig::TestsPath);
#endif
        return testsPath;
    }

    static const QString WaveFileExtension = "*.wav";

    static const QStringList WaveFileFilter = { WaveFileExtension };

    static const QString SettingsPath = "settings.ini";

    static QString GetFullSettingsPath()
    {
#ifdef ANDROID
        QString appPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QString dataPath = QDir(appPath).absoluteFilePath(ApplicationConfig::SettingsPath);
#else
        QString appPath = QGuiApplication::applicationDirPath();
        QString dataPath = QDir(appPath).absoluteFilePath(ApplicationConfig::SettingsPath);
#endif
        return dataPath;
    }

    static const QString ResultsPath = "results.txt";

    static QString GetFullResultsPath()
    {
#ifdef ANDROID
        QString appPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QString dataPath = QDir(appPath).absoluteFilePath(ApplicationConfig::ResultsPath);
#else
        QString appPath = QGuiApplication::applicationDirPath();
        QString dataPath = QDir(appPath).absoluteFilePath(ApplicationConfig::ResultsPath);
#endif
        return dataPath;
    }

    static const int RecordingFrequency =  8000;
    static const int RecordingBitsPerSample =  16;
    static const int RecordingChannelsCount =  1;
    static const QString RecordingAudioFormat = "audio/pcm";
    static const QString RecordingFileFormat = ".wav";
    static const QString RecordingContainerFormat = "audio/x-wav";
    static const QString RecordingFileNameTemplate = "dd.MM.yyyy.hh.mm.ss.zzz";

    static const QString SETTINGS_NAME = "name";
    static const QString SETTINGS_DESC = "description";
    static const QString SETTINGS_VAL = "value";
    static const QString SETTINGS_TYPE = "type";

    static const QString SETTINGS_TYPE_INTEGER = "int";
    static const QString SETTINGS_TYPE_DOUBLE = "double";
    static const QString SETTINGS_TYPE_BOOL = "bool";
    static const QString SETTINGS_TYPE_LIST_DELIMETER = ";";
    static const QString SETTINGS_TYPE_DOUBLE_LIST = "double_list";

    static const QString SETTINGS_VERSION_KEY = "version";
    static const QString SETTINGS_VERSION_VALUE = "1";

    static const QString SETTINGS_PITCH_ALGORITHM = "PitchAlgorithm";
    static const QString SETTINGS_PITCH_OUTPUT_FORMAT = "PitchOutputFormat";
    static const QString SETTINGS_PITCH_FRAME_SHIFT = "PitchFrameShift";
    static const QString SETTINGS_PITCH_RAPT_THRESHOLD = "PitchRaptThrehold";
    static const QString SETTINGS_PITCH_SWIPE_THRESHOLD = "PitchSwipeThrehold";
    static const QString SETTINGS_PITCH_SAMPLING_FREQUENCY = "PitchSamplingFrequency";
    static const QString SETTINGS_PITCH_MINIMUM_F0 = "PitchMinimumF0";
    static const QString SETTINGS_PITCH_MAXIMUM_F0 = "PitchMaximumF0";
    static const QString SETTINGS_PITCH_NORMALIZED = "PitchNormalized";
    static const QString SETTINGS_PITCH_OCTAVES = "PitchOctavesSeries";
    static const QString SETTINGS_PITCH_NORMALIZE_BY_OCTAVES = "PitchNormalizeOctavesSeries";

    static const QString SETTINGS_OCTAVES_HISTOGRAM_MEAN = "OctavesHistagramMean";

    static const QString SETTINGS_SEGMENTS_FRAME = "SegmentsFrame";
    static const QString SETTINGS_SEGMENTS_SHIFT = "SegmentsShift";
    static const QString SETTINGS_SEGMENTS_SMOOTH_FRAME = "SegmentsSmoothFrame";
    static const QString SETTINGS_SEGMENTS_SEGMENTS_LENGTH_LIMIT = "SegmentsLengthLimit";

    const static std::map<QString, std::map<QString, QString> > DEFAULT_SETTINGS = {
        {SETTINGS_SEGMENTS_FRAME,{
             {SETTINGS_NAME, "Intensity Frame"},
             {SETTINGS_DESC, "Intensity frame length used to calculate segments"},
             {SETTINGS_VAL, "240"},
             {SETTINGS_TYPE, SETTINGS_TYPE_INTEGER}
        }},
        {SETTINGS_SEGMENTS_SHIFT,{
             {SETTINGS_NAME, "Intensity Shift"},
             {SETTINGS_DESC, "Intensity frame shift used to calculate segments"},
             {SETTINGS_VAL, "120"},
             {SETTINGS_TYPE, SETTINGS_TYPE_INTEGER}
        }},
        {SETTINGS_SEGMENTS_SMOOTH_FRAME,{
             {SETTINGS_NAME, "Intensity Smooth Frame"},
             {SETTINGS_DESC, "Frame length used for smoothing intensity to segments calculation"},
             {SETTINGS_VAL, "120"},
             {SETTINGS_TYPE, SETTINGS_TYPE_INTEGER}
        }},
        {SETTINGS_SEGMENTS_SEGMENTS_LENGTH_LIMIT,{
             {SETTINGS_NAME, "Segments Length Limit"},
             {SETTINGS_DESC, "Segments length limit in millisec"},
             {SETTINGS_VAL, "15"},
             {SETTINGS_TYPE, SETTINGS_TYPE_INTEGER}
        }},

        {SETTINGS_PITCH_ALGORITHM,{
             {SETTINGS_NAME, "Pitch Algorithm"},
             {SETTINGS_DESC, "Algorithm used for extraction of pitch. \n[0: RAPT, 1: SWIPE, 2: Reaper, 3: World, 4: NumAlgorithms]"},
             {SETTINGS_VAL, "1"},
             {SETTINGS_TYPE, SETTINGS_TYPE_INTEGER}
        }},
        {SETTINGS_PITCH_OUTPUT_FORMAT,{
             {SETTINGS_NAME, "Pitch Output format"},
             {SETTINGS_DESC, "Output format. \n[0:pitch, 1:F0, 2:log(F0), 3: NumOutputFormats]"},
             {SETTINGS_VAL, "1"},
             {SETTINGS_TYPE, SETTINGS_TYPE_INTEGER}
        }},
        {SETTINGS_PITCH_FRAME_SHIFT,{
             {SETTINGS_NAME, "Pitch Frame shift"},
             {SETTINGS_DESC, "Frame shift"},
             {SETTINGS_VAL, "60"},
             {SETTINGS_TYPE, SETTINGS_TYPE_INTEGER}
        }},
        {SETTINGS_PITCH_RAPT_THRESHOLD,{
             {SETTINGS_NAME, "Pitch RAPT threhold"},
             {SETTINGS_DESC, "Voiced/unvoiced threhold (used only for RAPT algorithm)"},
             {SETTINGS_VAL, "0"},
             {SETTINGS_TYPE, SETTINGS_TYPE_DOUBLE}
        }},
        {SETTINGS_PITCH_SWIPE_THRESHOLD,{
             {SETTINGS_NAME, "Pitch SWIPE threhold"},
             {SETTINGS_DESC, "Voiced/unvoiced threhold (used only for SWIPE algorithm)"},
             {SETTINGS_VAL, "0.3"},
             {SETTINGS_TYPE, SETTINGS_TYPE_DOUBLE}
        }},
        {SETTINGS_PITCH_SAMPLING_FREQUENCY,{
             {SETTINGS_NAME, "Pitch Sampling frequency"},
             {SETTINGS_DESC, "Sampling frequency (kHz)"},
             {SETTINGS_VAL, "8.0"},
             {SETTINGS_TYPE, SETTINGS_TYPE_DOUBLE}
        }},
        {SETTINGS_PITCH_MINIMUM_F0,{
             {SETTINGS_NAME, "Pitch Minimum F0"},
             {SETTINGS_DESC, "Minimum fundamental frequency to search for (Hz)"},
             {SETTINGS_VAL, "30.0"},
             {SETTINGS_TYPE, SETTINGS_TYPE_DOUBLE}
        }},
        {SETTINGS_PITCH_MAXIMUM_F0,{
             {SETTINGS_NAME, "Pitch Maximum F0"},
             {SETTINGS_DESC, "Maximum fundamental frequency to search for (Hz)"},
             {SETTINGS_VAL, "1000.0"},
             {SETTINGS_TYPE, SETTINGS_TYPE_DOUBLE}
        }},
        {SETTINGS_PITCH_NORMALIZED,{
             {SETTINGS_NAME, "Pitch Normalization"},
             {SETTINGS_DESC, "Normalize Pitch data"},
             {SETTINGS_VAL, "true"},
             {SETTINGS_TYPE, SETTINGS_TYPE_BOOL}
        }},
        {SETTINGS_PITCH_NORMALIZE_BY_OCTAVES,{
             {SETTINGS_NAME, "Pitch Normalization By Octaves"},
             {SETTINGS_DESC, "Normalize Pitch data by ocataves"},
             {SETTINGS_VAL, "true"},
             {SETTINGS_TYPE, SETTINGS_TYPE_BOOL}
        }},
        {SETTINGS_OCTAVES_HISTOGRAM_MEAN,{
             {SETTINGS_NAME, "Octaves Histagram Mean"},
             {SETTINGS_DESC, "Apply mean values for octaves histogram"},
             {SETTINGS_VAL, "true"},
             {SETTINGS_TYPE, SETTINGS_TYPE_BOOL}
        }},

        {SETTINGS_PITCH_OCTAVES,{
             {SETTINGS_NAME, "Pitch Octaves Series"},
             {SETTINGS_DESC, "Pitch frequency segments"},
             {SETTINGS_VAL, "32.70;36.95;41.21;43.65;49.00;55.00;61.74;65.41;73.91;82.41;87.31;98.00;110.00;123.48;130.82;147.83;164.81;174.62;196.00;220.00;246.96;261.63;293.66;329.63;349.23;392.00;440.00;493.88;523.25;587.32;659.26;698.46;784.00;880.00;987.75"},
             {SETTINGS_TYPE, SETTINGS_TYPE_DOUBLE_LIST}
        }}
    };

    static QString SettingsKey(QString group, QString key){
        return group + "/" + key;
    }

    static QString SettingsNameKey(QString group){
        return SettingsKey(group, SETTINGS_NAME);
    }

    static QString SettingsDescKey(QString group){
        return SettingsKey(group, SETTINGS_DESC);
    }

    static QString SettingsValueKey(QString group){
        return SettingsKey(group, SETTINGS_VAL);
    }

    static QString SettingsTypeKey(QString group){
        return SettingsKey(group, SETTINGS_TYPE);
    }
}

#endif // APPLICATIONCONFIG_H
