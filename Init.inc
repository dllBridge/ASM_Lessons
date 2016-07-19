

;=======================================================================================

; Template for program using standard Win32 headers

  format PE GUI 4.0
  entry start

  include 'win32w.inc'

  section '.data' data readable writeable

  ;--------------------------------  My DATA  -----------------------------------------
  ;Заголовок и текст окошка О программе
  AboutCaption db 'About ASM_Lessons...', 0
  AboutText db 'The template for the first steps in programming ', 13, 10
            db 'and the basis for your long-term projects.', 13, 10, 13, 10
            db 'Rev: 0.32   16 July 2016', 13, 10
            db 'Email: dllBridge@gmail.com', 13, 10
            db 'www.a_1a.livejournal.com', 0

  PustayaSTR dB '                                                                      ',0
 ; lpStr   dd  0

  Transit dd 1000 dup(0)         ; Массив Transit для работы с dllBridge

  xMove   dd  0
  yMove   dd  0
  ZX      dd  0

  Timer_CLK dd 0


  hnewf    dd ?                  ;Дескриптор шрифта:

  BlackPen dd ?                  ;Дескрипторы карандашей:
  WhitePen dd ?
  GreenPen dd ?
  RedPen dd ?

;  ps          PAINTSTRUCT <?>
  PaintStruct PAINTSTRUCT  ?    ;Переменая для обработки сообщений прорисовки.
  TmpDC dd                 ?    ;Дескриптор временного холста
  TmpBmp dd                ?    ;Дескриптор отведённой памяти под него
  TmpRect RECT             ?    ;Квадратная область... Юзается при рисовании...
  hStatusBar dd            ?    ;Дескриптор строки состояния
  StatusBarParts dd 220, 440, -1;Массив расположения разделителей в строке состояния
  CharBuf_x  db 100 dup(0)
  UniMons    db 'UniMons.exe', 0
  SBScoreLab db '  Timer_CLK =              ', 0
  Mouse_X_Y  db '  Mouse: X =                    ', 0
  Mouse_Y    db ', Y =        ',0
  intmask    db    '%d ',0          ;Маска для перевода числа в строку, для wsprintf
  WordMask   db    '%s ',0
  E_mail     db    '   E-mail: dllBridge@gmail.com',0
  ; MesWindowLen    =   20 ; $-MesWindow
  ;------------------------------------------------------------------------------------

  _class TCHAR 'FASMWIN32',0
  _title TCHAR ' ASM_Lessons',0
  _error TCHAR 'Startup failed.',0

  wc WNDCLASS 0,WindowProc,0,0,NULL,NULL,NULL,7,303,_class    ; COLOR_BTNFACE+1

  msg MSG

  section '.idata' import data readable writeable

  library kernel32,'KERNEL32.DLL',user32,'USER32.DLL',gdi32,'GDI32.DLL',\
          comdlg, 'COMDLG32.DLL',\
          comctl, 'COMCTL32.DLL',\
          dllBridge,'kkldll.dll'

  include 'api\kernel32.inc'
  include 'api\user32.inc'
  include 'api\gdi32.inc'

  import comdlg,\
         GetOpenFileName, 'GetOpenFileNameA',\
         GetSaveFileName, 'GetSaveFileNameA'

  import comctl,\
         CreateStatusWindow, 'CreateStatusWindowA'

  import  dllBridge,\
          __Transit,'__Transit'

  include 'wiq_1.inc'
  include 'wiq_2.inc'
  include 'Menu.inc'


;----------------------------------------------------- 
; Функция быстрого копирования участка памяти 
;----------------------------------------------------- 
; lpDst - указатель на приемник 
; lpSrc - указатель на источник 
; dSize - размер копируемого блока 
;----------------------------------------------------- 
proc    _memcopy lpDst:DWORD, lpSrc:DWORD, dSize:DWORD 
        pusha
        cld     ; Установить указатели на источник и приемник
        mov     edi,[lpDst] 
        mov     esi,[lpSrc]
        mov     ecx,[dSize] 
        push    ecx
        shr     ecx,2  ; Разделить на 4 и получить длину в DWORD
        rep     movsd  ; Скопировать основную часть строки DWORD'ами
        pop     ecx
        and     ecx,3  ; Получить остаток от деления на 4
        rep     movsb   ; Скопировать остаток строки байтами
        popa 
        ret 
endp
;-----------------------------------------------------
; Функция получения длины строки 
;----------------------------------------------------- 
; lpStr - указатель на строку ASCIIZ 
; На выходе: EAX - длина строки без учета завершающего 
; нулевого байта 
;----------------------------------------------------- 
proc   _lstrlen  lpStr:DWORD
        push     edi ecx
        cld 
        mov      edi,[lpStr]
        xor      ecx,ecx
        dec      ecx
        xor      eax,eax
        repne    scasb
        not      ecx
        dec      ecx
        mov      eax,ecx
        pop      ecx edi
        ret 
endp
;----------------------------------------------------- 
; Функция быстрого копирования строки 
; используются функции _lstrlen, _memcopy 
;----------------------------------------------------- 
; lpDst - указатель на приемник 
; lpSrc - указатель на строку ASCIIZ 
;----------------------------------------------------- 
proc    _lstrcpy lpDst:DWORD, lpSrc:DWORD 
        pusha
        stdcall _lstrlen,[lpSrc] 
        inc     eax 
        stdcall _memcopy,[lpDst],[lpSrc],eax
        popa 
        ret 
endp
;----------------------------------------------------- 
; Функция быстрого слияния двух строк 
; используются функции _lstrlen, _lstrcpy 
;----------------------------------------------------- 
; lpDst - указатель на исходную строку ASCIIZ 
; lpSrc - указатель на добавляемую строку ASCIIZ 
;----------------------------------------------------- 
proc    _lstrcat lpDst:DWORD, lpSrc:DWORD 
        pusha
        stdcall _lstrlen,[lpDst] 
        add     eax,[lpDst]
        stdcall _lstrcpy,eax,[lpSrc]
        popa 
        ret 
endp 






             
