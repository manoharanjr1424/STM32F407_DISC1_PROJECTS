#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>

#define USB_DEVICE_LOCATION "/dev/ttyUSB0"
#define MAX_CMD_LEN 40
#define START_BYTE         0x81   // Extended ASCII � �
#define STOP_BYTE          0xA5   // Extended ASCII � � (Yen sign)

char start_byte = 0x81;
char stop_byte = 0xA5;

char cmdFromUser[MAX_CMD_LEN];

int main(void) {
    int fd;
    int len;

    fd = open(USB_DEVICE_LOCATION,O_WRONLY);
    if( fd < 0 ) {
        printf("File was not Found\n");
        return -1;
    }

    while(1) {
    printf("[*] IOEXP_PA_PIN00_SET_INPUT\n[*] IOEXP_PA_PIN00_SET_OUTPUT\n[*] IOEXP_PA_PIN00_WRITE_HIGH\n[*] IOEXP_PA_PIN00_WRITE_LOW\n[*] EXIT \n\n Enter the Command to Send : ");
    
    scanf(" %s",cmdFromUser);

    if(!(strcmp(cmdFromUser,"EXIT"))) {
        close(fd);
        printf("File was Closed Successfully \n");
        break;
    }
    len = write(fd,&start_byte,1);
    len = write(fd,cmdFromUser,strlen(cmdFromUser));
    len = write(fd,&stop_byte,1);
    printf("Command Send Successfully \n");
    }
    return 0;
}
