//
// Created by FireFlower on 2024/11/23.
//

#include "FSignal.h"
#include <stack>

using namespace godot;
using std::stack;

// FSignal0
namespace fireflower {
	FSignal0::DataType::const_iterator FSignal0::findSlot(Ref<FSlot0> slot, bool is_reverse) const {
		auto compareFunc = [&](const auto& slotPair) -> bool {
			return slotPair.first == slot;
		};
		return is_reverse ?
			   (
				   ++std::find_if(
					   this->slotPairList.rbegin(), this->slotPairList.rend(),
					   compareFunc
				   )
			   ).base() :
			   std::find_if(
				   this->slotPairList.begin(), this->slotPairList.end(),
				   compareFunc
			   );
	}
	
	void FSignal0::connect(Ref<FSlot0> slot, FConnectOption::FConnectOptionEnum option) {
		if (
			option & FConnectOption::FConnectOptionEnum::Unique &&
			this->findSlot(slot, true) != this->slotPairList.end()
			) {
			return;
		}
		
		this->slotPairList.push_back(std::make_pair(slot, option & FConnectOption::FConnectOptionEnum::Disposable));
	}
	
	void FSignal0::disconnect(Ref<FSlot0> slot) {
		auto iter = this->findSlot(slot, true);
		if (iter != this->slotPairList.end()) {
			this->slotPairList.erase(iter);
		}
	}
	
	bool FSignal0::isConnected(Ref<FSlot0> slot) const {
		return this->findSlot(slot, true) != this->slotPairList.end();
	}
	
	void FSignal0::emit() {
		stack<DataType::const_iterator> disposable_slotIterStack;
		
		for (auto iter = this->slotPairList.begin(); iter != this->slotPairList.end(); iter++) {
			auto& [slot, is_disposable] = *iter;
			slot->invoke();
			if (is_disposable) {
				disposable_slotIterStack.push(iter);
			}
		}
		
		while (!disposable_slotIterStack.empty()) {
			this->slotPairList.erase(disposable_slotIterStack.top());
			disposable_slotIterStack.pop();
		}
	}
	
	TypedArray<FSlot0> FSignal0::getConnectedSlots() const {
		TypedArray<FSlot0> resultSlot0Arr;
		for (auto& [slot, _]: this->slotPairList) {
			resultSlot0Arr.append(slot);
		}
		return resultSlot0Arr;
	}
	
	void FSignal0::_bind_methods() {
		// connect
		ClassDB::bind_method(
			D_METHOD("connect", "slot", "option"),
			&FSignal0::connect,
			DEFVAL(FConnectOption::FConnectOptionEnum::Default)
		);
		
		// disconnect
		ClassDB::bind_method(D_METHOD("disconnect", "slot"), &FSignal0::disconnect);
		
		// isConnected
		ClassDB::bind_method(D_METHOD("isConnected", "slot"), &FSignal0::isConnected);
		
		// emit
		ClassDB::bind_method(D_METHOD("emit"), &FSignal0::emit);
		
		// getConnectedSlots
		ClassDB::bind_method(D_METHOD("getConnectedSlots"), &FSignal0::getConnectedSlots);
	}
}

// FSignal1
namespace fireflower {
	FSignal1::DataType::const_iterator FSignal1::findSlot(Ref<FSlot1> slot, bool is_reverse) const {
		auto compareFunc = [&](const auto& slotPair) -> bool {
			return slotPair.first == slot;
		};
		return is_reverse ?
			   (
				   ++std::find_if(
					   this->slotPairList.rbegin(), this->slotPairList.rend(),
					   compareFunc
				   )
			   ).base() :
			   std::find_if(
				   this->slotPairList.begin(), this->slotPairList.end(),
				   compareFunc
			   );
	}
	
	void FSignal1::connect(Ref<FSlot1> slot, FConnectOption::FConnectOptionEnum option) {
		if (
			option & FConnectOption::FConnectOptionEnum::Unique &&
			this->findSlot(slot, true) != this->slotPairList.end()
			) {
			return;
		}
		
		this->slotPairList.push_back(std::make_pair(slot, option & FConnectOption::FConnectOptionEnum::Disposable));
	}
	
	void FSignal1::disconnect(Ref<FSlot1> slot) {
		auto iter = this->findSlot(slot, true);
		if (iter != this->slotPairList.end()) {
			this->slotPairList.erase(iter);
		}
	}
	
	bool FSignal1::isConnected(Ref<FSlot1> slot) const {
		return this->findSlot(slot, true) != this->slotPairList.end();
	}
	
	void FSignal1::emit(const Variant& arg) {
		stack<DataType::const_iterator> disposable_slotIterStack;
		
		for (auto iter = this->slotPairList.begin(); iter != this->slotPairList.end(); iter++) {
			auto& [slot, is_disposable] = *iter;
			slot->invoke(arg);
			if (is_disposable) {
				disposable_slotIterStack.push(iter);
			}
		}
		
		while (!disposable_slotIterStack.empty()) {
			this->slotPairList.erase(disposable_slotIterStack.top());
			disposable_slotIterStack.pop();
		}
	}
	
	TypedArray<FSlot1> FSignal1::getConnectedSlots() const {
		TypedArray<FSlot1> resultSlot1Arr;
		for (auto& [slot, _]: this->slotPairList) {
			resultSlot1Arr.append(slot);
		}
		return resultSlot1Arr;
	}
	
	void FSignal1::_bind_methods() {
		// connect
		ClassDB::bind_method(
			D_METHOD("connect", "slot", "option"),
			&FSignal1::connect,
			DEFVAL(FConnectOption::FConnectOptionEnum::Default)
		);
		
		// disconnect
		ClassDB::bind_method(D_METHOD("disconnect", "slot"), &FSignal1::disconnect);
		
		// isConnected
		ClassDB::bind_method(D_METHOD("isConnected", "slot"), &FSignal1::isConnected);
		
		// emit
		ClassDB::bind_method(D_METHOD("emit", "arg"), &FSignal1::emit);
		
		// getConnectedSlots
		ClassDB::bind_method(D_METHOD("getConnectedSlots"), &FSignal1::getConnectedSlots);
	}
}
