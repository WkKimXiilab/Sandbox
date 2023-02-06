
ARGUMENT=""
for i in $(seq 1 1 10)
do
	ARGUMENT="${ARGUMENT} rtspsrc is-live=true location=rtsp://192.168.2.44:3082/${i}/high protocols=tcp ! \
	typefind ! \
	multiqueue ! \
	rtph264depay ! \
	h264parse ! \
	queue max-size-buffers=20 ! \
	nvv4l2decoder enable-max-performance=1 ! \
	nvivafilter customer-lib-name=libnvsample_cudaprocess.so cuda-process=true post-process=true ! \
	nvoverlaysink sync=false "
done

echo ${ARGUMENT}

gst-launch-1.0 -v ${ARGUMENT} | grep current &

