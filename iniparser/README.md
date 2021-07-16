<!--
 * @Descripttion: a brief description of this library.
 * @version: 0.1
 * @Author: Ricardo Lu <sheng.lu@thundercomm.com>
 * @Date: 2021-04-26 10:21:09
 * @LastEditors: Ricardo Lu
 * @LastEditTime: 2021-04-26 10:37:14
-->
# iniparser
This is a rtsp camera config ini file parser developed based on the repository of [iniparser](https://github.com/ndevilla/iniparser), it helps to bind the section and key, so you can get the value of corresponding key under specific section.

**Notes:** the [iniparser](https://github.com/ndevilla/iniparser) is work under the [MIT LICENSE](./LICENSE), while I choosed the GPL LICENSE.

## build
```shell
mkdir build
cd build
cmake ..
make

./iniparser-test
```