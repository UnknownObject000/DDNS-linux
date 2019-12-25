English | [简体中文](./README-CN.md)

# DDNS-linux 
This is a DDNS program written in C++.It can change **Aliyun** domain record automatically,IPv4 and IPv6 are both supported.

## Build
To bulid this program,you need:
  - GCC 6.0.0 or newer (with c++11 support)
  - ***core*** and ***alidns*** module of <a href="https://github.com/aliyun/aliyun-openapi-cpp-sdk">Aliyun-openapi-cpp-sdk</a>
  - libcurl installed.(should be installed when you bulid aliyun-openapi-cpp-sdk)

Bulid Step:
  1. Clone code to your device by execuing following command.
  ```bash
    git clone https://github.com/UnknownObject000/DDNS-linux.git
  ```
  2. Build and install.
  ```bash
    cd DDNS-linux
    c++ -std=c++11 -o DDNS main.cpp -lalibabacloud-sdk-core -l alibabacloud-sdk-alidns -lcurl
    cp ./DDNS /usr/bin/
  ```
  3. Write Config
  
   **config.uson**
    
   config.uson recored your accesskey info and file path info,it must be putted in the same directory of main program. (the default is /usr/bin)
    
   You can see the 'config.uson' in source code to fill it with your data.('<' and '>' should not included)
    
   **dns.uson**
    
   dns.uson recorded your domain/dns record info.You can tell the program where it is by editing 'config.uson'.
   
   You can see the 'dns.uson' in source code to fill it with your data.('<' and '>' should not included).Make sure that all domains in that file is belong to one account.If you have only one domain,you must set the 'DOMAIN_COUNT to 1 and all '<no.>' to 1.If you had more than one domain,set this from 1 to n.
   
   **log**
   
   The name of a log file can be whatever you want.What you just need to make sure is the directory that store log file exist and needn't to create a log file by yourself.The program will do that for you.
   
  4. Execute the following command to finish.
  ```base
    mv ./config.uson /usr/bin/
  ```
 
 ## Useage
  To use start this DDNS service by execiting:
  ```bash
    DDNS
  ```
  If you want to run it at background,executing:
  ```bash
   DDNS > /dev/null 2>&1 &
  ```
