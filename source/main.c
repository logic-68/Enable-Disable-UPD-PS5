#include <resolve.h>

#define PATH_MAX 256
#define VERSION "1.0"

// https://github.com/OSM-Made/PS4-Notify
void printf_notification(const char *fmt, ...)
{
	SceNotificationRequest noti_buffer;

	va_list args;
	va_start(args, fmt);
	f_vsprintf(noti_buffer.message, fmt, args);
	va_end(args);

	noti_buffer.type = 0;
	noti_buffer.unk3 = 0;
	noti_buffer.use_icon_image_uri = 1;
	noti_buffer.target_id = -1;
	f_strcpy(noti_buffer.uri, "cxml://psnotification/tex_icon_system");

	f_sceKernelSendNotificationRequest(0, (SceNotificationRequest *)&noti_buffer, sizeof(noti_buffer), 0);
}
static int file_exists(const char *path)
{
	struct stat s;
	return (f_stat(path, &s) >= 0);
}

int payload_main(struct payload_args *args)
{
	dlsym_t *dlsym = args->dlsym;

	int libKernel = 0x2001;
	char src_path[PATH_MAX] = {0};

	dlsym(libKernel, "sceKernelLoadStartModule", &f_sceKernelLoadStartModule);
	dlsym(libKernel, "sceKernelDebugOutText", &f_sceKernelDebugOutText);
	dlsym(libKernel, "sceKernelSendNotificationRequest", &f_sceKernelSendNotificationRequest);
	dlsym(libKernel, "stat", &f_stat);
	dlsym(libKernel, "rmdir", &f_rmdir);
	dlsym(libKernel, "mkdir", &f_mkdir);
	dlsym(libKernel, "unlink", &f_unlink);

	int libC = f_sceKernelLoadStartModule("libSceLibcInternal.sprx", 0, 0, 0, 0, 0);
	dlsym(libC, "vsprintf", &f_vsprintf);
	dlsym(libC, "snprintf_s", &f_snprintf_s);
	dlsym(libC, "strcpy", &f_strcpy);

	printf_notification("PS5 Blocker Update v %s\nPorted Logic-68 C.S", VERSION);

	snprintf_s(src_path, sizeof(src_path), "/update/PS5UPDATE.PUP", ".temp");

	if (!file_exists(src_path))
	{
		f_unlink("/update/PS5UPDATE.PUP.temp");
		f_rmdir("/update/PS5UPDATE.PUP.temp");
		f_mkdir("/update/PS5UPDATE.PUP.temp", 777);

		f_unlink("/update/eula.xml");
		f_rmdir("/update/eula.xml");

		f_unlink("/update/PS5UPDATE.PUP");
		f_rmdir("/update/PS5UPDATE.PUP");
		f_mkdir("/update/PS5UPDATE.PUP", 777);

		printf_notification("Blocker enable\nRelaunch the payload to disable the blocker");
	}
	else
	{
		f_unlink("/update/PS5UPDATE.PUP.temp");
		f_rmdir("/update/PS5UPDATE.PUP.temp");

		f_unlink("/update/PS5UPDATE.PUP");
		f_rmdir("/update/PS5UPDATE.PUP");

		printf_notification("Warning! Blocker desable\nRelaunch the payload to enable the blocker");
	}
	return 0;
}
