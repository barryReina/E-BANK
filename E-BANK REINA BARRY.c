#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//***************PROJET E-BANK REINA BARRY ******************//
//definition du type booleen
typedef enum{
	false,
	true
}Bool;

//definition de la structure compte
typedef struct {
	char nom [50];
	char prenom[50];
	char cin [50];
	char mot_de_passe [50];
	double solde ;
}Compte;

//definition du type noeud pour la liste chainee
typedef struct Noeud{
	Compte val;
	struct Noeud * suiv;
}Noeud, *Liste;

//definition du 2 noeud pour la pile
typedef struct Noeud2{
	char val [256];
	struct Noeud2 * suiv;
}Noeud2, *Pile;

//******************Implementation apres la fonction main**************
//Taches de l'application bancaire
void interface_accueil();
void menu_compte();
void creer_nouveau_compte();
void sauvegarder_compte();
void ouvrir_compte_existant();
void mise_a_jour_information_compte_existant();
void changer_mot_de_passe();
void supprimer_compte();
void afficher_details_compte_existant();
void afficher_liste_clients();
void effectuer_une_transaction_bancaire();
void depot();
void retrait();
void paiement_factures();
void transfert_entre_comptes_existants();
void assistance_clientele();
void services_offerts();
void politique_banque();
void horaires_banque();
void afficher_historique();
void sauvegarder_historique();
void gestion_de_pret();
void recuperer_compte_supprime();
void afficher_comptes_supprimes();

//liste chainee procedures et fonctions
Liste nouvelle_liste();
int longueur_liste();
Bool est_vide_liste();
void inserer_debut();
void retirer_debut();
void retirer_fin();
void inserer_fin();

//fichiers
void sauvegarder_compte();
void sauvegarder_historique();

//pile procedures et fonctions
Pile nouvelle_pile();
Bool est_vide_pile();
void empiler();
void depiler();

//************************************************************
//************************************************************
int main(int argc, char *argv[]) {
	
	//ouvrir l'interface de l'application e-bank
	interface_accueil();		
	
	return 0;
}


//liste chainee implementation
Liste nouvelle_liste(void){
	return NULL;
}
Bool est_vide_liste(Liste L){
	return(L==NULL);
}
int longueur_liste(Liste L){
	int longueur=0;
	if (!est_vide_liste(L)){
		while(L!=NULL){
			longueur++;
			L=L->suiv;
		};
	};
	return longueur;
}
void inserer_debut(Liste * L,Compte x){
	Noeud * aux;
	aux=malloc(sizeof(*aux));
	aux->val=x;
	aux->suiv=*L;
	*L=aux;
}
void retirer_debut(Liste * L,Compte * x){
	if(*L!=NULL){
		Liste aux;
		aux=*L;
		*x=aux->val;
		*L=(*L)->suiv;
		free(aux);
	};
}
void inserer_fin(Liste * L,Compte x){
	Noeud * aux;
	aux=malloc(sizeof(*aux));
	aux->val=x;	
	if(est_vide_liste(*L)){
		aux->suiv=*L;
		*L=aux;
	}
	else{
	    Noeud *p ;
	    p=*L;
	    while(p->suiv!=NULL){
		p=p->suiv;
	};
	p->suiv=aux;
	aux->suiv=NULL;
};
}
void retirer_fin(Liste * L,Compte * x){
	if(!est_vide_liste(*L)){
		if(longueur_liste(*L)==1){
			retirer_debut(L,x);
		}
		else{
			Liste p,aux;
			p=*L;
			aux=(*L)->suiv;
			while(aux->suiv!=NULL){
				aux=aux->suiv;
				p=p->suiv;
			};
			*x=aux->val;
			p->suiv=NULL;
			free(aux);
		};
	};
}

//pile implementation
Pile nouvelle_pile(void){
	return NULL;
}
Bool est_vide_pile(Pile P){
	return(P==NULL);
}
void empiler(Pile * P,char x [256]){
	Noeud2 * aux;
	aux=malloc(sizeof(*aux));
	strcpy(aux->val,x);
	aux->suiv=*P;
	*P=aux;
}
void depiler(Pile * P,char x [256]){
	if(P!=NULL){
		Pile aux;
		aux=*P;
		strcpy(x,aux->val);
		*P=(*P)->suiv;
		free(aux);
	};
}




//taches application implementation


void interface_accueil(){
	//creation du fichier listeClients si il n'existe pas
	FILE * fic1;
	if(fopen("./listeClients.txt","r")==NULL){
		fic1=fopen("./listeClients.txt","w");
		fclose(fic1);
	};
	
	//interface
	printf("--------------------E-BANK------------------------\n");
	printf("**************************************************\n");
	printf("ACCUEIL\n");
	printf("--------------------------------------------------\n");
	printf("UTILISATEUR\n");
	printf("-----------------------------\n");
	printf("1.creer un nouveau compte\n");
	printf("2.se connecter a un compte existant\n");
	printf("3.recuperer un compte supprime\n");
	printf("4.afficher la liste des clients\n");
	printf("5.afficher la liste des comptes supprimes\n");
	printf("6.quitter l'application bancaire\n");
	
	//traitement du choix de l'utilisateur
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 : creer_nouveau_compte();break;
		case 2 : ouvrir_compte_existant();break;
		case 3 : recuperer_compte_supprime();break;
		case 4 : afficher_liste_clients();break;
		case 5 : afficher_comptes_supprimes();break;
		case 6 : exit(1);break;
		default: interface_accueil();
	};
}

void menu_compte(Compte c){
	printf("\nBIENVENU(E) SUR VOTRE COMPTE BANCAIRE\n");
	printf("------------------------------------------------------\n");
	printf("1.afficher les details du compte\n");
	printf("2.effectuer une transaction bancaire\n");
	printf("3.historique des transactions bancaires\n");
	printf("4.paiement des factures\n");
	printf("5.changer votre mot de passe \n");
	printf("6.supprimer le compte\n");
	printf("7.pret bancaire\n");
	printf("8.assistance clientele\n");
	printf("9.retour a l'interface d'accueil\n");
	printf("10.quitter l'application bancaire\n");
	
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1  : afficher_details_compte_existant(c);break;
		case 2  : effectuer_une_transaction_bancaire(&c);break;
		case 3  : afficher_historique(c);break;
		case 4  : paiement_factures(&c);break;
		case 5  : changer_mot_de_passe(&c);break;
		case 6  : supprimer_compte(c); break;
		case 7  : gestion_de_pret(&c);break;
		case 8  : assistance_clientele(c); break;
		case 9  : interface_accueil();break;
		case 10 : exit(1);break;
		default : printf("choix invalide\nREESSAYER\n");menu_compte(c);	
	}
}

void creer_nouveau_compte(){
	Compte c;
	char fichier[100];
	printf("\nremplir les informations du nouveau compte \n");
	printf("\tnom= ");
	scanf("%s",c.nom);
	printf("\tprenom= ");
	scanf("%s",&(c.prenom));
	printf("\tcin= ");
	scanf("%s",&(c.cin));
	getchar();
	printf("\tmot de passe= ");
	gets(c.mot_de_passe);
	c.solde=0;
    
    //creation du fichier historique du compte avec sa creation
	snprintf(fichier,sizeof fichier,"./historique_de_%s_%s.txt",c.nom,c.prenom);
	FILE * fic2 = fopen(fichier,"w");	
	fclose(fic2);
	
	printf("nouveau compte cree avec succes\n");
	
	//sauvegarder le  compte dans la base
	sauvegarder_compte(c);
	
	//redirection au menu du compte apres sa creation
	menu_compte(c);
}

void sauvegarder_compte(Compte c){
	FILE * fic1=fopen("./listeClients.txt","a");
	if(fic1==NULL){
		printf("impossible de sauvegarder le compte car fichier non cree\n");
	}
	else
	{
	fprintf(fic1,"%s %s %s %s %.2f\n",c.nom,c.prenom,c.cin,c.mot_de_passe,c.solde);
	printf("fichier sauvegarde avec succes \n");
    };
    fclose(fic1);
}

void ouvrir_compte_existant(){
	//informations entrees par le client
	char cin_x [50],mot_de_passe_x [100];
	printf("\nSE CONNECTER\n");
	printf("-------------------------------------------------\n");
	printf("DONNEES DE CONNEXION\n");
	printf("\tcin = ");
	scanf("%s",cin_x);
	getchar();
	printf("\tmot de passe= ");
	gets(mot_de_passe_x);
	//verifications des informations du client
	char chaine [256];
	Bool trouve=false;
	Compte c;
	FILE * fic1 =fopen("./listeClients.txt","r");
	fscanf(fic1,"%s %s %s %s %lf",c.nom,c.prenom,c.cin,c.mot_de_passe,&c.solde);
	if(strcmp(c.cin,cin_x)==0 && strcmp(c.mot_de_passe,mot_de_passe_x)==0){
		trouve=true;
	};
	while((fgets(chaine,256,fic1))!=NULL && !trouve){
		fscanf(fic1,"%s %s %s %s %lf",c.nom,c.prenom,c.cin,c.mot_de_passe,&c.solde);
		if(strcmp(c.cin,cin_x)==0 && strcmp(c.mot_de_passe,mot_de_passe_x)==0){
		   trouve=true;
	    };
	};
	if(trouve==true){
		menu_compte(c);//ouvrir le compte si informations correctes
	}
	else{
		printf("compte inexistant\n");
		printf("\n");
		printf("ENTRER \n");
		printf("--------------------------------------------\n");
		printf("1.essayer de nouveau\n");
		printf("2.retour a l'interface d'accueil\n");
		printf("3.quitter l'application bancaire\n");
	    int choix;
	    do{
	      printf("\nchoix= ");
	      scanf("%d",&choix);
	     }
	    while(choix!=1 && choix!=2 && choix!=3);
	    switch(choix){
		  case 1 : ouvrir_compte_existant();break;
		  case 2 : interface_accueil();break;
		  case 3 : exit(1);break;
	    };};
	fclose(fic1);
}

/*la procedure retrait sera utilisee pour les operations
  de retrait ,de paiement de factures et de remboursement
  bancaire. b==1:retrait,b==2:factures,b==3: remboursement
  
  la variable typeR pour preciser le nom de la facture pour
  enregistrer dans l'historique des transactions.
*/
void retrait(Compte * c,int b,char typeR [50]){
	double somme;
	if(b==1){
		printf("RETRAIT D'ARGENT\n");
	    printf("---------------\n");
	}
	else if(b==2){
		printf("PAIEMENT FACTURE %s\n",typeR);
	    printf("---------------\n");
	}else if(b==3){
		printf("REMBOURSEMENT DE PRET \n");
	    printf("---------------\n");
	};
	printf("montant= ");
	scanf("%lf",&somme);
	if(c->solde < somme){
		printf("solde insuffisant \n");menu_compte(*c);
	}
	else{
	c->solde=c->solde-somme;
	if(b==1){
		printf("retrait effectue avec succes \n");
	}
	else if(b==2){
		printf("facture payee avec succes\n");
	}
	else if(b==3){
		printf(" pret rembourse avec succes\n");
	};
	mise_a_jour_information_compte_existant(*c);
	printf("informations du compte mises a jour\n");
	if(b==1){
		char trans [100]="retrait d'argent";
	    sauvegarder_historique(*c,trans,somme);
	}
	else if(b==2){
		char trans [100]="paiement facture ";
		strcat(trans,typeR);
	    sauvegarder_historique(*c,trans,somme);
	}
	else if(b==3){
		char trans [100]="remboursement pret";
	    sauvegarder_historique(*c,trans,somme);
	};
	menu_compte(*c);
   };
}

/* la procedure depot sera utilise pour les operations de depot
et d'encaissement de pret bancaire b==1:depot,b==2:encaissement
de pret*/
void depot(Compte * c,int b){
	double somme;
	if(b==1){
		printf("DEPOT D'ARGENT\n");
	}
	else if(b==2){
		printf("OCTROI D'UN PRET\n");
	}
	printf("---------------\n");
	printf("montant= ");
	scanf("%lf",&somme);
	c->solde=c->solde+somme;
	if(b==1){
		printf("depot effectue avec succes\n");
		char trans [100]="depot d'argent";
	    sauvegarder_historique(*c,trans,somme);
	}
	else if(b==2){
		printf("felicitations votre demande de pret est accepte\n");
		char trans [100]="pret octroyee";
	    sauvegarder_historique(*c,trans,somme);
	};
	mise_a_jour_information_compte_existant(*c);
	printf("informations du compte mises a jour\n");
	menu_compte(*c);
}
void transfert_entre_comptes_existants(Compte * c1){
	double somme;
	Bool trouve=false;
	Compte c3,c2;
	char cin_x [50];
	printf("RETRAIT D'ARGENT\n");
	printf("---------------\n");
	
	// le cin du compte a transferer afin de l'identifier
	//dans la base et effectuer les modifications.
	printf("cin du compte a transferer= ");
	scanf("%s",cin_x);
	getchar();
	char chaine [256];
    FILE * fic1 = fopen("./listeClients.txt","r");
	fscanf(fic1,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
	if(strcmp(cin_x,c2.cin)==0){
		strcpy(c3.mot_de_passe,c2.mot_de_passe);
		strcpy(c3.nom,c2.nom);
		strcpy(c3.prenom,c2.prenom);
		strcpy(c3.cin,c2.cin);
	    c3.solde=c2.solde;
	    trouve=true;
	};
	while((fgets(chaine,256,fic1))!=NULL && !trouve){
		fscanf(fic1,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
	    if(strcmp(cin_x,c2.cin)==0){
	        strcpy(c3.mot_de_passe,c2.mot_de_passe);
		    strcpy(c3.nom,c2.nom);
		    strcpy(c3.prenom,c2.prenom);
		    strcpy(c3.cin,c2.cin);
	        c3.solde=c2.solde;
	    	trouve=true;
		};
	};
	fclose(fic1);
	
	printf("montant= ");
	scanf("%lf",&somme);
	if(c1->solde < somme){
		printf("solde insuffisant\n");
	}
	else {
	c1->solde=c1->solde-somme;
	c3.solde=c3.solde+somme;
	printf("transfert effectue avec succes \n");
	mise_a_jour_information_compte_existant(*c1);
	mise_a_jour_information_compte_existant(c3);
	printf("informations des comptes mises a jour\n");
	char trans1 [100]="transfert d'argent emis";
	char trans2 [100]="transfert d'argent recu";
	sauvegarder_historique(*c1,trans1,somme);
	sauvegarder_historique(c3,trans2,somme);
	};
	menu_compte(*c1);//retour au menu apres la transaction
}

void changer_mot_de_passe(Compte * c){
	char code [50],code2 [50];
	printf("CHANGEMENT MOT DE PASSE\n");
	printf("---------------------\n");
	printf("entrer votre ancien mot de passe= ");
	gets(code);
	while(strcmp(c->mot_de_passe,code)!=0){
		printf("mot de passe incorrect \n");
		printf("inserer de nouveau =");
		gets(code);
	};
	printf("entrer votre nouveau mot de passe= ");
	gets(code);
	printf("repeter votre nouveau mot de passe= ");
	gets(code2);
	while(strcmp(code,code2)!=0){
		printf("nouveaux mot de passe different\n");
		printf("entrer votre ancien mot de passe= ");
	    gets(code);
	    while(strcmp(code,c->mot_de_passe)!=0){
		   printf("\nmot de passe incorrect \n");
		   printf("inserer de nouveau =");
		   gets(code);
	    };
	    printf("entrer votre nouveau mot de passe= ");
	    gets(code);
	    printf("repeter votre nouveau mot de passe= ");
	    gets(code2);
	};
	strcpy(c->mot_de_passe,code2);
	printf("\nmot de passe modifie avec succes \n");
	mise_a_jour_information_compte_existant(*c);
	printf("mot de passe mise a jour\n");
	menu_compte(*c);
}

/*apres chaque transaction ,mettre a jour le compte 
dans la base dont le fichier listeClients*/
void mise_a_jour_information_compte_existant(Compte c){
	FILE * fic1;
	Compte c2;
	char chaine [256];
	Liste L=nouvelle_liste();
	/*on utilise une liste chainee pour stocker temporairement
	les comptes y compris le compte mis a jour puis de les
	reinserer dans le fichier des comptes*/
    fic1 = fopen("./listeClients.txt","r");
	fscanf(fic1,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
	if(strcmp(c.nom,c2.nom)==0 && strcmp(c.prenom,c2.prenom)==0 && strcmp(c.cin,c2.cin)==0){
		strcpy(c2.mot_de_passe,c.mot_de_passe);
	    c2.solde=c.solde;
	};
	inserer_debut(&L,c2);
	while((fgets(chaine,256,fic1))!=NULL){
		fscanf(fic1,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
	    if(strcmp(c.nom,c2.nom)==0 && strcmp(c.prenom,c2.prenom)==0 && strcmp(c.cin,c2.cin)==0){
	    	strcpy(c2.mot_de_passe,c.mot_de_passe);
	    	c2.solde=c.solde;
		};
		if(strcmp(c2.cin,(L->val).cin)!=0){
		  inserer_debut(&L,c2);
		};
	};
	fclose(fic1);
	fic1 = fopen("./listeClients.txt","w");
	while(L!=NULL){
		retirer_fin(&L,&c2);
		fprintf(fic1,"%s %s %s %s %.2f\n",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,c2.solde);
	};
	fclose(fic1);
}

/*effacer le compte et retourne a l'interface d'accueil*/
void supprimer_compte(Compte c){
	FILE * fic3;
	if(fopen("./corbeille.txt","r")==NULL){
		fic3=fopen("./corbeille.txt","w");
		fclose(fic3);
	};
	fic3=fopen("./corbeille.txt","a");
	fprintf(fic3,"%s %s %s %s %.2f\n",c.nom,c.prenom,c.cin,c.mot_de_passe,c.solde);
	fclose(fic3);
	printf("SUPPRESSION DU COMPTE\n");
	printf("-------------------------------------------\n");
	Compte c2;
	char chaine [256],c3[50];
	Liste L=nouvelle_liste();
    FILE * fic1 = fopen("./listeClients.txt","r");
	fscanf(fic1,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
	if(strcmp(c.cin,c2.cin)!=0){
		inserer_debut(&L,c2);
	};
	strcpy(c3,c2.cin);
	while((fgets(chaine,256,fic1))!=NULL){
		fscanf(fic1,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
	    if(strcmp(c.cin,c2.cin)!=0 && strcmp(c2.cin,c3)!=0){
		    inserer_debut(&L,c2);
		};
		strcpy(c3,c2.cin);
	};
	fclose(fic1);
	fic1 = fopen("./listeClients.txt","w");
	while(L!=NULL){
		retirer_fin(&L,&c2);
		fprintf(fic1,"%s %s %s %s %.2f\n",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,c2.solde);
	};
	printf("compte supprime avec succes \n");
	printf("corbeille mis a jour \n");
	fclose(fic1);
	interface_accueil();
}
void supprimer_compte_corbeille(Compte c){
	Compte c2;
	char chaine [256],c3[50];
	Liste L=nouvelle_liste();
    FILE * fic3 = fopen("./corbeille.txt","r");
	fscanf(fic3,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
	if(strcmp(c.cin,c2.cin)!=0){
		inserer_debut(&L,c2);
	};
	strcpy(c3,c2.cin);
	while((fgets(chaine,256,fic3))!=NULL){
		fscanf(fic3,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
	    if(strcmp(c.cin,c2.cin)!=0 && strcmp(c2.cin,c3)!=0){
		    inserer_debut(&L,c2);
		};
		strcpy(c3,c2.cin);
	};
	fclose(fic3);
	fic3 = fopen("./corbeille.txt","w");
	while(L!=NULL){
		retirer_fin(&L,&c2);
		fprintf(fic3,"%s %s %s %s %.2f\n",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,c2.solde);
	};
	printf("corbeille mis a jour \n");
	fclose(fic3);
}

void effectuer_une_transaction_bancaire(Compte * c){
	printf("TRANSACTION BANCAIRE\n");
	printf("---------------------------------------\n");
	printf("1.effectuer un depot bancaire\n");
	printf("2.effectuer un retrait bancaire\n");
	printf("3.effectuer un transfert\n");
	printf("4.retour au menu du compte\n");
	printf("5.quitter l'application\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1  : depot(c,1);break;
		case 2  : retrait(c,1," ");break;
		case 3  : transfert_entre_comptes_existants(c);break;
		case 4  : menu_compte(*c);break;
		case 5  : exit(1);break;
		default : printf("choix invalide\nREESSAYER\n");
		          effectuer_une_transaction_bancaire(c);
	};
}

/*afficher l'identification du compte et le solde*/
void afficher_details_compte_existant(Compte c){
	printf("DETAILS DE VOTRE COMPTE\n");
	printf("----------------------------------\n");
	printf("nom    : %s\n",c.nom);
	printf("prenom : %s\n",c.prenom);
	printf("cin    : %s\n",c.cin);
	printf("solde  : %.2f\n",c.solde);
	printf("-----------------------------------\n");
	printf("1.retour au menu du compte\n");
	printf("2.quitter l'application\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 : menu_compte(c);break;
		case 2 : exit(1);break;
		default: menu_compte(c);
	};
}

/*chaque transaction est stockee dans le fichier historique du 
compte associe avec la date et l'heure de la transaction*/
void sauvegarder_historique(Compte c,char trans[100],double somme){
	char fichier [100];
	time_t t = time(NULL);
	struct tm date= *localtime(&t);
	snprintf(fichier,sizeof fichier,"./historique_de_%s_%s.txt",c.nom,c.prenom);
	FILE * fic2;
	if(fopen(fichier,"r")==NULL){
		fic2=fopen(fichier,"w");
		fclose(fic2);
	};
	fic2 = fopen(fichier,"a");
	fprintf(fic2,"%s montant:%.2f %02d-%02d-%d %02d:%02d\n",trans,somme,
	         date.tm_mday,date.tm_mon+1,date.tm_year+1900,date.tm_hour,date.tm_min);
	fclose(fic2);	
}
void afficher_historique(Compte c){
	Pile P = nouvelle_pile();
	char fichier [100];
	char chaine [256];
	snprintf(fichier,sizeof fichier,"./historique_de_%s_%s.txt",c.nom,c.prenom);
	FILE * fic2;
	fic2 = fopen(fichier,"r");
	while(fgets(chaine,256,fic2)!=NULL){
		empiler(&P,chaine);
	};
	printf("HISTORIQUE DES TRANSACTIONS BANCAIRES\n");
	printf("-------------------------------------------------\n");
	if(est_vide_pile(P)){
		printf("historique vide\n");
	};
	while(!est_vide_pile(P)){
		depiler(&P,chaine);
		printf("%s",chaine);
	};
	printf("--------------------------------------------------\n");
	printf("1.retour au menu du compte\n");
	printf("2.quitter l'application\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 : menu_compte(c);break;
		case 2 : exit(1);break;
		default: menu_compte(c);
	};
	fclose(fic2);
}
void afficher_liste_clients(){
	printf("LISTE DES CLIENTS\n");
	printf("--------------------------------------\n");
	Compte c2;
	int k=0;
	char chaine [256],c3[50],c4[50];
	FILE * fic1 = fopen("./listeClients.txt","r");
	if((fgets(chaine,256,fic1))==NULL){
		printf("pas de client \n");
		fclose(fic1);
	}
	else{
	fic1 = fopen("./listeClients.txt","r");	
	fscanf(fic1,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
	printf("  %s %s \n",c2.nom,c2.prenom);
	k++;
	strcpy(c3,c2.nom);
	strcpy(c4,c2.prenom);
	while((fgets(chaine,256,fic1))!=NULL){
		fscanf(fic1,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
		if(strcmp(c2.nom,c3)!=0 && strcmp(c2.prenom,c4)!=0){
			printf("  %s %s \n",c2.nom,c2.prenom);
			k++;
		};
		strcpy(c3,c2.nom);
		strcpy(c4,c2.prenom);
	};
     };
	fclose(fic1);
	printf("Au total %d clients\n",k);
	printf("---------------------------------------\n");
	printf("1.retour a l'accueil\n");
	printf("2.quitter l'application\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 : interface_accueil();break;
		case 2 : exit(1);break;
		default: interface_accueil();
	};
}

void paiement_factures(Compte * c){
	printf("PAIEMENT FACTURES\n");
	printf("------------------------------------\n");
	printf("1.SONEDE\n");
	printf("2.STEG\n");
	printf("3.WIFI\n");
	printf("4.retour au menu du compte\n");
	printf("5.quitter l'application bancaire\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 :  retrait(c,2,"SONEDE");
		case 2 :  retrait(c,2,"STEG");
		case 3 :  retrait(c,2,"WIFI");
		case 4 :  menu_compte(*c);break;
		case 5 :  exit(1);
	}
}
void assistance_clientele(Compte c){
	printf("ASSISTANCE CLIENTELE\n");
	printf("-----------------------------------------\n");
	printf("1.services offerts\n");
	printf("2.politique de la banque\n");
	printf("3.horaires de la banque\n");
	printf("4.retour au menu du compte\n");
	printf("5.quitter l'application bancaire\n");
	printf("------------------------------------------\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 : services_offerts(c);break;
		case 2 : politique_banque(c);break;
		case 3 : horaires_banque(c);break;
		case 4 : menu_compte(c);break;
		case 5 : exit(1);break;
		default:assistance_clientele(c);
	};
}
void services_offerts(Compte c){
	printf("NOS SERVICES\n");
	printf("---------------------------------------\n");
	printf("+Gestion des transactions bancaires+\n");
	printf("+Gestion des moyens de paiement+\n");
	printf("+Compte bancaire+\n");
	printf("+Offres de pret bancaire+\n");
	printf("----------------------------------------\n");
	printf("1.retour au menu du compte\n");
	printf("2.quitter l'application bancaire\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 :menu_compte(c);break;
		case 2 :exit(1);break;
		default:menu_compte(c);
	};
}
void politique_banque(Compte c){
	printf("NOTRE POLITIQUE\n");
	printf("----------------------------------------------\n"); 
	printf("Notre agence a pour but, outre la qualite\n");
	printf("du service aux clients,le developpement de\n");
	printf("leur portefeuille de clientele.\n");
	printf("Le directeur de l'agence est partie prenante du\n");
	printf("plan marketing de la banque, et les conseillers\n");
	printf("de clienteles ont des objectifs commerciaux,\n");
	printf("notamment de placement,generalement suivis\n");
	printf("mensuellement.Votre reussite est notre priorite.\n");
	printf("----------------------------------------------\n");
	printf("1.retour au menu du compte\n");
	printf("2.quitter l'application bancaire\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 :menu_compte(c);break;
		case 2 :exit(1);break;
		default:menu_compte(c);
	};	
}
void horaires_banque(Compte c){
	printf("HORAIRES BANCAIRES\n");
	printf("------------------------------------------\n");
	printf("Du Lundi au Vendredi de 08h-12h\n");
	printf("et de 14h-16h30\n");
	printf("------------------------------------------\n");
	printf("1.retour au menu du compte\n");
	printf("2.quitter l'application bancaire\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 :menu_compte(c);break;
		case 2 :exit(1);break;
		default:menu_compte(c);
	};	
}
void gestion_de_pret(Compte * c){
	printf("ESPACE PRET BANCAIRE\n");
	printf("-----------------------------------------\n");
	printf("1.prendre un pret bancaire\n");
	printf("2.remboursement total du pret accorde\n");
	printf("3.retour au menu du compte\n");
	printf("4.quitter l'application bancaire\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 : depot(c,2);break;
		case 2 : retrait(c,3,"");break;
		case 3 : menu_compte(*c);break;
		case 4 : exit(1);break;
		default: gestion_de_pret(c);	
	};
}
void afficher_comptes_supprimes(){
	printf("COMPTES SUPPRIMES\n");
	printf("----------------------------------------\n");
	Compte c2;
	int k=0;
	char chaine [256],c3[50],c4[50];
	FILE * fic3 = fopen("./corbeille.txt","r");
	if((fgets(chaine,256,fic3))==NULL){
		printf("pas de compte supprime\n");
		fclose(fic3);
	}
	else{
	fic3 = fopen("./corbeille.txt","r");	
	fscanf(fic3,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
	printf("  %s %s \n",c2.nom,c2.prenom);
	k++;
	strcpy(c3,c2.nom);
	strcpy(c4,c2.prenom);
	while((fgets(chaine,256,fic3))!=NULL){
		fscanf(fic3,"%s %s %s %s %lf",c2.nom,c2.prenom,c2.cin,c2.mot_de_passe,&c2.solde);
		if(strcmp(c2.nom,c3)!=0 && strcmp(c2.prenom,c4)!=0){
			printf("  %s %s \n",c2.nom,c2.prenom);
			k++;
		};
		strcpy(c3,c2.nom);
		strcpy(c4,c2.prenom);
	};
     };
	fclose(fic3);
	printf("Au total %d comptes supprimes\n",k);
	printf("-----------------------------------------\n");
	printf("1.retour a l'accueil\n");
	printf("2.quitter l'application\n");
	int choix;
	printf("\nEntrer votre choix= ");
	scanf("%d",&choix);
	switch(choix){
		case 1 : interface_accueil();break;
		case 2 : exit(1);break;
		default: interface_accueil();
	};
}

void recuperer_compte_supprime(){
	//informations entrees par le client
	char cin_x [50],mot_de_passe_x [100];
	printf("\nRECUPERATION DU COMPTE\n");
	printf("-------------------------------------------------\n");
	printf("DONNEES DE CONNEXION\n");
	printf("\tcin = ");
	scanf("%s",cin_x);
	getchar();
	printf("\tmot de passe= ");
	gets(mot_de_passe_x);
	//verifications des informations du client
	char chaine [256];
	Bool trouve=false;
	Compte c;
	FILE * fic3 =fopen("./corbeille.txt","r");
	fscanf(fic3,"%s %s %s %s %lf",c.nom,c.prenom,c.cin,c.mot_de_passe,&c.solde);
	if(strcmp(c.cin,cin_x)==0 && strcmp(c.mot_de_passe,mot_de_passe_x)==0){
		trouve=true;
	};
	while((fgets(chaine,256,fic3))!=NULL && !trouve){
		fscanf(fic3,"%s %s %s %s %lf",c.nom,c.prenom,c.cin,c.mot_de_passe,&c.solde);
		if(strcmp(c.cin,cin_x)==0 && strcmp(c.mot_de_passe,mot_de_passe_x)==0){
		   trouve=true;
	    };
	};
	if(trouve==true){
		sauvegarder_compte(c);
		printf("compte recupere avec succes\n");
		supprimer_compte_corbeille(c);
		menu_compte(c);//ouvrir le compte si informations correctes
	}
	else{
		printf("compte inexistant dans la corbeille\n");
		printf("\n");
		printf("ENTRER \n");
		printf("--------------------------------------------\n");
		printf("1.essayer de nouveau\n");
		printf("2.retour a l'interface d'accueil\n");
		printf("3.quitter l'application bancaire\n");
	    int choix;
	    do{
	      printf("\nchoix= ");
	      scanf("%d",&choix);
	     }
	    while(choix!=1 && choix!=2 && choix!=3);
	    switch(choix){
		  case 1 : recuperer_compte_supprime();break;
		  case 2 : interface_accueil();break;
		  case 3 : exit(1);break;
	    };};
	fclose(fic3);
}

//******************FIN DU PROJET*******************************
