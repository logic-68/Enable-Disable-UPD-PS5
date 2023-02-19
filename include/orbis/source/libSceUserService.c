#include <utils.h>

int memset_s(void *s, rsize_t smax, int c, rsize_t n)
{
    int violation = (s == NULL) || (smax > SIZE_MAX) || (n > SIZE_MAX) || (n > smax);
    if (violation)
    {
        if ((s != NULL) && !(smax > SIZE_MAX))
        {
            for (rsize_t i = 0; i < smax; ++i)
            {
                ((volatile unsigned char *)s)[i] = c;
            }
        }
        return 1;
    }
    else
    {
        for (rsize_t i = 0; i < n; ++i)
        {
            ((volatile unsigned char *)s)[i] = c;
        }
        return 0;
    }
}
int getUserIDList(SceUserServiceLoginUserIdList *userIdList)
{
    if (f_sceUserServiceInitialize(NULL) == 0)
    {
        if (f_sceUserServiceGetLoginUserIdList(userIdList) == 0)
        {
            f_sceUserServiceTerminate();
            return 0;
        }
    }
    return -1;
}
char *getUserName(int32_t userId)
{
    char *retval = f_malloc(SCE_USER_SERVICE_MAX_USER_NAME_LENGTH + 1);
    if (retval == NULL)
    {
        return NULL;
    }
    if (f_sceUserServiceInitialize(0) == 0)
    {
        char username[SCE_USER_SERVICE_MAX_USER_NAME_LENGTH + 1];
        if (f_sceUserServiceGetUserName(userId, username, sizeof(username)) == 0)
        {
            f_strcpy(retval, username);
            f_sceUserServiceTerminate();
            return retval;
        }
    }
    f_free(retval);
    return NULL;
}
void get_User_Name(char **userName, int32_t *userId)
{
    SceUserServiceLoginUserIdList userIdList;
	memset_s(&userIdList, sizeof(SceUserServiceLoginUserIdList), 0, sizeof(SceUserServiceLoginUserIdList));
    if (getUserIDList(&userIdList) == 0)
    {
        for (int i = 0; i < SCE_USER_SERVICE_MAX_LOGIN_USERS; i++)
        {
            if (userIdList.userId[i] != -1 && userIdList.userId[i] != 0)
            {
                (*userId) = userIdList.userId[i];
                (*userName) = getUserName(userIdList.userId[i]);
            }
        }
    }
}