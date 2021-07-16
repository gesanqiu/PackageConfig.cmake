# 生成自己的PackageConfig.cmake

在[查找已有库](https://app.gitbook.com/@ricardolu/s/trantor/cmake-in-action/cmake-tutorial/cha-zhao-yi-you-ku)中简单介绍了`find_package`指令的原理，其中提到其搜包的的两种方式，对于**Config模式**其需要一个`<package_name>Config.cmake`或`<lower-case-package-name>-config.cmake`配置文件，这篇文章为[官方例子](https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-to-create-a-ProjectConfig.cmake-file)的翻译和修改，它将教你如何为自己的包创建一个`<package_name>Config.cmake`，但阅读这篇文章之前，你需要对`find_package`指令有一个详细的了解。

例子已经上传到我的GitHub仓库：[How to create a PackageConfig.cmake](https://github.com/gesanqiu/PackageConfig.cmake)，欢迎交流。

## 概述

假设项目`packageConfig`包含一个简单的动态库`iniparser`和一个调用这个库的测试用例`test`：

```shell
.
├── iniparser
│   ├── CMakeLists.txt						# 构建iniparser库
│   ├── inc
│   │   ├── dictionary.h
│   │   ├── ini_conf.h
│   │   └── iniparser.h
│   ├── iniparserConfig.cmake
│   ├── iniparserConfigVersion.cmake
│   ├── LICENSE
│   ├── README.md
│   └── src
│       ├── dictionary.c
│       ├── ini_conf.c
│       └── iniparser.c
├── LICENSE
├── README.md
└── test									# 测试用例
    ├── CMakeLists.txt						# find_package(iniparser REQUIRED)
    ├── main.c
    └── test.ini
```

事实上开发者并不需要关注`iniparser`这个库和测试用例的细节，在实际使用中可以替换成自己开发的库。

## iniparser/CMakeLists.txt

```cmake
# created by Ricardo Lu in 07-15-2021

cmake_minimum_required(VERSION 3.10)

PROJECT(iniparser)
# 用于版本控制
set(INIPARSER_MAJOR_VERSION 0)
set(INIPARSER_MINOR_VERSION 1)
set(INIPARSER_PATCH_VERSION 0)
set(INIPARSER_VERSION 
    ${INIPARSER_MAJOR_VERSION}.${INIPARSER_MINOR_VERSION}.${INIPARSER_PATCH_VERSION})

set(INIPARSER_HEADER_DIR ${PROJECT_SOURCE_DIR}/inc)
set(INIPARSER_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# .so输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# 设置安装目录前缀
set(CMAKE_INSTALL_PREFIX /usr/local/iniparser)
set(INIPARSER_HEADER_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)

# 生成动态库libiniparser.so
add_library(${PROJECT_NAME}
    SHARED
    ${INIPARSER_SOURCE_DIR}/dictionary.c
    ${INIPARSER_SOURCE_DIR}/iniparser.c
    ${INIPARSER_SOURCE_DIR}/ini_conf.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/inc
)

# 设置调用libiniparser.so需要的公共头文件，用于后续安装
# iniparser库实际只需要ini_conf.h即可
set_target_properties(${PROJECT_NAME}
    PROPERTIES PUBLIC_HEADER "${INIPARSER_HEADER_DIR}/ini_conf.h"
)

# 将编译产物和库的头文件安装到指定路径，并导出到对应目标
install(TARGETS ${PROJECT_NAME}
	# 等价于调用export(EXPORT <export-name>)命令，导出库的相关信息
	# 需要在安装target之前调用
	# 实际安装导出目标依赖于下面执行的install(EXPORT)
    EXPORT iniparserpackage
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

# .in可以理解为cmake的头文件
# 复制iniparserConfig.cmake.in的内容到指定位置的iniparserConfig.cmake中，并替换对应的变量值
# for build tree
##configure_file(iniparserConfig.cmake.in
# "${PROJECT_BINARY_DIR}/iniparserConfig.cmake"
# @ONLY)
# for install tree
configure_file(iniparserConfig.cmake.in
  "${PROJECT_SOURCE_DIR}/iniparserConfig.cmake" @ONLY
)

configure_file(iniparserConfigVersion.cmake.in
  "${PROJECT_SOURCE_DIR}/iniparserConfigVersion.cmake" @ONLY
)

# 将生成的iniparserConfig.cmake安装到对应目录
install(FILES 
    "${PROJECT_SOURCE_DIR}/iniparserConfig.cmake"
    "${PROJECT_SOURCE_DIR}/iniparserConfigVersion.cmake"
    DESTINATION lib/cmake
)

# 为构建树导出目标
# `export(TARGETS iniparser FILE iniparserTargets.cmake)
# 将导出的目标安装到指定目录的iniparserTargets.cmake
# 安装目录需要和iniparserConfig.cmake一致（依赖关系）
install(EXPORT iniparserpackage
		# 默认安装文件名为<export-name>.cmake，使用FILE选项指定文件名
        FILE iniparserTargets.cmake
        DESTINATION lib/cmake/
)
```

- 构建的核心在于`install(TARGETS ${PROJECT_NAME} EXPORT iniparserpackage …)`和`install EXPORT iniparserpackage FILE iniparserTargets.cmake DESTINATION lib/cmake/)`。
- 在不考虑库和头文件等的安装的情况下，只从构建树的角度来看，这两条命令等价于`export(TARGETS iniparser FILE iniparserTargets.cmake)`。
- 通常来说会考虑生成两个`<package_name>Config.cmake`，一个用于构建树，一个用于安装，上例中只有安装并且生成在`${PROJECT_SOURCE_DIR}`目录下，生成的位置并不重要，自行设置即可。

## export命令

export命令的功能是从构建树中导出目标供外部项目使用。

> export(EXPORT <export-name> [NAMESPACE <namespace>] [FILE <filename>])

从当前的构建树中生成一个可以被外部项目导入目标的文件。

- `NAMESPACE`：用于指定作用域。
- 要安装导出目标需要使用`install(EXPORT <export-name>)`命令。
- 生成的文件是针对当前构建树而言的，所以不能被安装，假如要安装导出目标的信息，需要从安装树中生成导出目标再安装，如上文例子所示。

> export(TARGETS [target1 [target2 [...]]] [NAMESPACE <namespace>]
>        [APPEND] FILE <filename> [EXPORT_LINK_INTERFACE_LIBRARIES])

此命令类似于`EXPORT`选项，但目标是显式列出的，而不是指定为`export-name`。

**注：**`export`的导出行为都是针对构建树而言的。

## iniparserConfig.cmake

```cmake
# created by Ricardo Lu in 07-15-2021

# - Config file for the INIPARSER package
# It defines the following variables
#  INIPARSER_INCLUDE_DIRS - include directories for INIPARSER
#  INIPARSER_LIBRARIES    - libraries to link against

# 设置库的头文件路径和库名，便于调用，注意与安装路径保持一致
set(INIPARSER_INCLUDE_DIRS "@CMAKE_INSTALL_PREFIX@/include")
set(INIPARSER_LIBRARIES "@PROJECT_NAME@")

# 库的依赖，包含IMPORTED目标的定义
# 库的构建树信息
if( NOT TARGET @PROJECT_NAME@ AND NOT @PROJECT_NAME@_BINARY_DIR )
	include(${CMAKE_CURRENT_LIST_DIR}/iniparserTargets.cmake)
endif()
```

## iniparserConfigVersion.cmake

```cmake
# created by Ricardo Lu in 07-15-2021

set(PACKAGE_VERSION "@INIPARSER_VERSION@")

# Check whether the requested PACKAGE_FIND_VERSION is compatible
if("${PACKAGE_VERSION}" VERSION_LESS "${PACKAGE_FIND_VERSION}")
  set(PACKAGE_VERSION_COMPATIBLE FALSE)
else()
  set(PACKAGE_VERSION_COMPATIBLE TRUE)
  if ("${PACKAGE_VERSION}" VERSION_EQUAL "${PACKAGE_FIND_VERSION}")
    set(PACKAGE_VERSION_EXACT TRUE)
  endif()
endif()
```

