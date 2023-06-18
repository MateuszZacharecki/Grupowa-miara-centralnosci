#include <iostream>
#include <vector>
#define n 5 //liczba wierzcholkow we wczytywanym grafie

using namespace std;

struct slistEl
{
  slistEl *next;
  int data;
};

void ini(slistEl **h)
// inicjalizacja listy 1-kierunkowej
{
  *h=NULL;
}

slistEl* nowy(int a)
// tworzenie elementu listy 1-kierunkowej
{
  slistEl *u;
  u=new slistEl;
  u->next=NULL;
  u->data=a;
  return u;
}

void dodaj(slistEl **h, slistEl *u)
// dodawanie elementu do listy 1-kierunkowej
{
  u->next=*h;
  *h=u;
}

void druk_list(slistEl *u)
// wypisanie listy 1-kierunkowej
{
  while (u!=nullptr)
  {
    cout<<u->data<< " ";
    u=u->next;
  }
  cout<<"\n";
}

void druk_graph(slistEl *G[])
// drukowanie grafu
{
  int i;
  cout<<"\n";
  for (i=0; i<n; i++)
  {
    cout<<i<<": ";
    druk_list(G[i]);
  }
}

slistEl** create_graph()
// tworzenie grafu wczytywanego z pliku
{
    FILE *f;
    int a;
    f=fopen("dane1.txt", "r");
    slistEl **G;
    G=new slistEl*[n];
    for(int i=0; i<n; i++)
    {
        ini(&G[i]);
    }
    for(int i=0; i<n; i++)
    {
        fscanf(f, "%d", &a);
        while(a!=-1)
        {
            dodaj(&G[i], nowy(a));
            fscanf(f, "%d", &a);
        }
    }
    fclose(f);
    return G;
}

void usun(slistEl **w)
// usuwanie pierwszego elementu z listy 1-kierunkowej
// o ile istnieje
{
    slistEl* u;
    if (*w!=nullptr)
    {
        u=*w;
        *w=(*w)->next;
        delete u;
    }
}

int factorial(int m)
// silnia
{
    if (m==0 || m==-1) return 1;
    int silnia=1;
    for (int i=1; i<=m; i++) silnia=silnia*i;
    return silnia;
}

void dfs(slistEl* G[], bool czy_odwiedzony[], int i)
//zwykle przeszukiwanie grafu wglab
{
    slistEl* h=G[i];
    czy_odwiedzony[i]=true;
    // zaznaczamy, ze odwiedzilismy wierzcholek o i-tym indeksie
    while (h!=nullptr)
    {
        if (czy_odwiedzony[h->data]==false)
        // mozemy wchodzic tylko do tych wierzcholkow,
        // w ktorych jeszcze nie bylismy
        {
            dfs(G, czy_odwiedzony, h->data);
        }
        h=h->next;
    }
}

int cardinality(slistEl* G[], vector <int> S)
//funkcja zwracajaca |K(G[S])|
{
    int moc=0;
    int s=S.size();
    bool czy_odwiedzony[n];
    // w tablicy beda zaznaczane wierzcholki, ktore zostaly odwiedzone
    // wierzcholki spoza S zaznaczamy od razu jako odwiedzone
    int j=0;
    for (int i=0; i<n; i++)
    {
        if (j<s)
        {
            if (S[j]==i)
            {
                czy_odwiedzony[i]=false;
                j++;
            }
            else czy_odwiedzony[i]=true;
        }
        else czy_odwiedzony[i]=true;
    }
    for (int i=0; i<n; i++)
    {
        if (czy_odwiedzony[i]==false)
        // jezeli wierzcholek o i-tym indeksie nie zostal jeszcze odwiedzony
        {
            dfs(G, czy_odwiedzony, i); // to przeszukujemy graf wglab
            moc++; // i zwiekszamy liczbe skladowych
        }
    }
    return moc;
}

slistEl** convert_group(slistEl* G[], vector <int> S)
// funkcja przeksztalca wektor reprezentujacy wierzcholki podgrafu grafu G na graf
{
    slistEl** H;
    H = new slistEl*[n];
    for(int i=0; i<n; i++)
    {
        ini(&H[i]);
    }
    int s=S.size();
    for (int i=0; i<s; i++)
    // przechodzimy po wszystkich wierzcholkach w grupie reprezentowanej przez wektor
    {
        slistEl* pom=G[S[i]];
        while (G[S[i]]!=nullptr)
        // przechodzimy po sasiadach tych wierzcholkow
        {
            for (int j=0; j<s; j++)
            {
                if (S[j]==G[S[i]]->data)
                // jezeli ktorys sasiad okaze sie tez nalezec do grupy
                {
                    dodaj(&H[S[i]], nowy(G[S[i]]->data));
                    // to dodajemy tego sasiada do grafu
                }
            }
            G[S[i]]=G[S[i]]->next;
        }
        G[S[i]]=pom;
    }
    return H;
}

vector <int> difference(vector <int> S, vector <int> T)
// funkcja zwracajaca S\T
{
    vector <int> roznica;
    int s=S.size();
    int t=T.size();
    int j=0;
    for (int i=0; i<s; i++)
    {
        bool czy_nierowne=true;
        while (S[i]>=T[j] && j<t)
        {
            if (S[i]==T[j])
            {
                czy_nierowne=false;
                break;
            }
            j++;
        }
        if (czy_nierowne) roznica.push_back(S[i]);
    }
    return roznica;
}

vector <int> to_vector(int T_tablica[], int rozmiar)
// funkcja konwertujaca tablice w wektor
{
    vector <int> T;
    for (int i=0; i<rozmiar; i++) T.push_back(T_tablica[i]);
    return T;
}

double group_attachment(slistEl *G[], vector <int> T)
// funkcja obliczajaca grupow¹ centralnoœæ ³¹czenia
{
    double centralnosc=0;
    unsigned int full_set;
    full_set=0xFFFFFFFF;
    // korzystamy z reprezentacji binarnej do przechodzenia po wszystkich podgrafach
    full_set>>=(32-n);
    for (unsigned int i=1; i<=full_set; ++i)
    {
        vector <int> S; // tu beda trzymane wierzcholki biezacego podgrafu
        for (unsigned char j=0; j<n; ++j)
        {
            if (i&(1<<j))
            {
                S.push_back(j);
            }
        }
        slistEl **G_S;
        G_S=convert_group(G,S);
        // zmieniamy reprezentacje biezacego podgrafu z wektora na graf
        vector <int> R;
        R=difference(S,T);
        // obliczamy roznice teoriomnogosciowa (biezacy podgraf \ dana grupa)
        slistEl **G_R;
        G_R=convert_group(G,R); // konwertujemy roznice do grafu
        int m_S = cardinality(G_S, S); // wyznaczam |K(G[S])|
        int m_R = cardinality(G_R, R); // wyznaczam |K(G[R])|
        int s=S.size();
        int r=R.size();
        centralnosc+=((((1.0*factorial(s-1))*(1.0*factorial(n-s)))/(1.0*factorial(n)))*((2.0*(s-m_S))-(2.0*(r-m_R)))); // stosuje wprost wzor na group attachment
    }
    return centralnosc;
}

int main()
{
    slistEl **G;
    G=create_graph();
    cout<<"Graph:";
    druk_graph(G);
    int rozmiar;
    cout<<"Insert size of group: ";
    cin>>rozmiar;
    int T_tablica[rozmiar];
    cout<<"Insert "<<rozmiar<<" elements of group: "<<endl;
    for (int i=0; i<rozmiar; i++) cin>>T_tablica[i];
    vector <int> T;
    T=to_vector(T_tablica,rozmiar);
    double centralnosc=group_attachment(G,T);
    cout<<centralnosc<<endl;
    return 0;
}
