#include <libPS5/ps5version.h>


char *get_firmware()
{
    char snprintf_buf[6];
    char *fw = f_malloc(sizeof(char) * 6);
	olden = sizeof(sdk_version);
    f_sysctlbyname("kern.sdk_version",(char *)&sdk_version, &olden, NULL, 0);
    f_snprintf(snprintf_buf, 0x6, "%2x.%03x", sdk_version >> 0x18, sdk_version >> 0xc & 0xfff);
    if (snprintf_buf[0] == ' ') f_strcpy(fw, snprintf_buf + 1);
    return fw;
}
char *get_os_version()
{
	char *os = f_malloc(sizeof(char) * 256);
	olden = sizeof(version);
	f_sysctlbyname("kern.version", &version, &olden, NULL, 0);
	f_strcpy(os, version);
	return os;
}
//PS5 Version by SISTRo
uint32_t get_ps4_sdk_version()
{
    olden = sizeof(ps4_sdk_version);
    f_sysctlbyname("kern.sdk_version", (char *)&ps4_sdk_version, &olden, NULL, 0);
    return ps4_sdk_version;
}
uint32_t get_kernel_version()
{
    olden = sizeof(sdk_version);
    f_sysctlbyname("kern.sdk_version", (char *)&sdk_version, &olden, NULL, 0);
    return sdk_version;
}
uint32_t get_upd_version()
{
 olden = sizeof(upd_version);
    f_sysctlbyname("machdep.upd_version", (char *)&upd_version, &olden, NULL, 0);
    return upd_version;
}