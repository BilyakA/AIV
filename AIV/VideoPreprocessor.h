#ifndef VIDEOPREPROCESSOR_H
#define VIDEOPREPROCESSOR_H

#include "FrameProvider.h"

class internalFramePreprocessor;

class VideoPreprocessor : public FrameProvider
{
    Q_OBJECT

    Q_PROPERTY(PreprocessorType type READ type WRITE setType NOTIFY typeChanged)

public:
    enum PreprocessorType {
        GRAYSCALE,
        HOMOGRAPHY,

        INVALID
    };
    Q_ENUM(PreprocessorType)

    explicit VideoPreprocessor(QQuickItem *parent = nullptr);

    QVariant source() override;
    PreprocessorType type();

signals:
    void typeChanged();

    void requestFrame();

public slots:
    void setSource(QVariant source) override;
    void sendNextFrame() override;
    void setType(PreprocessorType type);

private:
    QQuickItem* p_sourceItem;
    PreprocessorType m_type;
    internalFramePreprocessor* p_processor;

    void processFrame(frameData metaData);
};

class internalFramePreprocessor
{
public:
    virtual void processFrame(frameData* metaData) = 0;
};

#endif // VIDEOPREPROCESSOR_H
