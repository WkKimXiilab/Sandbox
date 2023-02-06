# GST_DEBUG=4 gst-launch-1.0 -e rtspsrc is-live=true location=rtsp://192.168.2.44:3082/1/high protocols=tcp ! typefind ! multiqueue ! rtph264depay ! h264parse ! nvv4l2decoder enable-max-performance=1 ! nvivafilter customer-lib-name=libnvsample_cudaprocess.so cuda-process=true post-process=true ! 'video/x-raw(memory:NVMM),format=(string)NV12,framerate=30/1,width=1920,height=1080' ! fpsdisplaysink video-sink=fakesink sync=false 

# GST_DEBUG=3 gst-launch-1.0 rtspsrc location=rtsp://192.168.2.44:3082/1/high ! rtph264depay ! h264parse ! nvv4l2decoder ! nvvidconv ! 'video/x-raw(memory:NVMM),width=(int)1920,height=(int)1080,format=(string)RGBA,framerate=(fraction)30001/1000' ! nvegltransform ! nveglglessink -e  

# GST_DEBUG=3 gst-launch-1.0 rtspsrc is-live=true location=rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mp4 ! rtph264depay ! queue ! nvv4l2decoder ! queue !  nvivafilter customer-lib-name=libnvsample_cudaprocess.so cuda-process=true post-process=true ! 'video/x-raw(memory:NVMM),format=(string)RGBA' ! nvegltransform ! 'video/x-raw(memory:EGLImage),format=(string)RGBA' !  nveglglessink

# GST_DEBUG=3 gst-launch-1.0 rtspsrc is-live=true location=rtspt://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mp4 ! rtph264depay ! h264parse ! nvv4l2decoder ! 'video/x-raw(memory:NVMM),width=(int)240,height=(int)160,format=(string)RGBA,framerate=(fraction)25001/1000' ! nvegltransform ! nveglglessink -e  

# GST_DEBUG=3 gst-launch-1.0 rtspsrc is-live=true location=rtsp://192.168.2.44:3082/1/high ! rtph264depay ! h264parse ! nvv4l2decoder enable-max-performance=1 ! 'video/x-raw(memory:NVMM),width=(int)1920,height=(int)1080,format=(string)NV12,framerate=(fraction)30001/1000' ! nvegltransform ! nvoverlaysink -e

#GST_DEBUG=3 gst-launch-1.0 \
#	filesrc location='/home/disk_mnt/workspace/wkkim/dev/ffmpeg_decoder/gstreamer/video_sample/Next_Level_HD.mp4' ! \
#	qtdemux name=demux ! \
#	h264parse ! \
#	nvv4l2decoder ! \
#	nvvidconv ! \
#	'video/x-raw(memory:NVMM),format=(string)NV12' ! \
#	nvegltransform ! \
#	'video/x-raw(memory:EGLImage),format=(string)RGBA' ! \
#	nveglglessink -e
#	nvoverlaysink -e

# GST_DEBUG=nveglglessink:4 gst-launch-1.0 -v videotestsrc is-live=true ! nvvidconv ! nvegltransform ! nveglglessink

# Simple
# GST_DEBUG=3 gst-launch-1.0 filesrc location='/home/disk_mnt/workspace/wkkim/dev/ffmpeg_decoder/gstreamer/video_sample/Next_Level_HD.mp4' ! qtdemux name=demux ! h264parse ! queue ! nvv4l2decoder ! nvvidconv ! fakesink -e

# GST_DEBUG=3 gst-launch-1.0 filesrc location='video_sample/Next_Level_HD.mp4' ! qtdemux ! h264parse ! queue ! nvv4l2decoder ! 'video/x-raw(memory:NVMM),format=NV12' ! nvivafilter customer-lib-name=libnvsample_cudaprocess.so cuda-process=true post-process=true ! 'video/x-raw(memory:NVMM),format=RGBA' ! nvoverlaysink sync=false

GST_DEBUG=3 gst-launch-1.0 filesrc location='video_sample/Next_Level_HD.mp4' ! qtdemux ! h264parse ! queue ! nvv4l2decoder ! 'video/x-raw(memory:NVMM),format=NV12' ! nvivafilter customer-lib-name=libnvsample_cudaprocess.so cuda-process=true post-process=true ! 'video/x-raw(memory:NVMM),format=RGBA' ! nvegltransform bufapi-version=true ! nveglglessink -e
