#include <libPS4/usb.h>

char *get_usb_path()
{
    char *retval = f_malloc(sizeof(char) * 10);
    char tmppath[64];
    char tmpusb[64];
    tmpusb[0] = '\0';
    for (int x = 0; x <= 7; x++)
    {
        f_sprintf(tmppath, "/mnt/usb%i/.probe", x);
        touch_file(tmppath);
        if (file_exists(tmppath))
        {
            f_unlink(tmppath);
            f_sprintf(tmpusb, "/mnt/usb%i", x);
            f_strcpy(retval, tmpusb);
            return retval;
        }
        tmpusb[0] = '\0';
    }
    return NULL;
}
void usb_disk_required()
{
    char *usb_mnt_path = get_usb_path();
    if (usb_mnt_path == NULL)
    {
        do
        {
            printf_notification("%s", "Please connect your usb media device");
            f_sceKernelSleep(7);
            usb_mnt_path = get_usb_path();
        } while (usb_mnt_path == NULL);
    }
    f_sprintf(usb_mount_path, "%s", usb_mnt_path);
    f_free(usb_mnt_path);
}