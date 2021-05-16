#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    char Red[5][50];
    char Green[5][50];
    char Blue[5][50];
} Salonlar;

typedef enum
{
    ogrenci = 1,
    tam
} ucretler;

void Login(char kul[], char sif[]);
void Register();

void Menu();

void Rezervasyon();
int RedRezerve();
int GreenRezerve();
int BlueRezerve();
int koltuk_matine();

void DosyaOlustur_ALL();
void RedDosyaOlustur();
void GreenDosyaOlustur();
void BlueDosyaOlustur();

void Izlenme();
void RedIzlenme();
void GreenIzlenme();
void BlueIzlenme();

void Hasilat();

FILE *pSifre;
FILE *phasilat;
FILE *koltukred;
FILE *koltukgreen;
FILE *koltukblue;
int matine_secim;
int koltukno;
int tutar = 0;
int odemesekli;
int hasilat;
int koltuksayaci;

int main()
{
    Salonlar salon;
    ucretler ucret;
    int hasilat;
    int koltuksayaci = 0;

    DosyaOlustur_ALL();

    Register();

    Menu();

    return 0;
}

void Register()
{

    if ((pSifre = fopen("Sifre.txt", "a+")) == NULL)
    {
        printf("Sifre.txt Dosyasi Olusturulmadi !");
        exit(0);
    }
    fclose(pSifre);

    pSifre = fopen("Sifre.txt", "r"); // Sifre dosya oku
    char Kullanici_adi[20];
    char sifreli_sifre[20] = {0};
    char Sifre[20];

    fscanf(pSifre, "%s %s", Kullanici_adi, sifreli_sifre); // Sifre dosyasinda verileri Kullanici_adi ve sifreli_sifre degiskenine atar

    fclose(pSifre);
    if (strlen(sifreli_sifre) != 0) // Sifre dosyasinda veri var mi ?
    {
        Login(Kullanici_adi, sifreli_sifre);
    }
    else
    {

        // Sifre dosyasinda veri yoksa kayit islemi gerceklesir
        printf("Kayit islemi icin lutfen kullanici adinizi giriniz\n >>>  ");
        scanf("%s", Kullanici_adi);
        printf("Kayit islemi icin lutfen sifrenizi giriniz\n >>> ");
        scanf("%s", Sifre);
        // girilen sifreyi sifreleme
        char b;
        for (int i = 0; i < strlen(Sifre); i++)
        {
            b = (char)(((int)Sifre[i] - 65 + 6) % 26 + 65);

            sifreli_sifre[i] = b;
        }

        pSifre = fopen("Sifre.txt", "w");
        fprintf(pSifre, "%s %s", Kullanici_adi, sifreli_sifre); // dosyaya sifrelenmiş hali ile kaydetme
        fclose(pSifre);
        system("CLS");
        Login(Kullanici_adi, sifreli_sifre); // login fonksiyonuna yonlendirilir
    }
}

void Login(char kul[], char sif[])
{

    char sifre[20];
    char Kullanici_adi[20];
c:
    //  Sifre giris
    printf("\nMenuyu gormek icin Lutfen Kullanici adinizi giriniz:  ");
    scanf("%s", Kullanici_adi);

    printf("Sifrenizi Giriniz:  ");
    scanf("%s", sifre);

    if (strcmp(Kullanici_adi, kul) == 0) // kullanici adi denetleme
    {
        // login(sif[]) degiskeni ile alinan sifrelenmis sifreyi denetleme
        char b;
        for (int i = 0; i < strlen(sifre); i++)
        {
            //consolda girilen sifreyi sifreli haliyle kiyaslamak icin sifreler ve tek tek kiyaslar
            b = (char)(((int)sifre[i] - 65 + 6) % 26 + 65);

            if (b != sif[i])
            {
                printf("Sifrenizi yanlis girdiniz !\nnLutfen tekrar deneyin");
                exit(1);
            }
        }
    }
    else
    {
        printf("Kullanici adinizi yanlis girdiniz !\nLutfen tekrar deneyin");
        exit(1);
    }
}

void Menu()
{

    char menu_secim[1];
    printf("SINEMA OTOMASYON SISTEMINE HOSGELDINIZ.\n");
n:
    printf("\n--------------------------------------\n");
    printf("\nRezervasyon yapmak icin 1'e");
    printf("\nHasilati ogrenmek icin 2'e");
    printf("\nIzlenme miktarlari icin 3'e");
    printf("\nCikis yapmak icin  q'ya basiniz \n");
    scanf("%s", menu_secim);

    switch (menu_secim[0])
    {
    case '1':
        system("CLS");
        Rezervasyon();
        goto n;
        break;
    case '2':
        system("CLS");
        Hasilat();
        goto n;
        break;
    case '3':
        system("CLS");
        Izlenme();
        goto n;
        break;
    case 'q':
        printf("\nBasariyla cikis yapildi..\n---iyi gunler---\n");
        break;
    default:
        printf("\nGecersiz menu numarasi !\n");
        goto n;
        break;
    }
}

void Rezervasyon()
{
    Salonlar salon;
    Salonlar *psalon;
    psalon = &salon;
    char salon_secim;

m:
    printf("\n****************************\nHangi salona rezarvasyon yapmak istersiniz?\n Red icin R/r\n Green icin G/g\n Blue icin B/b \n");
    scanf("%s", &salon_secim);
    switch (salon_secim)
    {
    case 'R':
    case 'r':

        if (koltuk_matine() == 0)
            goto m;
        if (RedRezerve() == 1)
            goto m;
        break;
        break;

    case 'G':
    case 'g':
        if (koltuk_matine() == 0)
            goto m;
        if (GreenRezerve() == 1)
            goto m;
        break;
        break;

    case 'B':
    case 'b':
        if (koltuk_matine() == 0)
            goto m;
        if (BlueRezerve() == 1)
            goto m;
        break;
        break;
    default:
        printf("\nGecersiz salon ! Lutfen tekrar deneyin !\n");
        goto m;
        break;
    }
}

int RedRezerve()
{
    Salonlar salon;
    Salonlar *psalon;
    psalon = &salon;

    // koltuk bilgilerini Red dizisizine aktarma fonksiyonu
    koltukred = fopen("koltukred.txt", "r+");

    char tutucured[250];
    fscanf(koltukred, "%s", tutucured);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            psalon->Red[i][j] = tutucured[i * 50 + j];
        }
    }
    fclose(koltukred);

    // koltuk numarasi bosmu
    if (psalon->Red[matine_secim - 1][koltukno - 1] == '1')
    {
        printf("Bu koltuk numarasi dolu ! Lutfen tekrar deneyin");
        return 1;
    }
    psalon->Red[matine_secim - 1][koltukno - 1] = '1';

    // dosyayı güncelleme
    koltukred = fopen("koltukred.txt", "w+");
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < 50; k++)
        {

            if (psalon->Red[i][k] == '0')
            {

                fprintf(koltukred, "%c", '0');
            }
            if (psalon->Red[i][k] == '1')
            {
                fprintf(koltukred, "%c", '1');
            }
        }
    }

    fclose(koltukred);

    // bilet turu secme ogrenci/tam
    printf("Ogrenci bilet icin 1 , Tam bilet icin 2 'ye basiniz\n>> ");
    scanf("%d", &odemesekli);

    if (odemesekli == ogrenci)
    {
        tutar = 20;
        hasilat += tutar;
    }
    else if (odemesekli == tam)
    {
        tutar = 30;
        hasilat += tutar;
    }

    phasilat = fopen("log.txt", "w+");
    fprintf(phasilat, "%d", hasilat);
    fclose(phasilat);

    printf("\n----------------\n ISLEMINIZ BASARILI \n----------------\n");

    printf("\nKoltuk numaraniz: %d", koltukno);
    printf("\nUcretiniz  %d lira ", tutar);
}

int GreenRezerve()
{
    Salonlar salon;
    Salonlar *psalon;
    psalon = &salon;

    // koltuk bilgilerini Blue dizisizine aktarma fonksiyonu
    koltukgreen = fopen("koltukgreen.txt", "r+");

    char tutucugreen[250];
    fscanf(koltukgreen, "%s", tutucugreen);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            psalon->Green[i][j] = tutucugreen[i * 50 + j];
        }
    }
    fclose(koltukgreen);

    // koltuk numarasi bosmu
    if (psalon->Green[matine_secim - 1][koltukno - 1] == '1')
    {
        printf("Bu koltuk numarasi dolu ! Lutfen tekrar deneyin");
        return 1;
    }
    psalon->Green[matine_secim - 1][koltukno - 1] = '1';

    // dosyayı güncelleme
    koltukgreen = fopen("koltukgreen.txt", "w+");
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < 50; k++)
        {

            if (psalon->Green[i][k] == '0')
            {

                fprintf(koltukgreen, "%c", '0');
            }
            if (psalon->Green[i][k] == '1')
            {
                fprintf(koltukgreen, "%c", '1');
            }
        }
    }

    fclose(koltukgreen);

    // bilet turu secme ogrenci/tam
    printf("Ogrenci bilet icin 1 , Tam bilet icin 2 'ye basiniz\n>> ");
    scanf("%d", &odemesekli);

    if (odemesekli == ogrenci)
    {
        tutar = 20;
        hasilat += tutar;
    }
    else if (odemesekli == tam)
    {
        tutar = 30;
        hasilat += tutar;
    }

    phasilat = fopen("log.txt", "w+");
    fprintf(phasilat, "%d", hasilat);
    fclose(phasilat);
    printf("\n----------------\n ISLEMINIZ BASARILI \n----------------\n");
    printf("\nKoltuk numaraniz: %d", koltukno);
    printf("\nUcretiniz  %d lira ", tutar);
}

int BlueRezerve()
{
    Salonlar salon;
    Salonlar *psalon;
    psalon = &salon;

    koltukblue = fopen("koltukblue.txt", "r+");

    char tutucublue[250];
    fscanf(koltukblue, "%s", tutucublue); // koltuk bilgilerini 'tutucublue' dizisizine aktarma

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            psalon->Blue[i][j] = tutucublue[i * 50 + j]; // tutucublue verilerini Blue dizisizine aktarma
        }
    }
    fclose(koltukblue);

    // koltuk numarasi bosmu
    if (psalon->Blue[matine_secim - 1][koltukno - 1] == '1')
    {
        printf("Bu koltuk numarasi dolu ! Lutfen tekrar deneyin");
        return 1;
    }
    psalon->Blue[matine_secim - 1][koltukno - 1] = '1';

    // dosyayı güncelleme
    koltukblue = fopen("koltukblue.txt", "w+");
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < 50; k++)
        {

            if (psalon->Blue[i][k] == '0')
            {

                fprintf(koltukblue, "%c", '0');
            }
            if (psalon->Blue[i][k] == '1')
            {
                fprintf(koltukblue, "%c", '1');
            }
        }
    }

    fclose(koltukblue);

    // bilet turu secme ogrenci/tam
    printf("Ogrenci bilet icin 1 , Tam bilet icin 2 'ye basiniz\n>> ");
    scanf("%d", &odemesekli);

    if (odemesekli == ogrenci)
    {
        tutar = 20;
        hasilat += tutar;
    }
    else if (odemesekli == tam)
    {
        tutar = 30;
        hasilat += tutar;
    }

    phasilat = fopen("log.txt", "w+");
    fprintf(phasilat, "%d", hasilat);
    fclose(phasilat);
    printf("\n----------------\n ISLEMINIZ BASARILI \n----------------\n");
    printf("\nKoltuk numaraniz: %d", koltukno);
    printf("\nUcretiniz  %d lira ", tutar);
}

int koltuk_matine() // Matine ve koltuk numara gecerliligi  (0<matine<6   0<koltuk<50)
{
    printf("\nKac numarali matine (1,2,3,4,5)\n");
    scanf("%d", &matine_secim);
    if (matine_secim > 5 || matine_secim < 1)
    {
        printf("\nGecersiz matine numarasi ! Lutfen tekrar deneyin\n");
        return 0;
    }

    printf("Lutfen koltuk numaranizi giriniz.\n");
    scanf("%d", &koltukno);

    if (koltukno > 50 || koltukno < 1)
    {
        printf("\nGecersiz koltuk numarasi ! Lutfen tekrar deneyin\n");
        return 0;
    }
}

void Hasilat() // Hasilat dosyasindan Total hasilati gosterir
{
    int total_hasilat;
    phasilat = fopen("log.txt", "r");
    fscanf(phasilat, "%d", &total_hasilat);
    fclose(phasilat);
    printf("\nToplam Hasilat  : %d TL \n", total_hasilat);
}

void DosyaOlustur_ALL() // Hasilat koltukred,koltukgreen ve koltukblue dosyalari olusturma
{

    // Hasilat dosya olusturma
    if ((phasilat = fopen("log.txt", "a+")) == NULL)
    {
        printf("log.txt Dosyasi Olusturulmadi !");
        exit(0);
    }
    fscanf(phasilat, "%d", &hasilat);
    fclose(phasilat);

    RedDosyaOlustur();
    GreenDosyaOlustur();
    BlueDosyaOlustur();
}

void RedDosyaOlustur()
{

    // Red koltuk bilgileri dosyasi olusturma
    if ((koltukred = fopen("koltukred.txt", "a+")) == NULL)
    {
        printf("koltukred.txt Dosyasi Olusturulmadi !");
        exit(0);
    }
    // koltukred dosyasinin icinde 250 adet 0 yoksa   (red dizi[5][50]) dosyayi sifirlayip icine 0 'lari yazdir

    char a[250];
    fscanf(koltukred, "%s", a);
    if (strlen(a) != 250)
    {

        koltukred = fopen("koltukred.txt", "w");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                fputs("0", koltukred);
            }
        }
        fclose(koltukred);
    }
    fclose(koltukred);
}

void GreenDosyaOlustur()
{

    // Green koltuk bilgileri dosyasi olusturma
    if ((koltukgreen = fopen("koltukgreen.txt", "a+")) == NULL)
    {
        printf("koltukgreen.txt Dosyasi Olusturulmadi !");
        exit(0);
    }
    // koltukgreen dosyasinin icinde 250 adet 0 yoksa   (green dizi[5][50]) dosyayi sifirlayip icine 0 'lari yazdir

    char b[250];
    fscanf(koltukgreen, "%s", b);
    if (strlen(b) != 250)
    {
        koltukgreen = fopen("koltukgreen.txt", "w");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                fputs("0", koltukgreen);
            }
        }
        fclose(koltukgreen);
    }

    fclose(koltukgreen);
}

void BlueDosyaOlustur()
{

    // Blue koltuk bilgileri dosyasi YOKSA olusturur
    if ((koltukblue = fopen("koltukblue.txt", "a+")) == NULL)
    {
        printf("koltukblue.txt Dosyasi Olusturulmadi !");
        exit(0);
    }
    fclose(koltukblue);
    // koltukblue dosyasinin icinde 250 adet 0 yoksa   (blue dizi[5][50]) dosyayi sifirlayip icine 0 'lari yazdir
    char c[250];
    fscanf(koltukblue, "%s", c);
    if (strlen(c) != 250)
    {
        koltukblue = fopen("koltukblue.txt", "w");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                fputs("0", koltukblue);
            }
        }
        fclose(koltukblue);
    }
}

void Izlenme() // Salon ve matine izlenme
{
    Salonlar salon;
    Salonlar *psalon;
    psalon = &salon;

    printf("\n--------RED---------\n");

    RedIzlenme();

    printf("\n--------GREEN---------\n");

    GreenIzlenme();

    printf("\n--------BLUE---------\n");

    BlueIzlenme();
}

void RedIzlenme()
{
    Salonlar salon;
    Salonlar *psalon;
    psalon = &salon;
    int koltuk_sayi_red = 0;

    koltukred = fopen("koltukred.txt", "r");

    char tutucured[250];
    fscanf(koltukred, "%s", tutucured);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            psalon->Red[i][j] = tutucured[i * 50 + j];
        }
    }

    fclose(koltukred);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (psalon->Red[i][j] == '1')
            {
                koltuk_sayi_red++;
            }
        }
        printf("\n%d. Matine icin izlenme sayisi:  %d\n", i + 1, koltuk_sayi_red);
        koltuk_sayi_red = 0;
    }
}

void GreenIzlenme()
{
    Salonlar salon;
    Salonlar *psalon;
    psalon = &salon;
    int koltuk_sayi_green = 0;

    koltukgreen = fopen("koltukgreen.txt", "r");

    char tutucugreen[250];
    fscanf(koltukgreen, "%s", tutucugreen);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            psalon->Green[i][j] = tutucugreen[i * 50 + j];
        }
    }

    fclose(koltukgreen);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (psalon->Green[i][j] == '1')
            {
                koltuk_sayi_green++;
            }
        }
        printf("\n%d. Matine icin izlenme sayisi:  %d\n", i + 1, koltuk_sayi_green);
        koltuk_sayi_green = 0;
    }
}

void BlueIzlenme()
{
    Salonlar salon;
    Salonlar *psalon;
    psalon = &salon;
    int koltuk_sayi_blue = 0;
    koltukblue = fopen("koltukblue.txt", "r");

    char tutucublue[250];
    fscanf(koltukblue, "%s", tutucublue);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            psalon->Green[i][j] = tutucublue[i * 50 + j];
        }
    }

    fclose(koltukgreen);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (psalon->Green[i][j] == '1')
            {
                koltuk_sayi_blue++;
            }
        }
        printf("\n%d. Matine icin izlenme sayisi:  %d\n", i + 1, koltuk_sayi_blue);
        koltuk_sayi_blue = 0;
    }
}
