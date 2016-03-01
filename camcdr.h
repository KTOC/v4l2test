#ifndef __CAMCDR_H__
#define __CAMCDR_H__

// ����ͷ�ļ�
#include <linux/videodev2.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>
#include <gui/ISurfaceComposer.h>
#include <ui/DisplayInfo.h>
#include <ui/GraphicBufferMapper.h>

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
    struct v4l2_format      fmt;
    struct v4l2_buffer      buf;
    struct video_buffer     vbs[VIDEO_CAPTURE_BUFFER_COUNT];
    int                     fd;
    sp<ANativeWindow>       new_win;
    sp<ANativeWindow>       cur_win;
    pthread_t               thread_id;
    int                     thread_state;
    int                     update_flag;
    int                     win_pixfmt;
    int                     cam_input;
    int                     cam_pixfmt;
    int                     cam_w;
    int                     cam_h;
    void                   *jpegdec;
} CAMCDR;

// ��������
CAMCDR* camcdr_init (const char *dev, int sub, int fmt, int w, int h);
void    camcdr_close(CAMCDR *cam);
void    camcdr_set_preview_window(CAMCDR *cam, const sp<ANativeWindow> win);
void    camcdr_set_preview_target(CAMCDR *cam, const sp<IGraphicBufferProducer>& gbp);
void    camcdr_start_preview(CAMCDR *cam);
void    camcdr_stop_preview (CAMCDR *cam);

#endif









