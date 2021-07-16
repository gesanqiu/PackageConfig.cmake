/*
 * @Descripttion: a test file of iniparser
 * @version: 0.1
 * @Author: Ricardo Lu <shenglu@thundercomm.com>
 * @Date: 2021-04-26 09:29:09
 * @LastEditors: Ricardo Lu
 * @LastEditTime: 2021-07-16 10:17:15
 */

#include <stdio.h>
#include <string.h>
#include "ini_conf.h"


int main()
{
    rtsp_conf m_camera;
    char ini_file[32] = "../test.ini";
    int ret = 0;

    memset(&m_camera, 0, sizeof(rtsp_conf));

    // assignment the section parameter of m_camera
    sprintf(m_camera.camera_section, "%s", "rtsp_0");
    ini_load(ini_file, &m_camera);

    ret = strncmp(m_camera.enable, "on", sizeof("on"));
    if(ret > 0) {
        printf("rtsp camera disabled\n");
    }

    printf("working in: %s\n", __func__);
	printf("cameraID: %d\n", m_camera.camera_id);
	printf("cameraName: %s\n", m_camera.camera_name);
	printf("decode: %s\n", m_camera.decode);
	printf("algo: %s\n", m_camera.algo);

	printf("enable: %s\n", m_camera.enable);
	printf("path: %s\n", m_camera.path);
	printf("height: %d\n", m_camera.height);
	printf("widh: %d\n", m_camera.width);

	printf("w_x: %d\n", m_camera.w_x);
	printf("w_y: %d\n", m_camera.w_y);
	printf("w_h: %d\n", m_camera.w_h);
	printf("w_w: %d\n", m_camera.w_w);

    return 0;
}