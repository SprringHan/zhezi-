# 🎮 C++ EasyX ZHEZI之路

![C++](https://img.shields.io/badge/Language-C++-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![Library](https://img.shields.io/badge/Library-EasyX-orange)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio-purple)

这是一个基于 **C++** 和 **EasyX 图形库** 开发的 2D 策略/塔防类游戏。项目包含完整的场景管理（菜单、游戏、升级）、动画渲染系统以及基于网格的游戏交互逻辑。

## ✨ 功能特性

* **多场景切换**：实现了 `MenuScene`（菜单）、`GameScene`（游戏）、`UpgradeScene`（结束）的平滑切换。
* **网格交互系统**：基于 10x10 网格的放置与判定系统，支持鼠标交互。
* **动画系统**：使用图集（Atlas）加载与帧动画播放，支持角色朝向翻转。
* **摄像机机制**：包含 `Camera` 类，支持游戏视野的控制。
* **流畅的帧率控制**：内置稳定的 60 FPS 帧率控制逻辑。

## 🛠️ 开发环境

* **操作系统**: Windows (EasyX 仅支持 Windows)
* **IDE**: Visual Studio 2019 / 2022
* **图形库**: [EasyX](https://easyx.cn/) (必须安装)

## 🚀 如何构建与运行

1.  **安装 Visual Studio**：确保安装了 "使用 C++ 的桌面开发" 工作负载。
2.  **安装 EasyX**：
    * 访问 [EasyX 官网](https://easyx.cn/) 下载安装程序。
    * 运行安装程序，将其配置到你的 Visual Studio 版本中。
3.  **克隆仓库**：
    ```bash
    git clone [https://github.com/你的用户名/你的仓库名.git](https://github.com/你的用户名/你的仓库名.git)
    ```
4.  **打开项目**：
    * 双击项目目录下的 `.sln` 文件打开解决方案。
5.  **配置资源**：
    * **重要**：请确保项目根目录下有一个 `resources` 文件夹，并且包含所有图片 (`.png`, `.jpg`) 和字体文件 (`IPix.ttf`)。代码中使用了相对路径 `./resources/` 读取资源。
6.  **编译运行**：
    * 按 `F5` 或点击 "本地 Windows 调试器" 即可运行。

## 📂 目录结构说明

```text
.
├── main.cpp           # 程序入口，包含主循环和资源加载
├── SceneManager.h     # 场景管理器
├── MenuScene.h        # 菜单场景
├── GameScene.h        # 核心游戏场景
├── UpgradeScene.h     # 升级/商店场景
├── Block.h            # 地图网格类
├── Atlas.h            # 动画图集处理
├── util.h             # 工具函数
└── resources/         # [必须] 存放图片和字体资源
    ├── IPix.ttf
    ├── menu_background.png
    ├── game_background.png
    └── ... (其他角色动画资源)
