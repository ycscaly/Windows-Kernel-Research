#include <ntddk.h>
#include <Segmentation.h>


NTSTATUS DriverEntry(
	IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath
	)
{
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	DbgPrint("Kernel Research Entry Point; J.C. In!\n");
	
	PrintSegmentsDetails();

	return STATUS_SUCCESS;
}
