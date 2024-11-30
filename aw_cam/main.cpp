#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <signal.h>
#include <iostream>
#include <vector>

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h> // sleep()
#include <sys/ioctl.h>

#include <sys/time.h>
#include <linux/fb.h>

#include <unistd.h> // sleep()

#include <float.h>
#include <stdio.h>
#include <vector>

cv::VideoCapture cap;
/* Signal handler */
static void terminate(int sig_no)
{
    printf("Got signal %d, exiting ...\n", sig_no);
    cap.release();
    exit(1);
}

static void install_sig_handler(void)
{
    signal(SIGBUS, terminate);
    signal(SIGFPE, terminate);
    signal(SIGHUP, terminate);
    signal(SIGILL, terminate);
    signal(SIGINT, terminate);
    signal(SIGIOT, terminate);
    signal(SIGPIPE, terminate);
    signal(SIGQUIT, terminate);
    signal(SIGSEGV, terminate);
    signal(SIGSYS, terminate);
    signal(SIGTERM, terminate);
    signal(SIGTRAP, terminate);
    signal(SIGUSR1, terminate);
    signal(SIGUSR2, terminate);
}

int main(int argc,char *argv[])
{
    cv::Mat bgr;
    install_sig_handler();
    int fb_fd = open("/dev/fb0", O_RDWR);
    if (fb_fd < 0)
    {
        fprintf(stderr, "open /dev/fb0 failed\n");
        return -1;
    }

    struct fb_var_screeninfo screen_info;
    memset(&screen_info, 0, sizeof(screen_info));
    ioctl(fb_fd, FBIOGET_VSCREENINFO, &screen_info);
    uint32_t xres_virtual = screen_info.xres_virtual;
    uint32_t bits_per_pixel = screen_info.bits_per_pixel;
    fprintf(stderr, "xres_virtual=%d,bits_per_pixel=%d\n", xres_virtual, bits_per_pixel);


    cap.set(cv::CAP_PROP_FRAME_WIDTH, 480);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.open(0);
    while(1)
    {
        cap >> bgr;
        cv::resize(bgr, bgr, cv::Size(240, 240));
        cv::transpose(bgr, bgr);
        cv::flip(bgr, bgr, 0);
        // cv::cvtColor(bgr, bgr, cv::COLOR_RGB2BGR565);
        // lseek(fb_fd, 0, SEEK_SET);
        // write(fb_fd, bgr.data, 240 * 240 * 2);
        // fsync(fb_fd);

        cv::imshow("fb",bgr);
    }
    //cv::imwrite("out.jpg", bgr);
    return 0;
}