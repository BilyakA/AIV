cmake_minimum_required(VERSION 3.13.1 FATAL_ERROR)

project(live555 VERSION 4.0.0 LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_library(liveMedia STATIC
    # $(LIVEMEDIA_LIB_OBJS) \ >
        #Media.$(OBJ)
        live/liveMedia/Media.cpp
        # $(MISC_SOURCE_OBJS) >
            #MediaSource.$(OBJ)
            live/liveMedia/MediaSource.cpp
            #FramedSource.$(OBJ)
            live/liveMedia/FramedSource.cpp
            #FramedFileSource.$(OBJ)
            live/liveMedia/FramedFileSource.cpp
            #FramedFilter.$(OBJ)
            live/liveMedia/FramedFilter.cpp
            #ByteStreamFileSource.$(OBJ)
            live/liveMedia/ByteStreamFileSource.cpp
            #ByteStreamMultiFileSource.$(OBJ)
            live/liveMedia/ByteStreamMultiFileSource.cpp
            #ByteStreamMemoryBufferSource.$(OBJ)
            live/liveMedia/ByteStreamMemoryBufferSource.cpp
            #BasicUDPSource.$(OBJ)
            live/liveMedia/BasicUDPSource.cpp
            #DeviceSource.$(OBJ)
            live/liveMedia/DeviceSource.cpp
            #AudioInputDevice.$(OBJ)
            live/liveMedia/AudioInputDevice.cpp
            #WAVAudioFileSource.$(OBJ)
            live/liveMedia/WAVAudioFileSource.cpp
            # $(MPEG_SOURCE_OBJS) >
                #MPEG1or2Demux.$(OBJ)
                live/liveMedia/MPEG1or2Demux.cpp
                #MPEG1or2DemuxedElementaryStream.$(OBJ)
                live/liveMedia/MPEG1or2DemuxedElementaryStream.cpp
                #MPEGVideoStreamFramer.$(OBJ)
                live/liveMedia/MPEGVideoStreamFramer.cpp
                #MPEG1or2VideoStreamFramer.$(OBJ)
                live/liveMedia/MPEG1or2VideoStreamFramer.cpp
                #MPEG1or2VideoStreamDiscreteFramer.$(OBJ)
                live/liveMedia/MPEG1or2VideoStreamDiscreteFramer.cpp
                #MPEG4VideoStreamFramer.$(OBJ)
                live/liveMedia/MPEG4VideoStreamFramer.cpp
                #MPEG4VideoStreamDiscreteFramer.$(OBJ)
                live/liveMedia/MPEG4VideoStreamDiscreteFramer.cpp
                #H264or5VideoStreamFramer.$(OBJ)
                live/liveMedia/H264or5VideoStreamFramer.cpp
                #H264or5VideoStreamDiscreteFramer.$(OBJ)
                live/liveMedia/H264or5VideoStreamDiscreteFramer.cpp
                #H264VideoStreamFramer.$(OBJ)
                live/liveMedia/H264VideoStreamFramer.cpp
                #H264VideoStreamDiscreteFramer.$(OBJ)
                live/liveMedia/H264VideoStreamDiscreteFramer.cpp
                #H265VideoStreamFramer.$(OBJ)
                live/liveMedia/H265VideoStreamFramer.cpp
                #H265VideoStreamDiscreteFramer.$(OBJ)
                live/liveMedia/H265VideoStreamDiscreteFramer.cpp
                #MPEGVideoStreamParser.$(OBJ)
                live/liveMedia/MPEGVideoStreamParser.cpp
                #MPEG1or2AudioStreamFramer.$(OBJ)
                live/liveMedia/MPEG1or2AudioStreamFramer.cpp
                #MPEG1or2AudioRTPSource.$(OBJ)
                live/liveMedia/MPEG1or2AudioRTPSource.cpp
                #MPEG4LATMAudioRTPSource.$(OBJ)
                live/liveMedia/MPEG4LATMAudioRTPSource.cpp
                #MPEG4ESVideoRTPSource.$(OBJ)
                live/liveMedia/MPEG4ESVideoRTPSource.cpp
                #MPEG4GenericRTPSource.$(OBJ)
                live/liveMedia/MPEG4GenericRTPSource.cpp
                # $(MP3_SOURCE_OBJS) >
                    #MP3FileSource.$(OBJ)
                    live/liveMedia/MP3FileSource.cpp
                    #MP3Transcoder.$(OBJ)
                    live/liveMedia/MP3Transcoder.cpp
                    #MP3ADU.$(OBJ)
                    live/liveMedia/MP3ADU.cpp
                    #MP3ADUdescriptor.$(OBJ)
                    live/liveMedia/MP3ADUdescriptor.cpp
                    #MP3ADUinterleaving.$(OBJ)
                    live/liveMedia/MP3ADUinterleaving.cpp
                    #MP3ADUTranscoder.$(OBJ)
                    live/liveMedia/MP3ADUTranscoder.cpp
                    #MP3StreamState.$(OBJ)
                    live/liveMedia/MP3StreamState.cpp
                    #MP3Internals.$(OBJ)
                    live/liveMedia/MP3Internals.cpp
                    #MP3InternalsHuffman.$(OBJ)
                    live/liveMedia/MP3InternalsHuffman.cpp
                    #MP3InternalsHuffmanTable.$(OBJ)
                    live/liveMedia/MP3InternalsHuffmanTable.cpp
                    #MP3ADURTPSource.$(OBJ)
                    live/liveMedia/MP3ADURTPSource.cpp
                # < $(MP3_SOURCE_OBJS)
                #MPEG1or2VideoRTPSource.$(OBJ)
                live/liveMedia/MPEG1or2VideoRTPSource.cpp
                #MPEG2TransportStreamMultiplexor.$(OBJ)
                live/liveMedia/MPEG2TransportStreamMultiplexor.cpp
                #MPEG2TransportStreamFromPESSource.$(OBJ)
                live/liveMedia/MPEG2TransportStreamFromPESSource.cpp
                #MPEG2TransportStreamFromESSource.$(OBJ)
                live/liveMedia/MPEG2TransportStreamFromESSource.cpp
                #MPEG2TransportStreamFramer.$(OBJ)
                live/liveMedia/MPEG2TransportStreamFramer.cpp
                #MPEG2TransportStreamAccumulator.$(OBJ)
                live/liveMedia/MPEG2TransportStreamAccumulator.cpp
                #ADTSAudioFileSource.$(OBJ)
                live/liveMedia/ADTSAudioFileSource.cpp
            # < $(MPEG_SOURCE_OBJS)
            # $(JPEG_SOURCE_OBJS) >
                #JPEGVideoSource.$(OBJ)
                live/liveMedia/JPEGVideoSource.cpp
                #JPEGVideoRTPSource.$(OBJ)
                live/liveMedia/JPEGVideoRTPSource.cpp
                #JPEG2000VideoRTPSource.$(OBJ)
                live/liveMedia/JPEG2000VideoRTPSource.cpp
            # < $(JPEG_SOURCE_OBJS)
            # $(H263_SOURCE_OBJS) >
                #H263plusVideoRTPSource.$(OBJ)
                live/liveMedia/H263plusVideoRTPSource.cpp
                #H263plusVideoStreamFramer.$(OBJ)
                live/liveMedia/H263plusVideoStreamFramer.cpp
                #H263plusVideoStreamParser.$(OBJ)
                live/liveMedia/H263plusVideoStreamParser.cpp
            # < $(H263_SOURCE_OBJS)
            # $(AC3_SOURCE_OBJS) >
                #AC3AudioStreamFramer.$(OBJ)
                live/liveMedia/AC3AudioStreamFramer.cpp
                #AC3AudioRTPSource.$(OBJ)
                live/liveMedia/AC3AudioRTPSource.cpp
            # < $(AC3_SOURCE_OBJS)
            # $(DV_SOURCE_OBJS) >
                #DVVideoStreamFramer.$(OBJ)
                live/liveMedia/DVVideoStreamFramer.cpp
                #DVVideoRTPSource.$(OBJ)
                live/liveMedia/DVVideoRTPSource.cpp
            # < $(DV_SOURCE_OBJS)
            #AMRAudioSource.$(OBJ)
            live/liveMedia/AMRAudioSource.cpp
            #AMRAudioFileSource.$(OBJ)
            live/liveMedia/AMRAudioFileSource.cpp
            #InputFile.$(OBJ)
            live/liveMedia/InputFile.cpp
            #StreamReplicator.$(OBJ)
            live/liveMedia/StreamReplicator.cpp
        # < $(MISC_SOURCE_OBJS)
        # $(MISC_SINK_OBJS) >
            #MediaSink.$(OBJ)
            live/liveMedia/MediaSink.cpp
            #FileSink.$(OBJ)
            live/liveMedia/FileSink.cpp
            #BasicUDPSink.$(OBJ)
            live/liveMedia/BasicUDPSink.cpp
            #AMRAudioFileSink.$(OBJ)
            live/liveMedia/AMRAudioFileSink.cpp
            #H264or5VideoFileSink.$(OBJ)
            live/liveMedia/H264or5VideoFileSink.cpp
            #H264VideoFileSink.$(OBJ)
            live/liveMedia/H264VideoFileSink.cpp
            #H265VideoFileSink.$(OBJ)
            live/liveMedia/H265VideoFileSink.cpp
            #OggFileSink.$(OBJ)
            live/liveMedia/OggFileSink.cpp
            # $(MPEG_SINK_OBJS) >
                #MPEG1or2AudioRTPSink.$(OBJ)
                live/liveMedia/MPEG1or2AudioRTPSink.cpp
                # $(MP3_SINK_OBJS) >
                    #MP3ADURTPSink.$(OBJ)
                    live/liveMedia/MP3ADURTPSink.cpp
                # < $(MP3_SINK_OBJS)
                #MPEG1or2VideoRTPSink.$(OBJ)
                live/liveMedia/MPEG1or2VideoRTPSink.cpp
                #MPEG4LATMAudioRTPSink.$(OBJ)
                live/liveMedia/MPEG4LATMAudioRTPSink.cpp
                #MPEG4GenericRTPSink.$(OBJ)
                live/liveMedia/MPEG4GenericRTPSink.cpp
                #MPEG4ESVideoRTPSink.$(OBJ)
                live/liveMedia/MPEG4ESVideoRTPSink.cpp
            # < $(MPEG_SINK_OBJS)
            # $(JPEG_SINK_OBJS) >
                #JPEGVideoRTPSink.$(OBJ)
                live/liveMedia/JPEGVideoRTPSink.cpp
                #JPEG2000VideoRTPSink.$(OBJ)
                live/liveMedia/JPEG2000VideoRTPSink.cpp
            # < $(JPEG_SINK_OBJS)
            # $(H263_SINK_OBJS) >
                #H263plusVideoRTPSink.$(OBJ)
                live/liveMedia/H263plusVideoRTPSink.cpp
            # < $(H263_SINK_OBJS)
            # $(H264_OR_5_SINK_OBJS) >
                #H264or5VideoRTPSink.$(OBJ)
                live/liveMedia/H264or5VideoRTPSink.cpp
                #H264VideoRTPSink.$(OBJ)
                live/liveMedia/H264VideoRTPSink.cpp
                #H265VideoRTPSink.$(OBJ)
                live/liveMedia/H265VideoRTPSink.cpp
            # < $(H264_OR_5_SINK_OBJS)
            # $(DV_SINK_OBJS) >
                #DVVideoRTPSink.$(OBJ)
                live/liveMedia/DVVideoRTPSink.cpp
            # < $(DV_SINK_OBJS)
            # $(AC3_SINK_OBJS) >
                #AC3AudioRTPSink.$(OBJ)
                live/liveMedia/AC3AudioRTPSink.cpp
            # < $(AC3_SINK_OBJS)
            #VorbisAudioRTPSink.$(OBJ)
            live/liveMedia/VorbisAudioRTPSink.cpp
            #TheoraVideoRTPSink.$(OBJ)
            live/liveMedia/TheoraVideoRTPSink.cpp
            #VP8VideoRTPSink.$(OBJ)
            live/liveMedia/VP8VideoRTPSink.cpp
            #VP9VideoRTPSink.$(OBJ)
            live/liveMedia/VP9VideoRTPSink.cpp
            #GSMAudioRTPSink.$(OBJ)
            live/liveMedia/GSMAudioRTPSink.cpp
            #SimpleRTPSink.$(OBJ)
            live/liveMedia/SimpleRTPSink.cpp
            #AMRAudioRTPSink.$(OBJ)
            live/liveMedia/AMRAudioRTPSink.cpp
            #T140TextRTPSink.$(OBJ)
            live/liveMedia/T140TextRTPSink.cpp
            #TCPStreamSink.$(OBJ)
            live/liveMedia/TCPStreamSink.cpp
            #OutputFile.$(OBJ)
            live/liveMedia/OutputFile.cpp
            #RawVideoRTPSink.$(OBJ)
            live/liveMedia/RawVideoRTPSink.cpp
        # < $(MISC_SINK_OBJS)
        # $(MISC_FILTER_OBJS) >
            #uLawAudioFilter.$(OBJ)
            live/liveMedia/uLawAudioFilter.cpp
        # < $(MISC_FILTER_OBJS)
        # $(RTP_OBJS) >
            # $(RTP_SOURCE_OBJS) >
                #RTPSource.$(OBJ)
                live/liveMedia/RTPSource.cpp
                #MultiFramedRTPSource.$(OBJ)
                live/liveMedia/MultiFramedRTPSource.cpp
                #SimpleRTPSource.$(OBJ)
                live/liveMedia/SimpleRTPSource.cpp
                #H261VideoRTPSource.$(OBJ)
                live/liveMedia/H261VideoRTPSource.cpp
                #H264VideoRTPSource.$(OBJ)
                live/liveMedia/H264VideoRTPSource.cpp
                #H265VideoRTPSource.$(OBJ)
                live/liveMedia/H265VideoRTPSource.cpp
                #QCELPAudioRTPSource.$(OBJ)
                live/liveMedia/QCELPAudioRTPSource.cpp
                #AMRAudioRTPSource.$(OBJ)
                live/liveMedia/AMRAudioRTPSource.cpp
                #VorbisAudioRTPSource.$(OBJ)
                live/liveMedia/VorbisAudioRTPSource.cpp
                #TheoraVideoRTPSource.$(OBJ)
                live/liveMedia/TheoraVideoRTPSource.cpp
                #VP8VideoRTPSource.$(OBJ)
                live/liveMedia/VP8VideoRTPSource.cpp
                #VP9VideoRTPSource.$(OBJ)
                live/liveMedia/VP9VideoRTPSource.cpp
                #RawVideoRTPSource.$(OBJ)
                live/liveMedia/RawVideoRTPSource.cpp
            # < $(RTP_SOURCE_OBJS)
            # $(RTP_SINK_OBJS) >
                #RTPSink.$(OBJ)
                live/liveMedia/RTPSink.cpp
                #MultiFramedRTPSink.$(OBJ)
                live/liveMedia/MultiFramedRTPSink.cpp
                #AudioRTPSink.$(OBJ)
                live/liveMedia/AudioRTPSink.cpp
                #VideoRTPSink.$(OBJ)
                live/liveMedia/VideoRTPSink.cpp
                #TextRTPSink.$(OBJ)
                live/liveMedia/TextRTPSink.cpp
            # < $(RTP_SINK_OBJS)
            # $(RTP_INTERFACE_OBJS) >
                #RTPInterface.$(OBJ)
                live/liveMedia/RTPInterface.cpp
            # < $(RTP_INTERFACE_OBJS)
        # < $(RTP_OBJS)
        # $(RTCP_OBJS) >
            #RTCP.$(OBJ)
            live/liveMedia/RTCP.cpp
            #rtcp_from_spec.$(OBJ)
            live/liveMedia/rtcp_from_spec.c
        # < $(RTCP_OBJS)
        # $(GENERIC_MEDIA_SERVER_OBJS) >
            #GenericMediaServer.$(OBJ)
            live/liveMedia/GenericMediaServer.cpp
        # < $(GENERIC_MEDIA_SERVER_OBJS)
        # $(RTSP_OBJS) >
            #RTSPServer.$(OBJ)
            live/liveMedia/RTSPServer.cpp
            #RTSPServerRegister.$(OBJ)
            live/liveMedia/RTSPServerRegister.cpp
            #RTSPClient.$(OBJ)
            live/liveMedia/RTSPClient.cpp
            #RTSPCommon.$(OBJ)
            live/liveMedia/RTSPCommon.cpp
            #RTSPServerSupportingHTTPStreaming.$(OBJ)
            live/liveMedia/RTSPServerSupportingHTTPStreaming.cpp
            #RTSPRegisterSender.$(OBJ)
            live/liveMedia/RTSPRegisterSender.cpp
        # < $(RTSP_OBJS)
        # $(SIP_OBJS) >
            #SIPClient.$(OBJ)
            live/liveMedia/SIPClient.cpp
        # < $(SIP_OBJS)
        # $(SESSION_OBJS) >
            #MediaSession.$(OBJ)
            live/liveMedia/MediaSession.cpp
            #ServerMediaSession.$(OBJ)
            live/liveMedia/ServerMediaSession.cpp
            #PassiveServerMediaSubsession.$(OBJ)
            live/liveMedia/PassiveServerMediaSubsession.cpp
            #OnDemandServerMediaSubsession.$(OBJ)
            live/liveMedia/OnDemandServerMediaSubsession.cpp
            #FileServerMediaSubsession.$(OBJ)
            live/liveMedia/FileServerMediaSubsession.cpp
            #MPEG4VideoFileServerMediaSubsession.$(OBJ)
            live/liveMedia/MPEG4VideoFileServerMediaSubsession.cpp
            #H264VideoFileServerMediaSubsession.$(OBJ)
            live/liveMedia/H264VideoFileServerMediaSubsession.cpp
            #H265VideoFileServerMediaSubsession.$(OBJ)
            live/liveMedia/H265VideoFileServerMediaSubsession.cpp
            #H263plusVideoFileServerMediaSubsession.$(OBJ)
            live/liveMedia/H263plusVideoFileServerMediaSubsession.cpp
            #WAVAudioFileServerMediaSubsession.$(OBJ)
            live/liveMedia/WAVAudioFileServerMediaSubsession.cpp
            #AMRAudioFileServerMediaSubsession.$(OBJ)
            live/liveMedia/AMRAudioFileServerMediaSubsession.cpp
            #MP3AudioFileServerMediaSubsession.$(OBJ)
            live/liveMedia/MP3AudioFileServerMediaSubsession.cpp
            #MPEG1or2VideoFileServerMediaSubsession.$(OBJ)
            live/liveMedia/MPEG1or2VideoFileServerMediaSubsession.cpp
            #MPEG1or2FileServerDemux.$(OBJ)
            live/liveMedia/MPEG1or2FileServerDemux.cpp
            #MPEG1or2DemuxedServerMediaSubsession.$(OBJ)
            live/liveMedia/MPEG1or2DemuxedServerMediaSubsession.cpp
            #MPEG2TransportFileServerMediaSubsession.$(OBJ)
            live/liveMedia/MPEG2TransportFileServerMediaSubsession.cpp
            #ADTSAudioFileServerMediaSubsession.$(OBJ)
            live/liveMedia/ADTSAudioFileServerMediaSubsession.cpp
            #DVVideoFileServerMediaSubsession.$(OBJ)
            live/liveMedia/DVVideoFileServerMediaSubsession.cpp
            #AC3AudioFileServerMediaSubsession.$(OBJ)
            live/liveMedia/AC3AudioFileServerMediaSubsession.cpp
            #MPEG2TransportUDPServerMediaSubsession.$(OBJ)
            live/liveMedia/MPEG2TransportUDPServerMediaSubsession.cpp
            #ProxyServerMediaSession.$(OBJ)
            live/liveMedia/ProxyServerMediaSession.cpp
        # < $(SESSION_OBJS)
        # $(QUICKTIME_OBJS) >
            #QuickTimeFileSink.$(OBJ)
            live/liveMedia/QuickTimeFileSink.cpp
            #QuickTimeGenericRTPSource.$(OBJ)
            live/liveMedia/QuickTimeGenericRTPSource.cpp
        # < $(QUICKTIME_OBJS)
        # $(AVI_OBJS) >
            #AVIFileSink.$(OBJ)
            live/liveMedia/AVIFileSink.cpp
        # < $(AVI_OBJS)
        # $(TRANSPORT_STREAM_TRICK_PLAY_OBJS) >
            #MPEG2IndexFromTransportStream.$(OBJ)
            live/liveMedia/MPEG2IndexFromTransportStream.cpp
            #MPEG2TransportStreamIndexFile.$(OBJ)
            live/liveMedia/MPEG2TransportStreamIndexFile.cpp
            #MPEG2TransportStreamTrickModeFilter.$(OBJ)
            live/liveMedia/MPEG2TransportStreamTrickModeFilter.cpp
        # < $(TRANSPORT_STREAM_TRICK_PLAY_OBJS)
        # $(MATROSKA_OBJS) >
            # $(MATROSKA_FILE_OBJS) >
                #MatroskaFile.$(OBJ)
                live/liveMedia/MatroskaFile.cpp
                #MatroskaFileParser.$(OBJ)
                live/liveMedia/MatroskaFileParser.cpp
                #EBMLNumber.$(OBJ)
                live/liveMedia/EBMLNumber.cpp
                #MatroskaDemuxedTrack.$(OBJ)
                live/liveMedia/MatroskaDemuxedTrack.cpp
            # < $(MATROSKA_FILE_OBJS)
            # $(MATROSKA_RTSP_SERVER_OBJS) >
                #MatroskaFileServerDemux.$(OBJ)
                live/liveMedia/MatroskaFileServerDemux.cpp
                # $(MATROSKA_SERVER_MEDIA_SUBSESSION_OBJS) >
                    #MatroskaFileServerMediaSubsession.$(OBJ)
                    live/liveMedia/MatroskaFileServerMediaSubsession.cpp
                    #MP3AudioMatroskaFileServerMediaSubsession.$(OBJ)
                    live/liveMedia/MP3AudioMatroskaFileServerMediaSubsession.cpp
                # < $(MATROSKA_SERVER_MEDIA_SUBSESSION_OBJS)
            # < $(MATROSKA_RTSP_SERVER_OBJS)
        # < $(MATROSKA_OBJS)
        # $(OGG_OBJS) >
            # $(OGG_FILE_OBJS) >
                #OggFile.$(OBJ)
                live/liveMedia/OggFile.cpp
                #OggFileParser.$(OBJ)
                live/liveMedia/OggFileParser.cpp
                #OggDemuxedTrack.$(OBJ)
                live/liveMedia/OggDemuxedTrack.cpp
            # < $(OGG_FILE_OBJS)
            # $(OGG_RTSP_SERVER_OBJS) >
                #OggFileServerDemux.$(OBJ)
                live/liveMedia/OggFileServerDemux.cpp
                # $(OGG_SERVER_MEDIA_SUBSESSION_OBJS) >
                    #OggFileServerMediaSubsession.$(OBJ)
                    live/liveMedia/OggFileServerMediaSubsession.cpp
                # < $(OGG_SERVER_MEDIA_SUBSESSION_OBJS)
            # < $(OGG_RTSP_SERVER_OBJS)
        # < $(OGG_OBJS)
        # $(MISC_OBJS) >
            #BitVector.$(OBJ)
            live/liveMedia/BitVector.cpp
            #StreamParser.$(OBJ)
            live/liveMedia/StreamParser.cpp
            #DigestAuthentication.$(OBJ)
            live/liveMedia/DigestAuthentication.cpp
            #ourMD5.$(OBJ)
            live/liveMedia/ourMD5.cpp
            #Base64.$(OBJ)
            live/liveMedia/Base64.cpp
            #Locale.$(OBJ)
            live/liveMedia/Locale.cpp
        # < $(MISC_OBJS)
    # < $(LIVEMEDIA_LIB_OBJS) \
    # $(GROUPSOCK_LIB_OBJS) >
        #GroupsockHelper.$(OBJ)
        live/groupsock/GroupsockHelper.cpp
        #GroupEId.$(OBJ)
        live/groupsock/GroupEId.cpp
        #inet.$(OBJ)
        live/groupsock/inet.c
        #Groupsock.$(OBJ)
        live/groupsock/Groupsock.cpp
        #NetInterface.$(OBJ)
        live/groupsock/NetInterface.cpp
        #NetAddress.$(OBJ)
        live/groupsock/NetAddress.cpp
        #IOHandlers.$(OBJ)
        live/groupsock/IOHandlers.cpp
    # < $(GROUPSOCK_LIB_OBJS)
    # $(UsageEnvironment OBJS) >
        #UsageEnvironment.$(OBJ)
        live/UsageEnvironment/UsageEnvironment.cpp
        #HashTable.$(OBJ)
        live/UsageEnvironment/HashTable.cpp
        #strDup.$(OBJ)
        live/UsageEnvironment/strDup.cpp
    # < $(UsageEnvironment OBJS)
    # $(BasicUsageEnvironment OBJS) >
        #BasicUsageEnvironment0.$(OBJ)
        live/BasicUsageEnvironment/BasicUsageEnvironment0.cpp
        #BasicUsageEnvironment.$(OBJ)
        live/BasicUsageEnvironment/BasicUsageEnvironment.cpp
        #BasicTaskScheduler0.$(OBJ)
        live/BasicUsageEnvironment/BasicTaskScheduler0.cpp
        #BasicTaskScheduler.$(OBJ)
        live/BasicUsageEnvironment/BasicTaskScheduler.cpp
        #DelayQueue.$(OBJ)
        live/BasicUsageEnvironment/DelayQueue.cpp
        #BasicHashTable.$(OBJ)
        live/BasicUsageEnvironment/BasicHashTable.cpp
    # < $(BasicUsageEnvironment OBJS)
)

target_include_directories(liveMedia
    PUBLIC live/liveMedia/include live/UsageEnvironment/include live/groupsock/include live/BasicUsageEnvironment/include
)

target_link_libraries(liveMedia
    PUBLIC Ws2_32.lib kernel32.lib advapi32.lib shell32.lib
)


add_executable(testH264VideoStreamer
    live/testProgs/testH264VideoStreamer.cpp
)
target_link_libraries(testH264VideoStreamer
    PUBLIC liveMedia
)

