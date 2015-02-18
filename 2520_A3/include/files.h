typedef struct FileInformation{
    char * name;
    char ** path;
    int instances;
    int * isdir;
} FileInfo;

FileInfo * file_info_init(char *, char *, int);

int file_info_compare(void *, void *);
int file_info_sec_compare(void *, void *);
void file_info_print_name(void *);
void file_info_print_path(void *);
void file_info_destroy(void *);
void file_info_coll_res(void *, void *);

char * get_name(FileInfo *);
char ** get_path(FileInfo *);