#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node NODE;

struct node {
    int info;
    NODE *ptr;
};

NODE *top, *top1, *temp;

void create () {
    top = NULL;
}

void push (int data) {
    if (top == NULL)
    {
        top = (NODE *) malloc (1 * sizeof (NODE));
        top->ptr  = NULL;
        top->info = data;
    }
    else
    {
        temp = (NODE *) malloc (1 * sizeof (NODE));
        temp->ptr  = top;
        temp->info = data;
        top = temp;
    }
}

void pop(){
    top1 = top;

    if (top1 == NULL)
    {
        printf ("\n Error : Trying to pop from empty stack");
        return;
    }
    else
        top1 = top1->ptr;
    
    free (top);
    top = top1;
}

void display () {
    top1 = top;

    if (top1 == NULL)
    {
        printf ("Stack is empty");
        return;
    }

    while (top1 != NULL)
    {
        printf ("%d->", top1->info);
        top1 = top1->ptr;
    }
 }

 int empty () {
    return (top == NULL)? 1: 0;
}

 int search (int value) {
    top1 = top;
    if (top1 == NULL)
    {
        printf ("Stack is empty");
        return;
    }

    while (top1 != NULL)
    {
        if (value == top1->info)
            return 1;
        else
        top1 = top1->ptr;
    }
    return 0;
 }

// Mevcut satır ve sütunun değerini döndürür.
int index_position (int row, int column, int edge){
    return (row * edge + column);
}

//Matris içerisinde yol arar.
int walk_in_maze (int* matrix, int edge, int out, int row, int column){
    int value = index_position (row, column, edge);

    // 1.  Burada matristen taşma önlenmiştir
    if(!(row>=0 && row<edge && column>=0 && column<edge))
        return 0;

    // 2.  Matrisin hesaplanan konumdaki değerine bakar 1 mi diye
    if(!(*(matrix+value)))
        return 0;

    // 3.  ilk stack boşmu bakar. Sonra Verilen değerin stackte olup olmadığına bakar.YOksa stack e koyar
    if (!empty() && search (value))
        return 0;
    else
        push (value);

    // 4.  Olası başka çıkışlara karşı çıkış koordinatını kontrol eder.
    if (value == out)
        return 1;

    // Burada matrisdeki mevcut konumun sağ sol alt ve üstünde yol var mı diye bakılır.
    if(!(walk_in_maze (matrix, edge, out, row, column+1)))
        if(!(walk_in_maze (matrix, edge, out, row, column-1)))
            if(!(walk_in_maze(matrix,edge,out,row+1,column)))
                if(!(walk_in_maze(matrix,edge,out,row-1,column))){
                    // Mevcut konumdan yol bulunmazsa bir adım geri gider.Yani son stack elemanını siler
                    pop();
                    return 0;
                }
}

// kare bir matrisi verilen araliklardaki sayilarla doldurur
void fill_rand_to_matrix (int* strt, int limit) {
    int i;
    for (i = 0; i < limit ;i++)
        *(strt++) = (rand() % 2);
}

// İstenilen boyuta göre bellekten yer ayırır 1 ve 0 ile doldurup çağıran fonksiyona adres return eder.
int* create_Matrix (int edge) {
    int  limit  = edge*edge;
    int* matrix = (int*) malloc (limit * sizeof (int));
    return matrix;
}

// Matrisi ekrana yazar
void put_matrix (int* matrix, int edge){
    int i, j;
    printf ("\n");
    for (i = 0; i < edge; i++) {
        printf ("{ ");
        for(j = 0; j < edge; j++)
            printf ("%d ", *(matrix++));
            printf ("}\n");
    }
}
// Mevcut yolu matrise  yazar
void write_current_route (int* matrix, int edge) {
    int i, j, value;
    for (i = 0; i < edge; i++) {    
        for (j = 0; j < edge; j++) {
            value = i * edge + j;
            *(matrix + value) = search(value)?1:0;
        }
    }
}

void find_way (int* matrix,int* matrix1, int edge) {
    int row, column, m, n, flag, out_value;
    int limit = edge*edge;
    fill_rand_to_matrix (matrix, limit);
    put_matrix (matrix, edge);

    printf ("\nGiris koordinati giriniz : \n");
    scanf  ("%d %d", &row, &column);

    printf ("Cikis koordinati giriniz : \n");
    scanf  ("%d %d", &m, &n);
    out_value = index_position (m, n, edge);
    flag = walk_in_maze (matrix, edge, out_value, row, column);

    if (flag) {
        printf ("\nYol bulunmustur\n");
        write_current_route (matrix1, edge);
        put_matrix (matrix1, edge);
        printf ("\nGuzergah : \n");
        display ();
        printf ("\n");
    }
    else
        printf ("\nYol bulunamamistir.\n");
}
int main () {
    int edge;
    int *matrix, *matrix1;
    create ();
    srand (time(NULL));
    printf ("Matris kenarini giriniz: ");
    scanf ("%d", &edge);
    
    //Buradaki Matrix1 stack deki değerleri aktarmak için Yani güzergahı daha net belirtmek için
    matrix  = create_Matrix (edge);
    matrix1 = create_Matrix (edge);
    
    find_way (matrix, matrix1, edge);
    
    free (matrix);
    free (matrix1);
    return 0;
}
