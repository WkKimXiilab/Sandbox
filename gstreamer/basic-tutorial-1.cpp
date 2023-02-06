#include <gst/gst.h>
#include <gst/app/gstappsrc.h>
#include <iostream>
#include <unistd.h>

GstElement *pipeline, *source, *demux, *parse, *decoder, *filter, *converter, *sink;

static GstPadProbeReturn cb_have_data(
	GstPad *pad, 
	GstPadProbeInfo *info, 
	gpointer user_data)
{
	std::cout << "cb_have_data start." << std::endl;
	GstMapInfo map;
	GstBuffer *buffer;

	buffer = GST_PAD_PROBE_INFO_BUFFER(info);
	buffer = gst_buffer_make_writable(buffer);

	int nRet = gst_buffer_map(buffer, &map, GST_MAP_WRITE);

	gst_buffer_unmap(buffer, &map);

	GST_PAD_PROBE_INFO_DATA(info) = buffer;

	static int nCount = 0;

	std::cout << "count : " << nCount++ << std::endl;

	return GST_PAD_PROBE_OK;
}

static void SourcePadCallback(
	GstElement *element,
	GstPad *pad,
	gpointer data)
{
	std::cout << "SourcePadCallback start." << std::endl;
	GstPad *sinkpad;
	
	GstElement *_demux = (GstElement*) data;

	sinkpad = gst_element_get_static_pad(_demux, "sink");

	gst_pad_link(pad, sinkpad);
	gst_object_unref(sinkpad);
}

static void NewPadCallback(
	GstElement *element,
	GstPad *pad,
	gpointer data)
{
	gchar *name;

	name = gst_pad_get_name(pad);
	if(strcmp(name, "video_0") == 0 && 
		!gst_element_link_pads(demux, name, parse, "sink"))
	{
		std::cout << "link demux-parse fail" << std::endl;
	}
	g_free(name);
}

int main (int argc, char *argv[])
{
	GstBus *bus;
	GstMessage *msg;
	GstStateChangeReturn ret;

	/* Initialize GStreamer */
	gst_init (nullptr, nullptr);

	// source = gst_element_factory_make("filesrc", "source");
	// demux = gst_element_factory_make("qtdemux", "demux");
	source = gst_element_factory_make("rtspsrc", "source");
	demux = gst_element_factory_make("rtph264depay", "demux");
	parse = gst_element_factory_make("h264parse", "parse");
	decoder = gst_element_factory_make("nvv4l2decoder", "decoder");
	filter = gst_element_factory_make("capsfilter", "filter");
	converter = gst_element_factory_make("videoconvert", "converter");
	// sink = gst_element_factory_make("appsink", "sink");
	sink = gst_element_factory_make("fakesink", "sink");

	GstElement *pipeline = gst_pipeline_new("test-pipeline");

	if (!pipeline || !source || !sink)
	{
		std::cout << "pipeline, source, sink error." << std::endl;
		return -1;
	}

	gst_bin_add_many(
		GST_BIN(pipeline), 
		source, 
		demux,
		parse,
		decoder,
		filter,
		converter,
		sink, 
		nullptr);
	
	// int nRet = gst_element_link(source, demux);
	// nRet = gst_element_link(parse, decoder);
	// nRet = gst_element_link(decoder, sink);

	int nRet = gst_element_link_many(demux, parse, decoder, filter, converter, sink, nullptr);

	// g_object_set(G_OBJECT(source), "location", "video_sample/Next_Level_HD.mp4", nullptr);
	g_object_set(G_OBJECT(source), "location", "rtsp://192.168.2.44:3082/1/high", nullptr);

	g_signal_connect_object(source, "pad_added", G_CALLBACK(SourcePadCallback), demux, G_CONNECT_AFTER);
	// g_signal_connect(demux, "pad_added", G_CALLBACK(NewPadCallback), nullptr);

	// Callback For Buffer?
	GstCaps *filtercaps;
	GstPad *pad;

	filtercaps = gst_caps_new_simple("video/x-raw(memory:NVMM)", 
		"format", G_TYPE_STRING, "NV12",
		"width", G_TYPE_INT, 1920,
		"height", G_TYPE_INT, 1080,
		"framerate", GST_TYPE_FRACTION, 30, 1, nullptr);

	g_object_set(G_OBJECT(filter), "caps", filtercaps, nullptr);
	gst_caps_unref(filtercaps);

	// pad = gst_element_get_static_pad(demux, "src");
	pad = gst_element_get_static_pad(converter, "src");

	gst_pad_add_probe(pad, GST_PAD_PROBE_TYPE_BUFFER, (GstPadProbeCallback) cb_have_data, nullptr, nullptr);
	gst_object_unref(pad);

	/* Start playing */
	ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE)
	{
		gst_object_unref(pipeline);
		return -1;
	}
	std::cout << "gst_element_set_state : " << ret << std::endl;

	/* Wait until error or EOS */
	bus = gst_element_get_bus (pipeline);

	if (bus == nullptr)
		std::cout << "bus error." << std::endl;

	std::cout << "gst_element_get_bus." << std::endl;
	msg =
		gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
		static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
		// static_cast<GstMessageType>(GST_MESSAGE_ERROR));

	// GError *err;
	// gchar *debug_info;
	// gst_message_parse_error(msg, &err, &debug_info);
	// std::cout << "gst_bus_timed_pop_filtered : " << err->message << std::endl;

	/* Free resources */
	if (msg != nullptr)
		gst_message_unref (msg);

	printf("get_message_unref.\n");

	gst_object_unref (bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);

	printf("end soon...\n");

	while(1)
		sleep(1);

	return 0;
}
