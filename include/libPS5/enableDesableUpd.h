#ifndef ENABLEDESABLEUPD_H
#define ENABLEDESABLEUPD_H
#include <utils.h>

#define INIT_FILE "fw.ini"     // USB DRIVE
#define SRC_UPDATES "/updates" // USB DRIVE
#define DEST_UPDATE "/update"
#define IS_ORIGINAL_PUP "/update/PS5UPDATE.PUP"
#define BLOCKER_INTERNAL "/user/data/blocker"
int if_pup_exist();
int is_fake_pup();
int is_update_blocked();
int is_sav_blocker_internal();
char *convert_firmware(char *sdk_version);
#endif
