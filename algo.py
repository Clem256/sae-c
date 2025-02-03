##---------------Importation des modules-------------------##
from numpy import*
from random import*
##--------------Définitions des fonctions------------------##


def repartition(tab:int,i_deb:int,i_fin:int):
    p = tab[i_deb] #p = pivot
    i = i_deb+1
    j = i_fin
    while i<j:
        if tab[i]>tab[j] and tab[j] <= p:
            echange(tab,i,j);
            i=i+1
            j=j+1
        if tab[i]<= p:
            i = i+1
            if tab[j]>p:
                j = j-1
    if tab[i]>p :
        i=i-1
    echange(tab,i,i_debut)
    return i



def tri_rapide(tab:int,i_deb:int,i_fin:int):
    if i_fin == i_deb+1:
        if tab[i_fin]<tab[i_deb]:
            echange(tab,i_deb,i_fin)
    else:
        if i_deb<i_fin:
            i_p = repartition(tab,i_deb,i_fin)
            tri_rapide(tab,i_deb,i_fin)
            tri_rapide(tab,i_p+1,i_fin)
#Dans le pire des cas,l'algo sera effectué    O(Nlog2N)


def fusionner(tab:int,i_deb:int,i_mill:int,i_fin:int):
    temp=zeros(i_fin-i_fin+1,float) # a retrenscrire en c
    i=i_deb
    j=i_mill+1
    k=0
    while i<=i_mill and j<= i_fin:
        if tab[i]<tab[j]:
            temp[k]=tab[i]
            i=i+1
        else:
            temp[k]=tab[j]
            j=j+1
        k=k+1
    while i<= i_mill:
        temp[k]=tab[i]
        i=i+1
        k=k+1    
    while j<= i_fin:
        temp[k]=tab[j]
        j=j+1
        k=k+1
    k=0
    while k<len(temp):
        tab[i_deb+k]=temp[k]
        k=k+1


def tri_fusion(tab:int,i_deb:int,i_fin:int):
    i_mill=(i_deb+i_fin)//2
    if i_deb<i_fin:
        tri_fusion(tab,i_deb,i_mill)
        tri_fusion(tab,i_mill+1,i_fin)
        fusionner(tab,i_deb,i_mill,i_fin)


def echange(tab:[float],i,j):
    p =tab[i]
    tab[i]=tab[j]
    tab[j]=tab[i]
#L'algorithme est composé de 3 opérations élémentaires,donc l'algo est de complexité linéaire,en O(n)


def recherche_dichotomie(tab:int, valeur:int):
    ind =-1
    i_deb=0
    i_fin = len(tab)-1
  
    while i_deb<=i_fin and ind == -1:
        i_mill=(i_deb+i_fin)//2
        if tab[i_mill]==valeur :
            ind = i_mill
        else :
            if tab[i_mill]>val:
                i_fin=i_mill-1
            else:
                i_deb = i_mill+1
    return ind
#Après chaque execution de la boule while,l'interval de recherche est divisé par 2(à un près).Au debut du dernier tour de boucle(le k-ième ),l'amplitude
#de l'interval initial aura donc été divisé par 2^k-1.Or cette amplitude est 1 donc n//2^k-1.Or cette amplitude est 1 donc n//2^k-1=1,c'est à dire
# 2>n/k-1>=1 ,k est le + grand entier tel que 2^k-1<=n<2^k.Or ln étant une fonction croissante,on a 2^k-1 <=n <=> log(2^k-1)<=ln(n)
# <=> (k-1)ln(2)<=ln(n) <=> k-1<=ln(n)/ln(2) <=> k<=(ln(n)/ln(2))+1 <=> k=log2(n)+1.
#Dès lors la complexité de la recherche par dichotomie est logaritmique en O(log2(n)).


def trie_croissant2(tab: int):
    global cpt
    i=len(tab)-1
    cpt=cpt+3
    while i>0:
        permuter_jusqua(tab, i)
        i=i-1
        cpt=cpt+3
    cpt=cpt+1
    return tab

def permuter_jusqua(tab: int,i: int) -> (int):
    global cpt2
    j=0
    cpt2=cpt2+1
    while j<i:
        if tab[j] > tab[j+1]:
            temp=tab[j]
            tab[j]=tab[j+1]
            tab[j+1]=temp
            cpt2=cpt2+7
        j=j+1
        cpt2=cpt2+5
    cpt2=cpt2+1

def trie_croissant2(tab: int):
    global cpt
    i=len(tab)-1
    cpt=cpt+3
    while i>0:
        permuter_jusqua(tab, i)
        i=i-1
        cpt=cpt+3
    cpt=cpt+1
    return tab
#L'algo trie_croissant2 est composé d'une boucle while ainsi que des opérations élémentaires et un appel à l'algo permuter_jusqua
def permuter_jusqua(tab: int,i: int) -> (int):
    global cpt2
    j=0
    cpt2=cpt2+1
    while j<i:
        if tab[j] < tab[j+1]:
            temp=tab[j]
            tab[j]=tab[j+1]
            tab[j+1]=temp
            cpt2=cpt2+7
        j=j+1
        cpt2=cpt2+5
    cpt2=cpt2+1
#L'algo permuter_jusqua est composer d'une boucle while et d'opération élémentaire.Dans le pire des cas,sa complexité correspond au nombre de tour de
#sa boucle la plus intérieur



# Les 4 algo suivant sont des versions améliorer des 4 algo précédents 
#Nicolas tri croissant insertion
def indice_mini(tab: int,i: int) -> (int):
    global cpt2
    i_mini= i
    cpt2=cpt2+1
    while i<len(tab):
        if tab[i]<tab[i_mini]:
            i_mini=i
            cpt2=cpt2+1
        i=i+1
        cpt2=cpt2+5
    cpt2=cpt2+1
    return i_mini
#En notant n la taille du tableau,la boucle est parcouru n-1 fois pour aller de 1 à n-1 .Le reste de l'algo est constitué
#d'opération élémentaire ce qui implique une complexité linéaire en O(n)


def trie_croissant(tab: int):
    global cpt
    i=0
    cpt=cpt+1
    while i<len(tab)-1:
        i_mini=indice_mini(tab, i)
        temp=tab[i]
        tab[i]=tab[i_mini]
        tab[i_mini]=temp
        i=i+1
        cpt=cpt+12
    return tab


def indice_maxi(tab: int,i:int) -> (int):
    global cpt2
    i_max= i
    cpt2=cpt2+1
    while i<len(tab):
        if tab[i]>tab[i_max]:
            i_max=i
            cpt2=cpt2+1
        i=i+1
        cpt2=cpt2+5
    cpt2=cpt2+1
    return i_max
#En notant n la taille du tableau,la boucle est parcouru n-1 fois pour aller de 1 à n-1 .Le reste de l'algo est constitué
#d'opération élémentaire ce qui implique une complexité linéaire en O(n)

# tri decroissant insertion
def trie_decroissant(tab: int):
    global cpt
    i=0
    cpt=cpt+1
    while i<len(tab)-1:
        i_max=indice_maxi(tab, i)
        temp=tab[i]
        tab[i]=tab[i_max]
        tab[i_max]=temp
        i=i+1
        cpt=cpt+12
    return tab

#tri indirect
p= 50
tab=[106 , 73 , 73 , 131 , 56 ,113 ,117 ,135 ,113 ,141 , 86, 163, 111,  57,  18, 143 ,119 , 67
,  50 ,167 ,121, 159, 177,  11,  65,  28,  40, 135,  34, 175 , 31,  35, 176,  89,  94, 147,
 167,  93, 158,  59, 162,  58, 101 ,115 ,121 , 12 ,179 , 39 ,  5 , 85]
defaut=tab


def indice_max(tab: int,i: int) -> (int):
    global cpt2
    i_max= i
    cpt2=cpt2+1
    while i<len(tab):
        if tab[i]>tab[i_max]:
            i_max=i
            cpt2=cpt2+1
        i=i+1
        cpt2=cpt2+7
    cpt2=cpt2+1
    return i_max

def trie_decroissan1(tab: int):
    global cpt
    i=0
    tab2=zeros([p])
    cpt=cpt+3
    while(i<p):
        tab2[i]=i
        i=i+1
        cpt=cpt+5
    i=0
    cpt=cpt+2
    while i<len(tab)-1:
        i_max=indice_max(tab, i)
        temp=tab[i]
        temp2=tab2[i]
        
        tab[i]=tab[i_max]
        tab2[i]=tab2[i_max]

        tab[i_max]=temp
        tab2[i_max]=temp2

        i=i+1
        cpt=cpt+21
    return defaut, tab, tab2

p = 50     # nb passagers

numsiege =[106 , 73 , 73 , 131 , 56 ,113 ,117 ,135 ,113 ,141 , 86, 163, 111,  57,  18, 143 ,119 , 67
,  50 ,167 ,121, 159, 177,  11,  65,  28,  40, 135,  34, 175 , 31,  35, 176,  89,  94, 147,
 167,  93, 158,  59, 162,  58, 101 ,115 ,121 , 12 ,179 , 39 ,  5 , 85]
defaut =numsiege
prixb = zeros([p])
daten = zeros([p])
np_numsiege = zeros([p])


    
def indice_mini(numsiege: int,i: int) -> (int):
    global cpt2
    i_mini= i
    cpt2=cpt2+1
    while i<len(numsiege):
        if numsiege[i]<numsiege[i_mini]:
            i_mini=i
            cpt2=cpt2+1
        i=i+1
        cpt2=cpt2+5
    cpt2=cpt2+1
    return i_mini

def trie_croissan1(numsiege: int):
    global cpt
    i=0
    numsiegetrie = zeros([p])
    cpt=cpt+3
    while(i<p):
        numsiegetrie[i]=i
        i=i+1
        cpt=cpt+5
    i=0
    cpt=cpt+2
    while i<len(numsiege)-1:
        i_mini=indice_mini(numsiege, i)
        
        temp=numsiege[i]
        temp2=numsiegetrie[i]
        
        numsiege[i]=numsiege[i_mini]
        numsiegetrie[i]=numsiegetrie[i_mini]
        
        numsiege[i_mini]=temp
        numsiegetrie[i_mini]=temp2
        
        i=i+1
        cpt=cpt+21
    return defaut, numsiege, numsiegetrie




##-------------Définitions des vraiables globales---------##

##------------Test en boite noir--------------------------##
mot = 15
cpt = 0
cpt2 = 0


##--------------Test affichage---------------------------##
print("recherche(mot) vaut :",mot)
cpt=0
cpt2 = 0



print("le nombre d'opérations générés pas cet appel est (Tri N°1): ", cpt+cpt2)
