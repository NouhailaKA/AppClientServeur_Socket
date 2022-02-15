
/***********************  Nom et Prénom: KARIMALLAH Nouhaila                **********************            Filière GI1            *****************************************/

/********************************************************************** Application Serveur **********************************************************************************/
#include<stdio.h>
#include<winsock2.h>
#include<string.h>

/**************************************************************************** S'identifier ***********************************************************************************/

typedef struct {
	char login[30];
	int mdp;
	char profil[30];
}compte;

char *Identification(SOCKET s){
	    
		send(s , "********************BIENVENUE*****************************\n\n    RQ: vous avez le droit d'entrer comme -ADMIN ou INVITE seulement :)" , 2000 , 0);
		
		compte c;
	    int trouve=0;
	    int passwd;
	    char *login,CH[2];	
	    int m ,i, j;
	    char *fichier="comptes.txt";
	    FILE *f=fopen(fichier,"r");
	    
	    
	    login=(char*)malloc(sizeof(char)*100);
	    
	    do{
        
        if((m = recv(s , login , 100 , 0)) == SOCKET_ERROR)
		{ puts("Erreur finction recv() ");
        }
		  
		login[m] = '\0'; 
	    printf("authentification#%s",login);
		   
		
        i=0;
        
		for(j=0;j<2;j++){ 
           while (login[i] != '#' && login[i])
            {
             strcpy(CH[j],login+i);  
	       }
	         puts(CH[j]);
	    }
     
	    
//	    char *p = (char*)malloc(sizeof(char)*100);
//		
//		p=strtok(login, "#");
//	    
//        while(p != NULL)
//       { for(i=0;i<2;i++){
//       	  CH[i]=p;
//         p = strtok(NULL, "#"); }
//        }

        i=0;
	    
	  	if(f!=NULL)
	
		while(!feof(f))
		{ 	
			fscanf(f,"%s %d %s \n",c.login,&c.mdp,c.profil);
		    if(strcmp(c.login,CH[0])==0 && c.mdp==CH[1])
		   { trouve=1; break;}
		}
		fclose(f);
		
		if(trouve==1){
		printf("Trouve !!!");
		send (s, c.profil, 50,0 );	
		return &c.profil;			
		}else {
		send(s,"0",100,0);
	     i++;}
	
	    if(i=2){
	    	send(s,"\n Vous avez dépacer le nombre de tentative \n",50,0);
	    	closesocket(s);
		}      
	   }while(i<3); 
	   
	   return NULL;
}

/************************************************************************ Ajouter Contact ***********************************************************************************/

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



contact SaisirServeur(SOCKET s){
	
	contact c; 
	int t;
	c.adr=(adresse*)malloc(sizeof(adresse));
	 
	send(s , "\n Donner le nom du contact:" , 100 , 0);
	t = recv(s , c.nom , 30 , 0);
	c.nom[t] = '\0'; 
	puts(c.nom);
	
	send(s , "\n Donner le prenom du contact:" , 100 , 0);
	t = recv(s , c.prenom , 30 , 0);
	c.prenom[t] = '\0'; 
	puts(c.prenom);

	send(s , "\n Donner le GSM:" , 100 , 0);
	t = recv(s , c.GSM , 30 , 0);
	c.GSM[t] = '\0'; 
	puts(c.GSM);

	send(s , "\n Donner l'email':" , 100 , 0);
	t = recv(s , c.email , 50 , 0);
	c.email[t] = '\0'; 
	puts(c.email);
	
	send(s , "\n Saisi l'adresse:\n\n veuillez entrer le nom de la rue :" , 100 , 0);
	t = recv(s , c.adr->rue , 30 , 0);
	c.adr->rue[t] = '\0'; 
	puts(c.adr->rue);

	send(s , "\n veuillez entrer la ville du contact :" , 100 , 0);
	t = recv(s , c.adr->ville , 30 , 0);
	c.adr->ville[t] = '\0'; 
	puts(c.adr->ville);

	send(s , "\n veuillez entrer la pays du contact :" , 100 , 0);
	t = recv(s , c.adr->pays , 30 , 0);
	c.adr->pays[t] = '\0'; 
	puts(c.adr->pays);
	
    return c;
}




void Ajouter_Contact(SOCKET s){
	char *nom_fich="contacts.txt";
	FILE *f=fopen(nom_fich,"a");
	contact c = SaisirServeur(s);
	if(f!=NULL){
		fprintf(f,"%s %s %ld %s %s %s %s \n",c.nom,c.prenom,c.GSM,c.email,c.adr->rue,c.adr->ville,c.adr->pays);
	}
	fclose(f);
	send(s , "\n Ajout avec succes:" , 100 , 0);
}



/***************************************************************************** Afficher Contact **********************************************************************************/


void Afficher_Contact(contact c, SOCKET s){
	
 strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(c.nom,"#"),c.prenom),"#"),c.email),"#"),c.GSM),"#"),c.adr->rue),"#"),c.adr->ville),"#"),c.adr->pays);
 
 send(s,c.nom,2000,0);

}

void Afficher_Tous(SOCKET s){
	
 FILE *f=fopen("contacts.txt","r");
 contact c;
   c.adr=(adresse*)malloc(sizeof(adresse));
   
	if(f!=NULL){
		while(!feof(f))
		{ 	
			fscanf(f,"%s %s %ld %s %s %s %s \n",c.nom,c.prenom,c.GSM,c.email,c.adr->rue,c.adr->ville,c.adr->pays);
		    Afficher_Contact(c,s);	 
		}

    fclose(f);	
}
}

/************************************************************************  Recherche contact  ********************************************************************************/

void Recherche_Contact(SOCKET s){
	
 FILE *f=fopen("contacts","r");
 contact c; 
 char *nom=(char*)malloc(sizeof(char)*30);
 int t;
 
 c.adr==(adresse*)malloc(sizeof(adresse));
 
 send(s , "\n Donner le nom du contact:" , 100 , 0);
	t = recv(s , nom , 30 , 0);
	nom[t] = '\0'; 
	printf("Recherche Contact: %s",nom);
      

 int trouve=0;
	if(f!=NULL){
	
		while(!feof(f))
		{ 	
			fscanf(f,"%s %s %ld %s %s %s %s \n",c.nom,c.prenom,c.GSM,c.email,c.adr->rue,c.adr->ville,c.adr->pays);
		  if(strcmp(c.nom,nom))
		   { trouve=1; break;}
			 
		}
		fclose(f);
		if(trouve==0)
		send(s," \n Contact introuvable \n ",50,0);
		else {
		Afficher_Contact(c,s);
          }
        	
}
}

/*************************************************************************** Supprimer contact ********************************************************************************/

void Supprimer_Contact(SOCKET s){
 FILE *fin=fopen("contacts.txt","r");
 char *nom_res="temp.txt";
 FILE *fout=fopen(s,"w");
 contact c; 
 c.adr = (adresse*)malloc(sizeof(adresse));
 char *nom = (char*)malloc(sizeof(char)*30);
 int t; 
 
    send(s , "\n Donner le nom du contact:" , 100 , 0);
	t = recv(s , nom , 30 , 0);
	nom[t] = '\0'; 
	scanf("Recherche Contact: %s",nom);
      

	if(fin!=NULL&&fout!=NULL){
	
		while(!feof(fin))
		{ 	
			fscanf(fin,"%s %s %ld %s %s %s %s \n",c.nom,c.prenom,c.GSM,c.email,c.adr->rue,c.adr->ville,c.adr->pays);
		  if(strcmp(c.nom,nom)!=0)
		   	fprintf(fout,"%s %s %ld %s %s %s %s \n",c.nom,c.prenom,c.GSM,c.email,c.adr->rue,c.adr->ville,c.adr->pays);
           if(strcmp(c.nom,nom)==0)
           send(s," Contact Supprime ",30,0);
			 
		}
		fclose(fin);
		fclose(fout);
		remove("contacts.txt");
		rename(nom_res,"contact.txt");
		
          }
    	
}

/**************************************************************************** Modifier contact ***********************************************************************************/

void Modifier_Contact(SOCKET s){
	
 FILE *fin=fopen("contacts.txt","r");
 char *nom_res="temp.txt";
 FILE *fout=fopen(s,"w");
 contact c; 
 char *nom = (char*)malloc(sizeof(char)*30);
  int t; 
 c.adr = (adresse*)malloc(sizeof(adresse));

 
    send(s , "\n Donner le nom du contact:" , 100 , 0);
	t = recv(s , nom , 30 , 0);
	nom[t] = '\0'; 
	printf("Recherche Contact: %s",nom);
      

	if(fin!=NULL&&fout!=NULL){
	
		while(!feof(fin))
		{ 	
			fscanf(fin,"%s %s %ld %s %s %s %s \n",c.nom,c.prenom,c.GSM,c.email,c.adr->rue,c.adr->ville,c.adr->pays);
		  if(strcmp(c.nom,nom)!=0)
		   	fprintf(fout,"%s %s %ld %s %s %s %s \n",c.nom,c.prenom,c.GSM,c.email,c.adr->rue,c.adr->ville,c.adr->pays);
           if(strcmp(c.nom,nom)==0)
            {c=SaisirServeur(s);
             fprintf(fout,"%s %s %ld %s %s %s %s \n",c.nom,c.prenom,c.GSM,c.email,c.adr->rue,c.adr->ville,c.adr->pays);
             send(s , "\n contact modifie :" , 100 , 0);
			}
			 
		}
		fclose(fin);
		fclose(fout);
		remove("contacts.txt");
		rename(nom_res,"contact.txt");
		
          }
    	
}

/**************************************************************************** Menus ***********************************************************************************/

void menuAdmin(SOCKET s){
	
	int c;
	char *choix;
	
	do{	
	send(s,"\n       -----------------------------VOUS ETES ADMINISTRATEUR------------------------------\n\n       ***************************************Menu*****************************************\n\n\n\n\n       1-Ajouter un contact\n       2-Recherche un contact\n       3-Supprimer un contact\n       4-Modifier un contact\n       5-Afficher tous les contacts\n       6-Quitter\n\n\n\nEntrer votre choix:",2000,0);
	
	c = recv(s , choix , 1 , 0);
	choix[c] = '\0'; 
	
	switch (*choix){
		
		case '1':
			Ajouter_Contact(s);
			break;
		case'2':
		    Recherche_Contact(s);
			break;
		case'3':
		    Supprimer_Contact(s);
			break;
		case'4':
		    Modifier_Contact(s);
			break;
		case'5':
		    Afficher_Tous(s);
			break;
		case'6':					
			break;
		default:
		    send(s,"Choix invalid essayez encore une fois",50,0);
			break;	
	}
	}while(choix!='6');	
}

void menuInvite(SOCKET s){
	
	int c;
	char *choix;
	
	do{	
	send(s,"\n       -----------------------------VOUS ETES UTILISATEUR------------------------------\n\n       ***************************************Menu*****************************************\n\n\n\n\n       1-Recherche un contact\n       2-Afficher tous les contacts\n       3-Quitter\n\n\n\nEntrer votre choix:",2000,0);
	
	c = recv(s , choix , 1 , 0);
	choix[c] = '\0'; 
	
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
		    send(s,"Choix invalid essayez encore une fois",50,0);
			break;	
	}
	}while(choix!='3');	
}


/**************************************************************************** Main ***********************************************************************************/


int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET serv_socket , client_socket;
	struct sockaddr_in server , client;
	int c;
	char *profil;

//  Initialisation de Winsock...

	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Erreur d'initialisation Code : %d",WSAGetLastError());
		return 1;
	}

//  Creér a socket


	if((serv_socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("erreur creation Socket : %d" , WSAGetLastError());
	}
	
	puts("Le socket 208 est maintenant ouverte en mode TCP/IP");


// Preparer la structure sockaddr_in 

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 23 );       // port de connexion

     // Bind

	if( bind(serv_socket ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Erreur Bind()  : %d" , WSAGetLastError());
	}
     
    puts("------>Listage du port 23..."); 
    

	//Pret à se connecter avec maximum 3 machines
	listen(serv_socket , 3);


	//Attendre la connexion
	puts("------>Patientez pendant que le client se connecte sur le port 23...");

	c = sizeof(struct sockaddr_in);
	


	while(( client_socket = accept(serv_socket , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
	{
		puts("Un client se connecte avec le socket :) ");

		//Communication avec client

        profil= (char*)malloc(sizeof(char)*100);
        profil = Identification(client_socket); 
		 
        
        if(strcmp(*profil,"admin")==0){
        	menuAdmin(client_socket);	
		}
		
		if(strcmp(*profil,"utilisateur")==0){
			menuInvite(client_socket);	
		}
	}


	if (client_socket == INVALID_SOCKET)
	{
		printf("Erreur accept() code : %d" , WSAGetLastError());
		return 1;
	}


	closesocket(serv_socket);
	WSACleanup();


	return 0;
}
