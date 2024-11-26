# FConnectOption
连接选项

## 枚举

### FConnectOptionEnum
连接选项枚举

不同值之间可以相互组合成新的值。

|枚举|值|
|:-|:-:|
|[Default](#default)|0|
|[Disposable](#disposable)|1|
|[Unique](#unique)|2|

#### Default
默认

#### Disposable
一次性
当槽被调用一次后自动与其断开连接。

#### Unique
唯一连接
确保相同的槽最多只能被连接一次。
