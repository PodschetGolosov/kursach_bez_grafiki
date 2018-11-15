#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

int main ()//весь мэйн надо поместить в цикл,окончить который можно только цифрой 3 ну или cntr+c
{
    for(;;)
    {
        int command;
        cout << "1: Add poll;" << endl;
        cout << "2: Vote in poll;"<<endl;
        cout << "3: Quit;" << endl;
        cout << "4: Reading answers;" << endl;
        cout << endl;
        cout << "Please enter number from 1 to 4 foe execute: ";

        cin >> command;
        cout << endl;
        //Выбор действий по указанной команде.
        switch(command)
        {
            case 1:
            {
                string text,txt,ques,space;
                char name[500];
                txt = ".txt";
                space=" ";
                cout << "Name of your poll" << endl;
                cin >> text;
                text = text+txt;
                strcpy(name,text.c_str());

                ofstream fout(name);
                cout << "=> Enter your question:(for stop press #)"<<endl;
                int x = 1;
                for (string line; getline(cin, line);) {
                    if (strcmp(line.c_str(), "#") == 0){
                        break;
                    }
                    if (strcmp(line.c_str(), "") == 0){
                        continue;
                    }
                    string y = to_string(x);
                    ques = y+space+line;
                    fout << ques << endl;
                    x++;
                }
                fout.close();
                break;
            }
            case 2:
            {
                string respname, opros;
                cout << "Choose poll:" << endl;
                cin >> opros;//тут надо вводить файл

                ifstream fin (opros+".txt");
                if (!fin){
                    cout << "Enter a valid poll name" << endl;
                    break;
                }
                int ques_count = 0;
                for (string line; getline(fin, line);){ // построчно получаем вопросы из файла
                    if (strcmp(line.c_str(), "") != 0 && strcmp(line.c_str(), "\n") != 0){
                        cout << line << endl;
                        ques_count++;
                    }

                }
                fin.close();

                cout << "What's your name?" << endl;
                cin >> respname;

                ofstream ans("answers.txt", ios_base::app);//тут идет запись в файл с ответом
                ans << "#" + opros + " ";// Название опроса
                ans << "#" + respname + " ";// Имя респондента
                ans << "#" + to_string(ques_count) + " ";//Сколько вопросов было

                cout << "Enter answers Y/N" << endl;
                for (int i = 0; i < ques_count; i++){
                    string cur_ans;
                    cin >> cur_ans;
                    if (strcmp(cur_ans.c_str(), "Y") == 0 || strcmp(cur_ans.c_str(), "N") == 0){
                        ans << cur_ans + " ";
                    }
                }
                ans << endl;
                ans.close();
            }
            case 3:
            {
                exit(0);
            }
            case 4: //НУЖНО ДОРАБОТАТЬ НЕ СЧИТЫВАЕТ ЕСЛИ ВЫБРАТЬ ОПРОС (ВОЗМОЖНО НЕ ТАК ТЕСТИЛ)
            {
                string opros;
                cout << "Choose poll:" << endl;
                cin >> opros;
                ifstream fin ("answers.txt");
                if (!fin){
                    cout << "Enter valid name of file with answers" << endl;
                    break;
                }
                for (string line; getline(fin, line);){ // построчно получаем вопросы из файла
                    cout << line << endl;
                    size_t opros_pos = line.find(" ");
                    string cur_opros;
                    cur_opros = line.substr(opros_pos+1, line.find(" ", opros_pos) - opros_pos);
                    cout << cur_opros;
                }
                fin.close();
            }
        }
    }
}
