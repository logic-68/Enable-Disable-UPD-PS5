#include <utils.h>

#define VERSION "1.0.3"
#define NAME_APP "ENABLE-DISABLE-UPD-PS5"
#define DEBUG_SOCKET
#define DEBUG_ADDR IP(192, 168, 1, 155);
#define DEBUG_PORT 5655

int sock;

int payload_main(struct payload_args *args)
{
	dlsym_t *dlsym = args->dlsym;

	int libKernel = 0x2001;

	dlsym(libKernel, "sceKernelSleep", &f_sceKernelSleep);
	dlsym(libKernel, "sceKernelLoadStartModule", &f_sceKernelLoadStartModule);
	dlsym(libKernel, "sceKernelDebugOutText", &f_sceKernelDebugOutText);
	dlsym(libKernel, "sceKernelSendNotificationRequest", &f_sceKernelSendNotificationRequest);
	dlsym(libKernel, "sceKernelUsleep", &f_sceKernelUsleep);
	dlsym(libKernel, "scePthreadMutexLock", &f_scePthreadMutexLock);
	dlsym(libKernel, "scePthreadMutexUnlock", &f_scePthreadMutexUnlock);
	dlsym(libKernel, "scePthreadExit", &f_scePthreadExit);
	dlsym(libKernel, "scePthreadMutexInit", &f_scePthreadMutexInit);
	dlsym(libKernel, "scePthreadCreate", &f_scePthreadCreate);
	dlsym(libKernel, "scePthreadMutexDestroy", &f_scePthreadMutexDestroy);
	dlsym(libKernel, "scePthreadJoin", &f_scePthreadJoin);
	dlsym(libKernel, "sceKernelGetFsSandboxRandomWord", &f_sceKernelGetFsSandboxRandomWord);
	dlsym(libKernel, "sysctlbyname", &f_sysctlbyname);
	dlsym(libKernel, "socket", &f_socket);
	dlsym(libKernel, "bind", &f_bind);
	dlsym(libKernel, "listen", &f_listen);
	dlsym(libKernel, "accept", &f_accept);
	dlsym(libKernel, "open", &f_open);
	dlsym(libKernel, "read", &f_read);
	dlsym(libKernel, "write", &f_write);
	dlsym(libKernel, "close", &f_close);
	dlsym(libKernel, "stat", &f_stat);
	dlsym(libKernel, "fstat", &f_fstat);
	dlsym(libKernel, "rename", &f_rename);
	dlsym(libKernel, "rmdir", &f_rmdir);
	dlsym(libKernel, "mkdir", &f_mkdir);
	dlsym(libKernel, "getdents", &f_getdents);
	dlsym(libKernel, "unlink", &f_unlink);
	dlsym(libKernel, "readlink", &f_readlink);
	dlsym(libKernel, "lseek", &f_lseek);
	dlsym(libKernel, "puts", &f_puts);
	dlsym(libKernel, "mmap", &f_mmap);
	dlsym(libKernel, "munmap", &f_munmap);
	dlsym(libKernel, "sceKernelReboot", &f_sceKernelReboot);

	int libNet = f_sceKernelLoadStartModule("libSceNet.sprx", 0, 0, 0, 0, 0);
	dlsym(libNet, "sceNetSocket", &f_sceNetSocket);
	dlsym(libNet, "sceNetConnect", &f_sceNetConnect);
	dlsym(libNet, "sceNetHtons", &f_sceNetHtons);
	dlsym(libNet, "sceNetAccept", &f_sceNetAccept);
	dlsym(libNet, "sceNetSend", &f_sceNetSend);
	dlsym(libNet, "sceNetInetNtop", &f_sceNetInetNtop);
	dlsym(libNet, "sceNetSocketAbort", &f_sceNetSocketAbort);
	dlsym(libNet, "sceNetBind", &f_sceNetBind);
	dlsym(libNet, "sceNetListen", &f_sceNetListen);
	dlsym(libNet, "sceNetSocketClose", &f_sceNetSocketClose);
	dlsym(libNet, "sceNetHtonl", &f_sceNetHtonl);
	dlsym(libNet, "sceNetInetPton", &f_sceNetInetPton);
	dlsym(libNet, "sceNetGetsockname", &f_sceNetGetsockname);
	dlsym(libNet, "sceNetRecv", &f_sceNetRecv);
	dlsym(libNet, "sceNetErrnoLoc", &f_sceNetErrnoLoc);
	dlsym(libNet, "sceNetSetsockopt", &f_sceNetSetsockopt);

	int libC = f_sceKernelLoadStartModule("libSceLibcInternal.sprx", 0, 0, 0, 0, 0);
	dlsym(libC, "vsprintf", &f_vsprintf);
	dlsym(libC, "memset", &f_memset);
	dlsym(libC, "sprintf", &f_sprintf);
	dlsym(libC, "snprintf", &f_snprintf);
	dlsym(libC, "snprintf_s", &f_snprintf_s);
	dlsym(libC, "strcat", &f_strcat);
	dlsym(libC, "free", &f_free);
	dlsym(libC, "memcpy", &f_memcpy);
	dlsym(libC, "strcpy", &f_strcpy);
	dlsym(libC, "strncpy", &f_strncpy);
	dlsym(libC, "sscanf", &f_sscanf);
	dlsym(libC, "scanf", &f_scanf);
	dlsym(libC, "scanf", &f_scanf);
	dlsym(libC, "malloc", &f_malloc);
	dlsym(libC, "calloc", &f_calloc);
	dlsym(libC, "strlen", &f_strlen);
	dlsym(libC, "strcmp", &f_strcmp);
	dlsym(libC, "strchr", &f_strchr);
	dlsym(libC, "strrchr", &f_strrchr);
	dlsym(libC, "gmtime_s", &f_gmtime_s);
	dlsym(libC, "time", &f_time);
	dlsym(libC, "localtime", &f_localtime);
	dlsym(libC, "closedir", &f_closedir);
	dlsym(libC, "opendir", &f_opendir);
	dlsym(libC, "readdir", &f_readdir);
	dlsym(libC, "fclose", &f_fclose);
	dlsym(libC, "fopen", &f_fopen);
	dlsym(libC, "strstr", &f_strstr);
	dlsym(libC, "fseek", &f_fseek);
	dlsym(libC, "ftell", &f_ftell);
	dlsym(libC, "fread", &f_fread);
	dlsym(libC, "usleep", &f_usleep);
	dlsym(libC, "fputs", &f_fputs);
	dlsym(libC, "fgetc", &f_fgetc);
	dlsym(libC, "fgets", &f_fgets);
	dlsym(libC, "feof", &f_feof);
	dlsym(libC, "fprintf", &f_fprintf);
	dlsym(libC, "realloc", &f_realloc);
	dlsym(libC, "seekdir", &f_seekdir);
	dlsym(libC, "strtok", &f_strtok);
	dlsym(libC, "strtol", &f_strtol);
	dlsym(libC, "atoi", &f_atoi);
	dlsym(libC, "isspace", &f_isspace);
	dlsym(libC, "ferror", &f_ferror);

	int libNetCtl = f_sceKernelLoadStartModule("libSceNetCtl.sprx", 0, 0, 0, 0, 0);
	dlsym(libNetCtl, "sceNetCtlInit", &f_sceNetCtlInit);
	dlsym(libNetCtl, "sceNetCtlTerm", &f_sceNetCtlTerm);
	dlsym(libNetCtl, "sceNetCtlGetInfo", &f_sceNetCtlGetInfo);

	int libSysModule = f_sceKernelLoadStartModule("libSceSysmodule.sprx", 0, 0, 0, 0, 0);
	dlsym(libSysModule, "sceSysmoduleLoadModuleInternal", &f_sceSysmoduleLoadModuleInternal);
	dlsym(libSysModule, "sceSysmoduleUnloadModuleInternal", &f_sceSysmoduleUnloadModuleInternal);

	int sysModule = f_sceSysmoduleLoadModuleInternal(SCE_SYSMODULE_INTERNAL_USER_SERVICE);

	int libUserService = f_sceKernelLoadStartModule("libSceUserService.sprx", 0, 0, 0, 0, 0);
	dlsym(libUserService, "sceUserServiceInitialize", &f_sceUserServiceInitialize);
	dlsym(libUserService, "sceUserServiceGetInitialUser", &f_sceUserServiceGetInitialUser);
	dlsym(libUserService, "sceUserServiceGetLoginUserIdList", &f_sceUserServiceGetLoginUserIdList);
	dlsym(libUserService, "sceUserServiceGetUserName", &f_sceUserServiceGetUserName);
	dlsym(libUserService, "sceUserServiceTerminate", &f_sceUserServiceTerminate);

	struct sockaddr_in server;
	server.sin_len = sizeof(server);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = DEBUG_ADDR;
	server.sin_port = f_sceNetHtons(DEBUG_PORT);
	f_memset(server.sin_zero, 0, sizeof(server.sin_zero));
	sock = f_sceNetSocket("debug", AF_INET, SOCK_STREAM, 0);
	f_sceNetConnect(sock, (struct sockaddr *)&server, sizeof(server));

	char *userName;
	int32_t userId;

	char *fw = get_firmware();
	f_strcpy(firmware, fw);
	f_free(fw);

	// personalized greetings
	if (sysModule == 0)
	{
		get_User_Name(&userName, &userId);
		printf_notification("Welcome %s to:\n%s V%s\n\nBy ★@Logic-68★", userName, NAME_APP, VERSION);
		f_sceKernelSleep(7);
	}
	sysModule = f_sceSysmoduleUnloadModuleInternal(SCE_SYSMODULE_INTERNAL_USER_SERVICE);

	if (!is_sav_internal())
	{
		if (dir_is_not_empty(DEST_UPDATE))
		{
			if (if_pup() && !is_fake())
				printf_notification("Warning!!!\nPS5UPDATE.PUP found\nDeleting...");	
			else if (if_pup() && is_fake())
				printf_notification("Warning!!!\nBlocker internal files not found.\nReinstallation required");
			f_sceKernelSleep(7);
		}
		printf_notification("Installation blocker Fw:%s\nIn progress please wait...", firmware);
		f_sceKernelSleep(7);
	}
	else
	{
		char *usb_mnt_path = get_usb_path();
		if (usb_mnt_path != NULL)
			printf_notification("USB drive found. Update Fw:%s\nIn progress please wait...", firmware);
		else
		{
			if (is_run())
			{
				printf_notification("Stop blocker services...");
				f_sceKernelSleep(7);
				if (stop_service())
					printf_notification("Warning!!!\nPlease note your blocker is DISABLE");
			}
			else
			{
				if (if_pup() && !is_fake())
				{
					printf_notification("Warning!!!\nPS5UPDATE.PUP found\nDeleting...");
					f_sceKernelSleep(7);
					erase_folder(DEST_UPDATE);
				}		
				printf_notification("Enabling blocker services...");
				f_sceKernelSleep(7);
				if (start_service())
					printf_notification("Succesfully!!!\nPlease note your blocker is ENABLE");
			}
			return 0;
		}
		f_sceKernelSleep(7);
	}
	usb_disk_required();
	if (cleaner())
	{
		if (install_update())
			printf_notification("Succesfully!!!\nPlease note your blocker is ENABLE\n");
	}
	return 0;
}