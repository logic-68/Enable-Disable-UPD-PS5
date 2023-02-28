#ifndef PS5VERSION_H
#define PS5VERSION_H
#include <utils.h>

char version[256];
char firmware[6];
uint32_t ps4_sdk_version, sdk_version, upd_version;
size_t olden;
uint32_t get_ps4_sdk_version();
uint32_t get_kernel_version();
uint32_t get_upd_version();
char *get_os_version();
char *get_firmware();
#endif