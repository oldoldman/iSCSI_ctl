
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void usage()
{
	printf("wt:\n");
	printf(" wt sourcefile\n");
	exit(0);
}

unsigned char buf[512];

int __cdecl main ( int argc , char * args[])
{
	HANDLE 	dest , source;
	char 	*src_file;
	int 	src_len , totalr = 0 , totalw = 0;
	DWORD	bytes;
	
	if ( argc != 2 )
		usage();
	
	dest = CreateFile ( "\\\\?\\E:\\Test_file" , 
						GENERIC_WRITE ,
						0 ,
						NULL ,
						CREATE_ALWAYS , 
						FILE_ATTRIBUTE_NORMAL|FILE_FLAG_WRITE_THROUGH , 
						NULL);
	
	src_len = strlen( args[1]);
	src_file = malloc ( src_len + 4 );
	wsprintf( src_file , "\\\\?\\%s" , args[1]);
	printf("Copy %s ...\n" , src_file);
						
	source = CreateFile ( src_file , 
						  GENERIC_READ ,
						  0 ,
						  NULL ,
						  OPEN_EXISTING , 
						  FILE_ATTRIBUTE_NORMAL|FILE_FLAG_NO_BUFFERING , 
						  NULL );
											
	while(TRUE)
	{
		ReadFile ( source , buf , 512 , &bytes , NULL );
		if ( bytes )
		{
			totalr += bytes;
			printf ("read %d bytes\n" , bytes );
			WriteFile( dest , buf , bytes , &bytes , NULL);
			totalw += bytes;
			printf ("write %d bytes\n" , bytes );
		}
		else
			break;
	}
	printf("total read : %d , total write : %d\n" , totalr , totalw);
	CloseHandle ( source );
	CloseHandle ( dest );
}