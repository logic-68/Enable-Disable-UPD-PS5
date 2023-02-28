#ifndef USB_H
#define USB_H

#include <utils.h>
char usb_mount_path[64];

char *get_usb_path();
void usb_disk_required();
#endif