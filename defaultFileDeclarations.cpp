#include <fcntl.h>
#include <unistd.h>

#define INTSIZE sizeof(int)

int main()
{
        int indexfile = open("indexes", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
        int dbfile = open("DBfile", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
        int allocatorfile = open("AllocTableFile", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

        int num1 = 1;
        int num0 = 0;
        int num8 = 8;
        char chra = 'a';

        char num1chr = 1;
        short num1shr = 1;

        /// setting indexfile
        write(indexfile,&num1, INTSIZE);

        lseek(indexfile, INTSIZE, SEEK_SET);
        write(indexfile, &num1, INTSIZE);

        lseek(indexfile, 2 * INTSIZE, SEEK_SET);
        write(indexfile, &num0, INTSIZE);

        lseek(indexfile, 3 * INTSIZE, SEEK_SET);
        write(indexfile, &num8, INTSIZE);

        /// setting dbfile
        write(dbfile, &num1chr, sizeof(char));

        lseek(dbfile, sizeof(char), SEEK_SET);
        write(dbfile, &num1shr, sizeof(short));

        lseek(dbfile, sizeof(char) + sizeof(short), SEEK_SET);
        write(dbfile, &chra, sizeof(char));

        lseek(dbfile, 2 * sizeof(char) + sizeof(short), SEEK_SET);
        write(dbfile, &num0, sizeof(int));

        ///setting allocfile

        int tenmb = 10485760;
        int tenmbscazut = tenmb - 1;

        lseek(allocatorfile,0,SEEK_SET);
        write(allocatorfile, &num1, sizeof(int));

        lseek(allocatorfile,sizeof(int),SEEK_SET);
        write(allocatorfile, &tenmb, sizeof(int));

        lseek(allocatorfile,sizeof(int)*2,SEEK_SET);
        write(allocatorfile, &num8, sizeof(int));

        lseek(allocatorfile,sizeof(int)*3,SEEK_SET);
        write(allocatorfile, &tenmbscazut, sizeof(int));

        close(allocatorfile);
        close(dbfile);
        close(indexfile);
        return 0;
}
