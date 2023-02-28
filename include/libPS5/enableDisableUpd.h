#ifndef ENABLEDISABLEUPD_H
#define ENABLEDISABLEUPD_H
#include <utils.h>

#define UPDATEMODE_INTERNAL "/user/data/Enable-Disable-UPD-PS5/updatemode.elf"
#define BLOCKER_INTERNAL "/user/data/Enable-Disable-UPD-PS5"
#define IS_PUP "/update/PS5UPDATE.PUP"
#define SRC_UPDATES "updates" // USB DRIVE
#define DEST_UPDATE "/update"

int start_service();
int stop_service();
int is_run();
int is_sav_internal();
int if_pup();
int is_fake();
int install_update();
int cleaner();

#endif
