//https://github.com/xanthium-enterprises/Serial-Programming-Win32API-C

#include <Windows.h>
#include <stdio.h>

void main(void)
{
	HANDLE hComm;                          // Handle to the Serial port
	char  ComPortName[] = "COM9";		   // Name of the Serial port(May Change) to be opened,
	BOOL  Status;                          // Status of the various operations 
	DWORD dwEventMask;                     // Event mask to trigger
	unsigned char TempChar;                        // Temperory Character
	unsigned char SerialBuffer[256];               // Buffer Containing Rxed Data
	DWORD NoBytesRead;                     // Bytes read by ReadFile()
	unsigned int i = 0;
	unsigned int j = 0;

	printf("\n\n +==========================================+");
	printf("\n |    Serial Port  Reception (Win32 API)    |");
	printf("\n +==========================================+\n");
	/*---------------------------------- Opening the Serial Port -------------------------------------------*/

	hComm = CreateFile(ComPortName,                  // Name of the Port to be Opened
		GENERIC_READ | GENERIC_WRITE, // Read/Write Access
		0,                            // No Sharing, ports cant be shared
		NULL,                         // No Security
		OPEN_EXISTING,                // Open existing port only
		0,                            // Non Overlapped I/O
		NULL);                        // Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE)
		printf("\n    Error! - Port %s can't be opened\n", ComPortName);
	else
		printf("\n    Port %s Opened\n ", ComPortName);

	/*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/

	DCB dcbSerialParams = { 0 };                         // Initializing DCB structure
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	Status = GetCommState(hComm, &dcbSerialParams);      //retreives  the current settings

	if (Status == FALSE)
		printf("\n    Error! in GetCommState()");

	dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
	dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
	dcbSerialParams.Parity = NOPARITY;        // Setting Parity = None 

	Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB 

	if (Status == FALSE)
	{
		printf("\n    Error! in Setting DCB Structure");
	}
	else //If Successfull display the contents of the DCB Structure
	{
		printf("\n\n    Setting DCB Structure Successfull\n");
		printf("\n       Baudrate = %d", dcbSerialParams.BaudRate);
		printf("\n       ByteSize = %d", dcbSerialParams.ByteSize);
		printf("\n       StopBits = %d", dcbSerialParams.StopBits);
		printf("\n       Parity   = %d", dcbSerialParams.Parity);
	}

	/*------------------------------------ Setting Timeouts --------------------------------------------------*/

	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (SetCommTimeouts(hComm, &timeouts) == FALSE)
		printf("\n\n    Error! in Setting Time Outs");
	else
		printf("\n\n    Setting Serial Port Timeouts Successfull");

	/*------------------------------------ Setting Receive Mask ----------------------------------------------*/

	Status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception

	if (Status == FALSE)
		printf("\n\n    Error! in Setting CommMask");
	else
		printf("\n\n    Setting CommMask successfull");


	/*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/

	printf("\n\n    Waiting for Data Reception");

	
	
	SerialBuffer[0] = '\0';
	i = 0;
	Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received

	/*-------------------------- Program will Wait here till a Character is received ------------------------*/

	if (Status == FALSE)
	{
		printf("\n    Error! in Setting WaitCommEvent()");
	}
	else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
	{

		printf("\n\n    Characters Received");
		do
		{
			Status = ReadFile(hComm, &TempChar, 1, &NoBytesRead, NULL);
			SerialBuffer[i] = TempChar;
			i++;
		} while (NoBytesRead > 0);



		/*------------Printing the RXed String to Console----------------------*/

		printf("\n\n    ");
		for (j = 1; j < i - 1; j++)		// j < i-1 to remove the dupliated last character
			printf("%i", SerialBuffer[j]);

		
	}

	CloseHandle(hComm);//Closing the Serial Port
	printf("\n +==========================================+\n");
	_getch();
}//End of Main()
