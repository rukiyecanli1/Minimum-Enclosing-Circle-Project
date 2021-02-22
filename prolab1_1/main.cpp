#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <graphics.h>


struct Nokta
{
    double x;
    double y;
};
struct Cember
{
    struct Nokta m;
    double yc;
};

FILE *dosya, *dosya2;
int i=0,satir=0,ch=0;
char karakter1[40],karakter2[40], karakter3[40],karakter4[20],karakter5[20];


void xEksenleriniCiz()
{
    for(int k=0; k<40; k++)
    {
        setcolor(RED);
        setlinestyle(DOTTED_LINE, 0, NORM_WIDTH );
        line(800,20*k,0,20*k);
        //kýsa cizgiler
        setcolor(WHITE);
        setlinestyle(SOLID_LINE, 0, THICK_WIDTH );
        line(395,20*k,405,20*k);

        if(k==20)
        {
            setcolor(WHITE);
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
            line(800,20*k,0,20*k);
        }
    }
}

void yEksenleriniCiz()
{
    for(int j=0; j<40; j++)
    {
        setcolor(RED);
        setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
        line(20*j,800,20*j,0);
        //kisa çizgiler
        setcolor(WHITE);
        setlinestyle(SOLID_LINE, 0, THICK_WIDTH );
        line(20*j,395,20*j,405);

        if(j==20)
        {
            setcolor(WHITE);
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH );
            line(20*j,800,20*j,0);

        }
    }
}

void xEkseniSayilari()
{
    int x=-20;
    for(int j=0; j<40; j++)
    {
        sprintf(karakter1, "%d",x);
        outtextxy(20*j,402,karakter1);
        x=x+1;
    }
}


void yEkseniSayilari()
{
    int y=20;
    for(int j=0; j<40; j++)
    {
        sprintf(karakter2, "%d",y);
        outtextxy(402,20*j,karakter2);
        y=y-1;

    }
}

void cemberCizdir(struct Cember min_cember)
{
    setcolor(YELLOW);
    circle(400+(min_cember.m.x)*20,400-(min_cember.m.y)*20,(20*min_cember.yc));
    setcolor(GREEN);
    line(400+min_cember.m.x*20,400-min_cember.m.y*20,400+min_cember.m.x*20+min_cember.yc*20,400-min_cember.m.y*20);
    sprintf(karakter5,"%.4f",min_cember.yc);
    outtextxy(370+(int)(min_cember.yc*20)/2+min_cember.m.x*20,380-min_cember.m.y*20,"R=");
    outtextxy(390+(int)(min_cember.yc*20)/2+min_cember.m.x*20,380-min_cember.m.y*20,karakter5);
    circle(400+min_cember.m.x*20,400-min_cember.m.y*20,3);
    sprintf(karakter4,"(%.2f,%.2f)",min_cember.m.x,min_cember.m.y);
    outtextxy(402+min_cember.m.x*20,402-min_cember.m.y*20,karakter4);
}


double mesafeHesapla(struct Nokta koordinatA, struct Nokta koordinatB)
{
    double mesafe=sqrt(pow(koordinatA.x-koordinatB.x,2)+pow(koordinatA.y-koordinatB.y,2));
    return mesafe;
}


struct Cember geciciCemberOlustur(struct Nokta aNoktasi, struct Nokta bNoktasi)
{
    struct Nokta cNoktasi;
    cNoktasi.x=(aNoktasi.x+bNoktasi.x)/2.0;
    cNoktasi.y=(aNoktasi.y+bNoktasi.y)/2.0;
    double mesafe2=(mesafeHesapla(aNoktasi,bNoktasi))/2.0;
    struct Cember c;
    c.m.x=cNoktasi.x;
    c.m.y=cNoktasi.y;
    c.yc=mesafe2;
    return c;
}

struct Cember geciciCemberOlustur2(struct Nokta aNoktasi, struct Nokta bNoktasi, struct Nokta cNoktasi)
{
    struct Nokta Q;
    double B=(bNoktasi.x-aNoktasi.x)*(bNoktasi.x-aNoktasi.x)+(bNoktasi.y-aNoktasi.y)*(bNoktasi.y-aNoktasi.y);
    double C=(cNoktasi.x-aNoktasi.x)*(cNoktasi.x-aNoktasi.x)+(cNoktasi.y-aNoktasi.y)*(cNoktasi.y-aNoktasi.y);
    double D=((bNoktasi.x-aNoktasi.x)*(cNoktasi.y-aNoktasi.y)-(bNoktasi.y-aNoktasi.y)*(cNoktasi.x-aNoktasi.x))+0.000000001;
    Q.x=((cNoktasi.y-aNoktasi.y)*B-(bNoktasi.y-aNoktasi.y)*C)/(2*D);
    Q.y=((bNoktasi.x-aNoktasi.x)*C-(cNoktasi.x-aNoktasi.x)*B)/(2* D);
    Q.x+=aNoktasi.x;
    Q.y+=aNoktasi.y;
    double mesafe=mesafeHesapla(Q,aNoktasi);
    struct Cember c2;
    c2.m.x=Q.x;
    c2.m.y=Q.y;
    c2.yc=mesafe;
    return c2;
};

bool kapsiyorMu(struct Cember cCemberi, struct Nokta koorXY[])
{
    int i=0;
    for(i=0; i<satir; i++)
        if((mesafeHesapla(cCemberi.m,koorXY[i])<=cCemberi.yc)!=true)
            return false;
    return true;
}

//kaynak: https://www.geeksforgeeks.org/cubic-bezier-curve-implementation-in-c/
void bezierCizdir(struct Nokta koorXY[])
{
    double t=0,xKoordinati=0,yKoordinati=0;
   while(t<1)
    {
        xKoordinati=pow(1-t,3)*(koorXY[0].x) + 3*t*pow(1-t,2)*(koorXY[1].x) +
           (3*pow(t,2))*(1-t)*(koorXY[2].x) + (pow(t,3)*koorXY[3].x);
        yKoordinati=pow(1-t,3)*(koorXY[0].y) + 3*t*pow(1-t,2)*(koorXY[1].y) +
           (3*pow(t,2))*(1-t)*(koorXY[2].y) + (pow(t,3)*koorXY[3].y);
        putpixel(400+(xKoordinati*20),400-(yKoordinati*20),9);
        t+=0.0001;
    }
}

int main()
{

    int gd = DETECT;
    int gm;
    initwindow(800,800,"");

    xEksenleriniCiz();
    xEkseniSayilari();
    yEksenleriniCiz();
    yEkseniSayilari();

    dosya=fopen("noktalarr.txt","r");
    dosya2= fopen("noktalarr.txt","r");

    if(dosya==NULL)
        printf("Dosya bulunamadi.");
    if(dosya2 == NULL)
        printf("Dosya bulunamadi.");


    while(!feof(dosya2))
    {
        ch = fgetc(dosya2);
        if(ch == '\n')//new line gordukce satir bir artirilir.
        {

            satir++;
        }
    }
    satir++;


    struct Nokta koordinatXY[satir];
    char vx[satir];
    char vy[satir];

    printf("\n-----Noktalar----\n");
    while( fscanf(dosya, "%s %s\n", &vx, &vy) != EOF )
    {
        printf("\n----%d----\n",i+1);
        koordinatXY[i].x =atof((const char*)vx);
        koordinatXY[i].y=atof((const char*)vy);
        printf("x : %.f| y : %.f\n",koordinatXY[i].x,koordinatXY[i].y);
        circle((400+(koordinatXY[i].x)*20),(400-(koordinatXY[i].y)*20),2);
        sprintf(karakter3,"(%.f,%.f)",koordinatXY[i].x,koordinatXY[i].y);
        outtextxy(402+koordinatXY[i].x*20,402-koordinatXY[i].y*20,karakter3);
        printf("/-----------/ \n");
        i++;
    }


    struct Cember min_cember;
    min_cember.m.x=0.0;
    min_cember.m.y=0.0;
    min_cember.yc=100.0;

    for(int i=0; i<satir; i++)
    {
        for(int j=i+1; j<satir; j++)
        {
            struct Cember gecici_cember=geciciCemberOlustur(koordinatXY[i],koordinatXY[j]);
            if (gecici_cember.yc < min_cember.yc && kapsiyorMu(gecici_cember, koordinatXY))
            {
                min_cember.m.x=gecici_cember.m.x;
                min_cember.m.y=gecici_cember.m.y;
                min_cember.yc=gecici_cember.yc;
            }
        }
    }


    for (int i=0; i<satir; i++)
    {
        for (int j=i+1; j<satir; j++)
        {

            for (int k=j+1; k<satir; k++)
            {

                struct Cember gecici_cember = geciciCemberOlustur2(koordinatXY[i], koordinatXY[j], koordinatXY[k]);
                if (gecici_cember.yc < min_cember.yc && kapsiyorMu(gecici_cember, koordinatXY))
                {
                    min_cember.m.x=gecici_cember.m.x;
                    min_cember.m.y=gecici_cember.m.y;
                    min_cember.yc=gecici_cember.yc;
                }
            }
        }
    }

    printf("\nEn kucuk cemberin yaricapi: %.4f\n",min_cember.yc);
    printf("En kucuk cemberin merkez koordinatlari: %.3f, %.3f", min_cember.m.x, min_cember.m.y);

    cemberCizdir(min_cember);
   bezierCizdir(koordinatXY);




    fclose(dosya);
    fclose(dosya2);
    getch();
    closegraph();

}
