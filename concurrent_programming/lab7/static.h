#define BUFLEN 80
#define PORT 9950

#define OPENR 1
#define READ 2
#define CLOSE 3
#define OPENW 4
#define WRITE 5
#define OPEN_DIR 6
#define READ_DIR 7
#define CLOSE_DIR 8

#define SRV_IP "127.0.0.1"

typedef struct {
  int typ;
  int ile;
  int fd;
  char buf[BUFLEN];
} msgt;
