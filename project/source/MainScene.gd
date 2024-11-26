extends Node

var number: int:
	set(v):
		if v == self.number:
			return
		number = v
		onNumberChanged.emit(v)
		pass
	
var onNumberChanged := FSignal1.new()

func _ready() -> void:
	testSlot0()
	testSlot1()
	testSlotEmpty()
	testSlotInvalid()
	
	testSignal0()
	testSignal1()
	testSignalSlot()
	pass

func testSlotEmpty():
	var slot = FSlot0.new()
	slot.invoke()
	pass

func testSlotInvalid():
	var slot = FSlot0.makeFromCallable(Callable(self, "无效的函数"))
	slot.invoke()
	pass

func testSlot0() -> void:
	var numberArr := [114, 514]
	var slot = FSlot0.makeFromCallable(
		func():
			numberArr[0] = 1919
			numberArr[1] = 810
			print("Hello FSlot0")
			pass
	)
	
	slot.invoke()
	assert(numberArr[0] == 1919 and numberArr[1] == 810, "testSlot0 测试失败")
	pass

func testSlot1() -> void:
	var numberArr := [114, 514]
	var slot = FSlot1.makeFromCallable(
		func(arr: Array):
			arr[0] = 1919
			arr[1] = 810
			print("Hello FSlot1")
			pass
	)
	
	slot.invoke(numberArr)
	assert(numberArr[0] == 1919 and numberArr[1] == 810, "testSlot1 测试失败")
	pass

func testSignal0() -> void:
	var sgnl := FSignal0.new()
	var numberArr := [114514]
	sgnl.connect(
		FSlot0.makeFromCallable(
			(func():
				numberArr[0] = 1919810
				print("Hello FSignal0")
				pass )
		),
		FConnectOption.Default
	)
	
	sgnl.emit()
	assert(numberArr[0] == 1919810, "testSignal0 测试失败")
	pass

func testSignal1() -> void:
	var sgnl := FSignal1.new()
	var numberArr := [114514]
	sgnl.connect(
		FSlot1.makeFromCallable(
			(func(arr: Array):
				arr[0] = 1919810
				print("Hello FSignal1")
				pass )
		),
		FConnectOption.Default
	)
	
	sgnl.emit(numberArr)
	assert(numberArr[0] == 1919810, "testSignal1 测试失败")
	pass

func testSignalSlot() -> void:
	self.number = 114514
	
	var callable := FSlot1.makeFromCallable(
		(func(new_number: int):
			print("new_number == ", new_number)
			pass )
	)
	self.onNumberChanged.connect(callable)
	
	print(self.onNumberChanged.isConnected(callable))
	print("已连接的槽：", self.onNumberChanged.getConnectedSlots())
	
	self.number = 1919810
	pass
