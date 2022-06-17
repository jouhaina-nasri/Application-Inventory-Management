#include <stdlib.h>


struct Produit
{
    int code_p ;
	char lib_p[30] ;
	int quant_disp ;
	float prix_u ;
    int seuil ;
    struct  mouvement *liste_mvt;
    struct Produit *suiv;
};
typedef struct Produit Produit;
typedef Produit* llist;

struct date
{
	int j, m, a ;
};
typedef struct date date;

struct mouvement
{
	int quant_mvt ;
	date date_mvt ;
	char type_mvt[30] ;
	struct mouvement *apres ;
};
typedef struct mouvement mouvement;

char * saisirLibelle();
llist recherche_code(llist liste, int valeur);
llist recherche_libelle(llist liste, char *libelle);
llist ajouterT(llist liste, Produit* element);
llist ajoutMvT(llist l,mouvement* mvt);
llist menuConsulter(llist l);

void afficher_menu_general()
{
    printf("\t***************************************\n");
	printf("\t\t\t Menu Generale \n");
	printf("\t***************************************\n");
	printf("\t\t 1- creation de stock \n");
	printf("\t\t 2- Mise a jour \n");
	printf("\t\t 3- Mouvements \n");
	printf("\t\t 4- Consultations de produits \n");
	printf("\t\t 5- Mise a jour du stock \n");
	printf("\t\t 6- Generer commande de produits \n");
	printf("\t\t 7- Quitter \n");
    printf("\t***************************************\n");
    printf("\t \t \t Donner votre choix SVP : \n");
}

void menu_general(llist l, Produit* Nouv)
{
    int x=0;
    mouvement* nouvelElement = malloc(sizeof(mouvement));
    do
    {
        afficher_menu_general();
        scanf("%d",&x);
        switch(x)
        {
            case 1 :      saisie(Nouv);
                          l=ajouterT(l,Nouv);
                          afficherListe(l);
                          break;
            case 2 :      menuMaj( l, Nouv);
                          break;
            case 3 :      saisieMVT(nouvelElement);//saisir quantite type et date mvt.
                          l=ajoutMvT(l,nouvelElement);
                          afficherListeMVT(l);
                          break;
            case 4 :      l=menuConsulter(l);
                          break;
            case 5 :      MiseAjour(l);afficherListeMVT(l);//E: quantite++ S: quantite--
                          break;
            case 6 :      genererCMD(l);afficherListeMVT(l);//quantite<seuil
                          break;
            case 7 :      printf("Fin menu general \n");break;

        }
    }while(x!=7);
    return l;
}

llist ajouterT(llist liste, Produit* element)
{
    Produit* nouvelElement = malloc(sizeof(Produit));


    nouvelElement->code_p = element->code_p;
    nouvelElement->quant_disp = element->quant_disp;
    nouvelElement->prix_u = element->prix_u;
    nouvelElement->seuil = element->seuil;
    strcpy(nouvelElement->lib_p , element->lib_p);


    nouvelElement->suiv = liste;


    return nouvelElement;
}

llist ajouterQ(llist liste, Produit* element)
{

    Produit* nouvelElement = malloc(sizeof(Produit));


    nouvelElement->code_p = element->code_p;
    nouvelElement->quant_disp = element->quant_disp;
    nouvelElement->prix_u = element->prix_u;
    nouvelElement->seuil = element->seuil;
    strcpy(nouvelElement->lib_p , element->lib_p);

    nouvelElement->suiv = NULL;

    if(liste == NULL)
    {
        /* Si la liste est vide il suffit de renvoyer l'élément créé */
        return nouvelElement;
    }
    else
    {
        /* Sinon, on cherche le dernier élément de la liste est relié au nouvel élément */
        Produit* temp=liste;
        while(temp->suiv != NULL)
        {
            temp = temp->suiv;
        }
        temp->suiv = nouvelElement;
        return liste;
    }
}

void afficherListe(llist liste)
{
     Produit *tmp = liste;

    while(tmp != NULL)
    {
        printf("Code : %d ", tmp->code_p);
        printf("Libelle : %s ", tmp->lib_p);
        printf("Quantite : %d ", tmp->quant_disp);
        printf("Prix : %f ", tmp->prix_u);
        printf("Seuil : %d ", tmp->seuil);
        printf("\n");
        tmp = tmp->suiv;
    }
}

void  afficherListeMVT(llist liste)
{
    Produit *tmp = liste;

    while(tmp != NULL)
    {
        printf("Code : %d ", tmp->code_p);
        printf("Libelle : %s ", tmp->lib_p);
        printf("Quantite : %d ", tmp->quant_disp);
        printf("Prix : %f ", tmp->prix_u);
        printf("Seuil : %d ", tmp->seuil);
        mouvement *mvt=tmp->liste_mvt;
        while(mvt != NULL)
        {
            printf("Quantite mvt : %d ", mvt->quant_mvt);
            printf("Date mvt : %d/%d/%d ", mvt->date_mvt.j,mvt->date_mvt.m,mvt->date_mvt.a);
            printf("Type mvt : %s ", mvt->type_mvt);
            mvt=mvt->apres;
        }
        printf("\n");
        tmp = tmp->suiv;
    }
}

llist supprimerT(llist liste)
{
    if(liste != NULL)
    {
        Produit* aRenvoyer = liste->suiv;

        free(liste);

        return aRenvoyer;
    }
    else
    {
        return NULL;
    }
}

llist supprimerQ(llist liste)
{
    if(liste == NULL)
        return NULL;

    /* Si la liste contient un seul élément */
    if(liste->suiv == NULL)
    {
        free(liste);
        return NULL;
    }

    Produit* tmp = liste;
    Produit* ptmp = liste;

    while(tmp->suiv != NULL)
    {
        ptmp = tmp;
        tmp = tmp->suiv;
    }

    ptmp->suiv = NULL;
    free(tmp);
    return liste;
}

llist supprimerE(llist liste, int valeur)
{
    if(liste == NULL)
        return NULL;

    if(liste->code_p == valeur)
    {
        Produit* tmp = liste->suiv;
        free(liste);
        tmp = supprimerE(tmp, valeur);
        return tmp;
    }
    else
    {
        liste->suiv = supprimerE(liste->suiv, valeur);
        return liste;
    }
}

void saisie(Produit* nouvelElement)
{
    int c,q,s;
    char lib[30];
    float p;
    printf("Code : ");scanf("%d",&c);
    printf("Libelle : ");scanf("%s",&lib);
    printf("Quantite : ");scanf("%d",&q);
    printf("Prix : ");scanf("%f",&p);
    printf("Seuil : ");scanf("%d",&s);
    nouvelElement->code_p=c;
    strcpy(nouvelElement->lib_p,lib);
    nouvelElement->prix_u=p;
    nouvelElement->quant_disp=q;
    nouvelElement->seuil=s;
    nouvelElement->liste_mvt=NULL;
}

void saisieMVT(mouvement* nouvelElement)
{
    int a,j,m,q;
    char type[30];

    printf("Qunatite de mouvement : ");scanf("%d",&q);
    printf("Date de mouvement: \n ");
    do
    {
        printf("Jour : ");
        scanf("%d",&j);
    }while((j<=0)||(j>31));
    do
    {
        printf("Mois : ");
        scanf("%d",&m);
    }while((m<=0)||(m>12));
    do
    {
        printf("Annee : ");
        scanf("%d",&a);
    }while(a<=0);
    do
    {
        printf("Type de mouvement E pour entree et S pour sortie: ");
        scanf("%s",&type);
    }while((strcmp(type,"E")!=0)&&(strcmp(type,"S")!=0));//strcmp comparer : type == "E"
    nouvelElement->quant_mvt=q;
    strcpy(nouvelElement->type_mvt,type);
    nouvelElement->date_mvt.j=j;
    nouvelElement->date_mvt.m=m;
    nouvelElement->date_mvt.a=a;
    nouvelElement->apres=NULL;
}

llist ajoutMvT(llist l,mouvement* mvt)
{
    int code = saisirCode();
    if(l==NULL)
    {
        printf("La liste est vide. \n");
        return NULL;
    }
    else
    {
        Produit *p=l;
        if(p->code_p==code)
        {
            p->liste_mvt=mvt;
            return p;
        }
        else
        {
            Produit *y=p->suiv;
            while((y!=NULL)&&(y->code_p!=code))
            {
                y=y->suiv;
            }
            p=y;
            if(p!=NULL)
            {
                p->liste_mvt=mvt;
                return p;
            }
            else
            {
               printf("Le produit n'existe pas \n");
               return NULL;
            }
        }
    }
}

void afficher_menu_maj()
{
            printf("\t***************************************\n");
            printf("\t\t\t Menu MAJ \n");
            printf("\t***************************************\n");
            printf("\t\t 1- Ajouter un nouveau produit  \n");
            printf("\t\t 2- Supprimer un produit \n");
            printf("\t\t 3- Modifier les donnees d un produit \n");
            printf("\t\t 4- Quitter \n");
            printf("\t***************************************\n");
            printf("\t \t \t Donner votre choix SVP : \n");

}

void afficher_menu_ajouter()
{
            printf("\t***************************************\n");
            printf("\t\t\t Menu Ajouter \n");
            printf("\t***************************************\n");
            printf("\t\t 1- Ajout en tete \n");
            printf("\t\t 2- Ajout un queue  \n");
            printf("\t\t 3- Quitter \n");
            printf("\t***************************************\n");
            printf("\t \t \t Donner votre choix SVP : \n");

}

void afficher_menu_supprimer()
{
            printf("\t***************************************\n");
            printf("\t\t\t Menu supprimer \n");
            printf("\t***************************************\n");
            printf("\t\t 1- Suppression en tete  \n");
            printf("\t\t 2- Suppression en queue  \n");
            printf("\t\t 3- Suppression d un produit donne\n");
            printf("\t\t 4- Quitter \n");
            printf("\t***************************************\n");
            printf("\t \t \t Donner votre choix SVP : \n");

}

void afficher_menu_modifier()
{
            printf("\t***************************************\n");
            printf("\t\t\t Menu Modification \n");
            printf("\t***************************************\n");
            printf("\t\t 1- Libelle  \n");
            printf("\t\t 2- Prix unitaire  \n");
            printf("\t\t 3- le seuil\n");
            printf("\t\t 4- Quitter \n");
            printf("\t***************************************\n");
            printf("\t \t \t Donner votre choix SVP : \n");

}

void afficher_menu_consulter()
{
            printf("\t***************************************\n");
            printf("\t\t\t Menu Consultation \n");
            printf("\t***************************************\n");
            printf("\t\t 1- Liste des produits avec ses mouvements  \n");
            printf("\t\t 2- Rechercher un produit par code \n");
            printf("\t\t 3- Rechercher un produit par libelle \n");
            printf("\t\t 4- Quitter \n");
            printf("\t***************************************\n");
            printf("\t \t \t Donner votre choix SVP : \n");

}

llist menuConsulter(llist l)
{
    int x=0;int code;
    do
    {
        afficher_menu_consulter();
        scanf("%d",&x);
        switch(x)
        {
            case 1 :      afficherListeMVT(l);
                          break;
            case 2 :      l=recherche_code(l,saisirCode());
                          afficherListe(l);
                          break;
            case 3 :      l=recherche_libelle(l,saisirLibelle());
                          afficherListe(l);
                          break;
            case 4 :      printf("Fin menu consultation \n");break;
        }
    }while(x!=4);
    return l;
}

int saisirCode()
{
    int code;
    printf("Donner le code du produit recherche : ");scanf("%d",&code);
    return code;
}

float saisirPrix()
{
    float prix;
    printf("Donner le nouvel prix de produit : ");scanf("%f",&prix);
    return prix;
}

int saisirSeuil()
{
    int seuil;
    printf("Donner le nouvel seuil de produit : ");scanf("%d",&seuil);
    return seuil;
}

char * saisirLibelle()
{
    char libelle[40];
    printf("Donner le libelle de produit : ");scanf("%s",&libelle);
    return libelle;
}

llist modifierPrix(llist l)
{
    int code = saisirCode();
    float prix=saisirPrix();
    if(l==NULL)
    {
        printf("La liste est vide. \n");
        return NULL;
    }
    else
    {
        Produit *p=l;
        if(p->code_p==code)
        {
            p->prix_u=prix;
            return p;
        }
        else
        {
            Produit *y=p->suiv;
            while((y!=NULL)&&(y->code_p!=code))
            {
                y=y->suiv;
            }
            p=y;
            if(p!=NULL)
            {
                p->prix_u=prix;
                return p;
            }
            else
            {
               printf("Le produit n'existe pas \n");
               return NULL;
            }
        }
    }

}

llist modifierSeuil(llist l)
{
    int code = saisirCode();
    int seuil=saisirSeuil();
    if(l==NULL)
    {
        printf("La liste est vide. \n");
        return NULL;
    }
    else
    {
        Produit *p=l;
        if(p->code_p==code)
        {
            p->seuil=seuil;
            return p;
        }
        else
        {
            Produit *y=p->suiv;
            while((y!=NULL)&&(y->code_p!=code))
            {
                y=y->suiv;
            }
            p=y;
            if(p!=NULL)
            {
                p->seuil=seuil;
                return p;
            }
            else
            {
               printf("Le produit n'existe pas \n");
               return NULL;
            }
        }
    }
}

llist modifierLibelle(llist l)
{
    int code = saisirCode();
    char libelle [30];
    strcpy(libelle,saisirLibelle());
    if(l==NULL)
    {
        printf("La liste est vide. \n");
        return NULL;
    }
    else
    {
        Produit *p=l;
        if(p->code_p==code)
        {
            strcpy(p->lib_p,libelle);
            return p;
        }
        else
        {
            Produit *y=p->suiv;
            while((y!=NULL)&&(y->code_p!=code))
            {
                y=y->suiv;
            }
            p=y;
            if(p!=NULL)
            {
                strcpy(p->lib_p,libelle);
                return p;
            }
            else
            {
               printf("Le produit n'existe pas \n");
               return NULL;
            }
        }
    }
}

llist menu_ajouter(llist l, Produit* Nouv)
{
    int x=0;
    do
    {
        afficher_menu_ajouter();
        scanf("%d",&x);
        switch(x)
        {
            case 1 :      saisie(Nouv);
                          l=ajouterT(l,Nouv);
                          afficherListe(l);
                          break;
            case 2 :      saisie(Nouv);
                          l=ajouterQ(l,Nouv);
                          afficherListe(l);
                          break;
            case 3 :      printf("Fin menu ajouter \n");break;
        }
    }while(x!=3);
    return l;
}

llist menu_supprimer(llist l)
{
    int x=0;
    do
    {
        afficher_menu_supprimer();
        scanf("%d",&x);
        switch(x)
        {
            case 1 :      l=supprimerT(l);
                          afficherListe(l);
                          break;
            case 2 :      l=supprimerQ(l);
                          afficherListe(l);
                          break;
            case 3 :      l=supprimerE(l,saisirCode());
                          afficherListe(l);
                          break;
            case 4 :      printf("Fin menu suppression \n");break;
        }
    }while(x!=4);
    return l;
}

llist menu_modifier(llist l)
{
    int x=0;

    do
    {
        afficher_menu_modifier();
        scanf("%d",&x);
        switch(x)
        {
            case 1 :      l=modifierLibelle(l);
                          afficherListe(l);
                          break;
            case 2 :      l=modifierPrix(l);
                          afficherListe(l);
                          break;
            case 3 :      l=modifierSeuil(l);
                          afficherListe(l);
                          break;
            case 4 :      printf("Fin menu modification \n");break;
        }
    }while(x!=4);
    return l;
}

void menuMaj(llist l,Produit* Nouv)
{
    int x=0;
    do
    {
        afficher_menu_maj();
        scanf("%d",&x);
        switch(x)
        {
            case 1 :      l=menu_ajouter(l,Nouv);
                          break;
            case 2 :      l=menu_supprimer(l);
                          break;
            case 3 :      l=menu_modifier(l);
                          break;
            case 4 :      printf("Fin menu MAJ \n");break;
        }
    }while(x!=4);

}

llist recherche_code(llist liste, int valeur)
{
    Produit *tmp=liste;

    while((tmp != NULL)&&(tmp->code_p != valeur))
    {
        tmp = tmp->suiv;
    }
    if(tmp != NULL)
    {
        return tmp;
    }
    return NULL;
}

llist recherche_libelle(llist liste, char *libelle)
{
    Produit *tmp=liste;

    while((tmp != NULL)&&(strcmp(tmp->lib_p,libelle) != 0))
    {
        tmp = tmp->suiv;
    }

    if(tmp!=NULL)
    {
        return tmp;
    }
    return NULL;
}

void MiseAjour(llist l)
{
    if(l!= NULL)
    {
        llist p;
        p= l;
        while (p != NULL )
        {
               mouvement * mv;
               mv=p->liste_mvt;
               if(strcmp(mv->type_mvt,"S")==0)
               {
                   p->quant_disp=p->quant_disp-mv->quant_mvt;
                   p->liste_mvt=NULL;
               }
               else
               {
                   p->quant_disp=p->quant_disp+mv->quant_mvt;
                   p->liste_mvt=NULL;
               }
            p=p->suiv;
        }
    }
    else
    {
        printf("la liste est vide");
    }

}

void genererCMD(llist l)
{
    if(l != NULL)
    {
        llist p;
        p= l;
        while (p != NULL )
        {
            if(p->quant_disp<p->seuil)
            {
                int quantite = p->seuil-p->quant_disp;
                printf("la quantite minimal a commander est : %d \n",quantite);
            }
            p=p->suiv;
        }
    }
    else
    {
        printf("liste est vide");
    }
}

int main()
{

        llist ma_liste = NULL;
        Produit* nouvelElement = malloc(sizeof(Produit));
        menu_general(ma_liste, nouvelElement);

    return 0;
}
