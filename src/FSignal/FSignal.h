//
// Created by FireFlower on 2024/11/23.
//

#ifndef FSIGNAL_FSIGNAL_H
#define FSIGNAL_FSIGNAL_H

#include <godot_cpp/classes/ref_counted.hpp>

#define FRegisterFSignal GDREGISTER_CLASS(fireflower::FSignal)

namespace fireflower {
	using namespace godot;
	
	/// @类名 信号
	/// @描述 线程安全
	class FSignal : public RefCounted {
	GDCLASS(FSignal, RefCounted);
	
	protected:
		static void _bind_methods();
	
	};
}

#endif //FSIGNAL_FSIGNAL_H
