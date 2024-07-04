#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <stdio.h>
// sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
static gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data) {
    GMainLoop *loop = (GMainLoop *) data;
    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_EOS:
            g_print("End of stream\n");
            g_main_loop_quit(loop);
            break;
        case GST_MESSAGE_ERROR: {
            gchar *debug;
            GError *error;
            gst_message_parse_error(msg, &error, &debug);
            g_free(debug);
            g_printerr("Error: %s\n", error->message);
            g_error_free(error);
            g_main_loop_quit(loop);
            break;
        }
        default:
            break;
    }
    return TRUE;
}

static GstFlowReturn on_new_sample(GstElement *sink, gpointer data) {
    GstSample *sample;
    GstBuffer *buffer;
    GstMapInfo map;

    // Get the sample
    sample = gst_app_sink_pull_sample(GST_APP_SINK(sink));
    buffer = gst_sample_get_buffer(sample);

    // Map the buffer to get access to the data
    if (gst_buffer_map(buffer, &map, GST_MAP_READ)) {
        // Process the raw data (map.data, map.size)
        g_print("New sample received with size %zu\n", map.size);

        // Unmap buffer
        gst_buffer_unmap(buffer, &map);
    }

    // Free the sample
    gst_sample_unref(sample);

    return GST_FLOW_OK;
}

int main(int argc, char *argv[]) {
    GMainLoop *loop;
    GstElement *pipeline, *source, *videoconvert, *encoder, *mpegtsmux, *sink;
    GstBus *bus;

    gst_init(&argc, &argv);
    loop = g_main_loop_new(NULL, FALSE);

    // Create elements
    pipeline = gst_pipeline_new("desktop-capture-pipeline");
    source = gst_element_factory_make("ximagesrc", "source");
    videoconvert = gst_element_factory_make("videoconvert", "videoconvert");
    encoder = gst_element_factory_make("x264enc", "encoder");
    mpegtsmux = gst_element_factory_make("mpegtsmux", "mpegtsmux");
    sink = gst_element_factory_make("appsink", "sink");

    if (!pipeline || !source || !videoconvert || !encoder || !mpegtsmux || !sink) {
        g_printerr("One element could not be created. Exiting.\n");
        return -1;
    }

    // Set properties
    // g_object_set(G_OBJECT(source), "use-damage", FALSE, NULL);
    // g_object_set(G_OBJECT(encoder), "bitrate", 5000, "speed-preset", 1, "tune", "zerolatency", NULL);
    g_object_set(G_OBJECT(sink), "emit-signals", TRUE, "sync", FALSE, NULL);
    g_signal_connect(sink, "new-sample", G_CALLBACK(on_new_sample), NULL);

    // Build the pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, videoconvert, encoder, mpegtsmux, sink, NULL);
    gst_element_link_many(source, videoconvert, encoder, mpegtsmux, sink, NULL);

    // Add a message handler
    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_watch(bus, bus_call, loop);
    gst_object_unref(bus);

    // Start playing
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    g_main_loop_run(loop);

    // Clean up
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(pipeline));
    g_main_loop_unref(loop);

    return 0;
}
