//
// Created by FireFlower on 2024/12/6.
//

#ifndef FSIGNAL_TEST_H
#define FSIGNAL_TEST_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/ref.hpp>

#include <FSignal/FSignal.h>


#define FRegisterTest GDREGISTER_CLASS(fireflower::Test)


using godot::RefCounted, godot::Ref;

namespace fireflower {
	/// @类名 测试
	class Test : public RefCounted {
	GDCLASS(Test, RefCounted);
	
	private:
		int number = 0;
	
	public:
		Ref<FSignal1> numberChanged = memnew(FSignal1);
		
	public:
		void setNumber(int new_number);
		int getNumber() const;
		Ref<FSignal1> getNumberChangedSignal() const;
	
	protected:
		static void _bind_methods();
		
	};
} // fireflower

#endif //FSIGNAL_TEST_H
