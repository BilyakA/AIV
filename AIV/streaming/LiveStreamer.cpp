#include "LiveStreamer.hpp"

LiveStreamer::LiveStreamer(UsageEnvironment *env, QObject *parent)
    : QObject(parent)
    , p_env(env)
{

}

LiveStreamer::~LiveStreamer()
{

}

void LiveStreamer::startStream()
{
    p_env->taskScheduler().doEventLoop(); // does not return
}
