#include <libPS4/file.h>

int fgetc_pointer(int fp)
{
  char c;
  if (f_read(fp, &c, 1) == 0)
  {
    return (-1);
  }
  return (c);
}
int file_exists(char *fname)
{
  int file = f_open(fname, O_RDONLY, 0);
  if (file != -1)
  {
    f_close(file);
    return 1;
  }
  return 0;
}

int dir_exists(char *dname)
{
  DIR *dir = f_opendir(dname);
  if (dir)
  {
    f_closedir(dir);
    return 1;
  }
  return 0;
}

void touch_file(char *destfile)
{
  int fd = f_open(destfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if (fd != -1)
  {
    f_close(fd);
  }
}

void copy_file(char *sourcefile, char *destfile)
{
  int src = f_open(sourcefile, O_RDONLY, 0);
  if (src != -1)
  {
    int out = f_open(destfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (out != -1)
    {
      char *buffer = f_malloc(4194304);
      if (buffer != NULL)
      {
        size_t bytes;
        while ((bytes = f_read(src, buffer, 4194304)) > 0)
        {
          f_write(out, buffer, bytes);
        }
        f_free(buffer);
      }
      f_close(out);
    }
    f_close(src);
  }
}

void copy_dir(char *sourcedir, char *destdir)
{
  DIR *dir = f_opendir(sourcedir);
  struct dirent *dp;
  struct stat info;
  char src_path[1024];
  char dst_path[1024];

  if (!dir)
  {
    return;
  }
  f_mkdir(destdir, 0777);
  while ((dp = f_readdir(dir)) != NULL)
  {
    if (!f_strcmp(dp->d_name, ".") || !f_strcmp(dp->d_name, ".."))
    {
      continue;
    }
    else
    {
      f_sprintf(src_path, "%s/%s", sourcedir, dp->d_name);
      f_sprintf(dst_path, "%s/%s", destdir, dp->d_name);

      if (!f_stat(src_path, &info))
      {
        if (S_ISDIR(info.st_mode))
        {
          copy_dir(src_path, dst_path);
        }
        else if (S_ISREG(info.st_mode))
        {
          copy_file(src_path, dst_path);
        }
      }
    }
  }
  f_closedir(dir);
}

int file_compare(char *fname1, char *fname2)
{
  int res = 0;
  int file1 = f_open(fname1, O_RDONLY, 0);
  int file2 = f_open(fname2, O_RDONLY, 0);
  char *buffer1 = f_malloc(65536);
  char *buffer2 = f_malloc(65536);

  if (file1 && file2 && buffer1 != NULL && buffer2 != NULL)
  {
    f_lseek(file1, 0, SEEK_END);
    f_lseek(file2, 0, SEEK_END);
    long size1 = f_lseek(file1, 0, SEEK_CUR);
    long size2 = f_lseek(file2, 0, SEEK_CUR);
    f_lseek(file1, 0L, SEEK_SET);
    f_lseek(file2, 0L, SEEK_SET);
    if (size1 == size2)
    {
      int lastBytes = 100;
      if (size1 < lastBytes)
      {
        lastBytes = size1;
      }
      f_lseek(file1, -lastBytes, SEEK_END);
      f_lseek(file2, -lastBytes, SEEK_END);
      int bytesRead1 = f_read(file1, buffer1, sizeof(char));
      int bytesRead2 = f_read(file2, buffer2, sizeof(char));
      if (bytesRead1 > 0 && bytesRead1 == bytesRead2)
      {
        res = 1;
        for (int i = 0; i < bytesRead1; i++)
        {
          if (buffer1[i] != buffer2[i])
          {
            res = 0;
            break;
          }
        }
      }
    }
  }
  f_free(buffer1);
  f_free(buffer2);
  f_close(file1);
  f_close(file2);
  return res;
}

int erase_folder(char *dest_path)
{
  DIR *dir = f_opendir(dest_path);
  struct dirent *dp;
  struct stat info;
  char src_file[1024];
  if (dir)
  {
    while ((dp = f_readdir(dir)) != NULL)
    {
      if (!f_strcmp(dp->d_name, ".") || !f_strcmp(dp->d_name, ".."))
        continue;
      else
      {
        f_sprintf(src_file, "%s/%s", dest_path, dp->d_name);
        if (!f_stat(src_file, &info))
        {
          if (S_ISDIR(info.st_mode))
            erase_folder(src_file);
          else if (S_ISREG(info.st_mode))
            f_unlink(src_file);
        }
      }
    }
  }
  f_closedir(dir);
  f_rmdir(dest_path);
  if (!dir_exists(dest_path))
    return 1;
  else
    return 0;
}
int dir_is_not_empty(char *dest_path)
{
  DIR *dir = f_opendir(dest_path);
  struct dirent *dp;
  struct stat info;
  char src_file[1024];
  int empty = 0;
  if (dir)
  {
    while ((dp = f_readdir(dir)) != NULL)
    {
      if (!f_strcmp(dp->d_name, ".") || !f_strcmp(dp->d_name, ".."))
        continue;
      else
      {
        f_sprintf(src_file, "%s/%s", dest_path, dp->d_name);
        if (!f_stat(src_file, &info))
        {
          if (S_ISDIR(info.st_mode))
          {
            empty = 1;
            break;
          }

          else if (S_ISREG(info.st_mode))
          {
            empty = 1;
            break;
          }
        }
      }
    }
  }
  f_closedir(dir);
  return empty;
}
char *reading_param(char *init_file_path, char *param)
{
  FILE *cfile;
  cfile = f_fopen(init_file_path, "rb");
  char *idata = f_malloc(sizeof(char) * 128);

  while (!f_feof(cfile))
  {
    f_fgets(idata, 128, cfile);
    if (f_strstr(idata, param) != NULL)
    {
      int bcnt = 0;
      char **buf = NULL;
      bcnt = split_string(idata, '=', &buf);
      split_string(buf[bcnt - 1], '\n', &buf);
      f_free(idata);
      f_fclose(cfile);
      return buf[0];
    }
  }
  return NULL;
}