
		;--------------------------------------------
		;	   ������ ���������		    =
		;--------------------------------------------
		invoke	    CreateStatusWindow, WS_CHILD or WS_VISIBLE or SBS_SIZEGRIP, 0,  [hwnd], 200
		mov	    [hStatusBar], eax
		invoke	    SendMessage, [hStatusBar], SB_SETPARTS, 3, StatusBarParts

		invoke	    SendMessage, [hStatusBar], SB_SETTEXT, 0, E_mail

		;---------------------------------------------------
		; ������������� ������ � ��������� ��� ���� ������ =
		;---------------------------------------------------
		invoke	    GetDC, [hwnd]
		push	    eax
		invoke	    CreateCompatibleDC, eax
		mov	    [TmpDC], eax
		pop	    eax
		invoke	    CreateCompatibleBitmap, eax, 640, 460
		mov	    [TmpBmp], eax
		invoke	    SelectObject, [TmpDC], [TmpBmp]

		;--------------------------------------------
		;  �������� �������� � ����������...	    =
		;--------------------------------------------
		invoke	   CreatePen, 0, 1,  $FFFFFF
		mov	   [WhitePen], eax
		invoke	   CreatePen, 0, 1,  $00FF00
		mov	   [GreenPen], eax
		invoke	   CreatePen, 0, 1,  $0000FF
		mov	   [RedPen], eax


		invoke	    SetTextColor, [TmpDC], $AAAAAA     ; ���� ������ �� ���������
		invoke	    SetBkColor,   [TmpDC], 0	       ; ׸���� ���� ���� ��� ������
		invoke	    GetStockObject, ANSI_VAR_FONT      ; ANSI_FIXED_FONT ;SYSTEM_FONT ;
		mov	    [hnewf], eax
		invoke	    SelectObject, [TmpDC], [hnewf]



		invoke SetTimer, [hwnd],  0, 200, 0		 ;������ ������
		ret ;jmp     .finish


