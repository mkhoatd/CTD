#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <fstream>
using namespace std;

const int MAX = 256;
const int ERROR_STATE = 100;
typedef int state;            // kieu cac trang thai
typedef unsigned char *attri; // kieu cua thuoc tinh
typedef unsigned char *token; // kieu cua tu to
unsigned char *x;             // xau vao x
unsigned int i = 0;           // vi tri cua ky tu doc trong xau x
int table[MAX][MAX];

// tra ve ky tu thu i cua xau vao x
unsigned char readchar(unsigned char *x, unsigned int i)
{
    if (i < strlen((char *)x))
        return (*(x + i));
    else
        return ('\0');
}

// tra ve thuoc tinh tuong ung voi trang thai ket thuc
attri attribute(state s)
{
    char *ch;
    ch = new char[100]();
    switch (s)
    {
    case 2:
        strcpy(ch, "so sanh lon hon bang");
        break;
    case 3:
        strcpy(ch, "dich phai");
        break;
    case 4:
        strcpy(ch, "so sanh lon hon");
        break;
    case 6:
        strcpy(ch, "so sanh nho hon bang");
        break;
    case 7:
        strcpy(ch, "dich trai");
        break;
    case 8:
        strcpy(ch, "so sanh nho hon");
        break;
    case 10:
        strcpy(ch, "so sanh khong bang");
        break;
    case 11:
        strcpy(ch, "phu dinh");
        break;
    case 13:
        strcpy(ch, "so sanh bang");
        break;
    case 14:
        strcpy(ch, "gan");
        break;
    case 17:
        strcpy(ch, "cong bang");
        break;
    case 18:
        strcpy(ch, "tang 1");
        break;
    case 19:
        strcpy(ch, "cong");
        break;
    case 21:
        strcpy(ch, "tru bang");
        break;
    case 22:
        strcpy(ch, "giam 1");
        break;
    case 23:
        strcpy(ch, "tru");
        break;
    case 25:
        strcpy(ch, "nhan bang");
        break;
    case 26:
        strcpy(ch, "nhan");
        break;
    case 28:
        strcpy(ch, "chia bang");
        break;
    case 29:
        strcpy(ch, "chia");
        break;
    case 30:
        strcpy(ch, "chia lay du");
        break;
    case 32:
        strcpy(ch, "AND");
        break;
    case 33:
        strcpy(ch, "AND bit roi gan");
        break;
    case 34:
        strcpy(ch, "AND bit");
        break;
    case 36:
        strcpy(ch, "OR");
        break;
    case 37:
        strcpy(ch, "OR bit roi gan");
        break;
    case 38:
        strcpy(ch, "OR bit");
        break;
    case 40:
        strcpy(ch, "XOR bit roi gan");
        break;
    case 41:
        strcpy(ch, "XOR");
        break;
    case 42:
        strcpy(ch, "phu dinh bit");
        break;
    case 44:
        strcpy(ch, "ten ham, ten bien, ten hang, tu khoa");
        break;
    case 46:
        strcpy(ch, "chu thich 1 dong");
        break;
    case 49:
        strcpy(ch, "chu thich nhieu dong");
        break;
    case 52:
        strcpy(ch, "loi dat ten bat dau bang so");
        break;
    case 53:
        strcpy(ch, "so nguyen khong dau");
        break;
    case 57:
        strcpy(ch, "so thap luc phan");
        break;
    case 67:
        strcpy(ch, "loi so thap luc phan co cac ki tu g|..|z hoac G|..|Z");
        break;
    case 60:
        strcpy(ch, "so bat phan");
        break;
    case 62:
        strcpy(ch, "loi so bat phan co cac chu so 8|9");
        break;
    case 63:
        strcpy(ch, "so 0");
        break;
    case 66:
        strcpy(ch, "so thuc");
        break;
    case 68:
        strcpy(ch, "loi so thap luc phan");
        break;
    case 69:
        strcpy(ch, "loi so thuc");
        break;
    case 71:
        strcpy(ch, "loi khong xac dinh");
        break;
    default:
        strcpy(ch, "token ko duoc doan nhan(tt ko dung) \0");
    }
    return (attri)ch;
}

// kiem tra trang thai s co phai la trang thai ket thuc khong * khong?
int nostar_end_state(state s)
{
    switch (s)
    {
    case 2:
    case 3:
    case 6:
    case 7:
    case 10:
    case 13:
    case 17:
    case 18:
    case 21:
    case 22:
    case 25:
    case 28:
    case 30:
    case 32:
    case 33:
    case 36:
    case 37:
    case 40:
    case 42:
    case 49:
        return 1;
    default:
        return 0;
    }
}

// kiem tra trang thai s co phai la trang thai ket thuc * khong?
int star_end_state(state s)
{
    switch (s)
    {
    case 4:
    case 8:
    case 11:
    case 14:
    case 19:
    case 23:
    case 26:
    case 29:
    case 34:
    case 38:
    case 41:
    case 44:
    case 46:
    case 52:
    case 53:
    case 57:
    case 60:
    case 62:
    case 63:
    case 66:
    case 67:
    case 68:
    case 69:
    case 71:
        return 1;
    default:
        return 0;
    }
}

// ghep them ky tu c vao cho tu to tk
void catchar_in_token(unsigned char c, token tk)
{
    *(tk + strlen((char *)tk) + 1) = '\0'; // add ki tu ket thuc vao cuoi token tk
    *(tk + strlen((char *)tk)) = c;        // gan ki tu cuoi cung = c
}

// tra ve thuoc tinh cua tu to bdau tu vi tri i, thuoc tinh tra ve cho tt
token search_token(unsigned int *i, attri tt)
{
    token tk = new unsigned char[100]();
    unsigned char c;
    state s = 0, cs;
    // do - while dung khi ki tu c ko phai ki tu trang hoac c la ki tu cuoi cung cua xau vao x hoac s != 0 (dang xet den ki tu thu 2 cua tu to)
        do
        {
            c = readchar(x, *i);
            *i = *i + 1;
        } while ((c == ' ') && (*i < strlen((char *)x)));
        // neu c la ki tu trang va c la ki tu cuoi cung va c la ki tu dau tien cua tu to dang xet
        if ((c == ' ') && *i == strlen((char *)x))
        {
            *tk = '\0';
            return tk;
        }
    do
    {
        // chuyen trang thai ke tiep
        cs = table[s][c];
        cout << "i = " << *i << endl;
        cout << "c : " << c << endl;
        cout << "cs = " << cs << endl;
        if (cs == ERROR_STATE)
        {
            cout << "loi tai ky tu thu " << *i - 1<< endl;
            *tk = '\0';
            break;
        }
        else if (star_end_state(cs))
        {
            cout << "end tu to" << endl << endl;
            if (c != '\0') *i = *i - 1;
            strcpy((char *)tt, (char *)attribute(cs));
            break;
        }
        else if (nostar_end_state(cs))
        {
            catchar_in_token(c, tk);
            cout << "length token = " << strlen((char *)tk) << endl;
            cout << "token : ";
            for (int j = 0; j < strlen((char *)tk); j++)
            {
                cout << *(tk + j);
            }
            cout << endl;
            cout << "end tu to" << endl << endl;
            strcpy((char *)tt, (char *)attribute(cs));
            break;
        }
        else if (*i > strlen((char *)x))
        {
            cout << "het xau vao, ko roi vao TT ket thuc" << endl;
            *tk = '\0';
            break;
        }
        else if (c == '\n' && cs != 45 && cs != 47)
        {
            c = readchar(x, *i);
            if (c != '\0')
            {
                *i = *i + 1;
            }
            cout << endl;
            if (s != 0) s = cs;
        }
        else
        {
            catchar_in_token(c, tk);
            cout << "length token = " << strlen((char *)tk) << endl;
            cout << "token : ";
            for (int j = 0; j < strlen((char *)tk); j++)
            {
                cout << *(tk + j);
            }
            cout << endl << endl;
            c = readchar(x, *i);
            if (c != '\0')
            {
                *i = *i + 1;
            }
            s = cs;
        }
    } while (true);
    return tk;
}

// tao bang chuyen trang thai table
void create_table(int table[][MAX])
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
    table[61]['.'] = 64;
}

list<pair<token, attri>> l;
// luu tru tk,a vao danh sach l
void save_token_and_attribute(token tk, attri a)
{
    attri b = new unsigned char[100]();
    strcpy((char *)b, (char *)a);
    l.push_back(pair<token, attri>(tk, b));
}

void lexical_analysis()
{
    token tk;
    attri a = new unsigned char[100]();
    create_table(table);
    do
    {
        tk = search_token(&i, a);
        if (*tk != '\0') save_token_and_attribute(tk, a);
    } while ((*tk != '\0') && (i < strlen((char *)x)));
}

int main()
{
    // nhap xau vao x
    ifstream ifs("input.txt");
    unsigned char c;
    x = new unsigned char[100]();
    *x = '\0';
    cout << "xau x : " << endl;
    while (ifs >> noskipws >> c)
    {
        cout << c;
        catchar_in_token(c, x);
    }
    ifs.close();
    // cout << "nhap xau vao x:" << endl;
    // string input;
    // getline(cin, input);
    // for (int j = 0; j < input.size(); j++)
    // {
    //     *(x + j) = input[j];
    // }
    cout << "\nlenght x = " << strlen((char *)x) << endl;
    for (int j = 0; j < strlen((char *)x); j++)
    {
        cout << "i = " << j << " : " << *(x + j) << endl;
    }
    cout << endl;

    create_table(table);
    i = 0;
    lexical_analysis();
    // in danh sach tu to va thuoc tinh
    cout << "danh sach token, attribute:" << endl;
    for (pair<token, attri> p : l)
    {
        for (int j = 0; j < strlen((char *)p.first); j++)
        {
            cout << *(p.first + j);
        }
        cout << " | ";
        for (int j = 0; j < strlen((char *)p.second); j++)
        {
            cout << *(p.second + j);
        }
        cout << endl;
    }

    // giai phong con tro
    for (pair<token, attri> p : l)
    {
        delete[] p.first;
        delete[] p.second;
    }
    delete[] x;
    return 0;
}