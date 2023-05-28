# DemoJsonParse

## 1. 语法知识点

### 1.1 头文件 `print.h`

#### 1.1.1 `#include <type_trait>`

- 概述：提供了丰富的**编译期间**计算、查询、判断、转换和选择的帮助类
- 作用：
  - 增加了泛型编程的能力
  - 编译期间就可以做到优化、改进甚至是排错，提高代码质量
  - 一定程度上可以消除冗长的`if-else`和`switch-case`语句，可以降低代码的复杂度，提高代码的可维护性
  - 编译期间可以检测出是否正确的类型，以便编写更为安全的代码

##### 1.1.1.1 `Helper Class`

```cpp
// 定义编译期常量
template<typename Type>
struct CompileTimeContents : std::integral_constant<int, 1>{};
// 获取编译期常量
int value = CompileTimeContents<int>::value;
```

##### 1.1.1.2 判断类型

- 判断类型的模板类都继承于`std::intergral_constant`

- `traits`判断类型

  | traits 类型    | 说明                            |
  | -------------- | ------------------------------- |
  | `is_array`     | 判断是否为数组类型              |
  | `is_class`     | 判断是否为类类型而非`union`类型 |
  | `is_function`  | 判断是否为函数类型              |
  | `is_reference` | 判断是否为引用类型              |
  | `is_pod`       | 判断是否为`POD`                 |

  ```cpp
  std::cout << std::is_array<int>::value << std::endl;
  std::cout << std::is_array<int[3]>::value << std::endl;
  std::cout << std::is_array<std::array<int, 3>>::value << std::endl;
  std::cout << std::is_array<std::string>::value << std::endl;
  ```

- 类型转换

  | `trait` 类型           | 说明             |
  | ---------------------- | ---------------- |
  | `remove_cv`            | 移除`cv`属性     |
  | `add_cv`               | 添加`cv`属性     |
  | `remove_reference`     | 移除引用         |
  | `add_lvalue_reference` | 添加左值引用     |
  | `remove_extent`        | 移除数组顶层维度 |

  ```cpp
  typedef const volatile char vchar;
  std::remove_cv<vchar>::type a;
  std::remove_cv<char* const>::type b;
  std::remove_cv<const char*>::type c;
  
  if (std::is_const<decltype(a)>::value) {} // exec
  if (std::is_volatile<decltype(a)>::value) {} // exec
  ```

- 根据条件选择`trait`类型

  ```cpp
  template<bool Cond, class T, class F> struct conditional;
  // example
  typedef std::conditional<(sizeof(long long)> sizeof(long double)), \
                           long long, long double >::type max_size_t;
  std::cout << typeid(max_size_t).name() << std::endl;
  ```

- 可调用对象返回值类型

  ```cpp
  // 
  decltype(std::declval<A>()(std::declval<int>())) i = 4;
  // trait 提供了另外一种途径
  std::result_of<A(int)>::type i = 4;
  ```

- 根据条件禁用或启动某些类型

  ```cpp
  template<class T>
  typename std::enable_if<std::is_integral<T>::value, bool>::type
  ```

  
