




  section '.text' code readable executable



  start:	invoke	GetModuleHandle,0		    ;заполняем структуру wc и создаём окно
		mov	[wc.hInstance],eax		    ; помещаем адрес в [wc.hInstance]
		invoke	LoadIcon,eax, 17		    ;
		mov	[wc.hIcon],eax
		invoke	LoadCursor,0,IDC_ARROW
		mov	[wc.hCursor],eax
		invoke	RegisterClass,wc

		test	eax,eax 			    ; WS_VISIBLE+WS_DLGFRAME+WS_SYSMENU,\
		jz	error				    ; WS_OVERLAPPEDWINDOW

		invoke	CreateWindowEx,0,_class,_title,WS_VISIBLE+WS_SYSMENU,\
			128,128,648,526,NULL,NULL,[wc.hInstance],NULL	 ;   [wc.hInstance]

		test	eax,eax
		jz	error

  ;-----------------------------------------------------------------------------------------
  msg_loop:	invoke	GetMessage,msg,NULL,0,0
		cmp	eax,1
		jb	end_loop
		jne	msg_loop
		invoke	TranslateMessage,msg
		invoke	DispatchMessage,msg
		jmp	msg_loop

  error:	invoke	MessageBox,NULL,_error,NULL,MB_ICONERROR+MB_OK


  end_loop:


		invoke	ExitProcess,[msg.wParam]
