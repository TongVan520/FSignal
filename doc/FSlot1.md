# FSlot1
参数数量为`1`的槽
**线程安全**

与此类对应的[信号类型](FSignal1.md)

## 父类
`RefCounted`

## 函数

### bind
```gdscript
FSlot0 bind(arg: Variant) const
```
绑定一个参数

`arg`
参数

**返回值**
[参数为`0`的槽](FSlot0.md)

### invoke
```gdscript
void invoke() const
```
调用
**线程安全**，**原子操作**

### makeFromCallable
```gdscript
static FSlot1 makeFromCallable(callable: Callable)
```
从Godot Callable创建
**线程安全**

`callable`
Godot Callable对象

**返回值**
类实例引用
