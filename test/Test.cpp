//
// Created by FireFlower on 2024/12/6.
//

#include "Test.h"

using namespace godot;

namespace fireflower {
	void Test::setNumber(int new_number) {
		this->number = new_number;
	}
	
	int Test::getNumber() const {
		return this->number;
	}
	
	Ref<FSignal1> Test::getNumberChangedSignal() const {
		return this->numberChanged;
	}
	
	void Test::_bind_methods() {
		// 属性 number
		ClassDB::bind_method(D_METHOD("setNumber", "new_number"), &Test::setNumber);
		ClassDB::bind_method(D_METHOD("getNumber"), &Test::getNumber);
		ClassDB::add_property(
			Test::get_class_static(),
			PropertyInfo(Variant::INT, "number"),
			"setNumber",
			"getNumber"
		);
		
		// 信号 numberChanged
		ClassDB::bind_method(D_METHOD("getNumberChangedSignal"), &Test::getNumberChangedSignal);
		ClassDB::add_property(
			Test::get_class_static(),
			PropertyInfo(
				Variant::OBJECT,
				"numberChanged",
				PROPERTY_HINT_NONE,
				"",
				PROPERTY_USAGE_NO_EDITOR
			),
			"",
			"getNumberChangedSignal"
		);
	}
} // fireflower