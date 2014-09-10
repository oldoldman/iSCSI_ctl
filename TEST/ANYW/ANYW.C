
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE	1024

unsigned char *buf;

void Write(int count , int bsize)
{
	int 	i , j;
	DWORD	bytes;
	HANDLE	file;
	
	file = CreateFile ( "\\\\?\\E:\\Test_file" , 
						GENERIC_WRITE ,
						0 ,
						NULL ,
						CREATE_ALWAYS , 
						FILE_ATTRIBUTE_NORMAL|FILE_FLAG_WRITE_THROUGH , 
						NULL);
	
	for ( i = 0 ; i < count ; i++ )
	{
		for ( j = 0 ; j < bsize ; j++ )
			buf[j] = i & 0xFF ;
			
		WriteFile ( file , 
					buf,
					bsize,
					&bytes,
					NULL );
					
		printf("Pass %d write %d bytes\n" , i , bytes );
	}
	
	CloseHandle (file);
}

void Read( int count , int bsize)
{
	int 	i , j;
	DWORD	bytes;
	HANDLE	file;
	
	file = CreateFile ( "\\\\?\\E:\\Test_file" , 
						GENERIC_READ ,
						0 ,
						NULL ,
						OPEN_EXISTING , 
						FILE_ATTRIBUTE_NORMAL|FILE_FLAG_NO_BUFFERING , 
						NULL);
						
	for ( i = 0 ; i < count ; i++ )
	{
		 ReadFile ( file , 
					buf,
					bsize,
					&bytes,
					NULL );
					
		printf("Pass %d read %d bytes\n" , i , bytes );			
		
		for ( j = 0 ; j < (int)bytes ; j++ )
		{
			if ( j && !(j & 0xf) )
				printf("\n");
			printf("%02X " , buf[j] );			
		}	
		printf("\n");
					
	}
}

void usage()
{
	printf("Test:\n");
	printf(" Test -[r|w] -b size -c count\n");
	exit(0);
}

int __cdecl main ( int argc , char * args[])
{
	unsigned char Op;
	int i , count , bufsize;
	
	if ( argc != 6 )
		usage();
	
	for ( i = 1 ; i < 6 ; i++ )
	{
		if (args[i][0] == '-' && args[i][1] == 'r' )
			Op = 'R';
		else if ( args[i][0] == '-' && args[i][1] == 'w')
			Op = 'W';
		else if ( args[i][0] == '-' && args[i][1] == 'b' )
			bufsize = atoi(args[++i]);
		else if (args[i][0] == '-' && args[i][1] == 'c' )
			count = atoi( args[++i] );
		else
			usage();
	}
	
	if ( !bufsize || !count)
		usage();
	
	buf = malloc (bufsize);
	
	if (Op == 'R')
		Read(count , bufsize);
	else if ( Op == 'W')
		Write(count , bufsize);
	else
		usage();
}