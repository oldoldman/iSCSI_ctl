
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void usage()
{
	printf("Comp:\n");
	printf(" Comp file1 file2\n");
	exit(0);
}

void LastErr()
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

	printf("(0x%X)%s" , Error , lpMsgBuf);
	LocalFree( lpMsgBuf );
}

unsigned char buf1[512];
unsigned char buf2[512];

int __cdecl main ( int argc , char * args[])
{
	HANDLE	file1 , file2;
	int 	i , j , k ;
	DWORD	bytes , pos = 0x10;
	
	file1 = CreateFile ( "\\\\?\\D:\\d1.img" , 
						GENERIC_READ ,
						FILE_SHARE_READ|FILE_SHARE_WRITE	,
						NULL ,
						OPEN_EXISTING , 
						FILE_ATTRIBUTE_NORMAL , 
						NULL);
	if (file1 == INVALID_HANDLE_VALUE)
	{
		printf("open d1.img failed\n");
		LastErr();
		exit(0);
	}
	
	file2 = CreateFile ( "\\\\?\\D:\\d2.img" , 
						GENERIC_READ ,
						FILE_SHARE_READ|FILE_SHARE_WRITE	,
						NULL ,
						OPEN_EXISTING , 
						FILE_ATTRIBUTE_NORMAL , 
						NULL);
	
	if (file2 == INVALID_HANDLE_VALUE)
	{
		printf("open d2.img failed\n");
		LastErr();
		exit(0);
	}
	while (TRUE)
	{
		ReadFile ( file1 , buf1 , 512 , &bytes , NULL );
		ReadFile ( file2 , buf2 , 512 , &bytes , NULL );

		if ( !bytes )
			break;
			
		for ( i = 0 ; i < (int)bytes ; i++ )
		{
			if ( buf1[i] != buf2[i] )
			{
				printf ("Start: 0x%X +0x%X\n" , ((pos + i) & ~0xF)>>4 ,  (pos + i) & 0xF);
				
				for ( j = i; j < (int)bytes ; j++ )
				 if ( buf1[j] == buf2[j] )
				 	break;
				 	
				for ( k =i ; k < j ; k++ )
					printf ("%02X " , buf1[k]);
				
				for ( k =i ; k < j ; k++ )
					printf ("%C" ,  buf1[k]>=0x20 && buf1[k]<=0x7E ?buf1[k]:'.');
					
				printf("\n");
				
				for ( k =i ; k < j ; k++ )
					printf ("%02X " , buf2[k]);	
				for ( k =i ; k < j ; k++ )
					printf ("%C" ,  buf2[k]>=0x20 && buf2[k]<=0x7E ?buf2[k]:'.');
				printf("\n");
				
				i = j;				
			}	
		}
		pos += bytes;
	}
	
	CloseHandle (file1);
	CloseHandle (file2);
}