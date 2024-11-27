//
// Created by FireFlower on 2024/11/23.
//

#include "FSignal.h"
#include <queue>

using namespace godot;
using std::queue, std::shared_lock, std::unique_lock;

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
		unique_lock writeLock(this->slot_listShrdmtx);
		if (
			option & FConnectOption::FConnectOptionEnum::Unique &&
			this->findSlot(slot, true) != this->slotPairList.end()
			) {
			return;
		}
		
		this->slotPairList.push_back(std::make_pair(slot, option & FConnectOption::FConnectOptionEnum::Disposable));
	}
	
	void FSignal0::disconnect(Ref<FSlot0> slot) {
		unique_lock writeLock(this->slot_listShrdmtx);
		auto iter = this->findSlot(slot, true);
		if (iter != this->slotPairList.end()) {
			this->slotPairList.erase(iter);
		}
	}
	
	bool FSignal0::isConnected(Ref<FSlot0> slot) const {
		shared_lock readLock(this->slot_listShrdmtx);
		return this->findSlot(slot, true) != this->slotPairList.end();
	}
	
	void FSignal0::emit() {
		// 为了保证在槽中可以访问信号，需要先拷贝一份槽列表
		// 同时可以删除槽列表中的`Disposable`槽
		queue<Ref<FSlot0>> slotQue;
		{
			unique_lock writeLock(this->slot_listShrdmtx);
			for (auto iter = this->slotPairList.begin(); iter != this->slotPairList.end(); iter++) {
				auto& [slot, is_disposable] = *iter;
				slotQue.push(slot);
				if (is_disposable) {
					iter = this->slotPairList.erase(iter);
				}
			}
		}
		
		// 解锁后再调用槽
		while (!slotQue.empty()) {
			slotQue.front()->invoke();
			slotQue.pop();
		}
	}
	
	TypedArray<FSlot0> FSignal0::getConnectedSlots() const {
		shared_lock readLock(this->slot_listShrdmtx);
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
		unique_lock writeLock(this->slot_listShrdmtx);
		if (
			option & FConnectOption::FConnectOptionEnum::Unique &&
			this->findSlot(slot, true) != this->slotPairList.end()
			) {
			return;
		}
		
		this->slotPairList.push_back(std::make_pair(slot, option & FConnectOption::FConnectOptionEnum::Disposable));
	}
	
	void FSignal1::disconnect(Ref<FSlot1> slot) {
		unique_lock writeLock(this->slot_listShrdmtx);
		auto iter = this->findSlot(slot, true);
		if (iter != this->slotPairList.end()) {
			this->slotPairList.erase(iter);
		}
	}
	
	bool FSignal1::isConnected(Ref<FSlot1> slot) const {
		shared_lock readLock(this->slot_listShrdmtx);
		return this->findSlot(slot, true) != this->slotPairList.end();
	}
	
	void FSignal1::emit(const Variant& arg) {
		// 为了保证在槽中可以访问信号，需要先拷贝一份槽列表
		// 同时可以删除槽列表中的`Disposable`槽
		queue<Ref<FSlot1>> slotQue;
		{
			unique_lock writeLock(this->slot_listShrdmtx);
			for (auto iter = this->slotPairList.begin(); iter != this->slotPairList.end(); iter++) {
				auto& [slot, is_disposable] = *iter;
				slotQue.push(slot);
				if (is_disposable) {
					iter = this->slotPairList.erase(iter);
				}
			}
		}
		
		// 解锁后再调用槽
		while (!slotQue.empty()) {
			slotQue.front()->invoke(arg);
			slotQue.pop();
		}
	}
	
	TypedArray<FSlot1> FSignal1::getConnectedSlots() const {
		shared_lock readLock(this->slot_listShrdmtx);
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
