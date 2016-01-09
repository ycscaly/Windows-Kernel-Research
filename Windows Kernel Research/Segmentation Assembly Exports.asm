.data
.code

PUBLIC getCodeSegmentRegister
getCodeSegmentRegister PROC

mov		ax, cs
ret

getCodeSegmentRegister ENDP


getStackSegmentRegister PROC

mov		ax, ss
ret

getStackSegmentRegister ENDP


getDataSegmentRegister PROC

mov		ax, ds
ret

getDataSegmentRegister ENDP


getESSegmentRegister PROC

mov		ax, es
ret

getESSegmentRegister ENDP


getFSSegmentRegister PROC

mov		ax, fs
ret

getFSSegmentRegister ENDP


getGSSegmentRegister PROC

mov		ax, gs
ret

getGSSegmentRegister ENDP



getGlobalDescriptorTableRegister PROC 

sgdt [rcx]
ret

getGlobalDescriptorTableRegister ENDP

END
