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

    /* NOTE: For the sake of brevity, any error checking has been omitted from
     *       this program, but we really should be checking the results of
     *       every system call and calling "perror" as appropriate. */
    chdir(argv[1]);

    /* NOTE: Every process has a "current working directory", relative to which
     *       file paths are interpreted. By changing into the directory we were
     *       given, we avoid needing to compute paths to its files. */
    dir = opendir(".");

    /* NOTE: Just like reading from an ordinary file, the second time we read
     *       from a directory, we pick up where we left off with the second
     *       filename-to-inode mapping; note this overwrites the first, and
     *       that the entries are in no particular order. */
    while((entry = readdir(dir)) != NULL) {
        /* NOTE: A directory maps filenames to inodes, and only a filename and
         *       an inode number are guaranteed to be in each entry. Any
         *       additional information must be queried with "stat". */
        stat(entry->d_name, &buf);

        printf("%s -> %ld (%ld bytes in %ld blocks)\n",
               entry->d_name, (long)(entry->d_ino),
               (long)(buf.st_size), (long)(buf.st_blocks));
    }

    closedir(dir);

    return EXIT_SUCCESS;
}
