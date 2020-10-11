
//using namespace std;
#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>

///ייצוג עבור כל קודקוד
typedef struct node {
    char prefix;  /// שם
    bool isEndOfWord;/// מסמן שיש פרפיקס שמסתיים בקודקוד הזה
    int count; /// סופר כמה פעמים עברתי בקודקוד (עוזר כשרוצים למחוק prefix)
    struct node* right; ///עבור '1'
    struct node* left; ///עבור '0'

}node;

///יצירת קודקוד חדש ואתחול הערכים ברירת מחדל
node* newVertex()
{
    node* head = NULL;
    head =(node*)malloc(sizeof(node));

    if (head!=NULL) {
        head->isEndOfWord = false;
        head->count = 0;
        head->left = NULL;
        head->right = NULL;
        head->prefix = '?';
    }
    return head;
}


/// פונקציה שמוצאת את עומק העץ
int maxDepth(node* node)
{
    if (node == NULL)
        return 0;
    else
    {
        /// compute the depth of each subtree
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

        /// use the larger one
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}

///הוספה של prefix לעץ שלנו
///מניחים שמקבלים קלט תקין בפורמט הנ"ל ADD 255.255.255/24 A
/// הip מגיע לאחר המרה לבינארי
void ADD(node* root,std::string ip,char name)

{
    for (int i = 0; i <ip.length(); i++)///נרוץ על כל המספר הבינארי שלנו
    {
        if (ip[i]=='1'){/// אם ראינו 1 ומימין לשורש אין קודקוד אז נייצר אחד ואז נזוז אליו
            if(root->right== nullptr){
                root->right =newVertex();
                root=root->right;
                root->count++; /// נעדכן שעברנו בקודקוד הזה
            }
            else{ /// קיים כבר קודקוד כזה
                root=root->right; ///  ראינו 1 נזוז ימינה
                root->count++; /// נעדכן שעברנו בקודקוד הזה

            }
        }
        else{/// ראינו אפס
            if(root->left== nullptr){ /// אם ראינו 0 ומשמאל לשורש אין קודקוד אז נייצר אחד ואז נזוז אליו
                root->left =newVertex();
                root=root->left;
                root->count++; /// נעדכן שעברנו בקודקוד הזה

            }
            else{ /// קיים כבר קודקוד כזה
                root=root->left; ///  ראינו 0 נזוז שמאלה
                root->count++; /// נעדכן שעברנו בקודקוד הזה

            }
        }

    }

    root->isEndOfWord = true; ///נסמן שקיים לנו perfix בקודקוד הזה
    root->prefix=name; ///נעדכן את השם שלו

}


///מציאה של prefix בעץ שלנו
///מניחים שמקבלים קלט תקין שקיים בעץ! בפורמט הנ"ל FIND 255.255.255.0
/// הip מגיע לאחר המרה לבינארי
void FIND(node* root,std::string ip)
{
    int counter =0;
    int counterTemp=0;
    char temp=' ';
    char temp2='?';
    for (int i = 0; i < ip.length(); i++)
    {
        if(root->isEndOfWord) ///אם קיים PERFIX בדרך נשמור אותו ואת הגובה שלו
        {
            temp=root->prefix;
            counterTemp=counter;
        }
        if(root->right==nullptr&&root->left== nullptr)
        {/// אם אנחנו בעלה תעצור כי אין לאן להתקדם
            temp2=root->prefix;
            break;
        }
        if (ip[i]=='1'&&root->right!=nullptr) ///אם ראינו 1 ובאמת מימין יש ילד נתקדם לשם ונעדכן גובה
        {
            root=root->right;
            counter++;
        }
        else if (ip[i]=='0'&&root->left!=nullptr) ///אם ראינו 0 ובאמת משמאל יש ילד נתקדם לשם ונעדכן גובה
        {
            root=root->left;
            counter++;

        }
            else{ ///עבור כל מקרה אחר תעצור
                break;
            }

    }
    if (temp2 == '?')
    { /// אם הגענו ל? זה אומר שלא הגענו לקודקוד הרצוי לנו אז תדפיס את הPREFIX האחרון התקין שהיה ואת הגובה שלו
        std::cout << temp <<" at the depth " << counterTemp << std::endl;
    }
    else{ /// אם זה לא ? שזה הברירת מחדל זה אומר שהגענו למה שחיפשנו אז תדפיס את העומק ואת הPREFIX
        std::cout << temp2 <<" at the depth " << counter << std::endl;
    }

}
/// פונקציה שמחזירה את כמות הקודקודים בעץ שלנו
int countVertex( node *root){
    if(root == NULL){
        return 0;
    }
    else{
        return 1 + countVertex(root->left) + countVertex(root->right);
    }
}

///מחיקה של prefix מהעץ שלנו
///מניחים שמקבלים קלט תקין שקיים בעץ! בפורמט הנ"ל REMOVE 255.255.255/24 A
/// הip מגיע לאחר המרה לבינארי
///subnet זה מספר התווים הבינארים הרלוונטים לנו לבדיקה (לפי זה הכנסנו לעץ)
void REMOVE(node* root,std::string ip,int subnet)
{
    for (int i = 0; i <=subnet ; i++) { ///נרוץ רק עד מספר האיברים הרלוונטים
        if(i==subnet){
        root->isEndOfWord=false;///אם הגענו לתנאי הזה זה אומר שיש בנים לקודקוד
          root->prefix='?';/// לכן רק נמחק את השם של הprefix לברירת המחדל
        }
        if(ip[i]=='1'){ ///אם ראינו 1
            root->right->count--; ///נוריד "ספירה של מעבר ימינה"
            if(root->right->count<1){ /// אם הסופר שלנו קטן מ-1 זה אומר שלא עוברים בו יותר
                root->right= nullptr; ///לכן נוכל למחוק את הקודקוד הזה ומה שמתחתיו ולעצור את הלולאה
                break;
            }
            root=root->right; ///נתקדם ימינה
        }
        else if(ip[i]=='0'){ ///אם ראינו 0
            root->left->count--; ///נוריד "ספירה של מעבר שמאלה"
            if(root->left->count<1){ /// אם הסופר שלנו קטן מ-1 זה אומר שלא עוברים בו יותר
                root->left= nullptr; ///לכן נוכל למחוק את הקודקוד הזה ומה שמתחתיו ולעצור את הלולאה
                break;

            }
            root=root->left; ///נתקדם שמאלה

        }
    }
}

///פונקציה שממירה ip למספר בינארי
std::string ipToBinary(int n)
{
    std::string d;
    /// array to store binary number
    int binaryNum[1000] = {};

    /// counter for binary array
    int i = 0;
    while (n > 0) {

        /// storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    /// printing binary array in reverse order
    int bits = 8;
    if ( i > 8 )
        bits = 8*((i + 7)/8);

    for (int j = bits-1; j >= 0; j--)
        d+= std::to_string(binaryNum[j]);

    return d;
}

bool findBeforRemove(node* root,std::string ip,char name){
    bool exist=false;

    int i;
    for (i = 0; i < ip.length(); i++) ///נבדוק אם האח הזה קיים
    {

        if(root->right==nullptr&&root->left== nullptr)
        {/// אם אנחנו בעלה תעצור כי אין לאן להתקדם
            break;
        }
        if (ip[i]=='1'&&root->right!=nullptr) ///אם ראינו 1 ובאמת מימין יש ילד נתקדם לשם
        {
            root=root->right;
        }
        else if (ip[i]=='0'&&root->left!=nullptr) ///אם ראינו 0 ובאמת משמאל יש ילד נתקדם לשם
        {
            root=root->left;
        }
        else{ ///עבור כל מקרה אחר תעצור
            break;
        }

    }
    if(i==ip.length()&&root->prefix==name) exist=true; ///אנו את הפרפיקס שחיפשנו


    return exist;
}

/// הפונקציה שמקבלת שם של קובץ קוראת אותו ומבצעת 3 פעולת בהתאם לאופרטור הנתון בשורה (בהנחה שהקלטים תקינים ובפורמט הנכון)
///ADD=מוסיפה לעץ פרפיקס נתון לפי המספר הבינארי של האייפי
///FIND=מחפשת פרפיקס מסויים שקיים כבר בעץ לפי המספר הבינארי של האייפי
///REMOVE=  מוחקת מהעץ פרפיקס קיים לפי המספר הבינארי של האייפי
void read (node* root,std::string nameFile)
{
    ///נמיר את הסטרינג למערך תווים בשביל הפונקציה fopen
    // assigning value to string s
    int n = nameFile.length();
    // declaring character array
    char char_nameFile[n + 1];
    // copying the contents of the
    // string to char array
    strcpy(char_nameFile, nameFile.c_str());

    FILE* file =fopen(char_nameFile,"r"); ///פתיחת הקובץ לקריאה

    if (file==NULL){ ///בדיקת תקינות
        std::cout<<("not good");
        return;
    }

/*
  char index;   ///ידפיס את כל הקובץ
    while ((ifOk=fscanf(file,"%c",&index)==1))
        printf("%c",index);
*/


  char index ;
  while(fscanf(file,"%c",&index)!=EOF) { ///תרוץ כל עוד הקובץ לא נגמר


      char op;                   ///האופרטור
      std::string ip = "";       ///אייפי
      char name = '-';           /// הפרפיקס
      std::string lastNum = "";       /// מס הביטים הרלוונטים להכנסה לעץ
      bool sign = true;

      ///זיהוי האופרטור לפי התו הראשון בשורה
      if (index == 'R') {
          op = 'R';
      } else if (index == 'A') {
          op = 'A';
      } else if (index == 'F') {
          op = 'F';
      }

      while (index != '\n') /// כל עוד אנחנו באותה שורה
      {
          if (index == '/')  /// אם ראינו את התו הזה אז זה אומר שאחריו יבוא הsubnet mask
          {
              index = getc(file); ///נתקדם למספר
              while (index != EOF && index != ' ')  /// וכל עוד לא ראינו רווח נשרשר את המספרים של הsubnet mask
              {
                  lastNum = lastNum + index;
                  index = getc(file);
              }

              index = getc(file); ///אחרי הרווח יבוא השם של הפרפיקס שלנו
              name = index;
          }
          index = getc(file);

          if (index != EOF && index == ' ' && sign)  ///אם הגענו לרווח הראשון זהו אומר שפה מתחילה כתובת האייפי
          {

              sign = false;///נסמן שעברנו את הרווח הראשון

              index = getc(file);

              while (index != EOF && index != '\n' && index != '/' && index != ' ')///נשרשר לIP את כל המספרים
              {
                  ip = ip + index;
                  index = getc(file);
              }

          }

      }

      ///המרה מסטרינג למערך תווים

      // assigning value to string s
      int n = ip.length();
      // declaring character array
      char char_array[n + 1];
      // copying the contents of the
      // string to char array
      strcpy(char_array, ip.c_str());


      ///המרת הIP שלנו לבינארי בשביל להכניס לעץ
      unsigned short a = 0, b = 0, c = 0, d = 0;
      sscanf(char_array, "%hu.%hu.%hu.%hu.", &a, &b, &c, &d);

      std:: string z = ipToBinary(a);
      std::string z1 = ipToBinary(b);
      std::string z2 = ipToBinary(c);
      std::string z3 = ipToBinary(d);

///הדפסת כל חלק בנפרד
   // cout<<z<<endl;
   // cout<<z1<<endl;
   // cout<<z2<<endl;
   // cout<<z3<<endl;

///שרשור כל החלקים
      std::string ans = z;
      ans += z1;
      ans += z2;
      ans += z3;

      ///הפיכת lastNum לINT
      std::stringstream geek(lastNum);
      int subnet=0;
      geek>>subnet;

      ///הכנת המספרים הבינארים שאמורים להיכנס לעץ (לפי הSUBNET שקיים לנו)
      std::string ipAfterSub;
      for(int k=0;k<subnet;k++) ///נשרשר את כל המספרים הבינארים כמספר הSUBNET שלנו
      {
          ipAfterSub=ipAfterSub+ans[k];
      }


    /// הפעלת הפונקציה המתאימה בהתאם לאופרטור בהתחלה
      int countVer=0;     ///בשביל מספר הקודקודים
      int depth=0;        /// בשביל העומק
      switch(op) {
          case 'R':
              if(findBeforRemove(root,ipAfterSub,name))
              REMOVE(root,ipAfterSub,subnet);
              depth=maxDepth(root)-1;///עומק העץ פחות קודקוד השורש

              countVer=countVertex(root);///מס הקודקודים בעץ

              std::cout<<"Removed "<<ip<<"/"<<lastNum<<" "<<name<<" at the depth "<<depth<<",total nodes "<<countVer<<std::endl;

              break;
          case 'A':
              ADD(root,ipAfterSub,name);
             depth=maxDepth(root)-1; ///עומק העץ פחות קודקוד השורש

              countVer=countVertex(root);///מס הקודקודים בעץ

              std::cout<<"Added "<<ip<<"/"<<lastNum<<" "<<name<<" at the depth "<<depth<<",total nodes "<<countVer<<std::endl;

              break;

          case 'F':
              std::cout<<"Found "<<ip<<" ";

              FIND(root,ans);
      }

  } //end while

    fclose(file);
}





int main()
{

    node *root = newVertex(); /// יצירת קודקוד השורש

    ///לכתוב את שם הקובץ שברצוננו להריץ
    read(root,"sample_input.txt");

    return 0;

}



