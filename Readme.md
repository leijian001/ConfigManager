# **配置文件管理器**

## 特点
1. 配置文件采用Json格式
2. 绑定变量和变量在文件中的名字
3. 支持默认值
4. 支持递归形式

## 注意
1. 由于采用了 std::any, 所以需要 C++17 或以上版本的编译器
2. 依赖于 [nlohmann json](https://github.com/nlohmann/json) 库
