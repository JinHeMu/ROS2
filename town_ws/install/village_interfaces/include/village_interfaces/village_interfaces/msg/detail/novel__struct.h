﻿// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from village_interfaces:msg/Novel.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACES__MSG__DETAIL__NOVEL__STRUCT_H_
#define VILLAGE_INTERFACES__MSG__DETAIL__NOVEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'content'
#include "std_msgs/msg/detail/string__struct.h"
// Member 'image'
#include "sensor_msgs/msg/detail/image__struct.h"

/// Struct defined in msg/Novel in the package village_interfaces.
/**
  * 标准消息接口std_msgs下的String类型
 */
typedef struct village_interfaces__msg__Novel
{
  std_msgs__msg__String content;
  /// 图像消息，调用sensor_msgs下的Image类型
  sensor_msgs__msg__Image image;
} village_interfaces__msg__Novel;

// Struct for a sequence of village_interfaces__msg__Novel.
typedef struct village_interfaces__msg__Novel__Sequence
{
  village_interfaces__msg__Novel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} village_interfaces__msg__Novel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VILLAGE_INTERFACES__MSG__DETAIL__NOVEL__STRUCT_H_
