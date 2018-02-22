/* PETRICA BIANCA GABRIELA
        323 CB */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    char curState[101];
    char tape1_curSymbol;
    char tape2_curSymbol;
    char newState[101];
    char tape1_newSymbol;
    char tape2_newSymbol;
    char tape1_dir;
    char tape2_dir;
} transition;

typedef struct {
    int states_len;
    char **states; //vectorul de stari
    int final_states_len; 
    char **finalStates; //vectorul de stari finale
    char *curState; //starea curenta
    char *tape1; //banda 1
    char *tape2; //banda 2
    int tran_len;
    transition** transitions; //vectorul de tranzitii
 } turingM;

turingM *create (FILE* input);
void run (turingM *TM, int* posTape1, int* posTape2, FILE* output);
char* move (char *tape, char dir, int* position);
char** str_split(char* line);

int main () {
    FILE *input = fopen("task1.in", "r");
    if (input == NULL) {
        exit(EXIT_FAILURE);
    }
    FILE *output = fopen("task1.out", "w");
    if (output == NULL) {
        fclose(input);
        exit(EXIT_FAILURE);
    }
    //creez o masina turing TM cu codificarea din fisierul input
    turingM* TM = create(input);
    int pos1 = 1;
    int pos2 = 1;
    run(TM, &pos1, &pos2, output);

    fclose(input);
    fclose(output);
    return 0;
}

char** str_split(char* line){
    /*separ cuvintele din stringul line dupa unul din delimitatori si salvez
      cuvintele in vectorul de stringuri tokens*/
    char delim[] = " \n\r";
    char** token = (char**)calloc(9, sizeof(char*));
    int i = 0;
    token[i] = strtok(line, delim);
    while (token[i] != NULL) {
        i++;
        token[i] = strtok(NULL, delim);
    }
    return token;
}

turingM *create (FILE* input) {
//intializez TM pentru a salva codificarea masinii Turing
    turingM *TM = malloc(sizeof (turingM));
    if (!TM) return NULL;
    int length;
    fscanf(input, "%d", &length);
//aloc memorie pentru vectorul de stari si le citesc din fisierul de input
    TM->states_len = length;
    TM->states = calloc(TM->states_len, sizeof (char *));
    if (!TM->states) return NULL;
    
    int i;
    char buffer[101];
    for (i = 0; i < TM->states_len; i++) {
        fscanf(input, "%s", buffer);        
        TM->states[i] = calloc(strlen(buffer), sizeof(char));
        if (!TM->states[i]) return NULL;
        strcpy(TM->states[i], buffer);
    }
//aloc memorie pentru vectorul de stari finale si le citesc din fisierul de input
    fscanf(input, "%d", &length);
    TM->final_states_len = length;
    TM->finalStates = calloc(TM->final_states_len, sizeof (char*));
    if (!TM->finalStates) return NULL;
    for (i = 0; i < TM->final_states_len; i++) {
        fscanf(input, "%s", buffer);
        TM->finalStates[i] = calloc(strlen(buffer), sizeof(char));
        if (!TM->finalStates[i]) return NULL;
        strcpy(TM->finalStates[i], buffer);
    }
//aloc memorie pentru starea curenta a benzilor si o citesc din fisierul de input
    fscanf(input, "%s", buffer);
    TM->curState = calloc(strlen(buffer), sizeof(char));
    if (!TM->curState) return NULL;
    strcpy(TM->curState, buffer);
//aloc memorie pentru vectorul de tranzitii si le citesc din fisierul de input
    fscanf(input, "%d", &length);
    TM->tran_len = length;
    TM->transitions = malloc(sizeof(transition) * length);
    if (!TM->transitions) return NULL;
    char *line = NULL;
    size_t len = 0;
    int j;
    getline(&line, &len, input);

    for (j = 0; j < TM->tran_len; j++) {
        getline(&line, &len, input);
        char **tokens = str_split(line);
        if (tokens[0] != NULL) {
            //aloc memorie pentru o tranzitie si o initializez 
            transition *tran = malloc(sizeof (transition));
            if (!tran) return NULL;
            strcpy(tran->curState, tokens[0]);
            tran->tape1_curSymbol = *(char*)tokens[1];
            tran->tape2_curSymbol = *(char*)tokens[2];
            strcpy(tran->newState, tokens[3]);
            tran->tape1_newSymbol = *(char*)tokens[4];
            tran->tape1_dir = *(char*)tokens[5];
            tran->tape2_newSymbol = *(char*)tokens[6];
            tran->tape2_dir = *(char*)tokens[7];  
            
            TM->transitions[j] = tran;
        }
    }
    char *tape = calloc(10001, sizeof(char));
    if (!tape) return NULL;
//aloc memorie pentru cele 2 benzi si le citesc din fisierul de input
    fscanf(input, "%s", tape);
    TM->tape1 = calloc(strlen(tape), sizeof(char));
    if (!TM->tape1) return NULL;
    strcpy(TM->tape1, tape);

    fscanf(input, "%s", tape);
    TM->tape2 = calloc(strlen(tape), sizeof(char));
    if (!TM->tape2) return NULL;
    strcpy(TM->tape2, tape);
   
    return TM;
}

void run (turingM *TM, int* posTape1, int* posTape2, FILE* output) {
    int i;
    while (1) {
        //verific daca starea curenta este de fapt o stare finala
        for (i = 0; i < TM->final_states_len; i++) {
            if (strcmp(TM->finalStates[i], TM->curState) == 0){
                /* ma aflu intr-o stare finala asa ca afisez cele 2 benzi si
                opresc rularea masinii */
                fprintf(output, "%s\n", TM->tape1);
                fprintf(output, "%s\n", TM->tape2);
                return;
            }
        }
        //nu am ajuns inca intr-o stare finala
        transition *tran;
        int ok = 0;
        /*caut in vectorul de tranzitii tranzitia corespunzatoarea starii 
        curente si simbolurilor de pe cele 2 benzi*/
        for (i = 0; i < TM->tran_len; i++){
            if (strcmp(TM->transitions[i]->curState, TM->curState) == 0 && 
                TM->transitions[i]->tape1_curSymbol == TM->tape1[*posTape1] &&
                TM->transitions[i]->tape2_curSymbol == TM->tape2[*posTape2] ) { 
                tran = TM->transitions[i];
                ok = 1; //am gasit tranzitia 
                break;
            }
        }
        if (ok == 0){
            //nu am gasit nicio tranzitie corespunzatoare,deci masina s-a blocat
            fprintf(output,"The machine has blocked!\n");
            return;
        }
        /*modific simbolurile curente pe cele 2 benzi si mut capatul de citire 
        in noua directie cu ajutorul functiei move*/
        TM->tape1[*posTape1] = tran->tape1_newSymbol;
        TM->tape1 = move(TM->tape1, tran->tape1_dir, posTape1);
        TM->tape2[*posTape2] = tran->tape2_newSymbol;
        TM->tape2 = move(TM->tape2, tran->tape2_dir, posTape2);
        // modific starea curenta
        TM->curState = tran->newState;
    }
}

char* move (char *tape, char dir, int* position) {
/*mut la stanga sau la dreapta pozitia capatului de citire prin efect lateral in
functie de dir */
    if (dir == 'R') {
        (*position)++;
        if ( *position == strlen(tape) - 1 ) {
            /*capatul de citire de afla pe ultimul caracter al benzii, dar banda 
            este inifinta la dreapta asa ca adaug caracterul # la sfarsit*/
            size_t sz = strlen(tape);
            char *str = calloc(sz + 2, 1);
            strcpy(str, tape);
            str[sz] = '#';
            str[sz + 1] = '\0';
            return str;
        }
    }
    else if (dir == 'L') {
        if (position > 0)
            (*position)--;
    }
    return tape;
}
