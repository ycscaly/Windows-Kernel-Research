#include <Segmentation.h>
void PrintSegmentRegisterValues(UINT16 cs, UINT16 ss, UINT16 ds,
	UINT16 es, UINT16 fs, UINT16 gs);

void PrintSegmentDescriptors(UINT16 cs, UINT16 ss, UINT16 ds,
	UINT16 es, UINT16 fs, UINT16 gs);

void PrintSegmentDescriptor(x64SegmentDescriptor segmentDescriptor);
void PrintParsedSegmentRegister(SegmentRegister segmentRegister);
void PrintGlobalDescriptorTable();

SegmentRegister ParseSegmentRegister(UINT16 segmentRegisterValue);
x64SegmentDescriptor GetSegmentDescriptor(SegmentRegister segmentRegister);

x64GlobalDescriptorTableRegister globalDescriptorTableRegister;
void initGlobalDescriptorTableRegister();


void PrintSegmentsDetails() {
	UINT16 cs, ds, ss, es, fs, gs;

	DbgBreakPoint();

	initGlobalDescriptorTableRegister();
	
	cs = getCodeSegmentRegister();
	ss = getStackSegmentRegister();
	ds = getDataSegmentRegister();
	es = getESSegmentRegister();
	fs = getFSSegmentRegister();
	gs = getGSSegmentRegister();


	PrintSegmentRegisterValues(cs, ss, ds, es, fs, gs);
	PrintSegmentDescriptors(cs, ss, ds, es, fs, gs);
	
	DbgBreakPoint();

	DbgPrint("Done printing segment registers information\n\n\n now printing all descriptors in GDT \n");

	PrintGlobalDescriptorTable();

	DbgPrint("Done printing segment information\n\n\n");
}

void PrintSegmentRegisterValues(UINT16 cs, UINT16 ss, UINT16 ds, 
	UINT16 es, UINT16 fs, UINT16 gs) 
{
	DbgPrint("The code segment register value is: %x\n", cs);
	DbgPrint("The stack segment register value is: %x\n", ss);
	DbgPrint("The data segment register value is: %x\n", ds);
	DbgPrint("The es segment register value is: %x\n", es);
	DbgPrint("The fs segment register value is: %x\n", fs);
	DbgPrint("The gs segment register value is: %x\n", gs);
}

void PrintSegmentDescriptor(x64SegmentDescriptor segmentDescriptor) {
	UINT64 baseAddress = segmentDescriptor.baseAddress24 +
		(segmentDescriptor.baseAddress32 << 24);

	UINT64 limit = segmentDescriptor.limit16 +
		(segmentDescriptor.limit20 << 16);
	
	DbgPrint("A segment descriptor with base address: %x and limit: %x\n ", baseAddress, limit);
	
	DbgPrint("Describing a %s, %s segment\n ", 
		segmentDescriptor.is64BitCodeSegment? "64-bit code":"(non 64-bit code)",
		segmentDescriptor.isCodeDataDescriptor? "code or data": "system" );

	DbgPrint("with privilege level (DPL) %d and type %d\n ",
		segmentDescriptor.descriptorPrivilegeLevel,
		segmentDescriptor.segmentType);

}

x64SegmentDescriptor GetSegmentDescriptor(SegmentRegister segmentRegister)
{
	return globalDescriptorTableRegister.globalDescriptorTable[segmentRegister.index];
}

SegmentRegister ParseSegmentRegister(UINT16 segmentRegisterValue) {
	PSegmentRegister pSegmentRegister = (PSegmentRegister) &segmentRegisterValue;
	return *pSegmentRegister;
}


void PrintSegmentDescriptors(UINT16 cs, UINT16 ss, UINT16 ds,
	UINT16 es, UINT16 fs, UINT16 gs) {

	x64SegmentDescriptor csDescriptor, ssDescriptor, dsDescriptor,
		esDescriptor, fsDescriptor, gsDescriptor;

	csDescriptor = GetSegmentDescriptor(ParseSegmentRegister(cs));
	ssDescriptor = GetSegmentDescriptor(ParseSegmentRegister(ss));
	dsDescriptor = GetSegmentDescriptor(ParseSegmentRegister(ds));
	esDescriptor = GetSegmentDescriptor(ParseSegmentRegister(es));
	fsDescriptor = GetSegmentDescriptor(ParseSegmentRegister(fs));
	gsDescriptor = GetSegmentDescriptor(ParseSegmentRegister(gs));

	DbgPrint("Printing code segment information...\n\n");
	PrintSegmentDescriptor(csDescriptor);

	DbgPrint("Printing stack segment information...\n\n");
	PrintSegmentDescriptor(ssDescriptor);

	DbgPrint("Printing data segment information...\n\n");
	PrintSegmentDescriptor(dsDescriptor);

	DbgPrint("Printing fs segment information...\n\n");
	PrintSegmentDescriptor(fsDescriptor);

	DbgPrint("Printing gs segment information...\n\n");
	PrintSegmentDescriptor(gsDescriptor);

	DbgPrint("Printing es segment information...\n\n");
	PrintSegmentDescriptor(esDescriptor);

}


void PrintGlobalDescriptorTable() {
	
	DbgPrint("The global descriptor table is at address: %016llX with limit: %d\n", globalDescriptorTableRegister.globalDescriptorTable, globalDescriptorTableRegister.limit);
	
	for(UINT16 i = 0; i < ((globalDescriptorTableRegister.limit + 1) / sizeof(x64SegmentDescriptor)); i++) {
		x64SegmentDescriptor currentSegmetDescriptor = globalDescriptorTableRegister.globalDescriptorTable[i];

		if (currentSegmetDescriptor.present == 0)
			DbgPrint("Empty (unpresent) Descriptor at index %d\n", i);
		else {
			DbgPrint("Printing Descriptor at index %d\n", i);
			PrintSegmentDescriptor(currentSegmetDescriptor);
		}
		DbgPrint("\n");
	}
}

void initGlobalDescriptorTableRegister() {
	getGlobalDescriptorTableRegister((UINT64)&globalDescriptorTableRegister);
}