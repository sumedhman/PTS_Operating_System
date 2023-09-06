// Custom Linux commands
// Implements a custom ls command in C. Covers system calls like stat() to get file metadata.
/*
struct stat {
	dev_t st_dev;
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	off_t st_size;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
	mode_t st_attr;
};

struct passwd {
	char *pw_name;
	char *pw_passwd;
	uid_t pw_uid;
	gid_t pw_gid;
	time_t pw_change;
	char *pw_class;
	char *pw_gecos;
	char *pw_dir;
	char *pw_shell;
	time_t pw_expire;
};

struct group {
	char *gr_name;
	char *gr_passwd;
	gid_t gr_gid;
	char **gr_mem;
};
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat file_stat;
    struct passwd *user_info;
    struct group *group_info;
    char permissions[10] = "----------";
    time_t access_time;
    time_t modification_time;

    for (int i = 1; i < argc; i++) {
        if (lstat(argv[i], &file_stat) < 0) { // lstat() it returns information about the link itself,
            perror(argv[i]);                  //  not the file that the link refers to
            continue;
        }

        // Get user and group information
        user_info = getpwuid(file_stat.st_uid);
        group_info = getgrgid(file_stat.st_gid);

        // Get file type
        switch (file_stat.st_mode & S_IFMT) { // int S_IFMT. This is a bit mask used to extract
            case S_IFREG:                     // the file type code from a mode value.
                permissions[0] = '-';
                break;
            case S_IFDIR:
                permissions[0] = 'd';
                break;
            case S_IFLNK:
                permissions[0] = 'l';
                break;
            case S_IFIFO:
                permissions[0] = 'p';
                break;
            case S_IFCHR:
                permissions[0] = 'c';
                break;
            case S_IFBLK:
                permissions[0] = 'b';
                break;
            case S_IFSOCK:
                permissions[0] = 's';
                break;
        }

        // Get permissions
        if (file_stat.st_mode & S_IRUSR) permissions[1] = 'r';
        if (file_stat.st_mode & S_IWUSR) permissions[2] = 'w';
        if (file_stat.st_mode & S_IXUSR) permissions[3] = 'x';
        if (file_stat.st_mode & S_IRGRP) permissions[4] = 'r';
        if (file_stat.st_mode & S_IWGRP) permissions[5] = 'w';
        if (file_stat.st_mode & S_IXGRP) permissions[6] = 'x';
        if (file_stat.st_mode & S_IROTH) permissions[7] = 'r';
        if (file_stat.st_mode & S_IWOTH) permissions[8] = 'w';
        if (file_stat.st_mode & S_IXOTH) permissions[9] = 'x';

        // Get access and modification times
        access_time = file_stat.st_atime;
        modification_time = file_stat.st_mtime;

        // Print file information
        printf("%s %2ld %s %s %5ld %s %s\n", permissions, file_stat.st_nlink, user_info->pw_name, group_info->gr_name, file_stat.st_size, ctime(&modification_time), argv[i]);
    }

    return 0;
}

/*
toor@LAPTOP-RLTA9ELC:~/system_progs$ gcc 10-myls.c
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./a.out ./5-producer_consumer.c ./a.out
-rw-r--r--  1 toor toor  2053 Sun Aug 27 00:16:35 2023
 ./producer_consumer.c
-rwxr-xr-x  1 toor toor 16224 Sun Aug 27 00:20:11 2023
 ./a.out
*/
