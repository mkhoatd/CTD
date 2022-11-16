#include <iostream>
#include <string>
#include <list>
#include <set>
#include <unordered_map>
#include <fstream>
#include <vector>
using namespace std;

const int MAX = 256;
const int ERROR_STATE = 100;
typedef int state;    // kieu cac trang thai
typedef string attri; // ten cua token
typedef string token; // token
string x;             // xau vao x
unsigned int i = 0;   // vi tri cua ky tu doc trong xau x
int table[MAX][MAX];

using namespace std;

unsigned char readchar(string x, unsigned int i)
{
    return x.length() > i ? x[i] : 0;
}

attri attribute(state s)
{
    attri ch;
    static unordered_map<state, attri> m;
    m[2] = "so sanh lon hon bang";
    m[3] = "dich phai";
    m[4] = "so sanh lon hon";
    m[6] = "so sanh nho hon bang";
    m[7] = "dich trai";
    m[8] = "so sanh nho hon";
    m[10] = "so sanh khong bang";
    m[11] = "phu dinh";
    m[13] = "so sanh bang";
    m[17] = "cong bang";
    m[18] = "tang 1";
    m[19] = "cong";
    m[21] = "tru bang";
    m[22] = "giam 1";
    m[23] = "tru";
    m[25] = "nhan bang";
    m[26] = "nhan";
    m[28] = "chia bang";
    m[29] = "chia";
    m[30] = "chia lay du";
    m[32] = "AND";
    m[33] = "AND bit roi gan";
    m[34] = "AND bit";
    m[36] = "OR";
    m[37] = "OR bit roi gan";
    m[38] = "OR bit";
    m[40] = "XOR bit roi gan";
    m[41] = "XOR";
    m[42] = "phu dinh bit";
    m[44] = "ten ham, ten bien, ten hang, tu khoa";
    m[46] = "chu thich 1 dong";
    m[49] = "chu thich nhieu dong";
    m[52] = "loi dat ten bat dau bang so";
    m[53] = "so nguyen khong dau";
    m[57] = "so thap luc phan";
    m[60] = "so bat phan";
    m[62] = "loi so bat phan co cac chu so 8|9";
    m[63] = "so 0";
    m[66] = "so thuc";
    m[67] = "loi so thap luc phan co cac ki tu g|..|z hoac G|..|Z";
    m[68] = "loi so thap luc phan";
    m[69] = "loi so thuc";
    m[71] = "loi khong xac dinh";
    return m.count(s) ? m[s] : "token khong duoc doan nhan(tt khong dung)";
}

bool no_star_end_state(state s)
{
    static set<state> v = {2, 3, 6, 7, 10, 13, 17, 18, 21, 22, 25, 28, 30, 32, 33, 36, 37, 40, 42, 49};
    return v.count(s) ? true : false;
}

bool star_end_state(state s)
{ 
    static set<state> v = {4, 8, 11, 14, 19, 23, 26, 29, 34, 38, 41, 44, 46, 52, 53, 57, 60, 62, 63, 66, 67, 68, 69, 71};
    return v.count(s) ? true : false;
}

void chatchar_in_token(unsigned char c, token& tk)
{
    tk+=c;
}

// tra ve thuoc tinh cua token bat dau tai vi tri i
pair<token, attri> search_token(unsigned int& i)
{
    token tk="";
    unsigned char c;
    state s=0, cs;
    attri tt="";

    //doc cac ky tu trang hoac  
    do
    {
        c=readchar(x, i);
        i+=1;
    }
    while ((c==' ') && (i<x.length()));
    if ((c==' ') && i == x.length())
    {
        tk="\0";
        return make_pair(tk, tt); 
    }

    do
    {
        // chuyen trang thai ke tiep
        cs = table[s][c];
        cout << "i = " <<i<<endl;
        cout << "c: "<<c<<endl;
        cout<<"cs = "<<cs<<endl;
        if (cs==ERROR_STATE)
        {
            cout<<"loi tai ky tu thu "<<i<<endl;
            tk="\0";
            break;
        }
        else if (star_end_state(cs))
        {
            cout<<"end token"<<endl<<endl;
            if (c!=0) i=i-1;
            tt=attribute(cs);
            break;
        }
        else if(no_star_end_state(cs))
        {
            tk+=c;
            cout<<"length token= "<<tk.length()<<endl;
            cout<<"token: "<<tk<<endl;
            cout<<"end tu to"<<endl<<endl;
            tt=attribute(cs);
            break;
        }
        else if(i>x.length())
        {
            cout<<"het xau vao, khong roi vao tu to ket thuc"<<endl;
            tk="\0";
            break;
        }
        else if (c == '\n' && cs != 45 && cs != 47)
        {
            c = readchar(x, i);
            if (c != '\0')
            {
                i++;
            }
            cout << endl;
            if (s != 0) s = cs;
        }
        else
        {
            tk+=c;
            cout << "length token = " << tk.length() << endl;
            cout << "token : "<<tk;
            cout << endl << endl;
            c = x[i];
            if (c != '\0')
            {
                i+=1;
            }
            s = cs;
        }
    }
    while (true);
    return make_pair(tk, tt);

}

void fill_table(int table[][MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        table[0][i] = 70;
        table[70][i] = 70;
        table[71][i] = 100;
        table[1][i] = 4;
        table[2][i] = 100;
        table[3][i] = 100;
        table[4][i] = 100;
        table[5][i] = 8;
        table[6][i] = 100;
        table[7][i] = 100;
        table[8][i] = 100;
        table[9][i] = 11;
        table[10][i] = 100;
        table[11][i] = 100;
        table[12][i] = 14;
        table[13][i] = 100;
        table[14][i] = 100;
        table[16][i] = 19;
        table[17][i] = 100;
        table[18][i] = 100;
        table[19][i] = 100;
        table[20][i] = 23;
        table[21][i] = 100;
        table[22][i] = 100;
        table[23][i] = 100;
        table[24][i] = 26;
        table[25][i] = 100;
        table[26][i] = 100;
        table[27][i] = 29;
        table[28][i] = 100;
        table[29][i] = 100;
        table[30][i] = 100;
        table[31][i] = 34;
        table[32][i] = 100;
        table[33][i] = 100;
        table[34][i] = 100;
        table[35][i] = 38;
        table[36][i] = 100;
        table[37][i] = 100;
        table[38][i] = 100;
        table[39][i] = 41;
        table[40][i] = 100;
        table[41][i] = 100;
        table[42][i] = 100;
        table[43][i] = 44;
        table[44][i] = 100;
        table[45][i] = 45;
        table[46][i] = 100;
        table[47][i] = 47;
        table[48][i] = 47;
        table[49][i] = 100;
        table[50][i] = 53;
        table[51][i] = 52;
        table[52][i] = 100;
        table[53][i] = 100;
        table[54][i] = 63;
        table[55][i] = 68;
        table[68][i] = 100;
        table[56][i] = 57;
        table[57][i] = 100;
        table[58][i] = 67;
        table[67][i] = 100;
        table[59][i] = 60;
        table[60][i] = 100;
        table[61][i] = 62;
        table[62][i] = 100;
        table[63][i] = 100;
        table[64][i] = 69;
        table[69][i] = 100;
        table[65][i] = 66;
        table[66][i] = 100;
    }
    table[0]['>'] = 1;
    table[0]['+'] = 16;
    table[0]['<'] = 5;
    table[0]['-'] = 20;
    table[0]['!'] = 9;
    table[0]['*'] = 24;
    table[0]['='] = 12;
    table[0]['/'] = 27;
    table[0]['%'] = 30;
    table[0]['&'] = 31;
    table[0]['|'] = 35;
    table[0]['^'] = 39;
    table[0]['~'] = 42;
    table[70]['>'] = 71;
    table[70]['+'] = 71;
    table[70]['<'] = 71;
    table[70]['-'] = 71;
    table[70]['!'] = 71;
    table[70]['*'] = 71;
    table[70]['='] = 71;
    table[70]['/'] = 71;
    table[70]['%'] = 71;
    table[70]['&'] = 71;
    table[70]['|'] = 71;
    table[70]['^'] = 71;
    table[70]['~'] = 71;
    for (int j = 'a'; j <= 'z'; j++)
    {
        table[0][j] = 43;
        table[0][j - 32] = 43;
        table[70][j] = 71;
        table[70][j - 32] = 71;
        table[43][j] = 43;
        table[43][j - 32] = 43;
        table[50][j] = 51;
        table[50][j - 32] = 51;
        table[51][j] = 51;
        table[51][j - 32] = 51;
        table[54][j] = 51;
        table[54][j - 32] = 51;
        table[55][j] = 58;
        table[55][j - 32] = 58;
        table[56][j] = 58;
        table[56][j - 32] = 58;
        table[58][j] = 58;
        table[58][j - 32] = 58;
        table[59][j] = 51;
        table[59][j - 32] = 51;
        table[61][j] = 51;
        table[61][j - 32] = 51;
    }
    table[0]['_'] = 43;
    table[70]['_'] = 71;
    table[1]['='] = 2;
    table[1]['>'] = 3;
    table[5]['='] = 6;
    table[5]['<'] = 7;
    table[9]['='] = 10;
    table[12]['='] = 13;
    table[16]['='] = 17;
    table[16]['+'] = 18;
    table[20]['='] = 21;
    table[20]['-'] = 22;
    table[24]['='] = 25;
    table[27]['='] = 28;
    table[31]['&'] = 32;
    table[31]['='] = 33;
    table[35]['|'] = 36;
    table[35]['='] = 37;
    table[39]['='] = 40;
    for (int j = '0'; j <= '9'; j++)
    {
        table[0][j] = 50;
        table[70][j] = 71;
        table[43][j] = 43;
        table[50][j] = 50;
        table[51][j] = 51;
        table[55][j] = 56;
        table[56][j] = 56;
        table[58][j] = 58;
        table[61][j] = 61;
        table[64][j] = 65;
        table[65][j] = 65;
    }
    table[43]['_'] = 43;
    table[27]['/'] = 45;
    table[27]['*'] = 47;
    table[45]['\n'] = 46; // enter
    table[45]['\0'] = 46; // end of file
    table[47]['*'] = 48;
    table[48]['*'] = 48;
    table[48]['/'] = 49;
    table[50]['_'] = 51;
    table[51]['_'] = 51;
    table[54]['_'] = 51;
    table[59]['_'] = 51;
    table[61]['_'] = 51;
    table[0]['0'] = 54;
    table[54]['x'] = 55;
    table[54]['X'] = 55;
    for (int j = 'a'; j <= 'f'; j++)
    {
        table[55][j] = 56;
        table[55][j - 32] = 56;
        table[56][j] = 56;
        table[56][j - 32] = 56;
    }
    for (int j = '0'; j <= '7'; j++)
    {
        table[54][j] = 59;
        table[59][j] = 59;
    }
    table[54]['8'] = 61;
    table[54]['9'] = 61;
    table[59]['8'] = 61;
    table[59]['9'] = 61;
    table[0]['.'] = 64;
    table[70]['.'] = 71;
    table[50]['.'] = 64;
    table[54]['.'] = 64;
    table[59]['.'] = 64;
    table[61]['.'] = 64;}

list<pair<token, attri> > l;

void lexical_analysis()
{
    pair<token, attri> p;
    fill_table(table);
    do
    {
        p=search_token(i);
        if (p.first!="\0") l.push_back(p);
    } while ((p.first!="\0") && i<x.length());
    
}

int main()
{
    ifstream ifs("input.txt");
    unsigned char c;
    x="\0";
    cout<<"xau x: "<<endl;
    while (ifs>>noskipws>>c)
    {
        cout<<c;
        x+=c;
    }
    ifs.close();

    cout<<"\nlength x = "<<x.length()<<endl;
    for (int j=0;j<x.length(); j++)
    {
        cout<<"i = "<<j<<" : "<<x[j]<<endl;
    }
    cout<<endl;
    fill_table(table);
    i=0;
    lexical_analysis();
    cout<<"danh sach token, attribute: "<<endl;
    for (auto p: l)
    {
        cout<<p.first<<" | "<<p.second<<endl;
    }
    return 0;


}