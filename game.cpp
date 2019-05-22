#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int,int);

class Konturas{
private:
    int skX, skY;
public:
    Konturas(): skX(2), skY(2){};
    ~Konturas(){};
    void sienos(){
        char a='A';
        for(int i=1; i<=10; i++){
            gotoXY(skX, 1);
           cout<<a;           //isveda ABCD
           gotoXY(skX++, 12);
           cout<<"I";
           gotoXY(skX++, 12);
           cout<<"I";
           a++;
           if(i==10){
               gotoXY(0, skY);
               cout<<i;
           }
           else{

               gotoXY(1, skY);
               cout<<i;
          }                    //isveda skiacius
          gotoXY(21, skY++);
          cout<<"|";
          }
       }
       virtual void Istrinti(){           //virtuali klase
           for(int i=0; i<14; i++){
               gotoXY(0, i);
               cout<<"                       ";
           }
       }
};
class Laivai:public Konturas{    //paveldejimas
private:
    int skX, skY, did;
protected:
    char S[23][13];
public:
    ~Laivai(){
    }
    Laivai(){
        for(int i=2; i<22; i++){
            for(int j=2; j<12; j++){
                S[i][j]='N';
            }
        }
        skX=2;
        skY=2;
    }
    void desinenirkairen(int a, int I[], int dk){
        if(S[skX+dk][skY]=='N'&&S[skX+dk][skY+I[1]]=='N'&&S[skX+dk][skY+I[2]]=='N'&&S[skX+dk][skY+I[3]]=='N'){
                for(int j=0; j<a; j++){
                    gotoXY(skX, skY+j);
                    cout<<" ";
                }
                skX+=dk;
                for(int j=0; j<a; j++){
                    gotoXY(skX, skY+j);
                    cout<<"S";
                }
            }
            else if(S[skX+dk*2][skY]=='N'&&S[skX+dk*2][skY+I[1]]=='N'&&S[skX+dk*2][skY+I[2]]=='N'&&S[skX+dk*2][skY+I[3]]=='N'){
                for(int j=0; j<a; j++){
                    gotoXY(skX, skY+j);
                    cout<<" ";
                }
                skX=skX+dk*2;
                for(int j=0; j<a; j++){
                    gotoXY(skX, skY+j);
                    cout<<"S";
                }
            }
    }
    void space(int a, int I[]){
        if(S[skX+2][skY]!='S'&&S[skX-2][skY]!='S'&&S[skX][skY-1]!='S'&&S[skX+2][skY+I[1]]!='S'&&S[skX-2][skY+I[1]]!='S'){
                if(S[skX+2][skY+I[2]]!='S'&&S[skX-2][skY+I[2]]!='S'&&S[skX-2][skY+I[3]]!='S'&&S[skX+2][skY+I[3]]!='S'&&S[skX][skY+a]!='S'){
                    for(int j=0; j<a; j++){
                        S[skX][skY+j]='S';
                    }
                    gotoXY(1, 15);
                    cout<<"                     ";
                    did--;
                    if(skX!=20) skX+=2;
                    else skX-=2;
                }
                else {
                    gotoXY(1, 15);
                    cout<<"Laivas per salia";
                    gotoXY(skX, skY);
                }
            }
            else {
                gotoXY(1, 15);
                cout<<"Laivas per salia";
                gotoXY(skX, skY);
            }

    }
    void padeti(int a){
        switch(a){
        case 4:
            did=1;
            break;
        case 3:
            did=2;
            break;
        case 2:
            did=3;
            break;
        case 1:
            did=4;
            break;
        }
        int i2=did;
        int I[4]={0, 0, 0, 0};
        for(int j=1; j<a; j++){
            I[j]=j;
        }
        while(did!=0){
        Sleep(200);
        for(int j=0; j<a; j++){
            gotoXY(skX, skY+j);
            cout<<"S";
        }
        if(GetAsyncKeyState(VK_RIGHT)){  // eina i desine
            desinenirkairen(a, I, 2);

        }
        if(GetAsyncKeyState(VK_LEFT)){  // eina i kaire
            desinenirkairen(a, I, -2);
        }
        if(GetAsyncKeyState(VK_DOWN)&&skY!=i2+7&&S[skX][skY+a]=='N'){   //eina i apacia
            gotoXY(skX, skY);
            cout<<" ";
            skY++;
            gotoXY(skX, skY+a-1);
            cout<<"S";
        }
        if(GetAsyncKeyState(VK_UP)&&skY!=2&&S[skX][skY-1]=='N'){  // eina i virsu
            gotoXY(skX, skY+a-1);
            cout<<" ";
            skY--;
            gotoXY(skX, skY);
            cout<<"S";
        }
        if(GetAsyncKeyState(VK_SPACE)){    //paspaudus 'space' pastato laiva
            space(a, I);
        }
        }
    }


};
class Musis:public Laivai{            //paveldejimas
private:
    int r, s, laivai, ok;
    char r2;
public:
    Musis(int l):laivai(l){};   //konstruktorius
    Musis():laivai(20), ok(0){}
    ~Musis(){};                   // destruktorius
    Musis operator-= (int sk){   // perkrovimas
        laivai-=sk;
    }
    bool operator< (int sk){   //binarinis perkrovimas
        if(laivai<sk) return true;
        else return false;
    }
    void isvedimas(){
        for(int i=2; i<22; i++){
            for(int j=2; j<12; j++){
                if(S[i][j]=='-'||S[i][j]=='X'){
                gotoXY(i, j);
                cout<<S[i][j];
                }
            }
        }
    }
    void musis(){
        ok=0;
        while(ok>-1){
        gotoXY(1, 17);
        cout<<"Iveskite raide: "<<endl;
        gotoXY(1, 18);
        cout<<"                       ";
        gotoXY(1, 18);
        cin>>r2;
        gotoXY(1, 17);
        cout<<"Iveskite skaiciu: "<<endl;
        gotoXY(1, 18);
        cout<<"                       ";
        gotoXY(1, 18);
        cin>>s;
        gotoXY(1, 17);
        cout<<"                     "<<endl;
        cout<<"   ";
        r=r2;
        if(r>90) r=(r-96)*2;
        else r=(r-64)*2;
        s++;
        if(r>=2&&r<=20&&s>=1&&s<=11){
            if(S[r][s]=='S'){
                S[r][s]='X';
                if(r+2!=22) S[r+2][s]='-';
                if(r-2!=0) S[r+2][s]='-';
                gotoXY(r, s);
                cout<<"X";
                if(r+2!=22){
                    gotoXY(r+2, s);
                    cout<<"-";
                }
                if(r-2!=0){
                    gotoXY(r-2, s);
                    cout<<"-";
                }
                gotoXY(1, 19);
                cout<<"Pataikete! Galite speti dar karta! " ;
                ok++;
                if(laivai-ok<1) break;
            }
            else if(S[r][s]=='X'||S[r][s]=='-'){
                gotoXY(1, 19);
                cout<<"Cia jau spejote, spekite kitur!          " ;
            }
            else if(S[r][s]!='X'){
                S[r][s]='-';
                gotoXY(r, s);
                cout<<"-";
                gotoXY(1, 19);
                cout<<"                                        ";
                break;
            }
        }
        else{
            gotoXY(1, 19);
            cout<<"Klaida!                          ";
            ok=-1;
            break;
        }
    }
    }
    void Istrinti(){
        for(int i=2; i<12; i++){
               gotoXY(2, i);
               cout<<"                   ";
        }
    }
    int returntrue(){
        return ok;
    }
};

int main(){
    int n;
    Musis A;
    Musis *am = &A;
    Konturas *ak = &A;
    Musis *m;
    cout<<"Iveskite, kiek zaideju zais? (min 2)";
    cin>>n;
    m=new Musis[n];
    gotoXY(0, 0);
    cout<<"                                      ";
    ak->sienos();
    for(int j=0; j<n; j++){
        gotoXY(0, 0);
        cout<<j+1<<"-tojo zaidejo laivai           ";
        for(int i=4; i>0; i--){
            m[j].padeti(i);
        }
        ak->Istrinti();
    }
    while(n>0){
        for(int i=0; i<n; i++){
            gotoXY(0, 0);
            if(i!=n-1) cout<<"Speja "<<i+2<<"-asis zaidejas               ";
            else cout<<"Speja 1-asis zaidejas               ";

            m[i].isvedimas();
            m[i].musis();
            if(m[i].returntrue()>0)m[i]-=m[i].returntrue();
            if(m[i]<1){
                gotoXY(1, 15);
                for(int i=0; i<21; i++){
                    gotoXY(1, i);
                    cout<<"                                      "<<endl;
                }
                if(i!=n-1) cout<<"Sveikinu "<<i+2<<"-asis zaidejau!!! Jus Laimejote ";
                else cout<<"Sveikinu 1-asis zaidejau!!! Jus Laimejote ";
                n=0;
            }
            ak->Istrinti();
        }
    }
    return 0;
}
void gotoXY(int x, int y)
{
CursorPosition.X = x;
CursorPosition.Y = y;
SetConsoleCursorPosition(console,CursorPosition);
}
