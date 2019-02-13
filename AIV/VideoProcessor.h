#ifndef VideoProcessor_H
#define VideoProcessor_H

#include "FrameProvider.h"

class internalFrameProcessor;

class VideoProcessor : public FrameProvider
{
    Q_OBJECT

    Q_PROPERTY(ProcessorType type READ type WRITE setType NOTIFY typeChanged)

public:
    enum ProcessorType {
        PEOPLEDETECT,

        INVALID
    };
    Q_ENUM(ProcessorType)

    explicit VideoProcessor(QQuickItem *parent = nullptr);

    QVariant source() override;
    ProcessorType type();

signals:
    void typeChanged();

    void requestFrame();

public slots:
    void setSource(QVariant source) override;
    void sendNextFrame() override;
    void setType(ProcessorType type);

private:
    QQuickItem* p_sourceItem;
    ProcessorType m_type;
    internalFrameProcessor* p_processor;

    void processFrame(frameData metaData);
};

class internalFrameProcessor
{
public:
    virtual void processFrame(frameData* metaData) = 0;
};

#endif // VideoProcessor_H
