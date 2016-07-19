

proc WindowProc uses ebx esi edi, hwnd,wmsg,wparam,lparam

local	 @@hdc:DWORD

		mov	edx, [wmsg]
		cmp	edx, WM_CREATE
		jz	.wmCreate
		cmp	edx, WM_TIMER
		jz	.wmTimer
		cmp	edx, WM_COMMAND
		jz	.wmCommand
		cmp	edx, WM_MOUSEMOVE
		jz	.wmMousemove
		cmp	edx, WM_PAINT
		jz	.wmPaint
		cmp	edx, WM_DESTROY
		jz	.wmdestroy

  .defwndproc:	invoke	DefWindowProc,[hwnd],[wmsg],[wparam],[lparam]
		ret

    .wmCreate:	include 'WM_Creat.inc'


     .wmTimer:	invoke	wsprintfA, SBScoreLab + 14, intmask, [Timer_CLK]
		invoke	SendMessage, [hStatusBar], SB_SETTEXT, 1, SBScoreLab

		inc	[Timer_CLK]
		cmp	[Timer_CLK], 1
		jnz	.L_01
		call	INIT
     .L_01:	call	START
		invoke	 __Transit, 3, Transit
		invoke	 InvalidateRect, [hwnd], 0, 0	;���������� ������� ���� ��������������...
		ret
 ;-------------------------------------------------------
		;	��������� ������� �� ����
		;----------------------------------------
 .wmCommand:	mov	dl, byte [wparam]
		cmp	dl, 1
		jnz	.L_04
		invoke	WinExec, UniMons, 1

      .L_04:	cmp	dl, 20
		jnz	.L_05
		invoke	MessageBoxA, [hwnd], AboutText, AboutCaption, MB_ICONINFORMATION

      .L_05:	ret


		;������� ����� ���� � ���������..
 ; .cmdAbout:	 invoke MessageBoxA, [hwnd], AboutText, AboutCaption, MB_ICONINFORMATION
 ;		 ret
 ; ------------------------------------------------------

 .wmMousemove:	mov	eax, [lparam]	 ; �������� ������� �����
		shl	eax, 16 	 ; ������� �������� ����� �� 16 bit
		shr	eax, 16 	 ; � ����� ������� (������) �� 16 bit
		mov	[xMove], eax	 ; ����� ���� ������� � ������� 16 bit �������� ������ ����
		mov	eax, [lparam]	 ; ������ �������� ������� �����...
		shr	eax, 16 	 ; ������ ���� ��� �������� ������ �� 16 bit
		mov	[yMove], eax	 ; ���������� Y ������ - ����� 16 bit �������� ���� ����    Mouse_Y
		invoke	wsprintfA, Mouse_X_Y + 14, intmask, [xMove]
		invoke	wsprintfA, Mouse_Y + 6, intmask, [yMove]
		ccall	_lstrcat,  Mouse_X_Y, Mouse_Y
		invoke	SendMessage, [hStatusBar], SB_SETTEXT, 2, Mouse_X_Y
		ret
 ; ------------------------------------------------------

  .wmPaint:	; invoke  TextOut,[TmpDC] , 130, 200 ,_error, 15	 ;  [TmpDC]	 'ASSA_SONY_�����'

		invoke	BeginPaint, [hwnd], PaintStruct   ; ps
				     ; 720, 480
		invoke	BitBlt,   eax, 0, 0, 608, 486, [TmpDC], 0, 0, SRCCOPY
		invoke	EndPaint, [hwnd], PaintStruct	;   ps
		ret
 ; ------------------------------------------------------

  .wmdestroy:
		invoke DeleteObject, [hnewf]		;  ������� ��� �������� �����
		invoke DeleteObject, [TmpDC]
		invoke DeleteObject, [TmpBmp]
		invoke DeleteObject, [BlackPen]
		invoke DeleteObject, [WhitePen]
		invoke DeleteObject, [GreenPen]
		invoke DeleteObject, [RedPen]

		invoke	PostQuitMessage,0
		xor	eax,eax
  .finish:	ret

endp







































 ; CreateStatusBar hwnd  ;�������� ������ ���������...