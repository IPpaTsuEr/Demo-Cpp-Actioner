# Demo-Cpp-Actioner
 通过代码操作鼠标键盘发送消息

	Action ac = Action(3);
	Screen sc = Screen();
	//int w, h;
	WORD lst[3] = { VK_LCONTROL, VK_LSHIFT,VK_ESCAPE };
	//相对位置移动
	ac.move(-200,-100)
		.click()
		.key_selectall()
		.keycompare(lst)
		.key_find()
		.key_res()
		.keydown(VK_LCONTROL).press('A').keyup(VK_LCONTROL).clean();

	//ac.move(0,0,true);//绝对坐标移动
	