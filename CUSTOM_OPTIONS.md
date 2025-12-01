# Protoc 自定义选项说明

## Changelog

### 2024-12-01

#### 新增功能

**1. `preserve_names` 选项**
- 支持语言：C#, Java
- 功能：保留 proto 文件中的原始字段名和枚举值名，不进行驼峰命名转换
- 修改文件：
  - C#: `csharp_options.h`, `csharp_generator.cc`, `csharp_helpers.h`, `csharp_helpers.cc`, `csharp_enum.cc`, `csharp_field_base.cc`
  - Java: `java/options.h`, `java/generator.cc`, `java/helpers.h`, `java/helpers.cc`, `java/names.h`, `java/names.cc`, `java/context.cc`

**2. `generate_specified` 选项**
- 支持语言：C#, Java
- 功能：为 optional 字段额外生成 `xxxSpecified` 属性/方法，用于序列化框架兼容
- 修改文件：
  - C#: `csharp_options.h`, `csharp_generator.cc`, `csharp_primitive_field.cc`, `csharp_message_field.cc`
  - Java: `java/options.h`, `java/generator.cc`, `java/full/primitive_field.cc`

---

## 使用方法

### 1. preserve_names

保留原始字段名，不进行命名转换。

#### 效果对比

| Proto 字段名 | 正常模式 | preserve_names |
|-------------|----------|----------------|
| `user_name` | `UserName` (C#) / `getUserName()` (Java) | `user_name` (C#) / `getuser_name()` (Java) |
| `buildingId` | `BuildingId` (C#) / `getBuildingId()` (Java) | `buildingId` (C#) / `getbuildingId()` (Java) |
| `BRT_XX` (枚举) | `BrtXx` | `BRT_XX` |

#### 命令示例

```bash
# C#
protoc --csharp_out=preserve_names:./output your.proto

# Java
protoc --java_out=preserve_names:./output your.proto
```

---

### 2. generate_specified

为 optional 字段生成额外的 `xxxSpecified` 属性（C#）或 `isXxxSpecified()` 方法（Java）。

#### 生成效果

**C#:**
```csharp
// 原有的 Has 属性
public bool HasCode { get; }

// 新增的 Specified 属性
public bool CodeSpecified {
  get { return HasCode; }
  set { /* setter for serialization compatibility */ }
}
```

**Java:**
```java
// 原有的 has 方法
public boolean hasCode();

// 新增的 isSpecified 方法
public boolean isCodeSpecified() {
  return hasCode();
}
```

#### 命令示例

```bash
# C#
protoc --csharp_out=generate_specified:./output your.proto

# Java
protoc --java_out=generate_specified:./output your.proto
```

---

### 3. 同时使用多个选项

多个选项用逗号分隔：

```bash
# C# - 同时启用两个选项
protoc --csharp_out=preserve_names,generate_specified:./output your.proto

# Java - 同时启用两个选项
protoc --java_out=preserve_names,generate_specified:./output your.proto
```

#### 同时启用效果

```csharp
// C# 示例
public long buildingId { get; set; }      // 保留原始名称
public bool HasbuildingId { get; }        // Has 属性也保留原始名称
public bool buildingIdSpecified { get; set; }  // Specified 属性
```

```java
// Java 示例
public long getbuildingId();              // 保留原始名称
public boolean hasbuildingId();           // has 方法也保留原始名称
public boolean isbuildingIdSpecified();   // isSpecified 方法
```

---

## 编译后的 protoc 路径

```
E:\github\protobuf\build\Release\protoc.exe
```

---

## 重新编译 protoc

如需修改代码后重新编译：

```powershell
& "E:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" --build E:\github\protobuf\build --config Release --target protoc --parallel 4
```
