//
// Created by FireFlower on 2024/12/2.
//

#include <iostream>
#include <FSignal/FSignal.h>
#include <FSignal/FSlot.h>

using namespace std;

void test() {
	using namespace fireflower;
	FSignal0 signal;
	signal.connect(
		FSlot0::makeFromLambda(
			[] {
				cout << "qwq 中文测试" << endl;
			}
		)
	);
	signal.emit();
}
