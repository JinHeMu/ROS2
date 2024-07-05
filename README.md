# ROS2学习记录

## 节点

### 定义

ROS2中每一个节点也是只负责一个单独的模块化的功能（比如一个节点负责控制车轮转动，一个节点负责从激光雷达获取数据、一个节点负责处理激光雷达的数据、一个节点负责定位等等）

### 如何通讯

话题,服务,动作,参数

## 工作空间

### 定义

工作空间是包含若干个功能包的目录，一开始大家把工作空间理解成一个文件夹就行了。这个文件夹包含下有`src`

### 功能包

功能包可以理解为存放节点的地方，ROS2中功能包根据编译方式的不同分为三种类型。

- `ament_python`，适用于python程序
- `cmake`，适用于C++
- `ament_cmake`，适用于C++程序,是cmake的增强版

## Colcon

### 定义

Colcon 是一个用于构建和管理多包项目的命令行工具，广泛应用于机器人操作系统（ROS）2和其他使用多包构建系统的项目。它提供了一个统一的界面来构建、测试和安装多个软件包，简化了复杂项目的管理和开发流程。

## RCLCPP编写节点

1. 创建工作空间和功能包

   ```
   mkdir -p chapt2_ws/src
   cd chapt2_ws/src
   ros2 pkg create example_cpp --build-type ament_cmake --dependencies rclcpp
   ```

   - pkg create 是创建包的意思
   - --build-type 用来指定该包的编译类型，一共有三个可选项`ament_python`、`ament_cmake`、`cmake`
   - --dependencies 指的是这个功能包的依赖，ros2的C++客户端接口`rclcpp`

   ```
   .
   └── src
       └── example_cpp
           ├── CMakeLists.txt
           ├── include
           │   └── example_cpp
           ├── package.xml
           └── src
   
   5 directories, 2 files
   ```

2. 创建节点

   在`example_cpp/src`下创建一个`node_01.cpp`文件

3. 编写代码

```cpp
#include "rclcpp/rclcpp.hpp"
int main(int argc, char **argv)
{
    /* 初始化rclcpp  */
    rclcpp::init(argc, argv);
    /*产生一个node_01的节点*/
    auto node = std::make_shared<rclcpp::Node>("node_01");
    // 打印一句自我介绍
    RCLCPP_INFO(node->get_logger(), "node_01节点已经启动.");
    /* 运行节点，并检测退出信号 Ctrl+C*/
    rclcpp::spin(node);
    /* 停止运行 */
    rclcpp::shutdown();
    return 0;
}
```

4. 修改CMakeLists

```cmake
add_executable(node_01 src/node_01.cpp)
ament_target_dependencies(node_01 rclcpp)
install(TARGETS
  node_01
  DESTINATION lib/${PROJECT_NAME}
)
```