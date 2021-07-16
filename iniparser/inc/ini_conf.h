/*
 * @Descripttion: ini parser supplement
 * @version: 0.1
 * @Author: Ricardo Lu <sheng.lu@thundercomm.com>
 * @Date: 2021-04-23 14:09:29
 * @LastEditors: Ricardo Lu
 * @LastEditTime: 2021-04-26 15:06:05
 */

#ifndef __INI_CONF_H__
#define __INI_CONF_H__

typedef struct ini_conf
{
    char camera_section[16];
	int camera_id;
	char camera_name[16];
	char decode[5];
	char enable[4];
	char algo[16];
	int height;
	int width;
	char color_space[16];

	int w_x;
	int w_y;
	int w_w;
	int w_h;

	char path[1024];
}rtsp_conf;

int ini_init(char *file_path);
void ini_deinit(void);
int ini_set_int(const char *section, const char *key, int val, char *file_path);
int ini_get_int(const char *section, const char *key, int notfound);
int ini_set_string(const char *section, const char *key, char *val, char *file_path);
char *ini_get_string(const char *section, const char *key, const char *notfound);
int ini_load(char *file_path, rtsp_conf *camera_conf);

#endif