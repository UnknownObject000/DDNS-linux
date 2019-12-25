# DDNS-linux 
This is a DDNS program written in C++.It can change **Aliyun** domain record automatically,IPv4 and IPv6 are both supported.

## Bulid
To bulid this program,you need:
  - GCC 6.0.0 or newer (with c++11 support)
  - ***core*** and ***alidns*** module of <a href="https://github.com/aliyun/aliyun-openapi-cpp-sdk">Aliyun-openapi-cpp-sdk</a>
  - libcurl installed.(should be installed when you bulid aliyun-openapi-cpp-sdk)

Bulid Step:
  1. Clone code to your device by execuing following command.
  ```bash
    git clone https://github.com/UnknownObject000/DDNS-linux.git
  ```
  2. Bulid and install.
  ```bash
    cd DDNS-linux
    c++ -std=c++11 -o DDNS main.cpp -lalibabacloud-sdk-core -l alibabacloud-sdk-alidns -lcurl
    cp ./DDNS /usr/bin/
  ```
  3. Write Config
    **config.uson**
    config.uson recored your accesskey info and file path info,it must be putted in the same directory. (the default is /usr/bin)
    You can see the 'config.uson' in source code to fill it with your data.('<' and '>' should not included)
    **dns.uson**
    dns.uson recorded your domain/dns record info.You can tell the program where it is in 'config.uson'.
