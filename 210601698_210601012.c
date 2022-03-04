//Seçim Simülasyonu Yazılımı: Grup 14
//Hazırlayanlar: Muhammed Samed Karakuş & Emre Horuz

#include <stdio.h>
#include <stdlib.h>

//Global olarak girdiğimiz atamalar.
char partiIsimleri[6] = {'A','B','C','D','E','F'};
int partiSayisi = 6, ilSayisi = 5 , milletvekiliSayisi, kabarcik, gecerliOySayisi[6][3] = {0}, genelPartiOyuSayisi[6] = {0};
int partilerinGenelMilletvekiliSayisi[6][2] = {0}, iktidarVeMuhalefetPartileri[6][2], birincilik[6][1] = {0};
float ildekiToplamGecerliOySayisi = 0, genelOySayisi = 0, partilerinOyYuzdesi = 0, partilerinMilletvekiliYuzdesi = 0, genelMilletvekiliSayisi = 0;

//Kabarcık Sıralama Fonksiyonu
int kabarcikSiralama(int c, int isim[c][2]){
    for(int b = 0; b < c; b++){
        for(int j = 0; j < c-1; j++){
            if(isim[j][0] < isim[j+1][0]){

                int kabarcik;
                kabarcik = isim[j][0];
                isim[j][0] = isim[j+1][0];
                isim[j+1][0] = kabarcik;

                kabarcik = isim[j][1];
                isim[j][1] = isim[j+1][1];
                isim[j+1][1] = kabarcik;
            }
        }
    }
}

//İktidar ve Ana Muhalefet Partilerini bulabilmek için yaptığımız fonksiyon.
int genelKabarcikSiralama(int c, int z[][2]){
    int iktidarVeMuhalefetPartileri[c][2];
    int partiSayisi = 6;
    for(int a = 0; a < c; a++){
        iktidarVeMuhalefetPartileri[a][0] = z[a][0];
        iktidarVeMuhalefetPartileri[a][1] = a;
    }
    kabarcikSiralama(partiSayisi, iktidarVeMuhalefetPartileri[c][2]);

    for(int i = 0; i < partiSayisi; i++){
        partilerinMilletvekiliYuzdesi = (partilerinGenelMilletvekiliSayisi[i][0] * 100) / genelMilletvekiliSayisi;
        partilerinOyYuzdesi = (genelPartiOyuSayisi[i] * 100) / genelOySayisi;
        printf("\n%c Partisi\t%d\t\t%.2f\t\t%d\t\t%.2f\t\t\t%d", partiIsimleri[i], genelPartiOyuSayisi[i], partilerinOyYuzdesi, partilerinGenelMilletvekiliSayisi[i][0], partilerinMilletvekiliYuzdesi, birincilik[i][0]);
    }
    printf("\n\nIktidar Partisi: %c\nAna Muhalefet Partisi: %c", partiIsimleri[iktidarVeMuhalefetPartileri[0][1]], partiIsimleri[iktidarVeMuhalefetPartileri[1][1]]);
}

//Partilerin oy sayılarına göre kaç ilde birinci parti olduklarını hesaplayan fonksiyon.
int oyaGoreKacIldeBirincilikSayisi(int x, int isim[x][2]){
    for(int i = 0; i < x; i++){
        if(isim[x][2] == i){
            birincilik[i][0]++;
            break;
        }
    }
}


int main(){
    //Sistemin kullanıcıdan istediği ilin milletvekili kontenjanın girişini yaptırıyoruz.
    for (int i = 0; i < ilSayisi; i++){
        printf("\n\nLutfen %d plaka kodlu ilin bilgilerini sirasiyla giriniz\n", i+1);
        printf("Milletvekili kontenjanini: ");
        scanf("%d", &milletvekiliSayisi);
        printf("\n");
        genelMilletvekiliSayisi += milletvekiliSayisi;

        for(int i = 0; i < partiSayisi; i++){
            printf("%c Partisi: ", partiIsimleri[i]); 
            scanf("%d", &gecerliOySayisi[i][0]);         //Kac adet parti varsa onların oylarını alıp gecerliOySayisi[i][0]'a atıyoruz.
            ildekiToplamGecerliOySayisi += gecerliOySayisi[i][0];         //Toplam oyu bulmak icin oyları toplatıyoruz.
            genelPartiOyuSayisi[i] += gecerliOySayisi[i][0];      //Partinin her ilden aldığı oyların toplamı.
        }
        genelOySayisi += ildekiToplamGecerliOySayisi;     //Ülke genelindeki oy sayısını, her ilden toplanan oyların bütünüyle birleştiriyoruz.
        
        //Parti sayısına göre, parti sayılarını ve milletvekili sayılarını matrikslere yerleştiriyoruz.
        for(int i = 0; i < partiSayisi; i++){
            gecerliOySayisi[i][2] = i;
            partilerinGenelMilletvekiliSayisi[i][1] = i;
        }

        //Partileri, aldıkları oylara göre sıralamaya sokuyoruz.
        for(int a = 0; a <= partiSayisi; a++){
            for(int b = 0; b <= partiSayisi; b++){
                if(gecerliOySayisi[a][0] > gecerliOySayisi[b][0]){

                    kabarcik = gecerliOySayisi[a][0];
                    gecerliOySayisi[a][0] = gecerliOySayisi[b][0];
                    gecerliOySayisi[b][0] = kabarcik;

                    kabarcik = gecerliOySayisi[a][2];
                    gecerliOySayisi[a][2] = gecerliOySayisi[b][2];
                    gecerliOySayisi[b][2] = kabarcik;
                }
            }
        }
        oyaGoreKacIldeBirincilikSayisi(partiSayisi, gecerliOySayisi);       //Her partinin oy sayısına göre, kaç kere birinci olduğunu gösteren fonksiyonu çağırıyoruz.
        
        /*Geçerli oy olarak girilen değeri sonucu etkilemesin diye başka bir matrikse kopyalıyoruz.
        Milletvekili ataması yaparken yeni atanan matrix, ikiye bölünerek sistemin devamını sağlayacaktır.*/
        int partiOyununYarisi[partiSayisi][2];
        for(int i = 0; i < partiSayisi; i++){
            partiOyununYarisi[i][0] = gecerliOySayisi[i][0];
            partiOyununYarisi[i][1] = i;
        }

        //Oy sıralaması sonucunda, kopyaladığımız matriksi kullanarak oy sayılarını 2'ye bölüyoruz ve milletvekili atamalarını tamamlıyoruz.
        while (milletvekiliSayisi > 0){
            kabarcikSiralama(partiSayisi, partiOyununYarisi);
            milletvekiliSayisi -= 1;
            gecerliOySayisi[partiOyununYarisi[0][1]][1] += 1;
            partiOyununYarisi[0][0] /= 2;
        }
        printf("\n\t\tOy Sayisi\tOy Yuzdesi\tMilletvekili Sayisi");
        printf("\n\t\t---------\t----------\t-------------------");
        
        //Oy yüzdesinin de hesabıyla illerdeki partilerin bilgilerini çıktı veriyoruz.
        for(int k = 0; k < partiSayisi; k++){
            partilerinOyYuzdesi = ((gecerliOySayisi[k][0] * 100) / ildekiToplamGecerliOySayisi);
            printf("\n%c Partisi \t   %d \t\t  %.2f\t\t\t%d", partiIsimleri[gecerliOySayisi[k][2]], gecerliOySayisi[k][0], partilerinOyYuzdesi, gecerliOySayisi[k][1]);
        }
        printf("\n\n%d plaka kodlu ildeki toplam gecerli oy sayisi: %.0f", i+1, ildekiToplamGecerliOySayisi);       //İldeki geçerli oy sayısı.
        
        //Atamalardan sonra sayısal olarak belli olan milletvekili sayılarını matriksin içine depoluyoruz.
        for(int i = 0; i < partiSayisi; i++){
        	partilerinGenelMilletvekiliSayisi[gecerliOySayisi[i][2]][0] += gecerliOySayisi[i][1];
		}

        //En büyük "for" döngüsü sonunda, il için geçerli bilgileri sıfırlıyoruz çünkü gerekli olduğu alanlara depolandılar ve sıradaki il için gerekli bilgileri alacağız.
        ildekiToplamGecerliOySayisi = 0;
        milletvekiliSayisi = 0;
        for(int i = 0; i < partiSayisi; i++){
            gecerliOySayisi[i][1] = 0;
        }
    }
    
    //Ülke genelindeki sonuçların açıklanması.
    printf("\n\nIllerin Genel Sonuclari");
    printf("\nGenel Milletvekili Kontenjani: %.0f", genelMilletvekiliSayisi);
    printf("\nGenel Gecerli Oy Sayisi: %.0f", genelOySayisi);
    printf("\n\t     Oy Sayisi\t     Oy Yuzdesi\t     MV Sayisi\t     MV Yuzdesi\t     Oya Gore Kac ilde Birinci");
    printf("\n\t     ---------\t     ----------\t     ---------\t     ----------\t     -------------------------");
    genelKabarcikSiralama(partiSayisi, partilerinGenelMilletvekiliSayisi);

    return 0;
}