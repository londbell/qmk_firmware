# UF2 LD固件转换

参考这个教程：<https://www.zfrontier.com/app/flow/eMzZjJZRgP6z> ，可以实现qmk构建产生UF2构建。

前提是：
1.APM32F103CBT6已经通过STLINK刷写过UF2-STM32F103 bootloader，否则无法通过USB磁盘方式复写UF2固件。
2.这个作者提供了两个ld文件来转换固件，而不是用QMK官方的UF2 bootloader转换方案，实际上经过测试，可以直接用QMK的UF2生成方案。
3.所以两个ld已经过时，存储ld文件作为记录。