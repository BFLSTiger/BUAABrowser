# 北航浏览器（已停止维护）

北航浏览器是一款基于Qt开发的浏览器，可使北航沙河校区学生**在不消耗校园网流量的情况下**实现基本的浏览网页和下载文件功能。

由于需要北航账号，该浏览器仅限北航学生使用。

在该浏览器停止维护后将会推出`public`版本，删去不消耗校园网流量的特性，使得所有人都可使用该浏览器，欢迎有兴趣的人前来交流指导。

如果喜欢的话可以Star该项目。

## 下载和安装

### 下载地址

https://github.com/BFLSTiger/BUAABrowser/releases

### 安装

下载BUAABrowserSetup.exe后点击安装即可。如果无法打开浏览器，请在安装目录下点击运行`vc_redist.x64.exe`后再次尝试。

如果是进行版本更新，请先卸载旧版本浏览器后再安装新版浏览器。

## 使用方法

在北航沙河校区连接BUAA-WiFi或电脑插入网线的情况下，**不进行上网认证的情况下**使用该浏览器即可，如果已经认证，可进入上网认证页面注销后使用。

需要注意的是，该浏览器地址栏位置**仅支持输入网址**，如果仅进行搜索请使用主页中的搜索栏，当前主页搜索栏使用的搜索引擎为百度搜索。

## 原理介绍

在北航沙河校区，可以在连接校园网但不认证的情况下访问校园内网，而作为内网的VPN1和VPN4可以访问外网，该浏览器就是通过修改网址的方式借由VPN1访问外网，以实现不消耗校园网流量。

需要注意的是，VPN1和VPN4在访问外网时都会出现一定的错误，例如VPN4无法完全加载B站主页，VPN1看B站直播无法调至原画画质，且VPN1会在cookie过多时清空cookie。进行权衡后，本浏览器使用了VPN1。

## 源代码构建

### 构建环境

Windows 10 64-bit, Windows 11

Qt >= 6.2 （根据Qt版本不同，Qt WebEngine使用的Chromium内核会有所不同）

Visual Studio >= 2019 （具体请根据Qt中MSVC套件的需求进行调整）

### 注意事项

由于实现浏览器所需的的Qt WebEngine库仅支持通过MSVC编译，所以请在**Windows平台**使用msvc进行构建。

由于版权原因，官网安装包安装的Qt WebEngine库不带有视频解码功能。如果想要实现视频播放，需要添加`-webengine-proprietary-codecs`参数后重新编译源码。

## LICENSE

基于 [LGPLv3.0](LICENSE)。请在获取源代码后遵循此许可证。
