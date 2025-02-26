
# 运动会计分系统

## 题目

### 问题描述

参加运动会有n个学校，学校编号为1~n。比赛分为m个男子项目，和w个女子项目。项目编号为男子1~m，女子m+1~m+w。不同的项目取前五名或前三名积分。取前五名的积分分别为：7、5、3、2、1；取前三名的积分分别为：5、3、2。哪些项目取前五名，哪些项目取前三名可自行设定。（m<=20，n<=20）

### 功能要求

1. 可以输入各个项目的运动员（含前三名或前五名）的比赛成绩（注：比赛成绩指真实成绩，如甲运动员男子百米成绩9″8，而不是指积分。）；
2. 能统计各学校总分；
3. 可以按学校编号或名称、学校总分、男女团体总分排序输出；
4. 可以按学校编号查询学校某个项目的情况；可以按项目编号查询前三名或前五名的学校。
5. 数据存入文件并能随时查询。
6. 规定

- 输入数据形式和范围：可以输入学校名称，运动项目名称。
- 输出形式：有中文提示，各学校分数为整数。
- 界面要求：有合理的提示，每个功能可以设立菜单，根据提示，可以完成相关的功能要求。
- 存储结构：根据系统功能要求进行设计，但是要求运动会的相关数据要存储在文件中。
- 测试数据：使用1、全部合法数据；2、整体非法数据；3、局部非法数据。进行测试，以保证程序的稳定性。

## 简介

本项目用于运动会计分系统的开发，实现对运动会各比赛项目、学校及成绩的录入、查询、修改与统计。系统采用命令行菜单交互，利用链表管理数据，支持数据的保存与校验。

## 功能特性

- 录入、修改和查询比赛项目信息
- 录入、修改和查询学校信息
- 录入及修改比赛成绩并自动计算得分
- 基于 CMake 构建和多模块开发，便于扩展和维护
- 数据校验机制确保数据文件安全性

## 目录结构

- **include/**：项目头文件及公共宏定义
- **src/**：源代码实现，包括核心数据、打印、菜单、文件存取等模块

## 编译与运行

### 环境依赖

- CMake (版本 3.10 及以上)
- MinGW 或其他 C 语言编译器

### 编译步骤

1. 新建构建目录：

   ```bash
   mkdir build
   ```
2. 进入构建目录并配置项目：

   ```bash
   cd build
   cmake ../
   ```

   如使用非默认 Generator，请使用如下命令：

   ```bash
   cmake -G "MinGW Makefiles" ../
   ```
3. 构建项目：

   ```bash
   cmake --build .
   ```
4. 运行程序：
   编译完成后，在 `build/bin` 目录下运行 `Scorecalculation.exe`。

## 数据配置

- **config.h.in**：用于 CMake 配置生成项目所需的 `config.h` 文件
- **data.ini**：数据存储文件，记录学校信息和比赛项目成绩。请注意修改后可能导致数据失效。

## 使用说明

运行程序后，系统将提供命令行菜单：

- 主菜单用于选择信息查询、录入、修改和保存等操作
- 根据提示输入对应选项编号完成操作
- 修改数据后，记得保存以确保数据持久化

## 注意事项

- 修改 `data.ini` 文件可能导致数据校验失败，建议通过程序操作数据
- 程序支持调试模式，在调试模式下会打印额外提示信息，有助于开发和测试

## 版权与许可

本项目代码仅供学习和研究使用，任何商业用途均需经过授权。如需分发，请保留原作者信息及版权声明。
By LeonardoTan
