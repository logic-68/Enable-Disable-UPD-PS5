#include <libPS5/enableDisableUpd.h>
int if_pup_exist()
{
    if (file_exists(IS_ORIGINAL_PUP))
        return 1;
    else
        return 0;
}
int is_fake_pup()
{
    char tmpfile[64];
    f_sprintf(tmpfile, "%s/%s", IS_ORIGINAL_PUP, ".probe");
    touch_file(tmpfile);
    if (file_exists(tmpfile))
    {
        f_unlink(tmpfile);
        return 1;
    }
    return 0;
}
int is_update_blocked()
{
    if (file_exists(IS_ORIGINAL_PUP))
        return 1;
    else
        return 0;
}
int is_sav_blocker_internal()
{
    if (dir_exists(BLOCKER_INTERNAL))
        return 1;
    else
        return 0;
}
char *convert_firmware(char *sdk_version)
{
    char *fw = f_malloc(sizeof(char) * 8);
    int size, i;

    f_strcpy(fw, sdk_version + 1);
    i = size = f_strlen(fw) - 1;
    while (i > size - 1)
    {
        fw[i] = '\0';
        i--;
    }
    return fw;
}
