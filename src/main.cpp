#include <gst/gst.h>
#include <glib.h>
#include <csignal>
#include <iostream>

// Global variables for the pipeline and main loop
GstElement *pipeline;
GMainLoop *loop;

// Function to handle the SIGINT signal (Ctrl+C)
void handle_sigint(int sig) {
    std::cout << "Stopping pipeline..." << std::endl;
    gst_element_set_state(pipeline, GST_STATE_NULL);
    g_main_loop_quit(loop);
}

int main(int argc, char *argv[]) {
    GstElement *source, *videoconvert, *queue, *encoder, *muxer, *sink;

    // Initialize GStreamer
    gst_init(&argc, &argv);

    // Create elements
    source = gst_element_factory_make("ximagesrc", "source");
    videoconvert = gst_element_factory_make("videoconvert", "videoconvert");
    queue = gst_element_factory_make("queue", "queue");
    encoder = gst_element_factory_make("x264enc", "encoder");
    muxer = gst_element_factory_make("mpegtsmux", "muxer");
    sink = gst_element_factory_make("srtsink", "sink");

    // Check if all elements are created successfully
    if (!source ) {
        g_printerr("Failed to create source.\n");
        return -1;
    }

   if (!videoconvert ) {
        g_printerr("Failed to create videoconvert.\n");
        return -1;
    }

   if (!queue ) {
        g_printerr("Failed to create queue.\n");
        return -1;
    }

   if ( !encoder) {
        g_printerr("Failed to create encoder.\n");
        return -1;
    }

   if ( !muxer ) {
        g_printerr("Failed to create muxer.\n");
        return -1;
    }

   if ( !sink) {
        g_printerr("Failed to create sink.\n");
        return -1;
    }

    // Create the empty pipeline
    pipeline = gst_pipeline_new("desktop-stream-pipeline");

    // Build the pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, videoconvert, queue, encoder, muxer, sink, NULL);
    if (!gst_element_link_many(source, videoconvert, queue, encoder, muxer, sink, NULL)) {
        g_printerr("Failed to link elements.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    // Set properties
    g_object_set(G_OBJECT(sink), "uri", "srt://192.168.207.58:5000?mode=listener&latency=2000", NULL);
    g_object_set(G_OBJECT(encoder), "bitrate", 2000, "speed-preset", 1, "tune", 4, NULL); // speed-preset=superfast (1), tune=zerolatency (4)

    // Start playing the pipeline
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Create a GLib main loop
    loop = g_main_loop_new(NULL, FALSE);

    // Set the signal handler for SIGINT (Ctrl+C)
    signal(SIGINT, handle_sigint);

    // Run the loop
    g_main_loop_run(loop);

    // Clean up
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    g_main_loop_unref(loop);

    std::cout << "Pipeline stopped." << std::endl;

    return 0;
}

