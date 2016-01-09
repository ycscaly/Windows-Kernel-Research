#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <ntddk.h>



typedef struct Segment_Descriptor_x64 {
	
	UINT64 limit16 : 16,
		baseAddress24 : 24,
		segmentType : 4,
		isCodeDataDescriptor : 1, //1 means descriptor of a code/data segment, 0 means system
		descriptorPrivilegeLevel : 2,
		present : 1,
		limit20 : 4,
		available : 1,
		is64BitCodeSegment : 1,
		defaultOpeartionSize : 1, //0 = 16bit segment, 1 = 32bit
		granularity : 1,
		baseAddress32 : 8;
		
} x64SegmentDescriptor, *Px64SegmentDescriptor;

#pragma pack(push)
#pragma pack(1)
typedef struct Global_Descriptor_Table_Register_x64 {
	UINT16 limit;
	x64SegmentDescriptor *globalDescriptorTable;
} x64GlobalDescriptorTableRegister, *Px64GlobalDescriptorTableRegister;
#pragma pack(pop)

typedef struct Gate_Descriptor_x64 {
	UINT32 offsetInSegment16 : 16,
		segmentSelector : 16;
	UINT32 :8,
		typeA : 4,
		: 1,
		DPL : 2,
		P : 1,
		offsetInSegment32 : 16;

	UINT32 offsetInSegment64;
	UINT32:8,
	   typeB : 6;

} x64GateDescriptor, *Px64GateDescriptor;

typedef struct Segment_Register {
	UINT16 requistedPrivilegeLevel : 2,
		tableIndicator : 1,
		index : 13;
} SegmentRegister, *PSegmentRegister;



extern UINT16 getCodeSegmentRegister();
extern UINT16 getStackSegmentRegister();
extern UINT16 getDataSegmentRegister();
extern UINT16 getESSegmentRegister();
extern UINT16 getFSSegmentRegister();
extern UINT16 getGSSegmentRegister();

extern void getGlobalDescriptorTableRegister(UINT64 pGDTR);

void PrintSegmentsDetails();

#endif