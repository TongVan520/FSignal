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
	testSlot1Bind()
	testSlotEmpty()
	testSlotInvalid()
	
	testSignal0()
	testSignal1()
	testSignalSlot()
	# print(self.onNumberChanged.getConnectedSlots())
	
	# testSignalSlotThread()
	testSignalSlotInSlot()
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

func testSlot1Bind() -> void:
	# var s1 := FSlot1.makeFromCallable(
	# 	func(n: int):
	# 		print("n == ", n)
	# 		pass
	# )
	# s1.bind(114514).invoke()
	
	# FSlot1.makeFromCallable(
	# 	func(n: int):
	# 		print("n == ", n)
	# 		pass
	# ).bind(114514).invoke()
	
	
	var numberArr := [114514]
	var slot := FSlot1.makeFromCallable(
		func(arr: Array):
			arr[0] = 1919810
			print("Hello FSlot1 Bind")
			pass
	)
	
	var new_slot := slot.bind(numberArr)
	new_slot.invoke()
	assert(numberArr[0] == 1919810, "testSlot1Bind 测试1失败")
	
	var sgnl0 := FSignal0.new()
	sgnl0.connect(
		FSlot1.makeFromCallable(
			(func(arr: Array):
				arr[0] = "2333"
				print("arr == ", arr)
				pass )
		).bind(numberArr)
	)
	
	sgnl0.emit()
	assert(numberArr[0] == "2333", "testSlot1Bind 测试2失败")
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

func testSignalSlotThread() -> void:
	# TODO 测试信号槽的线程安全
	
	var threadArr: Array[Thread] = []
	var stopRequested := FSignal0.new()
	const thread_count := 10
	
	var sgnl1 := FSignal1.new()
	
	stopRequested.connect(
		FSlot0.makeFromCallable(
			(func():
				print("停止信号已发出")
				pass )
		)
	)
	
	for i in thread_count:
		var thread := Thread.new()
		
		thread.start(self.mainForThread.bind(stopRequested, sgnl1))
		
		threadArr.append(thread)
		pass
	
	OS.delay_msec(10)
	stopRequested.emit()
	print("等待线程退出...")
	for thread in threadArr:
		thread.wait_to_finish()
		pass
	pass

func mainForThread(stopRequested: FSignal0, sgnl1: FSignal1):
	var is_need_stop := [false]
	stopRequested.connect(
		FSlot0.makeFromCallable(
			(func():
				is_need_stop[0] = true
				pass )
		)
	)
	
	sgnl1.connect(
		FSlot1.makeFromCallable(
			(func():
				
				pass )
		)
	)
	
	while not is_need_stop[0]:
		
		pass
	pass

## 测试在槽中访问信号的行为
func testSignalSlotInSlot() -> void:
	testSignalSlot0InSlot()
	testSignalSlot1InSlot()
	pass

func testSignalSlot0InSlot() -> void:
	var sgnl := FSignal0.new()
	var numberArr := [114514]
	
	sgnl.connect(
		FSlot0.makeFromCallable(
			(func():
				numberArr[0] = 1919810
				print("sgnl.getConnectedSlots() == ", sgnl.getConnectedSlots())
				pass )
		)
	)
	
	sgnl.emit()
	assert(numberArr[0] == 1919810, "testSignalSlot0InSlot 测试失败")
	pass

func testSignalSlot1InSlot() -> void:
	var sgnl := FSignal1.new()
	var numberArr := [114514]
	
	sgnl.connect(
		FSlot1.makeFromCallable(
			(func(na: Array):
				na[0] = 1919810
				print("sgnl.getConnectedSlots() == ", sgnl.getConnectedSlots())
				pass )
		)
	)
	
	sgnl.emit(numberArr)
	assert(numberArr[0] == 1919810, "testSignalSlot1InSlot 测试失败")
	pass
