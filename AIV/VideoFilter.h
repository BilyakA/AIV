#ifndef VIDEOFILTER_H
#define VIDEOFILTER_H

#include "FrameProvider.h"

class internalFrameFilter;

class VideoFilter : public FrameProvider
{
    Q_OBJECT

    Q_PROPERTY(FilterType type READ type WRITE setType NOTIFY typeChanged)

public:
    enum FilterType {
        STABILIZATION,
        STICHER,

        INVALID
    };
    Q_ENUM(FilterType)

    explicit VideoFilter(QQuickItem *parent = nullptr);

    QVariant source() override;
    FilterType type();

signals:
    void typeChanged();

    void requestFrame();

public slots:
    void setSource(QVariant source) override;
    void sendNextFrame() override;
    void setType(FilterType type);

private:
    QQuickItem* p_sourceItem;
    FilterType m_type;
    internalFrameFilter* p_filter;

    void processFrame(frameData metaData);
};

class internalFrameFilter
{
public:
    virtual void processFrame(frameData* metaData) = 0;
};

#endif // VIDEOFILTER_H
