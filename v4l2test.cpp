#include <cutils/properties.h>
#include "camcdr.h"

int main(int argc, char *argv[])
{
    CAMCDR *cam = NULL;
    char    dev[32] = "/dev/video0";
    int     sub     = 0;
    int     fmt     = V4L2_PIX_FMT_YUYV;
    int     w       = 640;
    int     h       = 480;

    switch (argc) {
    case 6: h = atoi(argv[5]);
    case 5: w = atoi(argv[4]);
    case 4: fmt = !strcmp(argv[3], "mjpeg") ? V4L2_PIX_FMT_MJPEG : fmt;
    case 3: sub = atoi(argv[2]);
    case 2: strcpy(dev, argv[1]);
    }
    printf("dev = %s, sub = %d, fmt = %d, w = %d, h = %d\n", dev, sub, fmt, w, h);

    // set exit flag to 0
    property_set("sys.v4l2.test.exit", "0");

    // create a client to surfaceflinger
    sp<SurfaceComposerClient> client = new SurfaceComposerClient();
    sp<IBinder> dtoken(SurfaceComposerClient::getBuiltInDisplay(
            ISurfaceComposer::eDisplayIdMain));

    DisplayInfo dinfo;
    status_t status = SurfaceComposerClient::getDisplayInfo(dtoken, &dinfo);
    if (status) {
        return -1;
    }

    sp<SurfaceControl> surfaceControl = client->createSurface(String8("yuvtest_surface"),
            dinfo.w, dinfo.h, PIXEL_FORMAT_RGBX_8888, 0);

    SurfaceComposerClient::openGlobalTransaction();
    surfaceControl->setLayer(0x40000000);
//  surfaceControl->setPosition(0, 0);
//  surfaceControl->setSize(dinfo.w, dinfo.h);
    SurfaceComposerClient::closeGlobalTransaction();

    sp<Surface> surface = surfaceControl->getSurface();
    sp<ANativeWindow> win = surface;
    native_window_set_buffers_dimensions(win.get(), dinfo.w, dinfo.h);

    // init camcdr
    cam = camcdr_init(dev, sub, fmt, w, h);

    // startpreview
    camcdr_set_preview_window(cam, win);
    camcdr_start_preview(cam);

    // wait exit
    while (1) {
        char exit[PROP_VALUE_MAX];
        property_get("sys.v4l2.test.exit", exit, "0");
        if (strcmp(exit, "1") == 0) {
            break;
        }
    }

    // stoppreview
    camcdr_stop_preview(cam);

    // close camcdr
    camcdr_close(cam);

    return 0;
}

