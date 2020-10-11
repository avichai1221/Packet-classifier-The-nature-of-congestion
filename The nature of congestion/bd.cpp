#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
using namespace  std;





void bd(std::string fileName,std::string sizeOfQueue)
{
    typedef pair<int, int> pair1;
    priority_queue<pair1, vector<pair1>, greater<pair1> > queue1;
    int sizeOfQueueInt = stoi(sizeOfQueue);
    int arrivedPackets=0,droppedPackets=0,transmittedPackets=0,transmittedValue=0;

    ///המרה של סטרינג למערך תווים
    // assigning value to string s
    int n = fileName.length();
    // declaring character array
    char FileName[n + 1];
    // copying the contents of the
    // string to char array
    strcpy(FileName, fileName.c_str());

    FILE *file = fopen(FileName, "r"); ///פתיחת הקובץ לקריאה שהוא הפרמטר השלישי
    if (file == NULL) { ///בדיקת תקינות
        std::cout << ("not good");
        return;
    }
    char index;
    std::string line = "";
    while (fscanf(file, "%c", &index) != EOF) { ///תרוץ כל עוד הקובץ לא נגמר
        std::string numOfPackeg = "";
        std::string slack = "";
        std::string value = "";
        int numOfPackegInt, slackInt, valueInt;


        if (index == '(') {
            index = getc(file);

            while (index != ',') {
                numOfPackeg += index;
                index = getc(file);

            }

            if (index == ',') {
                index = getc(file);
                while (index != ',') {
                    slack += index;
                    index = getc(file);
                }

                if (index == ',') {
                    index = getc(file);
                    while (index != ')') {
                        value += index;
                        index = getc(file);
                    }
                    index = getc(file);
                    //  if (index == '\n') flag=true;
                }
            }

        }
        numOfPackegInt = std::stoi(numOfPackeg);
        slackInt = std::stoi(slack);
        valueInt = std::stoi(value);
        //    std::cout << "numOfPackeg= " << numOfPackegInt << std::endl << "slack= " << slackInt << std::endl << "value= "
        //              << valueInt << std::endl;

        ///////////////////////////////////////עד כאן הוצאנו את שלושת המשתנים שלנו למשתנים נפרדים



        for (int i = 0; i < numOfPackegInt; i++) ///נכניס את אותו השלשה כמספר הפעמים שביקשו  (amount, slack, value)
        {
            priority_queue<pair1, vector<pair1>, greater<pair1> > queueTemp;


            if (queue1.size() < sizeOfQueueInt) {///יש מקום בתור לכן נכניס את החבילה
                queue1.push(make_pair(valueInt , slackInt));
                arrivedPackets++;

            } else if (queue1.size() >= sizeOfQueueInt && queue1.top().first < valueInt) ///אין מקום בתור ויש ערך קטן יותר בתור
            {
                queue1.pop();
                queue1.push(make_pair(valueInt, slackInt));
                droppedPackets++;
                arrivedPackets++;


            }
            else if(queue1.size() >= sizeOfQueueInt && queue1.top().first >= valueInt){///אין ערך קטן יותר בתור
                droppedPackets++;
                arrivedPackets++;

            }

        }

        if(index=='\n') ///מסמן לנו שהייתה ירידת שורה
        {

            priority_queue<pair<int, int> > queueTemp;///תור עדיפויות שהערך הגבוה בראש התור

            ///ניעזר בתור נוסף כדי לבצע -1 לכל הסלאקים

            while(!queue1.empty())
            {
                if(queue1.top().second-1>0) ///אם לאחר הורדה של 1 הסלאק גדול מאפס אז נמשיך
                {
                    queueTemp.push(make_pair(queue1.top().first, queue1.top().second - 1));
                    queue1.pop();
                } else///אחרת הוא נחשב מהנזרקים אז לא נכניס לתור מלכתחילה
                {
                    droppedPackets++;
                    queue1.pop();

                }
            }

            if(!queueTemp.empty()) ///ניקח את הערך הגבוה ביותר
            {
                transmittedPackets++;
                transmittedValue += queueTemp.top().first;
                queueTemp.pop();
            }
            while(!queueTemp.empty()) ///נחזיר הכל לתור שלנו
            {
                queue1.push(queueTemp.top());
                queueTemp.pop();
            }

        }

        /*           priority_queue<pair1, vector<pair1>, greater<pair1> > queueTemp;
           /// הדפסה
                       while(!queue1.empty())
                       {
                           queueTemp.push(queue1.top());
                           cout<<queue1.top().first<<" "<<queue1.top().second<<"--";
                           queue1.pop();
                       }
                       cout<<endl;
                       while(!queueTemp.empty())
                       {
                           queue1.push(queueTemp.top());
                           queueTemp.pop();
                       }
           ///*/
    }//end main while

    priority_queue<pair<int, int> > queueTemp2;
    while(!queue1.empty()) ///עדכון בסוף הקובץ לחישוב הנשלחים עד שהתור יתרוקן
    {

        while(!queue1.empty())
        {
            if(queue1.top().second-1>0)///אם לאחר הורדה של 1 הסלאק גדול מאפס אז נמשיך
            {
                queueTemp2.push(make_pair(queue1.top().first, queue1.top().second - 1));
                queue1.pop();
            } else ///אחרת הוא נחשב מהנזרקים אז לא נכניס לתור מלכתחילה
            {
                droppedPackets++;
                queue1.pop();

            }
        }

        if(!queueTemp2.empty()) ///ניקח את הערך הגבוה ביותר
        {
            //cout<<queueTemp2.top().first;
            transmittedPackets++;
            transmittedValue += queueTemp2.top().first;
            queueTemp2.pop();
        }

        while(!queueTemp2.empty())///נחזיר הכל לתור שלנו
        {
            queue1.push(queueTemp2.top());
            queueTemp2.pop();
        }

    }
    cout<<"total arrived packets "<<arrivedPackets<<", "<< "total dropped packets "<<droppedPackets<<", "<<
        "total transmitted packets "<<transmittedPackets<<", "<< "total transmitted value "<<transmittedValue<<"."<<endl;

    fclose(file);
}




int main(int argc, char *argv[]) {


    std::string algo = argv[0];
    std::string sizeOfQueue = argv[1];
    std::string fileName = argv[2];

    
    bd(fileName,sizeOfQueue);


   /* switch(algo[0]) {
        case 'e':
            edf(fileName,sizeOfQueue);
            break;
        case 'b':
            break;

    }*/


}