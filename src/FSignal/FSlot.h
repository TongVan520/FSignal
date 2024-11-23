//
// Created by FireFlower on 2024/11/23.
//

#ifndef FSIGNAL_FSLOT_H
#define FSIGNAL_FSLOT_H

#include <godot_cpp/classes/ref_counted.hpp>

#define FRegisterFSlot GDREGISTER_CLASS(fireflower::FSlot)

namespace fireflower {
	using namespace godot;
	
	/// @类名 槽
	/// @描述 线程安全
	class FSlot : public RefCounted {
	GDCLASS(FSlot, RefCounted);
	
	protected:
		static void _bind_methods();
		
	};
}

#endif //FSIGNAL_FSLOT_H
