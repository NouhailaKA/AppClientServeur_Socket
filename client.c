#include<io.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include<winsock2.h>

typedef struct {
	char login[30];
	char mdp[30];
	char profil[30];
}compte;

void Identification(SOCKET s){
	     
	    char message[2000],reponse[100];
	    int m = recv(s , message , 2000 , 0);
	    message[m] = '\0'; 
		
		compte c;
	    int size;
		
		if((size = recv(s , message , 2000 , 0)) == SOCKET_ERROR)
		    puts("recv failed");
	     

	    message[size] = '\0';   // Ajouter '\0' pour marquer la chaine 
		puts(message);	

	    do{
        
        printf("\n    S'il vous palait saisir votre login:");
        scanf("%s",c.login);
        printf("\n    S'il vous plait saisir votre password:");
        scanf("%s",c.mdp);
        
        strcat(strcat(c.login, "#"),c.mdp);
	    send(s , c.login , 100 , 0);
	    
		size = recv(s , reponse , 2000 , 0);
	    reponse[size]='\0';
	    
 		      
	   }while(strcmp(reponse,"admin")!=0 || strcmp(reponse,"invite")!=0); 
}


typedef struct {
	char rue[30];
	char ville[30];
	char pays[30];
}adresse;


typedef struct {
    char nom[30];
    char prenom[30];
    char GSM[30];
    char email[50];
    adresse *adr;
}contact;



contact SaisirClient(SOCKET s){

	contact c; 
	int t;
    char nom[30],prenom[30],GSM[30],email[50],rue[30],ville[30],pays[30];

    c.adr=(adresse*)malloc(sizeof(adresse));	
		 
	t = recv(s , nom , 30 , 0);
	nom[t] = '\0'; 
	scanf("%s",c.nom);
	send(s , c.nom , 30 , 0);
	

	t = recv(s , prenom , 30 , 0);
	prenom[t] = '\0'; 
	scanf("%s",c.prenom);
	send(s , c.prenom , 30 , 0);
	

	t = recv(s , GSM , 30 , 0);
	GSM[t] = '\0'; 
	scanf("%s",c.GSM);
	send(s , c.GSM , 30 , 0);
	
	t = recv(s , email , 30 , 0);
	email[t] = '\0'; 
	scanf("%s",c.email);
	send(s , c.email , 30 , 0);
	
	
	t = recv(s , rue , 30 , 0);
	rue[t] = '\0'; 
	scanf("%s",c.adr->rue);
	send(s , c.adr->rue , 30 , 0);
	
	t = recv(s , ville , 30 , 0);
	ville[t] = '\0'; 
	scanf("%s",c.adr->ville);
	send(s , c.adr->ville , 30 , 0);

	t = recv(s , pays , 30 , 0);
	pays[t] = '\0'; 
	scanf("%s",c.adr->pays);
	send(s , c.adr->pays , 30 , 0);
	
    return c;
}

void Ajouter_Contact(SOCKET s){
	
	char *msg;
	int size;
	
	msg=(char*)malloc(sizeof(char)*100);

	contact c = SaisirClient(s);

	size=recv(s , msg , 100 , 0);
	msg[size]='\0';
	puts(msg);
}

void Afficher_Tous(SOCKET s){
	
    char *msg;
	int size;
    
    while(recv(s , msg , 2000 , 0)!=0)
	{
		size=recv(s , msg , 2000 , 0);
	    msg[size]='\0';
	    puts(msg);
	}
}

void Recherche_Contact(SOCKET s){

 contact c; 
 char *nom=(char*)malloc(sizeof(char)*30);
 char *cont=(char*)malloc(sizeof(char)*30);
 char *resultat=(char*)malloc(sizeof(char)*30);
 int t;
 
	t = recv(s , nom , 30 , 0);
	nom[t] = '\0';
	puts(nom); 
	scanf("%s",cont);
	send(s,cont,30,0);
      

	t = recv(s , resultat , 30 , 0);
	resultat[t] = '\0';
	puts(resultat); 
    	
}

void Supprimer(SOCKET s){

 contact c;
 c.adr=(adresse*)malloc(sizeof(adresse)); 
 char *nom= (char*)malloc(sizeof(char)*30);
 char *cont =(char*)malloc(sizeof(char)*30);
 char *resultat=(char*)malloc(sizeof(char)*100);
 int t;
 
	t = recv(s , nom , 30 , 0);
	nom[t] = '\0';
	puts(nom); 
	
	scanf("%s",cont);
	send(s,cont,30,0);
      

	t = recv(s , resultat , 2000 , 0);
	resultat[t] = '\0';
	puts(resultat); 
    	
}

void Modifier(SOCKET s){
	 contact c;
     c.adr=(adresse*)malloc(sizeof(adresse)); 
     char *nom= (char*)malloc(sizeof(char)*30);
     char *cont =(char*)malloc(sizeof(char)*30);
     char *resultat=(char*)malloc(sizeof(char)*100);
     int t;
 
	t = recv(s , nom , 30 , 0);
	nom[t] = '\0';
	puts(nom); 
	
	scanf("%s",cont);
	send(s,cont,30,0);
      
	Ajouter_Contact(s); 
}

void menuAdmin(SOCKET s){	
	int c;
	char *menu=(char*)malloc(sizeof(char)*2000);
	char *choix=(char*)malloc(sizeof(char)*10);
	char *erreur=(char*)malloc(sizeof(char)*50);
	do{	
	c = recv(s , menu , 2000 , 0);
	menu[c] = '\0';
	puts(menu); 
	
	scanf("%s",choix);
	send(s,choix,4,0);
	switch (*choix){	
		case '1':
			Ajouter_Contact(s);
			break;
		case'2':
		    Recherche_Contact(s);
			break;
		case'3':
		    Supprimer(s);
			break;
		case'4':
		    Modifier(s);
			break;
		case'5':
		    Afficher_Tous(s);
			break;
		case'6':					
			break;
		default:
		    c = recv(s , erreur , 2000 , 0);
	        erreur[c] = '\0';
			puts(erreur); 
			break;	
	}
	}while(*choix !='6');	
}

void menuInvite(SOCKET s){
	
	int c;
	char *menu=(char*)malloc(sizeof(char)*2000);
	char *choix=(char*)malloc(sizeof(char)*10);
	char *erreur=(char*)malloc(sizeof(char)*50);
	
	do{	

	c = recv(s , menu , 2000 , 0);
	menu[c] = '\0';
	puts(menu); 
	
	scanf("%s",choix);
	send(s,choix,4,0);
	
	switch (*choix){
		case '1':
			Ajouter_Contact(s);
			break;
		case'2':
		    Afficher_Tous(s);
			break;
		case'3':
			break;
		default:
		    c = recv(s , menu , 2000 , 0);
	        menu[c] = '\0';
			puts(menu); 
			break;		
	}
	}while(*choix!='3');	
}

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char server_reply[2000],profil[20];
	int recv_size;


// Initialising Winsock...

	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}


// Créer un socket (Function socket() creates a socket and returns a socket descriptor)

   if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)  // Address Family : AF_INET (this is IP version 4),Type : SOCK_STREAM (this means connection oriented TCP protocol,Protocol : 0 [ or IPPROTO_TCP , IPPROTO_UDP ]
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}


//	create a sockaddr_in structure / server Socket address

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 23 );
	

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}


	//Recevoir message Bienvenue
    
    	char message[2000],reponse[100];
	    int m = recv(s , message , 2000 , 0);
	    message[m] = '\0'; 
        puts(message);
		
		compte c;
	    int size;
			

	    do{
        
        printf("\n    S'il vous plait saisir votre login:");
        scanf("%s",c.login);
        printf("\n    S'il vous plait saisir votre password:");
        scanf("%s",c.mdp);
        
        strcat(strcat(c.login, "#"),c.mdp);
	    send(s , c.login , 100 , 0);
	    
	    if((size = recv(s , reponse , 2000 , 0))!= 1)
	    {
	    	reponse[size]='\0';
		    puts("");
	    }
 		      
	   }while(strcmp(reponse,"0")==0); 
	


// recevoir profil	
	size=recv(s,profil,20,0);
	profil[size]='\0';
	
	if(strcmp(profil,"admin")==0)
	   menuAdmin(s);
	else
	   menuInvite(s);  		

	closesocket(s); //close the socket
    WSACleanup();	//unload the winsock library (ws2_32.dll)

	return 0;
}
