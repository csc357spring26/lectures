#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat buf;

    /* NOTE: Every process has a "current working directory" relative to which
     *       file paths are resolved; by changing our CWD, we will be in the
     *       directory we opened, and we can then use the correspoding entry
     *       filenames without having to construct the path ourselves. */
    chdir(argv[1]);

    /* NOTE: For the sake of brevity, we'll omit any error checking from this
     *       program, but we really should be in the habit of checking the
     *       results of any system calls and printing error messages with
     *       "perror" as needed. */
    dir = opendir(".");

    /* NOTE: Just like reading from an ordinary file, the second time we read
     *       from a directory, we pick up where we left off with the second
     *       filename-to-inode mapping; note this overwrites the first, and
     *       that the entries are in no particular order. */
    while((entry = readdir(dir)) != NULL) {
        /* NOTE: A directory maps filenames to inodes; the only information
         *       that is guaranteed to be in a directory entry is a filename
         *       and the inode to which it is mapped. Any additional
         *       information can then be retrieved with "stat". */
        stat(entry->d_name, &buf);
        printf("%s -> %ld (%ld bytes in %ld blocks)\n",
               entry->d_name, (long)(entry->d_ino),
               (long)(buf.st_size), (long)(buf.st_blocks));
    }

    closedir(dir);

    return EXIT_SUCCESS;
}
