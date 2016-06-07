#ifndef __CAMDEV_H__
#define __CAMDEV_H__

// ����ͷ�ļ�
#include <linux/videodev2.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>
#include <gui/ISurfaceComposer.h>
#include <ui/DisplayInfo.h>
#include <ui/GraphicBufferMapper.h>

extern "C" {
#include "libswscale/swscale.h"
}

using namespace android;

// ��������
#define VIDEO_CAPTURE_BUFFER_COUNT  3
#define NATIVE_WIN_BUFFER_COUNT     3

// ���Ͷ���
struct video_buffer{
    void    *addr;
    unsigned len;
};

typedef struct {
    struct v4l2_buffer      buf;
    struct video_buffer     vbs[VIDEO_CAPTURE_BUFFER_COUNT];
    int                     fd;
    sp<ANativeWindow>       new_win;
    sp<ANativeWindow>       cur_win;
    int                     win_w;
    int                     win_h;
    #define CAMDEV_TS_EXIT    (1 << 0)
    #define CAMDEV_TS_PAUSE   (1 << 1)
    #define CAMDEV_TS_PREVIEW (1 << 2)
    pthread_t               thread_id;
    int                     thread_state;
    int                     update_flag;
    int                     cam_pixfmt;
    int                     cam_stride;
    int                     cam_w;
    int                     cam_h;
    SwsContext             *swsctxt;
    void                   *encoder;
} CAMDEV;

// ��������
CAMDEV* camdev_init (const char *dev, int sub, int w, int h);
void    camdev_close(CAMDEV *cam);
void    camdev_set_preview_window(CAMDEV *cam, const sp<ANativeWindow> win);
void    camdev_set_preview_target(CAMDEV *cam, const sp<IGraphicBufferProducer>& gbp);
void    camdev_start_preview(CAMDEV *cam);
void    camdev_stop_preview (CAMDEV *cam);
void    camdev_set_encoder  (CAMDEV *cam, void *encoder);

#endif









