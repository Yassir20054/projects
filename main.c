#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct monome{
    int coeffi;
    int expos;
    struct monome *suivant;
}monome;
monome *ajouterAudebut(monome *tete,int coe,int exp){
    monome *nouv = (monome*)malloc(sizeof(monome));
    nouv->coeffi = coe;
    nouv->expos = exp;
    nouv->suivant = NULL;
    if(tete == NULL)
        return nouv;
    nouv->suivant = tete;
    tete = nouv;
    return tete;
}
monome *ajouterAlafin(monome *tete,int coe,int exp){
    monome *nouv = (monome*)malloc(sizeof(monome));
    nouv->coeffi = coe;
    nouv->expos = exp;
    nouv->suivant = NULL;
    if(tete == NULL)
        return nouv;
    monome *courant = tete;
    while(courant->suivant != NULL)
        courant = courant->suivant;
    courant->suivant = nouv;
    return tete;
}
void afficher(monome *tete){
    monome *courant = tete;
    while(courant != NULL){
        if(courant->expos == 0){
            printf("%d",courant->coeffi);
        }else if(courant->expos == 1){
            printf("%dx+", courant->coeffi);
        }else{
            if(courant->suivant->coeffi > 0){
                    printf("%dx^%d+",courant->coeffi,courant->expos);
            }else{
                printf("%dx^%d",courant->coeffi,courant->expos);
            }
        }
        courant = courant->suivant;
    }
    printf("\n");
}
int evalue(monome *tete,int x){
    int resultat = 0;
    monome *courant = tete;
    while(courant != NULL){
        resultat = resultat + courant->coeffi * pow(x,courant->expos);
        courant = courant->suivant;
    }
    return resultat;
}
monome *derivee(monome *tete){
    monome *derive = NULL;
    monome *courant = tete;
    while(courant != NULL){
        if(courant->expos != 0){
            derive = ajouterAlafin(derive,courant->coeffi*courant->expos,courant->expos-1);
        }
        courant = courant->suivant;
    }
    return derive;
}
int tailleMono(monome *tete){
    int taille = 0;
    monome *courant = tete;
    while(courant != NULL){
        taille++;
        courant = courant->suivant;
    }
    return taille;
}
monome *supprimermon(monome *tete,int pos){
    if(tete == NULL){
        printf("La liste est deja vide.\n");
        return NULL;
    }
    int taille = tailleMono(tete);
    if(pos < 1 || pos > taille){
        printf("La position est invalible.\n");
        return tete;
    }
    monome *courant = tete;
    monome *temp = tete;
    if(pos == 1){
        tete = tete->suivant;
        free(temp);
        return tete;
    }
    int i;
    for(i=1;i<pos-1;i++)
        courant =courant->suivant;
    temp = courant->suivant;
    courant->suivant = temp->suivant;
    free(temp);
    return tete;
}
void menu(){
    int c,i,N;
    int coe,exp;
    monome *L1 = NULL;
    monome *derive = NULL;
    int x;
    do{
        printf("\t\t---------menu-------------------------------\n");
        printf("\t\t---------1.saisir l'equation.---------------\n");
        printf("\t\t---------2.afficher l'equation.-------------\n");
        printf("\t\t---------3.resultat valeur l'equation.------\n");
        printf("\t\t---------4.calculer derivee.----------------\n");
        printf("\t\t---------5.quitter.-------------------------\n");
        printf("Saisir votre choix : ");
        scanf("%d", &c);
        switch(c){
        case 1 :system("cls");
                printf("Saisir la taille de polynome : ");
                scanf("%d", &N);
                for(i=0;i<N+1;i++){
                    printf("Saisir la %d coefficiant : ", i+1);
                    scanf("%d", &coe);
                    printf("Saisir la %d exposant : ",i+1);
                    scanf("%d", &exp);
                    L1 = ajouterAlafin(L1,coe,exp);
                }
                system("cls");
                break;
        case 2 :system("cls");
                afficher(L1);
                system("pause");
                system("cls");
                break;
        case 3 :system("cls");
                printf("Saisir le nombre a evalue : ");
                scanf("%d", &x);
                int eval = evalue(L1,x);
                printf("La resultat : %d \n", eval);
                system("pause");
                system("cls");
                break;
        case 4 :system("cls");
                derive = derivee(L1);
                printf("La derivee est : \n");
                afficher(derive);
                system("pause");
                system("cls");
                break;
        case 5 :system("cls");
                printf("\t\t\t----------------------------thank you for using this app.-------------------------------------\n");
                printf("\t\t\t----------------------------this app powered by Yassir Chakir---------------------------------\n");
                _sleep(4000);
                return;
                break;
        default:printf("Votre choix est incorrect !\n");
                _sleep(3000);
                system("cls");
                menu();
                break;
        }
    }while(c != 5);
}
int main()
{
    menu();
    return 0;
}
