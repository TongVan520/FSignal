//
// Created by FireFlower on 2024/11/23.
//

#ifndef FSIGNAL_FSLOT_H
#define FSIGNAL_FSLOT_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <functional>


#define FRegisterFSlot \
GDREGISTER_CLASS(fireflower::FSlot0) \
GDREGISTER_CLASS(fireflower::FSlot1) \


using godot::RefCounted, godot::Ref, godot::Callable, godot::Variant, godot::String;
using std::function;

namespace fireflower {
	/// @类名 槽（无参）
	/// @描述 参数数量为<code>0</code>的槽\n
	/// <b>线程安全</b>
	class FSlot0 : public RefCounted {
	GDCLASS(FSlot0, RefCounted);
	
	public:
		using FunctionType = function<void()>;
	
	private:
		FunctionType function;
	
	public:
		/// @名称 从C++ Lambda函数创建
		/// @参数名称 <code>lambdaFunc</code>
		/// @参数描述 C++ Lambda函数
		/// @返回值 类实例引用
		static Ref<FSlot0> makeFromLambda(const FunctionType& lambdaFunc);
		
		/// @名称 从Godot Callable创建
		/// @参数名称 <code>callable</code>
		/// @参数描述 Godot Callable对象
		/// @返回值 类实例引用
		static Ref<FSlot0> makeFromCallable(const Callable& callable);
		
		/// @名称 调用
		void invoke() const;
	
	protected:
		static void _bind_methods();
		String _to_string() const;
		
	};
	
	/// @类名 槽（单参）
	/// @描述 参数数量为<code>1</code>的槽\n
	/// <b>线程安全</b>
	class FSlot1 : public RefCounted {
	GDCLASS(FSlot1, RefCounted);
	
	public:
		using FunctionType = function<void(const Variant&)>;
	
	private:
		FunctionType function;
	
	public:
		/// @名称 从C++ Lambda函数创建
		/// @描述 C++ Lambda函数
		/// @参数名称 <code>lambdaFunc</code>
		/// @参数描述 C++ Lambda函数
		/// @返回值 类实例引用
		static Ref<FSlot1> makeFromLambda(const FunctionType& lambdaFunc);
		
		/// @名称 从Godot Callable创建
		/// @参数名称 <code>callable</code>
		/// @参数描述 Godot Callable对象
		/// @返回值 类实例引用
		static Ref<FSlot1> makeFromCallable(const Callable& callable);
		
		/// @名称 调用
		/// @参数名称 <code>arg</code>
		/// @参数描述 参数
		void invoke(const Variant& arg) const;
		
		/// @名称 绑定参数
		/// @描述 绑定一个参数
		/// @参数名称 <code>arg</code>
		/// @参数描述 参数
		/// @返回值 参数为<code>0</code>的槽
		Ref<FSlot0> bind(const Variant& arg) const;
	
	protected:
		static void _bind_methods();
		String _to_string() const;
		
	};
}

#endif //FSIGNAL_FSLOT_H
