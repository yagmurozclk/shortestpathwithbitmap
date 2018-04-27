#include <malloc.h>
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>



#define INFINITY 9999
#define MAX 81

struct city
{
    char name[50];
    int id;
    int X;
    int Y;
};

void dijkstra(int G[MAX][MAX],int n,int startnode,int endnode);
int getCityId(char* name);
int getCityIndex(char* name);
city* getCityById(int id);
void printG(int G[MAX][MAX]);


int pathIndex[81];
int pathIndexLength=0;
city cityList[81] = {
        {"Adana",-1,635,477},
        {"Adýyaman",-1,827,407},
        {"Afyon",-1,307,320},
        {"Aðrý",-1,1128,247},
        {"Amasya",-1,645,162},
        {"Ankara",-1,444,221},
        {"Antalya",-1,301,476},
        {"Artvin",-1,1022,82},
        {"Aydyn",-1,111,390},
        {"Balykesir",-1,123,214},
        {"Bilecik",-1,274,197},
        {"Bingöl",-1,983,292},
        {"Bitlis",-1,1096,341},
        {"Bolu",-1,372,157},
        {"Burdur",-1,256,415},
        {"Bursa",-1,195,191},
        {"Çanakkale",-1,54,178},
        {"Çankýrý",-1,497,160},
        {"Çorum",-1,573,177},
        {"Denizli",-1,197,372},
        {"Diyarbakýr",-1,957,380},
        {"Edirne",-1,57,51},
        {"Elazýð",-1,908,325},
        {"Erzincan",-1,885,235},
        {"Erzurum",-1,1022,205},
        {"Eskiþehir",-1,330,234},
        {"Gaziantep",-1,774,467},
        {"Giresun",-1,840,138},
        {"Gümüþhane",-1,895,175},
        {"Hakkari",-1,1217,405},
        {"Hatay",-1,687,520},
        {"Isparta",-1,310,372},
        {"Mersin",-1,565,488},
        {"Ýstanbul",-1,211,109},
        {"Ýzmir",-1,36,339},
        {"Kars",-1,1138,140},
        {"Kastamonu",-1,516,65},
        {"Kayseri",-1,646,340},
        {"Kýrklareli",-1,114,40},
        {"Kýrþehir",-1,543,272},
        {"Kocaeli",-1,255,130},
        {"Konya",-1,426,360},
        {"Kütahya",-1,232,254},
        {"Malatya",-1,800,329},
        {"Manisa",-1,108,290},
        {"Kahramanmaraþ",-1,733,396},
        {"Mardin",-1,992,440},
        {"Muðla",-1,144,463},
        {"Muþ",-1,1046,309},
        {"Nevþehir",-1,574,333},
        {"Niðde",-1,573,396},
        {"Ordu",-1,780,129},
        {"Rize",-1,978,115},
        {"Sakarya",-1,300,146},
        {"Samsun",-1,667,99},
        {"Siirt",-1,1080,382},
        {"Sinop",-1,592,66},
        {"Sivas",-1,737,245},
        {"Tekirdað",-1,97,100},
        {"Tokat",-1,702,194},
        {"Trabzon",-1,909,126},
        {"Tunceli",-1,894,287},
        {"Þanlýurfa",-1,874,459},
        {"Uþak",-1,212,319},
        {"Van",-1,1188,331},
        {"Yozgat",-1,608,239},
        {"Zonguldak",-1,389,90},
        {"Aksaray",-1,520,366},
        {"Bayburt",-1,944,187},
        {"Karaman",-1,494,462},
        {"Kýrýkkale",-1,512,238},
        {"Batman",-1,1035,405},
        {"Þýrnak",-1,1122,416},
        {"Bartýn",-1,436,69},
        {"Ardahan",-1,1113,79},
        {"Iðdýr",-1,1208,196},
        {"Yalova",-1,212,149},
        {"Karabük",-1,446,113},
        {"Kilis",-1,750,502},
        {"Osmaniye",-1,686,463},
        {"Düzce",-1,345,136}
};
int cityListLength=81;




struct BMP
{
    char Type[2];           //File type. Set to "BM".
    unsigned long Size;     //Size in BYTES of the file.
    unsigned long Reserved;      //Reserved. Set to zero.
    unsigned long OffSet;   //Offset to the data.
    unsigned long headsize; //Size of rest of header. Set to 40.
    unsigned long Width;     //Width of bitmap in pixels.
    unsigned long Height;     //  Height of bitmap in pixels.
    unsigned int  Planes;    //Number of Planes. Set to 1.
    unsigned int  BitsPerPixel;       //Number of Bits per pixels.
    unsigned long Compression;   //Compression. Usually set to 0.
    unsigned long SizeImage;  //Size in bytes of the bitmap.
    unsigned long XPixelsPreMeter;     //Horizontal pixels per meter.
    unsigned long YPixelsPreMeter;     //Vertical pixels per meter.
    unsigned long ColorsUsed;   //Number of colors used.
    unsigned long ColorsImportant;  //Number of "important" colors.
};

int getcol(int col)
{
    switch(col)
    {
        case 0: return 0;     //BLACK;
        case 1: return 4;     //RED;
        case 2: return 2;     //GREEN
        case 3: return 6;     //BROWN
        case 4: return 1;     //BLUE;
        case 5: return 5;     //MAGENTA;
        case 6: return 3;     //CYAN;
        case 7: return 7;     //LIGHTGRAY;
        case 8: return 8;     //DARKGRAY;
        case 9: return 12;    //LIGHTRED;
        case 10:return 10;    //LIGHTGREEN
        case 11:return 14;    //YELLOW;
        case 12:return 9;     //LIGHTBLUE;
        case 13:return 13;    //LIGHTMAGENTA
        case 14:return 11;    //LIGHTCYAN;
        case 15:return 15;    //WHITE;
    }
    return col;
}

int loadbitmap(char *filename)
{
    FILE *ptr=NULL;                //file handle to open bitmap file
    int width,height;              //width and height of the bitmap
    unsigned long temp=0,i=0,j=0;  //some variables i need
    unsigned long ww;
    ptr=fopen(filename,"rb");      //open the bitmap file
    if(!ptr) return 0;             //if its not there return
    width=0;height=0;              //initialise wisth and height to zero
    fseek(ptr,18,SEEK_SET);        //got to offset 18 in file
    for(i=0x1;i<=0x10000;i*=0x100) //read the width
    {
        temp=fgetc(ptr);
        width+=(temp*i);
    }
    fseek(ptr,22,SEEK_SET);        //go to offset 22 in file
    for(i=0x1;i<=0x10000;i*=0x100) //read the height
    {
        temp=fgetc(ptr);
        height+=(temp*i);
    }

    ww=width;
    //ww is the number of reads to make for each horizontal line
    if(ww%2)
        //ww has to be half of width - since each pixel is only 4 bits of information
        ww++;ww/=2;
    //just getting the correct value
    if(ww%4)
        //now - ww is stored as sets of 4 pixels each
        ww=(ww/4)*4+4;
    //if width is less than ww*2 we ignore what we read

    fseek(ptr,119,SEEK_SET);
    //Ok! offset 119 - lets read the pixels -
    //remember the bitmap is stroed up - side - down
    int ch,ch1,ch2;
    for(i=0;i<height;i++)
        for(j=0;j<ww;j++)
        {
            ch=fgetc(ptr);
            //each character read is 2 pixels - yes 4 bits per pixel - so 16 colors
            ch1=ch;ch2=ch;
            //find those colors using bitwise ops
            ch1=ch1&(0xf0);ch1=ch1>>4;
            // ~~
            ch2=ch2&(0x0f);
            // ~~
            if(j*2<width)
                //ok so put the first pixel read on screen
                putpixel((j)*2,(height-1-i),getcol(ch1));
            if(j*2+1<width)
                //put the second pixel read on screen
                putpixel((j)*2+1,(height-1-i),getcol(ch2));
        }
    fclose(ptr);
    //close the file handle
    return 1;
}

void readCitiesFromFile(){
    char fileName[50];

    printf("Sehir Kodlari dosyasinin adini giriniz : \n");
    scanf("%s", &fileName);


    FILE *fptr;
    fptr = fopen(fileName, "r");
    if (fptr != NULL) {
        char line [ 250 ]; /* or other suitable maximum line size */

        fgets ( line, sizeof line, fptr );
        char cityName[50];
        int id;
        while ( fgets ( line, sizeof line, fptr ) != NULL ) /* read a line */
        {
            char *token;
            token = strtok(line, "-");
            int order = 0;
            while (token != NULL)
            {

                if (order == 0)
                    strcpy(cityName, token);
                else if (order == 1)
                    id = atoi(token);


                token = strtok(NULL, "-");
                order++;
            }
            cityList[getCityIndex(cityName)].id=id;

        }

        fclose ( fptr );
    }
    else
        printf("File Not Found.\r\n");

}

int readCityDistancesToMatrix(int G[MAX][MAX]){
    char fileName[50];

    printf("Sehirler arasi mesafe dosyasini giriniz : \n");
    scanf("%s", &fileName);


    FILE *fptr;
    int i=0;
    fptr = fopen(fileName, "r");
    if (fptr != NULL) {
        char line [ 250 ]; /* or other suitable maximum line size */

        fgets ( line, sizeof line, fptr );
        char city1[50];
        char city2[50];
        int distance;
        while ( fgets ( line, sizeof line, fptr ) != NULL ) /* read a line */
        {
            char *token;
            token = strtok(line, "-");
            int order = 0;
            while (token != NULL)
            {

                if (order == 0)
                    strcpy(city1, token);
                else if (order==1)
                    strcpy(city2, token);
                else if(order==2)
                    distance = atoi(token);

                token = strtok(NULL, "-");
                order++;

            }
            G[getCityId(city1)][getCityId(city2)]=distance;
            G[getCityId(city2)][getCityId(city1)]=distance;

            i++;
        }

        fclose ( fptr );
    }
    else
        printf("File Not Found.\r\n");

//    printG(G);
    return i;

}


int getCityId(char* name){

    for (int i = 0; i < cityListLength; ++i) {
        if(strcmp(cityList[i].name,name)==0){
            return cityList[i].id;
        }
    }
    return -1;
}

int getCityIndex(char* name){

    for (int i = 0; i < cityListLength; ++i) {
        if(strcmp(cityList[i].name,name)==0){
            return i;
        }
    }
    return -1;
}

city* getCityById(int id){

    for (int i = 0; i < cityListLength; ++i) {
        if(cityList[i].id==id){
            return &cityList[i];
        }
    }
    return NULL;
}

void drawAllNodes(int G[MAX][MAX]){
    setcolor(BLACK);
    setlinestyle(0,0,5);
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            if(G[i][j]!=0){
                //line((*getCityById(i)).X-1,(*getCityById(i)).Y-1,(*getCityById(j)).X-1,(*getCityById(j)).Y-1);
                line((*getCityById(i)).X,(*getCityById(i)).Y,(*getCityById(j)).X,(*getCityById(j)).Y);
                //line((*getCityById(i)).X+1,(*getCityById(i)).Y+1,(*getCityById(j)).X+1,(*getCityById(j)).Y+1);
            }
        }
    }
}

void printG(int G[MAX][MAX]){
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            printf("%d  ",G[i][j]);
        }
        printf("\n");
    }
}

int main()
{

    setlocale(LC_ALL,"Turkish");

    int G[MAX][MAX];

    int color;
    int gd , gm ;
    gd = VGA ; gm = VGAHI;

    //initgraph(&gd,&gm,"");
    initwindow(1280, 578);
    loadbitmap("tur.bmp");
    setcolor(BLUE);
//    for(int i=0;i<cityListLength;i++) {
//            circle(cityList[i].X,cityList[i].Y,10);
//
//    }
    readCitiesFromFile();
    for(int i=0;i<cityListLength;i++){
        for(int j=0;j<cityListLength;j++){
            G[i][j]=0;
//            if(i==j){
//                G[i][j]=0;
//            }
//            else{
//                G[i][j]=INFINITY;
//            }

        }
    }

    readCityDistancesToMatrix(G);
    printG(G);
    drawAllNodes(G);
    char cityName[50];
    printf("Baslangic Sehrinin Adini Giriniz:\n");
    scanf("%s",&cityName);


    char endCityName[50];
    printf("Bitis Sehrinin Adini Giriniz:\n");
    scanf("%s",&endCityName);


    dijkstra(G,cityListLength,getCityId(cityName),getCityId(endCityName));


    getch();
    closegraph();
    return 0;

//    int G[MAX][MAX],i,j,n,u;
//    printf("Enter no. of vertices:");
//    scanf("%d",&n);
//    printf("\nEnter the adjacency matrix:\n");
//
//    for(i=0;i<n;i++)
//        for(j=0;j<n;j++)
//            scanf("%d",&G[i][j]);
//
//    printf("\nEnter the starting node:");
//    scanf("%d",&u);
//    dijkstra(G,n,u);

    return 0;
}

void dijkstra(int G[MAX][MAX],int n,int startnode,int endnode)
{

    int cost[MAX][MAX],distance[MAX],pred[MAX];
    int visited[MAX],count,mindistance,nextnode,i,j;

    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=G[i][j];

    //initialize pred[],distance[] and visited[]
    printG(G);
    printG(cost);
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }

    distance[startnode]=0;
    visited[startnode]=1;
    count=1;

    while(count<n-1)
    {
        mindistance=INFINITY;

        //nextnode gives the node at minimum distance
        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }

        //check if a better path exists through nextnode
        visited[nextnode]=1;
        for(i=0;i<n;i++)
            if(!visited[i])
                if(mindistance+cost[nextnode][i]<distance[i])
                {
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
        count++;
    }

    //print the path and distance of each node
    setcolor(YELLOW);
    setlinestyle(0,0,3);
    pathIndexLength=0;
    bool flag=false;
    for(i=0;i<n;i++) {
        if (i != startnode) {

            if (distance[i] != INFINITY) {
                flag=false;
                printf("\nDistance of node%d=%d", i, distance[i]);
                printf("\nPath=%s", (*getCityById(i)).name);
                if(endnode==i){
                    pathIndex[pathIndexLength]=i;
                    pathIndexLength++;
                    flag=true;
                }
                j = i;
                do {
                    line((*getCityById(j)).X, (*getCityById(j)).Y, (*getCityById(pred[j])).X,
                         (*getCityById(pred[j])).Y);
                    j = pred[j];
                    if(flag==true){
                        pathIndex[pathIndexLength]=j;
                        pathIndexLength++;
                    }

                    printf("<-%s", (*getCityById(j)).name);
                } while (j != startnode);
            }
        }
    }

    setcolor(GREEN);
    setlinestyle(0,0,7);
    for (int k = 0; k < pathIndexLength-1; ++k) {

        line((*getCityById(pathIndex[k])).X, (*getCityById(pathIndex[k])).Y, (*getCityById(pathIndex[k+1])).X,
             (*getCityById(pathIndex[k+1])).Y);
    }

}
