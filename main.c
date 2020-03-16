
#include <stdio.h>
#include <stdlib.h>

struct takim
{
    char takma_isim;
    char isim[20][12];
    int galibiyet;         //struct yapisi tanimladik.//
    int beraberlik;
    int maglubiyet;
    int atilan_gol;
    int yenilen_gol;
    int averaj;
    int puan;
    int takimsayisi;

};
struct takim ev[50];
struct takim misafir[50];
int macsayisi; //her yerde tekrar tekrar cagirmamak icin global//

void satirsayisi()
{
     FILE *dosya1=fopen("maclar.txt","r");
     macsayisi=0;
     char ch;

     if(dosya1!=NULL)
       {while(ch!=EOF)                //satir sayisini cekerek dosyaya girilen mac sayisini hesapladik.//
            {ch=fgetc(dosya1);
                    if(ch=='\n')
                      {macsayisi++;
                      }
            }
        //printf("satir=%d",macsayisi+1);//
        fclose(dosya1);}
      else{
        printf("Dosya bulunamadi");}

}

void ayarlama()
{
//ayarlar.txt den takimsayisi, galibiyet... gibi verileri cektik//
    FILE *dosya=fopen("ayarlar.txt","r");
    fscanf(dosya, "%d %d %d %d" ,&ev[0].takimsayisi,&ev[0].galibiyet,&ev[0].beraberlik,&ev[0].maglubiyet);
    fclose(dosya);

}

void d_acma()
{

    FILE *dosya=fopen("maclar.txt","r");
    int i,k,j;
    satirsayisi();                    //maclar dosyasini okutup golleri diziye atadik.//

    if(dosya!=NULL)
      {for(i=1;i<=macsayisi+1;i++)
        {
        fscanf(dosya,"%s %d %s %d",&ev[i].takma_isim,&ev[i].atilan_gol,&misafir[i].takma_isim,&misafir[i].atilan_gol);
        }
   fclose(dosya);
      }

        else{
  printf("Dosya bulunamadi");}

}

void kontrol(){

int i,j,k;        //yanlis giris kontrollerini yaptik//
ayarlama();
d_acma();
for(i=1;i<=macsayisi+1;i++)
    {if(misafir[i].takma_isim==ev[i].takma_isim)
        {
        printf("\n\t Bir takim kendi kendine mac yapamaz!!\n"); //Bir takim kendi kendiyle maç yapmaya çalýþýrsa ekranda uyarý mesajý çýkar.//
        }
    }
for(k=1;k<=macsayisi+1;k++)
            {for(j=k+1;j<=macsayisi+1;j++)
                {if(misafir[k].takma_isim==misafir[j].takma_isim && ev[k].takma_isim==ev[j].takma_isim)
                   { printf("\t Ayni mac iki kere oynanmistir!!\n"); //Oynanan mac tekrar ediyorsa uyarý verir.//
                   }
                 }
            }

}

void hesaplama(int sonuclar[5][ev[0].takimsayisi]){

d_acma();
ayarlama();
char* alfabe[23]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','R','S','T','U','V','Y','Z'};
int g,m,b,i,j;
g=ev[0].galibiyet;
m=ev[0].maglubiyet;
b=ev[0].beraberlik;
     //Tüm takimlari 1'den başlattığımız için döngüleri ona göre ayarladik.//

    for(j=0;j<ev[0].takimsayisi;j++)
        {for(i=1;i<=macsayisi+1;i++)
            {
            if(ev[i].takma_isim==alfabe[j])
              {if(ev[i].atilan_gol>misafir[i].atilan_gol)
                 {
                    sonuclar[0][j]++;
                    sonuclar[4][j]+=ev[i].atilan_gol-misafir[i].atilan_gol; //averaj hesabi//
                 }
               if(ev[i].atilan_gol==misafir[i].atilan_gol)     //Burda sonuc hesaplamak icin ev sahibi takimin ismine(A,B,C.. göre )//
                  {                     //katsayi(mağlubiyet,galibiyet ve beraberlik) hesapladik.//
                    sonuclar[1][j]++;
                  }
               if(ev[i].atilan_gol<misafir[i].atilan_gol)
                 {
                    sonuclar[2][j]++;
                    sonuclar[4][j]+=ev[i].atilan_gol-misafir[i].atilan_gol; //averaj hesabi//
                 }
              }

             }
         }
    for(j=0;j<ev[0].takimsayisi;j++)
       {for(i=1;i<=macsayisi+1;i++)
           {if(misafir[i].takma_isim==alfabe[j])
              {if(misafir[i].atilan_gol>ev[i].atilan_gol)
                 {
                    sonuclar[0][j]++;   //galibiyet.//
                    sonuclar[4][j]+=misafir[i].atilan_gol-ev[i].atilan_gol; //averaj hesabi//
                 }
                if(misafir[i].atilan_gol==ev[i].atilan_gol)
                  {
                    sonuclar[1][j]++;  //beraberlik//
                  }
                if(misafir[i].atilan_gol<ev[i].atilan_gol)
                  {
                    sonuclar[2][j]++;  //mağlubiyet//
                    sonuclar[4][j]+=misafir[i].atilan_gol-ev[i].atilan_gol; //averaj hesabi//
                  }
              }
           }
       }


         for(i=0;i<ev[0].takimsayisi;i++)
            {
                sonuclar[3][i]=(sonuclar[0][i]*g)+(sonuclar[1][i]*b)+(sonuclar[2][i]*m);  //puan hesabi//
            }
}

void takim_isimleri(char isimler[10][12])
{  isimler[ev[0].takimsayisi][12];
    int i=0;
    FILE *dosya1=fopen("takimlar.txt","r");
    while(i<ev[0].takimsayisi){              //takim isimlerini dosyadan cektik//
    fscanf(dosya1,"%s",isimler[i]);

    i++;}

}
void sort(int dizi[], int eleman,char alfabe[],int dizi1[],int dizi2[],int dizi3[],int dizi4[]){

 int i,j,kucuk1,kucuk2,kucuk3,temp1,kucuk,temp,temp2,temp3,temp4,temp5,kucuk4,kucuk5;


  for(i=0;i<eleman-1;i++){
    kucuk=i;
    kucuk1=i;
    kucuk2=i;
    kucuk3=i;
    kucuk4=i;
    kucuk5=i;

    for(j=i+1;j<eleman;j++){
        if(dizi[kucuk]>dizi[j]){
            kucuk=j;
            kucuk1=j;
            kucuk2=j;
            kucuk3=j;
            kucuk4=j;
            kucuk5=j;
            }
    }
        if(kucuk!=i){
        temp=dizi[i];
        dizi[i]=dizi[kucuk];
        dizi[kucuk]=temp;

        temp1=alfabe[i];
        alfabe[i]=alfabe[kucuk1];
        alfabe[kucuk1]=temp1;

        temp2=dizi1[i];
        dizi1[i]=dizi1[kucuk2];
        dizi1[kucuk2]=temp2;


        temp3=dizi2[i];
        dizi2[i]=dizi2[kucuk3];
        dizi2[kucuk3]=temp3;

        temp4=dizi3[i];
        dizi3[i]=dizi3[kucuk4];
        dizi3[kucuk4]=temp4;

        temp5=dizi4[i];
        dizi4[i]=dizi4[kucuk5];
        dizi4[kucuk5]=temp5;
    }
  }
}


void d_yazma1()
{   int i=0,j=0,k=0;

   int sonuclar[5][ev[0].takimsayisi];
   for(j=0;j<5;j++){
        for(k=0;k<ev[0].takimsayisi;k++){
            sonuclar[j][k]=0;
        }
    }

hesaplama(sonuclar);
    char* alfabe[23]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','R','S','T','U','V','Y','Z'};
    FILE *dosya=fopen("output.txt","w");
    char kelime[ev[0].takimsayisi][12];
    takim_isimleri(kelime);
    int sira[7][ev[0].takimsayisi];
    int gecici,tut;

     for(i=0;i<ev[0].takimsayisi;i++){
        sira[0][i]=kelime[i];
        sira[1][i]=alfabe[i];
        sira[2][i]=sonuclar[0][i];
        sira[3][i]=sonuclar[1][i];
        sira[4][i]=sonuclar[2][i];
        sira[5][i]=sonuclar[3][i];
        sira[6][i]=sonuclar[4][i];

     }


      for(i=0;i<ev[0].takimsayisi;i++){

    fprintf(dosya,"  %s (%c)Takiminin Galibiyet Sayisi:%d Beraberlik sayisi:%d  Maglubiyet Sayisi:%d  Puan Durumu:%d  Averaj:%d\n\n",kelime[i],sira[1][i],sira[2][i],sira[3][i],sira[4][i],sira[5][i],sira[6][i]);

                      }
}
void d_yazma2()
{   int i=0,j=0,k=0;

   int sonuclar[5][ev[0].takimsayisi];
   for(j=0;j<5;j++)
      {
        for(k=0;k<ev[0].takimsayisi;k++)
            {
            sonuclar[j][k]=0;
            }
      }


hesaplama(sonuclar);
    char alfabe[10]={'A','B','C','D','E','F','G','H','I','J'};
    FILE *dosya=fopen("output.txt","w");
    char kelime[ev[0].takimsayisi][12];
    takim_isimleri(kelime);
    int sira[7][ev[0].takimsayisi];
    int a,b,gecici,tut;

     for(i=0;i<ev[0].takimsayisi;i++)
        {
            sira[0][i]=kelime[i];
            sira[1][i]=alfabe[i];
            sira[2][i]=sonuclar[0][i];
            sira[3][i]=sonuclar[1][i];
            sira[4][i]=sonuclar[2][i];
            sira[5][i]=sonuclar[3][i];
            sira[6][i]=sonuclar[4][i];

       }

sort(sira[5],ev[0].takimsayisi,alfabe,sira[2],sira[3],sira[4],sira[6]);

for(i=ev[0].takimsayisi-1;i>=0;i--)
        {
            fprintf(dosya," (%c)Takiminin Galibiyet Sayisi:%d Beraberlik sayisi:%d  Maglubiyet Sayisi:%d  Puan Durumu:%d  Averaj:%d\n\n",alfabe[i],sira[2][i],sira[3][i],sira[4][i],sira[5][i],sira[6][i]);

        }


}

int main()
{int secim;
kontrol();
printf("secim="); scanf("%d",&secim);
if(secim==0)
    {
        d_yazma1();
    }
else{
    d_yazma2();
    }

}

