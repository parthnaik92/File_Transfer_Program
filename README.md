File_Transfer_Program
=====================

File transfer program using client server model for linux

This program is an example of client server programming.
In this program, when the client connects to the server, the server sends a file list.
The client can download any file from the list by just typing the file name.
The full program contains the following files.

Server Side:
1.FileServer.c
2.makelist.sh

Client Side:
1.FileClient.c
2.filelist.sh

Note:
On the server side, the file makelist.sh should be in the same directory as FileServer.c
On the client side, the file filelist.sh should be in the same directory as FileClient.c
Please change the file path in the following accordingly.
1.FileServer.c(line 24)
2.FileClient.c(line 78)
3.filelist.sh(line 1 and 2)
You will need to change the permissions of the downloaded file as linux protects acoount from unknown files over LAN.


