

typedef struct bigInt
{
	unsigned* words;
    int wordsCount;
	int sign;
} bigInt;

bigInt* initializationBigInt(char* strNumber);
void print(bigInt* a);
bigInt* sumPositive(bigInt* a, bigInt* b);
bigInt* subPositive(bigInt *a, bigInt *b);
int cmpAbs(bigInt *f, bigInt *s);
bigInt* addition(bigInt* a, bigInt* b);
bigInt* substraction(bigInt* a, bigInt* b);
int checkInput(char* str);
void freeAll(bigInt* a);
