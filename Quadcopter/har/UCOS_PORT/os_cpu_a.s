		IMPORT  OSRunning
        IMPORT  OSPrioCur
        IMPORT  OSPrioHighRdy
        IMPORT  OSTCBCur
        IMPORT  OSTCBHighRdy
        IMPORT  OSIntNesting
        IMPORT  OSIntExit
        IMPORT  OSTaskSwHook
           
        EXPORT  OSStartHighRdy               
        EXPORT  OSCtxSw
        EXPORT  OSIntCtxSw
		EXPORT  OS_CPU_SR_Save
    	EXPORT  OS_CPU_SR_Restore       
        EXPORT  PendSV_Handler
        	
NVIC_INT_CTRL   	EQU     0xE000ED04  ; 中断控制寄存器
NVIC_SYSPRI2    	EQU     0xE000ED22  ; 系统优先级寄存器(2)
NVIC_PENDSV_PRI 	EQU         0xFFFF  ; PendSV中断和系统节拍中断
                                        ; (都为最低，0xff).
NVIC_PENDSVSET  	EQU     0x10000000  ; 触发软件中断的值.


		PRESERVE8 
		
		AREA    |.text|, CODE, READONLY
        THUMB 

OS_CPU_SR_Save
    MRS     R0, PRIMASK  	;读取PRIMASK到R0,R0为返回值 
    CPSID   I				;PRIMASK=1,关中断(NMI和硬件FAULT可以响应)
    BX      LR			    ;返回

OS_CPU_SR_Restore
    MSR     PRIMASK, R0	   	;读取R0到PRIMASK中,R0为参数
    BX      LR				;返回		

OSStartHighRdy
        LDR     R4, =NVIC_SYSPRI2      ; 设置pendsv中断优先级
        LDR     R5, =NVIC_PENDSV_PRI
        STR     R5, [R4]

        MOV     R4, #0                 ; 将PSP置0表示是第一次触发调度
        MSR     PSP, R4

        LDR     R4, =OSRunning         ; OSRunning = TRUE
        MOV     R5, #1
        STRB    R5, [R4]

                                       ;切换到最高优先级的任务
        LDR     R4, =NVIC_INT_CTRL     ;调用pendsv中断，进行上下文切换
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]

        CPSIE   I                      ;使能中断，一般不会运行到这里，运行到这里了就是出错了
OSStartHang
        B       OSStartHang            ;无线循环，防止函数出错时出问题
	
OSCtxSw
		PUSH    {R4, R5}
        LDR     R4, =NVIC_INT_CTRL  	;触发PendSV异常 (causes context switch)
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]
		POP     {R4, R5}
        BX      LR

OSIntCtxSw
		PUSH    {R4, R5}
        LDR     R4, =NVIC_INT_CTRL      ;触发PendSV异常 (causes context switch)
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]
		POP     {R4, R5}
        BX      LR
        NOP

PendSV_Handler
    CPSID   I                                                   ; 防止上下文切换被打断
    MRS     R0, PSP                                             ; 指示第一次调度
    CBZ     R0, PendSV_Handler_nosave		                    ; 第一次调度没有上文
	
	;检查FPU的使用
	TST 	R14, #0x10
	IT 		EQ
	VSTMDBEQ R0!, {S16-S31} 
	
    SUBS    R0, R0, #0x20                                       ; 保存r4-r11
    STM     R0, {R4-R11}

    LDR     R1, =OSTCBCur                                       ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R1, [R1]
    STR     R0, [R1]                                            ; R0是上文的堆栈指针

                                                                ; 保存上文完成
PendSV_Handler_nosave
    PUSH    {R14}                                               ; 保存pc，这里压lr入栈
    LDR     R0, =OSTaskSwHook                                   ; OSTaskSwHook();
    BLX     R0
    POP     {R14} 

    LDR     R0, =OSPrioCur                                      ; OSPrioCur = OSPrioHighRdy;
    LDR     R1, =OSPrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0, =OSTCBCur                                       ; OSTCBCur  = OSTCBHighRdy;
    LDR     R1, =OSTCBHighRdy
    LDR     R2, [R1]
    STR     R2, [R0]

    LDR     R0, [R2]                                            ; r0是下文的堆栈指针 SP = OSTCBHighRdy->OSTCBStkPtr;
    LDM     R0, {R4-R11}                                        ; 获取下文的寄存器r4-r11
    ADDS    R0, R0, #0x20

	;检查FPU的使用
	TST 	R14, #0x10
	IT 		EQ
	VLDMIAEQ R0!, {S16-S31} 
		
	MSR     PSP, R0                                             ; 将下文的堆栈指针给psp
    ORR     LR, LR, #0x04                                       ; 保证跳转后使用线程栈
    CPSIE   I
    BX      LR                                                  ; 自动出栈其他的寄存器
    nop
	end  
