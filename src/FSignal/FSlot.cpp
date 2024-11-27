//
// Created by FireFlower on 2024/11/23.
//

#include "FSlot.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using std::shared_lock;

// FSlot0
namespace fireflower {
	Ref<FSlot0> FSlot0::makeFromLambda(const FunctionType& lambdaFunc) {
		auto result = Ref(memnew(FSlot0));
		
		result->function = lambdaFunc;
		
		return result;
	}
	
	Ref<FSlot0> FSlot0::makeFromCallable(const Callable& callable) {
		auto result = Ref(memnew(FSlot0));
		
		result->function = [=]() {
			if (callable.is_valid()) {
				callable.call();
			}
			else {
				UtilityFunctions::push_warning(L"Callable无效");
			}
		};
		
		return result;
	}
	
	void FSlot0::invoke() const {
		shared_lock readLock(this->functionShrdmtx);
		if (this->function) {
			this->function();
		}
	}
	
	void FSlot0::_bind_methods() {
		// makeFromCallable
		ClassDB::bind_static_method(
			FSlot0::get_class_static(),
			D_METHOD("makeFromCallable", "callable"),
			&FSlot0::makeFromCallable
		);
		
		// invoke
		ClassDB::bind_method(D_METHOD("invoke"), &FSlot0::invoke);
	}
	
	String FSlot0::_to_string() const {
		String resultStr = "{";
		
		resultStr += L"类名：";
		resultStr += FSlot0::get_class_static();
		resultStr += L"，";
		
		resultStr += L"内存地址：";
		resultStr += String::num_int64(reinterpret_cast<intptr_t>(this), 16);
		
		return resultStr + "}";
	}
}

// FSlot1
namespace fireflower {
	Ref<FSlot1> FSlot1::makeFromLambda(const FunctionType& lambdaFunc) {
		auto result = Ref(memnew(FSlot1));
		
		result->function = lambdaFunc;
		
		return result;
	}
	
	Ref<FSlot1> FSlot1::makeFromCallable(const Callable& callable) {
		auto result = Ref(memnew(FSlot1));
		
		result->function = [=](const Variant& arg) {
			if (callable.is_valid()) {
				callable.call(arg);
			}
			else {
				UtilityFunctions::push_warning(L"Callable无效");
			}
		};
		
		return result;
	}
	
	void FSlot1::invoke(const Variant& arg) const {
		shared_lock readLock(this->functionShrdmtx);
		if (this->function) {
			this->function(arg);
		}
	}
	
	Ref<FSlot0> FSlot1::bind(const Variant& arg) const {
		// 确保自己的生命周期长于新槽的生命周期
		auto self = Ref(const_cast<FSlot1*>(this));
		return FSlot0::makeFromLambda(
			[=]() {
				self->invoke(arg);
			}
		);
	}
	
	void FSlot1::_bind_methods() {
		// makeFromCallable
		ClassDB::bind_static_method(
			FSlot1::get_class_static(),
			D_METHOD("makeFromCallable", "callable"),
			&FSlot1::makeFromCallable
		);
		
		// invoke
		ClassDB::bind_method(D_METHOD("invoke", "arg"), &FSlot1::invoke);
		
		// bind
		ClassDB::bind_method(D_METHOD("bind", "arg"), &FSlot1::bind);
	}
	
	String FSlot1::_to_string() const {
		String resultStr = "{";
		
		resultStr += L"类名：";
		resultStr += FSlot0::get_class_static();
		resultStr += L"，";
		
		resultStr += L"内存地址：";
		resultStr += String::num_int64(reinterpret_cast<intptr_t>(this), 16);
		
		return resultStr + "}";
	}
}
