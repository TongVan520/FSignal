# FSlot0
参数数量为`0`的槽
**线程安全**

与此类对应的[信号类型](FSignal0.md)

## 父类
`RefCounted`

## 函数

### invoke
```gdscript
void invoke() const
```
调用
**线程安全**，**原子操作**

### makeFromCallable
```gdscript
static FSlot0 makeFromCallable(callable: Callable)
```
从Godot Callable创建
**线程安全**

`callable`
Godot Callable对象

**返回值**
类实例引用
