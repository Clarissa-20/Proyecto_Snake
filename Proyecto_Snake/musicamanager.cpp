#include "musicamanager.h"
#include <QCoreApplication>

MusicaManger& MusicaManger::instance() {
    static MusicaManger instance;
    return instance;
}

MusicaManger::MusicaManger() {
    globalPlayer = new QMediaPlayer();
    globalAudio = new QAudioOutput();
    globalPlayer->setAudioOutput(globalAudio);
    globalAudio->setVolume(0.4);

    levelPlayer = new QMediaPlayer();
    levelAudio = new QAudioOutput();
    levelPlayer->setAudioOutput(levelAudio);
    levelAudio->setVolume(0.5);

    QObject::connect(globalPlayer, &QMediaPlayer::playbackStateChanged, [=](QMediaPlayer::PlaybackState state){
        if(state == QMediaPlayer::StoppedState) globalPlayer->play();
    });

    QObject::connect(levelPlayer, &QMediaPlayer::playbackStateChanged, [=](QMediaPlayer::PlaybackState state){
        if(state == QMediaPlayer::StoppedState) levelPlayer->play();
    });
}

MusicaManger::~MusicaManger() {
    delete globalPlayer; delete globalAudio;
    delete levelPlayer; delete levelAudio;
}

void MusicaManger::playMusicaJuego(const QString &fileName) {
    if (levelPlayer->isPlaying()) levelPlayer->stop();
    QString fullPath = QCoreApplication::applicationDirPath() + "/sonidos/" + fileName;
    globalPlayer->setSource(QUrl::fromLocalFile(fullPath));
    globalPlayer->play();
}

void MusicaManger::playMusicaNiveles(const QString &fileName) {
    if (globalPlayer->isPlaying()) globalPlayer->stop();
    QString fullPath = QCoreApplication::applicationDirPath() + "/sonidos/" + fileName;
    levelPlayer->setSource(QUrl::fromLocalFile(fullPath));
    levelPlayer->play();
}

void MusicaManger::stopAll() {
    globalPlayer->stop();
    levelPlayer->stop();
}