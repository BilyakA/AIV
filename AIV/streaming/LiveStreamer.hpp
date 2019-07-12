#pragma once

#include <QObject>

#include "live555.h"

class LiveStreamer : public QObject
{
    Q_OBJECT
public:
    explicit LiveStreamer(UsageEnvironment* env, QObject* parent = nullptr);
    ~LiveStreamer() override;

public slots:
    void startStream();

private:
    UsageEnvironment* p_env;
};
