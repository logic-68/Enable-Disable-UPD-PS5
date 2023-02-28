#include <libPS5/enableDisableUpd.h>


int start_service()
{
    copy_dir(BLOCKER_INTERNAL, DEST_UPDATE);
    if (dir_is_not_empty(DEST_UPDATE)) return 1;
    return 0;
}
int stop_service()
{
    erase_folder(DEST_UPDATE);
    if (!dir_is_not_empty(DEST_UPDATE)) return 1;
    return 0;
}
int is_run()
{
    if (if_pup() && is_fake()) return 1;
    return 0;
}
int is_sav_internal()
{
    if (file_exists(UPDATEMODE_INTERNAL)) return 1;
    return 0;
}
int if_pup()
{
    if (file_exists(IS_PUP)) return 1;
    return 0;
}
int is_fake()
{
    char tmpfile[64];
    f_sprintf(tmpfile, "%s/%s", IS_PUP, ".probe");
    touch_file(tmpfile);
    if (file_exists(tmpfile))
    {
        f_unlink(tmpfile);
        return 1;
    }
    return 0;
}
int install_update()
{
    char sourcedir[1024];
    f_mkdir(BLOCKER_INTERNAL, 0777);
    f_sprintf(sourcedir, "%s/%s/%s", usb_mount_path, SRC_UPDATES, firmware);
    copy_dir(sourcedir, BLOCKER_INTERNAL);
    copy_dir(sourcedir, DEST_UPDATE);
    if (dir_is_not_empty(DEST_UPDATE) && dir_is_not_empty(BLOCKER_INTERNAL)) return 1;
    return 0;
}
int cleaner()
{
    //Remove old version
    if(dir_exists("/user/data/blocker")) erase_folder("/user/data/blocker");
    if (dir_is_not_empty(DEST_UPDATE))
        erase_folder(DEST_UPDATE);
    if (dir_exists(BLOCKER_INTERNAL)){
        if (dir_is_not_empty(BLOCKER_INTERNAL))
            erase_folder(BLOCKER_INTERNAL);
    } 
    if (!dir_is_not_empty(DEST_UPDATE) && !dir_exists(BLOCKER_INTERNAL)) return 1; 
    return 0;
}