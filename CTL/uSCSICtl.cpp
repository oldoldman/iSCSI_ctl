#include <iostream>
#include <windows.h>
#include <iomanip>
#include <stdlib.h>
#include <setupapi.h>
#include "public.h"

using namespace std;

void LastErr(LPCTSTR Prefix = NULL )
{	
	DWORD	Error = GetLastError();	
	LPVOID 	lpMsgBuf;

	FormatMessage( 
    	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
    	NULL,
    	Error,
    	MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), // Default language
    	(LPTSTR) &lpMsgBuf,
    	0,
    	NULL );

	cout << Prefix << " " << hex << showbase << Error << lpMsgBuf << endl;
	LocalFree( lpMsgBuf );
}

//
//
//

HANDLE OpenDevice()
{
	DWORD								bytes = 0, cnt = 0;
	HANDLE								file;
	HDEVINFO 							devinfo;
	SP_DEVINFO_DATA 					devinfodata;
	SP_DEVICE_INTERFACE_DATA 			devitfcdata;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	devitfcdatadtl;
	
	devinfo = SetupDiGetClassDevs(&USCSI_DISK_INTERFACE , 
									NULL , 
									NULL ,
									DIGCF_DEVICEINTERFACE| DIGCF_PRESENT);
	if ( INVALID_HANDLE_VALUE == devinfo )
	{
		LastErr("SetupDiGetClassDevs");
		return NULL;
	}
			
	devinfodata.cbSize = sizeof(devinfodata);
	devitfcdata.cbSize = sizeof(devitfcdata);
												
	while(SetupDiEnumDeviceInterfaces( devinfo , 
							NULL , 
							&USCSI_DISK_INTERFACE,
							cnt++,
							&devitfcdata))
	{
		DWORD required_size;
				
		SetupDiGetDeviceInterfaceDetail(devinfo,
										&devitfcdata,
										NULL,
										0,
										&required_size,
										NULL);
		devitfcdatadtl = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc (required_size);
		devitfcdatadtl->cbSize = sizeof (SP_DEVICE_INTERFACE_DETAIL_DATA);
		
		if(SetupDiGetDeviceInterfaceDetail(devinfo,
											&devitfcdata,
											devitfcdatadtl,
											required_size,
											&required_size,
											&devinfodata))
		{
			
			file = CreateFile( 
						devitfcdatadtl->DevicePath,
                        GENERIC_READ|GENERIC_WRITE, // Only read access
                        0, // FILE_SHARE_READ | FILE_SHARE_WRITE
                        NULL, // no SECURITY_ATTRIBUTES structure
                        OPEN_EXISTING, // No special create flags
                        0, // No special attributes
                        NULL);		
			
			free (devitfcdatadtl);
			
			if (INVALID_HANDLE_VALUE != file)
				return file;
			else
				LastErr("OpenDevice");
		}
		else
			LastErr("SetupDiGetDeviceInterfaceDetail");
	}

	return NULL;
}


VOID AddTarget( PUCHAR Target , ULONG IpAddr , USHORT Port )
{
	PTGTS	Tgts;
	PTGT	Tgt;
	ULONG	Size;
	HANDLE	Device;
	DWORD	Bytes;
	
	Size = strlen((char*)Target) + 1 + sizeof (TGTS) + sizeof (TGT);
	Tgts = (PTGTS)malloc ( Size );
	
	if ( Tgts )
	{
		Tgts->Count = 1;
		Tgts->Size = Size;
		
		Tgt = (PTGT)(Tgts + 1);
		Tgt->TargetName = (PUCHAR)( Tgt + 1 );
		
		strcpy ( (char*)Tgt->TargetName , (char*)Target );
		Tgt->Addr = IpAddr;
		Tgt->Port = Port;
		
		Device = OpenDevice();
	
		if (Device)
		{
			if(!DeviceIoControl( Device , 
   		             			 IOCTL_ISCSI_ADD_TARGETS ,               					
     		           			 Tgts,
       		         			 Size,
         		       			 NULL,
           		     			 0,
             		   			 &Bytes,
               		 			 NULL))
				LastErr("DeviceIoControl");
			else
				cout << "Target " << Tgt->TargetName << "@" << Tgt->Addr << ":" << Tgt->Port << " added" << endl;
		}
		else
			goto Out;
	}
	
Out:
	if ( Tgts )
		free ( Tgts );
	if ( Device )
		CloseHandle ( Device);
}

VOID GetTargets()
{
	TGTS	Tgts;
	PTGTS	Tgts2;
	PTGT	Tgt;
	HANDLE	Device;
	DWORD	Bytes;
	ULONG	i;
	
	Device = OpenDevice();
	
	if (Device)
	{
		while (TRUE)
		{
			Tgts.Size = 0;
		
			if(!DeviceIoControl( Device , 
   		             			 IOCTL_ISCSI_GET_TARGETS ,               					
     		           			 &Tgts,
       		         			 sizeof (TGTS),
         		       			 &Tgts,
           		     			 sizeof (TGTS),
             		   			 &Bytes,
               		 			 NULL))
            {
				LastErr("DeviceIoControl");
			}
			else if (!Tgts.Size)
				break;
			else
			{
				Tgts2 = (PTGTS)malloc ( Tgts.Size );
				Tgts2->Size = Tgts.Size;
				
				if(!DeviceIoControl( Device , 
   		             			 	 IOCTL_ISCSI_GET_TARGETS ,               					
     		           			 	 Tgts2,
       		         			 	 Tgts.Size,
         		       			 	 Tgts2,
           		     			 	 Tgts.Size,
             		   			 	 &Bytes,
               		 			 	 NULL))
               	{
               		LastErr("DeviceIoControl");
               	}
               	else
               	{
               		cout << "Target list : " << Tgts2->Count << endl;
               		
               		Tgt = (PTGT) ( Tgts2 + 1 );
               		for ( i = 0 ; i < Tgts2->Count ; i++ )
               		{
               			cout 
               			<< i << " "
               			<< ((char*)Tgts2 + Tgt->NameOffset ) 
               			<< " Ip " << (Tgt->Addr &0xFF) << "." 
               				     << ((Tgt->Addr &0xFF00 ) >> 8) << "." 
               				     << ((Tgt->Addr &0xFF0000)>>16) << "." 
               				     << ((Tgt->Addr &0xFF000000)>>24)
               			<< " Port " << ((Tgt->Port &0xFF) << 8 | (Tgt->Port &0xFF00) >> 8)
               			<< endl;
               			
               			Tgt++;
               		}
               		break;
               	}
               				
			}
		}		
	}
	
	if ( Tgts2 )
		free ( Tgts2 );
	if ( Device )
		CloseHandle ( Device);
}


VOID ConnectTarget( PUCHAR Target)
{
	HANDLE	Device;
	DWORD	Bytes;
	
	Device = OpenDevice();
	
	if (Device)
	{
		if(!DeviceIoControl( Device , 
                			 IOCTL_ISCSI_CREATE_SESSION ,               					
                			 Target,
                			 strlen ((char*)Target) + 1,
                			 NULL,
                			 0,
                			 &Bytes,
                			 NULL))
			LastErr("DeviceIoControl");
		else
			cout << "Disk OK" << endl;
	
		CloseHandle ( Device);
	}	
}

VOID Usage()
{
	cout << "uSCSICtl" << endl;
	cout << "-t TargetName IpAddr [Port]    : Add a Target" << endl;
	cout << "-l                             : List all Targets" << endl;
	cout << "-c Target                      : Connect to Target" << endl;
	exit(0);
}

#define INETADDR(a, b, c, d) (a | (b<<8) | (c<<16) | (d<<24))
#define HTONL(a) (((a&0xFF)<<24) | ((a&0xFF00)<<8) | ((a&0xFF0000)>>8) | ((a&0xFF000000)>>24)) 
#define HTONS(a) (((0xFF&a)<<8) | ((0xFF00&a)>>8))

BOOLEAN	ParseIpAddr( PUCHAR Addr , PULONG IpAddr)
{
	PUCHAR	Addr2;
	UCHAR	Comp = 4 , C , AddrComp[4];
	
	Addr2 = Addr;	
	
	while ( Comp-- >= 0 )
	{
		while ( C = *Addr2 , C != '.' && C != '\0' )
			Addr2++;
		
		if ( C == '.' )
			*Addr2++ = '\0';
		
		AddrComp[Comp] = (UCHAR)atoi ( (char*)Addr );
		Addr = Addr2;
		
		if ( C == '\0' )
			break;
	}
	
	if ( Comp > 0 )
		return FALSE;
	
	if ( IpAddr )
	{
		*IpAddr = INETADDR (AddrComp[3] , AddrComp[2] , AddrComp[1] , AddrComp[0] );
		return TRUE;
	}
	else
		return FALSE;
	
}

BOOLEAN	ParsePort( PUCHAR Port , PUSHORT Port2)
{
	USHORT	Port3;
	Port3 = (USHORT) atoi((char*)Port);
	if ( Port2 )
	{
		*Port2 = HTONS(Port3);
		return TRUE;
	}
	else
		return FALSE;
}

int __cdecl main(int argc , char * args[])
{
	PUCHAR		Target;
	ULONG		IpAddr;
	USHORT		Port;	
	UCHAR		Op;
	
	if ( argc < 2 )
		Usage();
	
	if ( argc == 5 )
	{
		if ( args[1][0] == '-' && args[1][1] == 't')
		{
			Op = 'T';
			Target = (PUCHAR)args[2];
			if ( !ParseIpAddr ( (PUCHAR)args[3] , &IpAddr ) || 
				 !ParsePort ( (PUCHAR)args[4] , &Port) )
				Usage();
		}
		
	}
	else if ( argc == 4 )
	{
		if ( args[1][0] == '-' && args[1][1] == 't')
		{
			Op = 'T';
			Target = (PUCHAR)args[2];
			if ( !ParseIpAddr ( (PUCHAR)args[3] , &IpAddr ))
				Usage();
			Port = HTONS( 3260 );
		}		
	}
	else if ( argc == 3)
	{
		if ( args[1][0] == '-' && args[1][1] == 'c')
		{
			Op = 'C';
			Target = (PUCHAR)args[2];
		}		
	}
	else if ( argc == 2 )
	{
		if ( args[1][0] == '-' && args[1][1] == 'l')
			Op = 'L';
	}
	else
		Usage();
		
	switch ( Op )
	{
		case 'L':
			GetTargets();
			break;
		case 'T':
			AddTarget( Target , IpAddr , Port );
			break;
		case 'C':
			ConnectTarget ( Target );
			break;
	}
	
	return 0;
}	
