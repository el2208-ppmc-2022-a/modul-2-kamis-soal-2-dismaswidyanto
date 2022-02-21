/*EL2208 Praktikum Pemecahan Masalah dengan C 2021/2022
*Modul            : 2 - Strings and External Files
*Percobaan        : -
*Hari dan Tanggal : Kamis, 24 Februari 2022
*Nama (NIM)       : -
*Asisten (NIM)    : -
*Nama File        : soal-02.c
*Deskripsi        : -
*/

#define MAX_ENTRY 20
#define MAX_STRLEN 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    //variabel baca file
    FILE *fp;
    char buff[255]; 
    char filename[MAX_STRLEN]; 
    int eof = 0;

    //variabel kota, penduduk, dan indeks jatah makanan
    char kota[MAX_ENTRY][MAX_STRLEN];
    int penduduk[MAX_ENTRY];
    int konsum[MAX_ENTRY];  

    //variabel search
    char search[MAX_STRLEN];
    int isNumber = 0;

    //Input nama file
    printf("Masukkan nama file: ");
    scanf(" %s",filename); 
 
    //buka file csv
    fp = fopen(filename, "r");    

    //parsing
    int index = 0;
    while (!feof(fp)){
        char* token;
        fgets(buff, 255, (FILE*)fp);  

        token = strtok(buff, ",");          //parsing nama kota   
        strcpy(kota[index], token);           
        token = strtok(NULL, ",");          //parsing jumlah penduduk
        penduduk[index] = atoi (token);     
        index++;  
    }

    fclose(fp); 

    //mencari indikator jatah makan tiap kota
    for (int i = 0; i < index; i++){
        if (penduduk[i] < 50000) {
            konsum[i] = 1;
        }  
        else if (penduduk[i] >= 50000 && penduduk[i] < 100000) {
            konsum[i] = 2;
        } 
        else if (penduduk[i] >= 100000 && penduduk[i] < 150000) {
            konsum[i] = 3;
        } 
        else if (penduduk[i] >= 150000 && penduduk[i] < 200000) {
            konsum[i] = 4;
        } 
        else if (penduduk[i] >= 200000) {
            konsum[i] = 5;
        } 
    } 
    
    //user input untuk search
    printf("\nMasukkan pencarian: ");
    scanf("%s", search);

    //perintah print all. setelah print all, program selesai.
    if (strcmp(search,"all") == 0){
        for (int i = 0; i < index; i++){ 
            printf("Kota %s - populasi: %d - jatah makan: %d\n", kota[i], penduduk[i], konsum[i]); 
        }
        return 0;           
    }
    
    //check apakah input berupa integer atau huruf
    if(search[0] > '0' && search[0] < '9'){
        isNumber = 1;
    }
    else{
        isNumber = 0;
    }
       
    //search serta print hasil search bila ada entry yang valid 
    int isAnyFound = 0;
    for (int i = 0; i < index; i++){
        
        if (strstr(kota[i],search)>0 && isNumber == 0){ 
            printf("Kota %s - populasi: %d - jatah makan: %d\n", kota[i], penduduk[i], konsum[i]);
            isAnyFound = 1;
        }
        
        if ( (atoi(search) == konsum[i]) || (abs(atoi(search) - penduduk[i]) < 20000) && (isNumber == 1) ){ 
            printf("Kota %s - populasi: %d - jatah makan: %d\n", kota[i], penduduk[i], konsum[i]);
            isAnyFound = 1;
        }
    }

    //output bila tidak ada entry yang valid
    if (!isAnyFound){
        printf("Tidak ada entry yang valid. Harap coba lagi\n");
    } 

    return 0;
}
