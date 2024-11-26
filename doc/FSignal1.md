# FSignal1
参数数量为`1`的信号

与此类对应的[槽类型](FSlot1.md)

## 父类
`RefCounted`

## 函数

### connect
```gdscript
void connect(slot: FSlot1, option: FConnectOption.FConnectOptionEnum = 0)
```
连接指定槽

`slot`  
槽

`option`  
连接选项，是一个类型为[FConnectOption](FConnectOption.md)的枚举值，用于指定连接方式。
默认值为[FConnectOption.Default](FConnectOption.md#default)。

### disconnect
```gdscript
void disconnect(slot: FSlot1)
```
断开与指定槽的连接

`slot`
槽

### isConnected
```gdscript
bool isConnected(slot: FSlot1)
```
判断是否已连接指定槽

`slot`
槽

**返回值**
是否已连接

### emit
```gdscript
void emit(arg: Variant)
```
触发信号

`arg`
参数

### getConnectedSlots
```gdscript
Array[FSlot1] getConnectedSlots() const
```
获取已连接的槽

**返回值**
已连接的槽组成的数组
