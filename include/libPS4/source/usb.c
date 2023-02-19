#include <libPS4/usb.h>

char *getusbpath()
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
