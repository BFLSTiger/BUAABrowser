# 北航浏览器（公共版）

北航浏览器（公共版）是一款基于Qt开发的浏览器。

该浏览器已停止维护，公共版本可供任何人进行使用，同时也删去了不消耗校园网流量的特性。

如果喜欢的话可以Star该项目。

## 下载和安装

### 下载地址

https://github.com/BFLSTiger/BUAABrowser/releases

### 安装

下载BUAABrowserSetup.exe后点击安装即可。如果无法打开浏览器，请在安装目录下点击运行`vc_redist.x64.exe`后再次尝试。

如果是进行版本更新，请先卸载旧版本浏览器后再安装新版浏览器。

## 使用方法

公共版浏览器打开即可使用。

需要注意的是，该浏览器地址栏位置**仅支持输入网址**，如果仅进行搜索请使用主页中的搜索栏，当前主页搜索栏使用的搜索引擎为百度搜索。

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