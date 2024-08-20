#include <iostream>
#include <png.h>
#include <cstdlib>
#include <string>
#include "RWimage.h"

constexpr int MaleCase[] = {4,3,3,3,3,3}; //C++11부터
constexpr int FemaleCase[] = {4,12,4,4,4,4};

using namespace std;

class face{
public:
    std::vector<unsigned char> background, overlay;
    int backgroundWidth, backgroundHeight, overlayWidth, overlayHeight;
    char sex;
    string name;
    face(){}
    face(char _sex, string _name):sex(_sex), name(_name){
        readPNG("./ingredients/mirror.png", background, backgroundWidth, backgroundHeight);
    }
    int isthisegg(char sex, string name);
    void add_color(char sex, int n);
    void add_hair(char sex, int n);
    void add_eyebrow(char sex, int n);
    void add_eyes(char sex, int n);
    void add_nose(char sex, int n);
    void add_lips(char sex, int n);
    void add_earrings(char sex, int n);
    void add_egg(int n);
};

int face::isthisegg(char sex, string name){
    if (sex == 'm'){
        if (name == "이동규") return 1;
        if (name == "이주호") return 3;
    }
    if(sex == 'f'){
        if (name == "정희선") return 2;
    }
    return 0;
}

void face::add_color(char sex, int n){
    string stringpath;
    if (sex == 'm'){
        stringpath = ("./ingredients/male/color/" + to_string(n) + ".png");
    }
    if (sex == 'f'){
        stringpath = ("./ingredients/female/color/" + to_string(n) + ".png");
    }
    const char* path = stringpath.c_str();
    readPNG(path, overlay, overlayWidth, overlayHeight);
    overlayImages(background, overlay, std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));
}
void face::add_hair(char sex, int n){
    string stringpath;
    if (sex == 'm'){
        stringpath = ("./ingredients/male/hair/" + to_string(n) + ".png");
    }
    if (sex == 'f'){
        stringpath = ("./ingredients/female/hair/" + to_string(n) + ".png");
    }
    const char* path = stringpath.c_str();
    readPNG(path, overlay, overlayWidth, overlayHeight);
    overlayImages(background, overlay, std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));
}
void face::add_eyebrow(char sex, int n){
    string stringpath;
    stringpath = ("./ingredients/male/eyebrow/" + to_string(n) + ".png");

    const char* path = stringpath.c_str();
    readPNG(path, overlay, overlayWidth, overlayHeight);
    overlayImages(background, overlay, std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));
}
void face::add_earrings(char sex, int n){
    string stringpath;
    stringpath = ("./ingredients/female/earrings/" + to_string(n) + ".png");

    const char* path = stringpath.c_str();
    readPNG(path, overlay, overlayWidth, overlayHeight);
    overlayImages(background, overlay, std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));
}
void face::add_eyes(char sex, int n){
    string stringpath;
    if (sex == 'm'){
        stringpath = ("./ingredients/male/eyes/" + to_string(n) + ".png");
    }
    if (sex == 'f'){
        stringpath = ("./ingredients/female/eyes/" + to_string(n) + ".png");
    }
    const char* path = stringpath.c_str();
    readPNG(path, overlay, overlayWidth, overlayHeight);
    overlayImages(background, overlay, std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));
}
void face::add_nose(char sex, int n){
    string stringpath;
    if (sex == 'm'){
        stringpath = ("./ingredients/male/nose/" + to_string(n) + ".png");
    }
    if (sex == 'f'){
        stringpath = ("./ingredients/female/nose/" + to_string(n) + ".png");
    }
    const char* path = stringpath.c_str();
    readPNG(path, overlay, overlayWidth, overlayHeight);
    overlayImages(background, overlay, std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));
}
void face::add_lips(char sex, int n){
    string stringpath;
    if (sex == 'm'){
        stringpath = ("./ingredients/male/lips/" + to_string(n) + ".png");
    }
    if (sex == 'f'){
        stringpath = ("./ingredients/female/lips/" + to_string(n) + ".png");
    }
    const char* path = stringpath.c_str();
    readPNG(path, overlay, overlayWidth, overlayHeight);
    overlayImages(background, overlay, std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));
}
long long int makeseedbyname(string name){
    hash<string> hasher;
    return hasher(name);
}
void face::add_egg(int n){
    switch (n)
    {
    case 1:
        readPNG("./ingredients/male/egg/ldg.png",overlay,overlayWidth,overlayHeight);
        overlayImages(background,overlay,std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));
        break;
    case 2:
        readPNG("./ingredients/female/egg/jhs.png",overlay,overlayWidth,overlayHeight);
        overlayImages(background,overlay,std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));
        break;
    case 3:
        readPNG("./ingredients/male/egg/ljh.png",overlay,overlayWidth,overlayHeight);
        overlayImages(background,overlay,std::min(backgroundWidth, overlayWidth), std::min(backgroundHeight, overlayHeight));
        break;    
    default:
        break;
    }
}
face generate_face(char sex, string name){
    cout << "얼굴을 생성합니다." << endl;
    face* newface = new face(sex, name);
    long long int seed;
    int egg;
    egg = newface -> isthisegg(sex, name);
    if (egg){
        newface -> add_egg(egg);
        face tmp = *newface;
        delete newface;
        return tmp;
    }
    seed = makeseedbyname(name);
    srand(seed);

    if (sex == 'm'){
        newface -> add_color(sex, rand()%MaleCase[0]+1);
        newface -> add_hair(sex, rand()%MaleCase[1]+1);
        newface -> add_eyebrow(sex, rand()%MaleCase[2]+1);
        newface -> add_eyes(sex, rand()%MaleCase[3]+1);
        newface -> add_nose(sex, rand()%MaleCase[4]+1);
        newface -> add_lips(sex, rand()%MaleCase[5]+1);
    }
    if (sex == 'f'){
        newface -> add_color(sex, rand()%FemaleCase[0]+1);
        newface -> add_hair(sex, rand()%FemaleCase[1]+1);
        newface -> add_earrings(sex, rand()%FemaleCase[2]+1);
        newface -> add_eyes(sex, rand()%FemaleCase[3]+1);
        newface -> add_nose(sex, rand()%FemaleCase[4]+1);
        newface -> add_lips(sex, rand()%FemaleCase[5]+1);
    }
    face tmp = *newface;
    delete newface;
    return tmp;
}

int main(){
    while(1){
        string getname, path;
        char sex;
        char done;
        face theface;
        cout << "랜덤 얼굴 생성" << endl;
        while(1){
            cout << "성별을 입력해주세요. [m/f]";
            cin >> sex;
            if (sex != 'm' && sex != 'f') cout << "잘못된 입력입니다." << endl;
            else break;
        }
        cout << "이름을 입력해주세요: ";
        cin >> getname;
        theface = generate_face(sex, getname);
        if (sex == 'm') path = "./result/"+getname+" 군의 얼굴.png";
        if (sex == 'f') path = "./result/"+getname+" 양의 얼굴.png";
        writePNG(path.c_str(),theface.background,theface.backgroundWidth,theface.backgroundHeight);
        int exitflag = -1;
        while(1){
            cout << "종료하시겠습니까? [y/n] ";
            cin >> done;
            if (done == 'y'){
                exitflag = 1; break;
            }
            if (done == 'n'){
                exitflag = 0; break;
            }
            else cout << "잘못된 입력입니다." << endl;
        }
        if(exitflag) break;
    }
}