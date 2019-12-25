[English](./README.md) | 简体中文

# DDNS-linux 
一个C++编写的DDNS程序，可实现**阿里云**域名的动态解析记录修改，同时支持IPv4和IPv6。

## 编译
编译此程序需要以下程序/组件：
  - GCC 6.0.0或以上版本 (支持c++11)
  - <a href="https://github.com/aliyun/aliyun-openapi-cpp-sdk">Aliyun-openapi-cpp-sdk</a>的 ***core*** 和 ***alidns*** 组件
  - 安装了libcurl(在构建aliyun-openapi-cpp-sdk时应已安装)

编译步骤：
  1. 执行以下命令将源代码下载到设备上。
  ```bash
    git clone https://github.com/UnknownObject000/DDNS-linux.git
  ```
  2. 编译并安装。
  ```bash
    cd DDNS-linux
    c++ -std=c++11 -o DDNS main.cpp -lalibabacloud-sdk-core -l alibabacloud-sdk-alidns -lcurl
    cp ./DDNS /usr/bin/
  ```
  3. 编辑配置文件
  
   **config.uson**
    
   config.uson存储了Accesskey信息、dns.uson和日志文件的位置，此文件必须与程序放到同一目录下。 (默认目录是 /usr/bin)
    
   参考源代码中的 'config.uson' 并填写自己的数据。(不包括'<' 和 '>')
    
   **dns.uson**
    
   dns.uson 记录了域名和DNS解析记录信息，它的目录需要填写在 'config.uson' 中。
   
   参考源代码中的 'dns.uson' 并填写自己的数据。(不包括'<' and '>').确保该文件下的所有域名属于同一账户。当你只有一个域名时， 'DOMAIN_COUNT 和所有的 '<no.>' 必须被设置为1.如果你有多个域名，序号为从 1 到 n.
   
   **log**
   
   日志文件的名称是任意的。你只需要确保存储日志文件的文件夹存在而不需要创建日志文件。程序会自动创建它。
   
  4. 执行以下命令完成安装。
  ```base
    mv ./config.uson /usr/bin/
  ```
 
 ## 使用方法
  启动DDNS服务请执行以下命令：
  ```bash
    DDNS
  ```
  如果你需要它在后台运行则执行：
  ```bash
   DDNS > /dev/null 2>&1 &
  ```
