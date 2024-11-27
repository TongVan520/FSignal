//
// Created by FireFlower on 2024/11/23.
//

#ifndef FSIGNAL_FSIGNAL_H
#define FSIGNAL_FSIGNAL_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <list>

#include "FSlot.h"


#define FRegisterFSignal \
GDREGISTER_CLASS(fireflower::FSignal0) \
GDREGISTER_CLASS(fireflower::FSignal1) \
GDREGISTER_CLASS(fireflower::FConnectOption) \


using godot::RefCounted, godot::Ref, godot::TypedArray;
using std::list, std::pair, std::shared_mutex;

/// 枚举<code>FConnectOption::FConnectOptionEnum</code>
namespace fireflower {
	class FConnectOption : public RefCounted {
	GDCLASS(FConnectOption, RefCounted);
	
	public:
		/// @类名 连接选项枚举
		enum FConnectOptionEnum {
			/// @名称 默认
			Default = 0b0,
			
			/// @名称 一次性
			/// @描述 当槽被调用一次后自动与其断开连接
			Disposable = 0b1,
			
			/// @名称 唯一
			/// @描述 确保相同的槽最多只能被连接一次
			Unique = 0b10,
		};
	
	protected:
		static void _bind_methods() {
			BIND_ENUM_CONSTANT(Default);
			BIND_ENUM_CONSTANT(Disposable);
			BIND_ENUM_CONSTANT(Unique);
		}
	};
}
VARIANT_ENUM_CAST(fireflower::FConnectOption::FConnectOptionEnum);

namespace fireflower {
	/// @类名 信号（无参）
	/// @描述 参数数量为<code>0</code>的信号\n
	/// <b>线程安全</b>
	class FSignal0 : public RefCounted {
	GDCLASS(FSignal0, RefCounted);
	
	private:
		using DataType = list <pair<Ref<FSlot0>, bool>>;
		
		/// @名称 槽列表
		/// @描述 列表中存储的是<i>槽</i>和<i>是否为一次性槽标志</i>的二元元组
		DataType slotPairList;
		
		/// @名称 槽列表的读写锁
		/// @描述 用于确保槽列表的线程安全
		mutable shared_mutex slot_listShrdmtx;
	
	private:
		/// @名称 查找指定槽
		/// @描述 从槽列表中查找指定槽
		/// @参数名称 <code>slot</code>
		/// @参数描述 槽
		/// @参数名称 <code>is_reverse</code>
		/// @参数描述 是否反向查找
		/// @返回值 对应的迭代器
		DataType::const_iterator findSlot(Ref<FSlot0> slot, bool is_reverse = false) const;
	
	public:
		/// @名称 连接
		/// @描述 <b>线程安全</b>，<b>原子操作</b>
		/// @参数名称 <code>slot</code>
		/// @参数描述 槽
		/// @参数名称 <code>option</code>
		/// @参数描述 连接选项枚举
		void connect(
			Ref<FSlot0> slot,
			FConnectOption::FConnectOptionEnum option = FConnectOption::FConnectOptionEnum::Default
		);
		
		/// @名称 断开连接
		/// @描述 <b>线程安全</b>，<b>原子操作</b>
		/// @参数名称 <code>slot</code>
		/// @参数描述 槽
		void disconnect(Ref<FSlot0> slot);
		
		/// @名称 判断是否已连接指定槽
		/// @描述 <b>线程安全</b>，<b>原子操作</b>
		/// @参数名称 <code>slot</code>
		/// @参数描述 槽
		/// @返回值 是否已连接
		bool isConnected(Ref<FSlot0> slot) const;
		
		/// @名称 触发
		/// @描述 <b>线程安全</b>，<b>原子操作</b>\n
		/// <b>注意</b>：在此次调用中对<i>槽列表</i>的修改，只会从<b>下一次</b>调用起开始生效
		void emit();
		
		/// @名称 获取已连接的槽
		/// @描述 <b>线程安全</b>，<b>原子操作</b>
		/// @返回值 已连接的槽组成的数组
		TypedArray<FSlot0> getConnectedSlots() const;
	
	protected:
		static void _bind_methods();
		
	};
	
	/// @类名 信号（单参）
	/// @描述 参数数量为<code>1</code>的信号
	class FSignal1 : public RefCounted {
	GDCLASS(FSignal1, RefCounted);
	private:
		using DataType = list <pair<Ref<FSlot1>, bool>>;
		
		/// @名称 槽列表
		/// @描述 列表中存储的是<i>槽</i>和<i>是否为一次性槽标志</i>的二元元组
		DataType slotPairList;
		
		/// @名称 槽列表的读写锁
		/// @描述 用于确保槽列表的线程安全
		mutable shared_mutex slot_listShrdmtx;
	
	private:
		DataType::const_iterator findSlot(Ref<FSlot1> slot, bool is_reverse = false) const;
	
	public:
		/// @名称 连接
		/// @描述 <b>线程安全</b>，<b>原子操作</b>
		/// @参数名称 <code>slot</code>
		/// @参数描述 槽
		/// @参数名称 <code>option</code>
		/// @参数描述 连接选项枚举
		void connect(
			Ref<FSlot1> slot,
			FConnectOption::FConnectOptionEnum option = FConnectOption::FConnectOptionEnum::Default
		);
		
		/// @名称 断开连接
		/// @描述 <b>线程安全</b>，<b>原子操作</b>
		/// @参数名称 <code>slot</code>
		/// @参数描述 槽
		void disconnect(Ref<FSlot1> slot);
		
		/// @名称 判断是否已连接指定槽
		/// @描述 <b>线程安全</b>，<b>原子操作</b>
		/// @参数名称 <code>slot</code>
		/// @参数描述 槽
		/// @返回值 是否已连接
		bool isConnected(Ref<FSlot1> slot) const;
		
		/// @名称 触发
		/// @描述 <b>线程安全</b>，<b>原子操作</b>\n
		/// <b>注意</b>：在此次调用中对<i>槽列表</i>的修改，只会从<b>下一次</b>调用起开始生效
		void emit(const Variant& arg);
		
		/// @名称 获取已连接的槽
		/// @描述 <b>线程安全</b>，<b>原子操作</b>
		/// @返回值 已连接的槽组成的数组
		TypedArray<FSlot1> getConnectedSlots() const;
		
	protected:
		static void _bind_methods();
		
	};
}

#endif //FSIGNAL_FSIGNAL_H
