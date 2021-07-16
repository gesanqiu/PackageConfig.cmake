/*
 * @Descripttion: ini parser supplement
 * @version: 0.1
 * @Author: Ricardo Lu <sheng.lu@thundercomm.com>
 * @Date: 2021-04-23 14:09:29
 * @LastEditors: Ricardo Lu
 * @LastEditTime: 2021-04-26 15:06:37
 */

#include "iniparser.h"
#include "ini_conf.h"

static dictionary *ini_dic;

int is_file_exist(char *file_path)
{
    if (!file_path)
    {
        printf("file path empty!\n");
        return -1;
    }

    if (access(file_path, 0) < 0)
    {
        printf("file not exist!\n");
        return -1;
    }

    return 0;
}

int ini_init(char *file_path)
{
    int ret = 0;

    ret = is_file_exist(file_path);
    if (ret < 0)
        return -1;

    ini_dic = iniparser_load(file_path);
    if (!ini_dic)
    {
        printf("%s: failed to load ini file: %s!\n", __func__, file_path);
        return -1;
    }

    return 0;
}

void ini_deinit(void)
{
    if (ini_dic)
        iniparser_freedict(ini_dic);

}

int ini_set_int(const char *section, const char *key, int val, char *file_path)
{
    int ret = 0;
    char section_key[32];
    char val_str[32];
    FILE *fp;

    if (!ini_dic)
        return -1;

    sprintf(section_key, "%s:%d", section, key);
    sprintf(val_str, "%d", val);

    ret = iniparser_set(ini_dic, (const char *)section_key, (const char *)val_str);
    if (ret < 0) {
        printf("%s: ini set dic failed!\n", __func__);
        return ret;
    }

    // dump the modified section into source file
    fp = fopen(file_path, "w");
    if (!fp) {
        printf("%s: ini file open failed!\n", __func__);
        return -1;
    }

    iniparser_dumpsection_ini(ini_dic, section, fp);

    fclose(fp);
    return ret;
}

int ini_set_string(const char *section, const char *key, char *val, char *file_path)
{
    int ret = 0;
    char section_key[32];
    FILE *fp;

    if (!ini_dic)
        return -1;

    sprintf(section_key, "%s:%s", section, key);

    ret = iniparser_set(ini_dic, (const char *)section_key, (const char *)val);
    if (ret < 0) {
        printf("%s: ini set dic failed!\n", __func__);
        return ret;
    }

    // dump the modified section into source file
    fp = fopen(file_path, "w");
    if (!fp) {
        printf("%s: ini file open failed!\n", __func__);
        return -1;
    }

    iniparser_dumpsection_ini(ini_dic, section, fp);

    fclose(fp);
    return ret;
}

int ini_get_int(const char *section, const char *key, int notfound)
{
	char buf[32];
	int ret = 0;

	sprintf(buf, "%s:%s", section, key);

	ret = iniparser_getint(ini_dic, buf, notfound);

	return ret;
}

char *ini_get_string(const char *section, const char *key, const char *notfound)
{
	char buf[32];
	char *str = NULL;

	sprintf(buf, "%s:%s", section, key);

	str =  (char *)iniparser_getstring(ini_dic, buf, notfound);
	return str;
}

int ini_load(char *file_path, rtsp_conf *camera_conf)
{
    int ret = 0;

    ret = ini_init(file_path);
    if (ret < 0) {
        printf("%s: ini file init fialed!\n", __func__);
        return ret;
    }
    
    sprintf(camera_conf->camera_name, "%s", ini_get_string(camera_conf->camera_section, "cameraname", "camera_zero"));

	sprintf(camera_conf->decode, "%s", ini_get_string(camera_conf->camera_section, "decode", "NULL"));
	sprintf(camera_conf->enable, "%s", ini_get_string(camera_conf->camera_section, "enable", "off"));
	sprintf(camera_conf->path, "%s", ini_get_string(camera_conf->camera_section, "path", "NULL"));
	sprintf(camera_conf->algo, "%s", ini_get_string(camera_conf->camera_section, "algo", "NULL"));
    sprintf(camera_conf->color_space, "%s", ini_get_string(camera_conf->camera_section, "color", "NULL"));

	camera_conf->camera_id = ini_get_int(camera_conf->camera_section, "cameraid", 0);
	camera_conf->height = ini_get_int(camera_conf->camera_section, "height", 1920);
	camera_conf->width = ini_get_int(camera_conf->camera_section, "width", 1080);
	camera_conf->w_x = ini_get_int(camera_conf->camera_section, "w_x", 0);
	camera_conf->w_y = ini_get_int(camera_conf->camera_section, "w_y", 0);
	camera_conf->w_w = ini_get_int(camera_conf->camera_section, "w_w", 320);
	camera_conf->w_h = ini_get_int(camera_conf->camera_section, "w_h", 180);

    ini_deinit();

    return ret;
}