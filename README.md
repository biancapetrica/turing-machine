# turing-machine

	In main deschid cele 2 fisiere de input si de output si creez o masina 
turing cu codificarea citita din fisierul input cu functia create si incep 
executia masinii turing cu functia run avand capetele de citire(pos1 si pos2) 
aflate pe pozitia 1. 
	In functia create este initializat un element de tip turingM(TM) in care 
este citita din fisierul de input codificarea unei masini Turing. Tranzitiile 
masinii vor fi salvate intr-un vector de structuri de tip transition 
(TM->transitions). Pentru citirea tranzitiilor din fisier folosesc functia 
str_split care are rolul de a desparti cuvintele de pe fiecare linie citita dupa
unul dintre delimitatoarele " ", \n, \r, si va returna un vector de cuvinte. 
Cele 2 benzi sunt salvate fiecare ca un string (TM->tape1 si TM->tape2). 
	In functia run are loc executia masinii. Aceasta primeste ca parametrii 
pozitiile in care se afla capetele de citire pe cele 2 benzi,masina turing TM si 
fisierul de output. Se verifica mai intai daca starea curenta a TM este o stare 
finala si in caz afirmativ se scriu in fisierul de output cele 2 benzi: 
TM->tape1 si TM->tape2. Altfel, este parcurs vectorul de tranzitii 
(TM->transitions) pana este gasita tranzitia corespunzatoare starii curente a TM 
si a simbolurilor citite de pe benzi. Se inlocuiesc simbolurile pe cele 2 benzi 
si este apelata functia move cu noile directii de mers pentru capetele de citire.
	Functia move primeste ca parametrii banda, directia de deplasare a 
cursorului pentru banda, pozitia acestuia si intoarce noua banda. Daca directia 
este R si capatul de citire se afla pe ultimul simbol de pe banda, atunci adaug 
la sfarsitul benzii caracterul #. Pozitia capatului de citire este modificata 
prin efect lateral in functie de directie.	
