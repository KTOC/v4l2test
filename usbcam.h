#ifndef __USBCAM_H__
#define __USBCAM_H__

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
    struct v4l2_capability  cap;
    struct v4l2_fmtdesc     desc;
    struct v4l2_format      fmt;
    struct v4l2_buffer      buf;
    struct video_buffer     vbs[VIDEO_CAPTURE_BUFFER_COUNT];
    int                     fd;
    sp<ANativeWindow>       new_win;
    int                     new_w;
    int                     new_h;
    sp<ANativeWindow>       cur_win;
    int                     cur_w;
    int                     cur_h;
    pthread_t               thread_id;
    int                     thread_state;
    int                     update_preview_flag;
    void                   *decoder;
} USBCAM;

// ��������
USBCAM* usbcam_init (const char *dev);
void    usbcam_close(USBCAM *cam);
void    usbcam_set_preview_window(USBCAM *cam, const sp<ANativeWindow> win, int w, int h);
void    usbcam_set_preview_target(USBCAM *cam, const sp<IGraphicBufferProducer>& gbp, int w, int h);
void    usbcam_start_preview(USBCAM *cam);
void    usbcam_stop_preview (USBCAM *cam);

#endif









