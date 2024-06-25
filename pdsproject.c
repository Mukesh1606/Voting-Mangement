#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
typedef struct voter_information
{
    char aadhar[20];
    char name[50];
    char birth_date[15];
    struct voter_information *next;
} node;
node *start;
typedef struct admin
{
    char adminname[30];
    char password[30];
    struct admin *next;
} admin_node;
admin_node *head;

typedef struct candidate_information
{
    int no;
    char name[50];
    char symbol[15];
    int vote;
    struct candidate_information *next1;
} node1;
node1 *root, *last = NULL;

//Voter
int isempty();
void insert_voters();
void voterwrite();
void readvoters();
void voterrewrite();
void delete_voters();
void display_voters();
void voterupdate();


//Candidate
int is_empty();
void insert_candidates();
void writecandidate();
void read_candidates();
void delete_candidates();
void display_candidates();
void candidateupdate();



//ADMIN
int admin_empty();
int checkadmin();
void admin();
void adminwrite();
void adminread();
void admindisplay();
int pp();
void stop();
void startprocess();


//Voting
void check();
void not_again();
void voting(char[], int);
void rewritevote();
void winning();









int isempty()
{
    return start == NULL;
}
void insert_voters()
{
    node *new;
    char name[40], aadhar[20], dob[20];
    new = (node *)malloc(sizeof(node));
    printf("Enter the voter's name: ");
    scanf("%s", name);
    printf("Enter his/her aadhar no: ");
    scanf("%s", aadhar);
    printf("Enter his/her dob: ");
    scanf("%s", dob);
    if (isempty())
    {
        strcpy(new->name, name);
        strcpy(new->aadhar, aadhar);
        strcpy(new->birth_date, dob);
        new->next = NULL;
        start = new;
    }
    else
    {
        node *new, *ptr;
        new = (node *)malloc(sizeof(node));
        ptr = start;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        strcpy(new->name, name);
        strcpy(new->aadhar, aadhar);
        strcpy(new->birth_date, dob);
        new->next = NULL;
        ptr->next = new;
    }
    voterwrite();
}
void voterwrite()
{
    FILE *ptr;
    ptr = fopen("voterinfo.txt", "a");
    int i;
    node *temp;
    temp = start;
    if (temp == NULL)
    {
        printf("Empty File");
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                fprintf(ptr, "%s\t%s\t%s\n", (temp->name), (temp->aadhar), (temp->birth_date));
            }
            temp = temp->next;
        }
    }
    fclose(ptr);
}

void readvoters()
{
    node *ptr;
    ptr = start;
    int fileempty = 0;
    FILE *infile = fopen("voterinfo.txt", "r");
    fseek(infile, 0, SEEK_END);
    if (ptr == NULL)
    {
        ptr = (node *)malloc(sizeof(node));
        start = ptr;
    }
    int len = (int)ftell(infile);
    if (len <= 0)
    {
        fileempty = 1;
        printf("File is Empty!!");
        ptr = NULL;
        start = ptr;
    }
    if (fileempty == 0)
    {
        rewind(infile);
        while (fscanf(infile, "\n%s\t%s\t%s", &(ptr->name), &(ptr->aadhar), &(ptr->birth_date)))
        {
            if (feof(infile))
            {
                break;
            }
            ptr->next = (node *)malloc(sizeof(node));
            ptr = ptr->next;
            //last=ptr;
            ptr->next = NULL;
        }
    }
    fclose(infile);
}

void voterrewrite()
{
    FILE *ptr;
    ptr = fopen("voterinfo.txt", "w");
    int i;
    node *temp;
    temp = start;
    if (temp == NULL)
    {
        printf("Empty File");
    }
    else
    {
        while (temp->next != NULL)
        {

            fprintf(ptr, "%s\t%s\t%s\n", (temp->name), (temp->aadhar), (temp->birth_date));
            temp = temp->next;
        }
    }
    fclose(ptr);
}


void delete_voters()
{
    readvoters();
    char c[30];
    display_voters();
    printf("Enter the Aadhar Number You want to Delete :");
    scanf("%s", c);
    node *temp, *ptr;
    temp = start;
    int position = 1, pos, found = 0;
    while (temp->next != NULL)
    {

        if (strcmp(temp->aadhar, c) == 0)
        {
            found = 1;
            pos = position;
        }
        temp = temp->next;
        position++;
    }

    if (found == 0)
    {
        printf("Entered Aadhar Number is not There in Voter's List :(\nTRY AGAIN!!\n");
        delete_voters();
    }
    else if (pos == 1)
    {
        temp = start;
        start = temp->next;
        printf("%s Successfully Deleted!\n", temp->name);
        free(temp);
    }
    else
    {
        int i = 1;
        temp = start;
        while (temp->next != NULL && i < pos - 1)
        {
            temp = temp->next;
            i++;
        }
        ptr = temp->next;
        temp->next = ptr->next;
        printf("%s Successfully Deleted!\n", ptr->name);
        free(ptr);
    }
    voterrewrite();
}

void display_voters()
{
    readvoters();
    node *ptr;
    ptr = start;
    if (ptr == NULL)
    {
        printf("List is Empty\n");
    }
    else
    {
        printf("-------------------------------------------------------------------------------------------\n");
        printf("Name\t\tAadharNo.\tDate of Birth\n");
        printf("-------------------------------------------------------------------------------------------\n");
        while (ptr->next != NULL)
        {
            printf("%s\t\t%s\t\t%s\n", (ptr->name), (ptr->aadhar), (ptr->birth_date));
            ptr = ptr->next;
        }
    }
}
void voterupdate()
{
    readvoters();
    node *ptr = start;
    char a[20];
    int found = 0;
    display_voters();
    printf("Enter the Aadhar Number Whose Details You Want To edit :");
    scanf("%s", a);
    while (ptr->next != NULL)
    {
        if (strcmp(ptr->aadhar, a) == 0)
        {
            found = 1;
            int ch;
            char nn[30];
            char adh[30];
            char d[30];
            do
            {
                printf("What do You Want to Edit?\n1.Name\n2.Aadhar\n3.Date of Birth\n4.Exit\n");
                scanf("%d", &ch);
                switch (ch)
                {
                case 1:
                    printf("Enter the New Name :");
                    scanf("%s", nn);
                    strcpy(ptr->name, nn);
                    break;
                case 2:

                    printf("Enter the New AADHAR NO. :");
                    scanf("%s", adh);
                    strcpy(ptr->aadhar, adh);
                    break;
                case 3:

                    printf("Enter the New DOB :");
                    scanf("%s", d);
                    strcpy(ptr->birth_date, d);
                    break;
                case 4:
                    break;
                default:
                    printf("Invalid!!!");
                }
            } while (ch != 4);
        }
        ptr = ptr->next;
    }
    if (found == 0)
    {
        printf("Entered Aadhar Number is not There in Voter's List :(\nTRY AGAIN!!\n");
        voterupdate();
    }
    voterrewrite();
}


//candidate related Functions


int is_empty()
{
    return root == NULL;
}
void insert_candidates()
{
    node1 *new;
    int no, vote = 0;
    char name[50], symbol[15];
    new = (node1 *)malloc(sizeof(node1));
    printf("Enter the S.no: ");
    scanf("%d", &no);
    printf("Enter the candidates name: ");
    scanf("%s", name);
    printf("Enter the symbol: ");
    scanf("%s", symbol);
    if (is_empty())
    {
        new->no = no;
        strcpy(new->name, name);
        strcpy(new->symbol, symbol);
        new->vote = 0;
        new->next1 = NULL;
        root = new;
    }
    else
    {
        node1 *new, *ptr;
        new = (node1 *)malloc(sizeof(node1));
        ptr = root;
        while (ptr->next1 != NULL)
        {
            ptr = ptr->next1;
        }
        new->no = no;
        strcpy(new->name, name);
        strcpy(new->symbol, symbol);
        new->vote = 0;
        new->next1 = NULL;
        ptr->next1 = new;
    }
    writecandidate();
}
void writecandidate()
{
    FILE *ptr;
    ptr = fopen("candidates_info.txt", "a");
    int i;
    node1 *temp;
    temp = root;
    if (temp == NULL)
    {
        printf("Empty File");
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->next1 == NULL)
            {
                fprintf(ptr, "%d\t%s\t%s\t\t%d\n", (temp->no), (temp->name), (temp->symbol), (temp->vote));
            }
            temp = temp->next1;
        }
    }
    fclose(ptr);
}

void read_candidates()
{
    node1 *ptr;
    ptr = root;
    int fileempty = 0;
    FILE *infile = fopen("candidates_info.txt", "r");
    fseek(infile, 0, SEEK_END);
    if (ptr == NULL)
    {
        ptr = (node1 *)malloc(sizeof(node1));
        root = ptr;
    }
    int len = (int)ftell(infile);
    if (len <= 0)
    {
        fileempty = 1;
        printf("File is Empty!!");
        ptr = NULL;
        root = ptr;
    }
    if (fileempty == 0)
    {
        rewind(infile);
        while (fscanf(infile, "\n%d\t%s\t%s\t%d", &(ptr->no), &(ptr->name), &(ptr->symbol), &(ptr->vote)))
        {
            if (feof(infile))
            {
                break;
            }
            ptr->next1 = (node1 *)malloc(sizeof(node1));
            ptr = ptr->next1;
            last = ptr;
            ptr->next1 = NULL;
        }
    }
    fclose(infile);
}

void delete_candidates()
{
    read_candidates();
    int c;
    display_candidates();
    printf("Enter the choice You want to Delete :");
    scanf("%d", &c);
    node1 *temp, *ptr;
    temp = root;
    int position = 0, pos, found = 0;
    while (temp->next1 != NULL)
    {
        position++;
        if (temp->no == c)
        {
            found = 1;
            pos = position;
        }
        temp = temp->next1;
    }
    if (found == 0)
    {
        printf("Entered Candidate Number is Not There in Candidate's List!!\nTRY AGAIN!!\n");
        delete_candidates();
    }
    else if (pos == 1)
    {
        temp = root;
        root = temp->next1;
        printf("%s Successfully Deleted!\n", temp->name);
        free(temp);
    }
    int i = 1;
    temp = root;
    while (temp->next1 != NULL && i < pos - 1)
    {
        temp = temp->next1;
        i++;
    }
    ptr = temp->next1;
    temp->next1 = ptr->next1;
    printf("%s Successfully Deleted!\n", ptr->name);
    free(ptr);
    rewritevote();
}

void display_candidates()
{
    read_candidates();
    node1 *ptr;
    ptr = root;
    if (ptr == NULL)
    {
        printf("List is Empty\n");
    }
    else
    {
        printf("-------------------------------------------------------------------------------------------\n");
        printf("S.no\tName\tSymbol\n");
        printf("-------------------------------------------------------------------------------------------\n");
        while (ptr->next1 != NULL)
        {
            printf("%d\t%s\t%s\n", (ptr->no), (ptr->name), (ptr->symbol));
            ptr = ptr->next1;
        }
    }
}

void candidateupdate()
{
    read_candidates();
    node1 *ptr = root;
    int a, found = 0;
    display_candidates();
    printf("Enter the Candidate Number Whose Details You Want To edit :");
    scanf("%d", &a);
    while (ptr->next1 != NULL)
    {
        if (ptr->no == a)
        {
            found = 1;
            int ch, candidateno;
            char name[30], sym[20];
            do
            {
                printf("What do You Want to Edit?\n1.Candidate Number\n2.Name\n3.Symbol\n4.Exit\n");
                scanf("%d", &ch);
                switch (ch)
                {
                case 1:
                    printf("Enter the New Candidate Number :");
                    scanf("%d", &candidateno);
                    ptr->no = candidateno;
                    break;
                case 2:

                    printf("Enter the New Candidate Name :");
                    scanf("%s", name);
                    strcpy(ptr->name, name);
                    break;
                case 3:

                    printf("Enter the New Symbol :");
                    scanf("%s", sym);
                    strcpy(ptr->symbol, sym);
                    break;
                case 4:
                    break;
                default:
                    printf("Invalid!!!");
                }
            } while (ch != 4);
        }
        else
        {
            found = 0;
        }
        ptr = ptr->next1;
    }
    if (found == 0)
    {
        printf("Entered Candidate Number is Not There in Candidate's List!!\nTRY AGAIN!!\n");
        candidateupdate();
    }
    rewritevote();
}


//Admin Related Functions


int admin_empty()
{
    return head == NULL;
}
int checkadmin()
{
    adminread();
    char name[30], pass[30];
    int flag = 0;
    admin_node *ptr;
    ptr = head;
    printf("Enter Your Name :");
    scanf("%s", name);
    printf("Enter Password :");
    scanf("%s", pass);
    while (ptr->next != NULL)
    {
        if (strcmp(ptr->adminname, name) == 0)
        {
            if (strcmp(ptr->password, pass) == 0)
            {
                flag = 1;
            }
        }
        ptr = ptr->next;
    }
    return flag;
}
void admin()
{
    admin_node *new;
    int flag = 0;
    char name[40], pass[30], confpass[30];
    new = (admin_node *)malloc(sizeof(admin_node));
    printf("Enter the Admin's name: ");
    scanf("%s", name);
    printf("Enter Password :");
    scanf("%s", pass);
    printf("Confirm Password :");
    scanf("%s", confpass);
    if (strcmp(pass, confpass) == 0)
    {
        flag = 1;
    }
    if (flag == 1)
    {
        if (admin_empty())
        {
            strcpy(new->adminname, name);
            strcpy(new->password, pass);
            new->next = NULL;
            head = new;
        }
        else
        {
            admin_node *new, *ptr;
            new = (admin_node *)malloc(sizeof(admin_node));
            ptr = head;
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            strcpy(new->adminname, name);
            strcpy(new->password, pass);
            new->next = NULL;
            ptr->next = new;
        }
    }
    else
    {
        printf("Password And Confirm Password mismatched :(\nTRY AGAIN!!");
        admin();
    }
    adminwrite();
}

void adminwrite()
{
    FILE *ptr;
    ptr = fopen("admindetails.txt", "a");
    admin_node *temp;
    temp = head;
    if (temp == NULL)
    {
        printf("Empty File");
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->next == NULL)
                fprintf(ptr, "%s\t%s\n", (temp->adminname), (temp->password));
            temp = temp->next;
        }
    }
    fclose(ptr);
}
void adminread()
{
    admin_node *ptr;
    ptr = head;
    int fileempty = 0;
    FILE *infile = fopen("admindetails.txt", "r");
    fseek(infile, 0, SEEK_END);
    if (ptr == NULL)
    {
        ptr = (admin_node *)malloc(sizeof(admin_node));
        head = ptr;
    }
    int len = (int)ftell(infile);
    if (len <= 0)
    {
        fileempty = 1;
        printf("File is Empty!!");
        ptr = NULL;
        head = ptr;
    }
    if (fileempty == 0)
    {
        rewind(infile);
        while (fscanf(infile, "\n%s\t%s", &(ptr->adminname), &(ptr->password)))
        {
            if (feof(infile))
            {
                break;
            }
            ptr->next = (admin_node *)malloc(sizeof(admin_node));
            ptr = ptr->next;
            ptr->next = NULL;
        }
    }
    fclose(infile);
}

void admindisplay()
{
    adminread();
    admin_node *ptr;
    ptr = head;
    if (ptr == NULL)
    {
        printf("List is Empty\n");
    }
    else
    {
        system("cls");
        printf("-------------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t\tName\n");
        printf("-------------------------------------------------------------------------------------------\n");
        while (ptr->next != NULL)
        {
            printf("\t\t\t\t\t%s\n", (ptr->adminname));
            ptr = ptr->next;
        }
    }
}

int pp()
{
    FILE *ptr = fopen("process.txt", "r");
    int pp;
    fseek(ptr, 0, SEEK_END);
    int len = (int)ftell(ptr);
    rewind(ptr);
    while (len > 0)
    {
        fscanf(ptr, "%d", &pp);
        if (feof(ptr))
        {
            break;
        }
        len--;
    }
    fclose(ptr);
    return pp;
}

void stop()
{
    int c=pp();
    FILE *ptr;
    ptr = fopen("process.txt", "w");
    if(c==0)
    {
        int p = 1;
        fprintf(ptr, "%d", p);
        printf("Election Process Has been stopped successfully");
    }
    else
    {
        printf("Election Process is already stopped!!\n");
    }
    fclose(ptr); 
}

void startprocess()
{
    int c=pp();
    FILE *ptr;
    ptr = fopen("process.txt", "w");
    if (c == 1)
    {
        int p = 0;
        fprintf(ptr, "%d", p);
        printf("Election Process has been started Successfully");
    }
    else
    {
        printf("Election Process has been started already !!\n");
    }
    fclose(ptr);
}

//Voting Process Related Functions


void check()
{
    FILE *ptr;
    char a[12];
    ptr = fopen("voterinfo.txt", "r");
    int c = pp();
    if (c == 1)
    {
        printf("Sorry the voting process has been closed !!");
    }
    else
    {
        printf("Enter Your AADHAR Number :");
        scanf("%s", a);
        int len = strlen(a), flag = 0, found = 0;
        if (len > 13)
        {
            printf("Invalid AADHAR ID!!");
        }
        else
        {
            char c;
            c = fgetc(ptr);
            while (c != EOF)
            {
                if (c == a[flag])
                {
                    flag++;
                }
                else
                {
                    flag = 0;
                }
                if (flag == len)
                {
                    found = 1;
                    break;
                }
                c = fgetc(ptr);
            }
            if (found == 1)
            {
                fclose(ptr);
                not_again(a, len);
            }
            else
            {
                fclose(ptr);
                printf("Entered AADHAR Number is Not there in voter list!!\n\nPlease try Again :(\n");
                check();
            }
        }
    }
}
void not_again(char aa[], int n)
{
    FILE *fp;
    fp = fopen("check.txt", "r");
    char ch;
    int flag = 0, found = 0;
    ch = fgetc(fp);
    while (ch != EOF)
    {
        if (ch == aa[flag])
        {
            flag++;
        }
        else
        {
            flag = 0;
        }
        if (flag == n)
        {
            found = 1;
            break;
        }
        else
        {
            found = 0;
        }
        ch = fgetc(fp);
    }
    if (found == 1)
    {
        printf("Sorry You cannot vote again as You have already Voted!!\n");
    }
    else
    {
        voting(aa, n);
    }
}
void voting(char aadhar[], int n)
{
    display_candidates();
    int vote;
    printf("Enter Your Choice :");
    scanf("%d", &vote);
    node1 *ptr = root;
    while (ptr->next1 != NULL)
    {
        if (ptr->no == vote)
        {
            ptr->vote++;
        }
        ptr = ptr->next1;
    }
    rewritevote();
    FILE *kc;
    kc = fopen("check.txt", "a");
    fprintf(kc, "%s\n", aadhar);
    fclose(kc);
}
void rewritevote()
{
    FILE *ptr;
    ptr = fopen("candidates_info.txt", "w");
    int i;
    node1 *temp;
    temp = root;
    if (temp == NULL)
    {
        printf("Empty File");
    }
    else
    {
        for (i = 0; temp->next1 != NULL; i++)
        {
            fprintf(ptr, "%d\t%s\t%s\t%d\n", (temp->no), (temp->name), (temp->symbol), (temp->vote));
            temp = temp->next1;
        }
    }
    fclose(ptr);
}

void winning()
{
    read_candidates();
    node1 *ptr, *max;
    ptr = root;
    max = ptr;
    int count = 0;
    char arr[100][100];
    while (ptr->next1 != NULL)
    {
        if (max->vote < ptr->vote)
        {
            max = ptr;
        }
        ptr = ptr->next1;
    }
    ptr = root;
    while (ptr->next1 != NULL)
    {
        if (max->vote == ptr->vote)
        {
            strcpy(arr[count], ptr->name);
            count++;
        }
        ptr = ptr->next1;
    }
    if (count == 1)
    {
        printf("%s is leading in the election with %d votes", max->name, max->vote);
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            if (i == count - 2)
            {
                printf("%s and ", arr[i]);
            }
            else if (i == count - 1)
            {
                printf("%s ", arr[i]);
            }
            else
            {
                printf("%s, ", arr[i]);
            }
        }
        printf("are leading with same amount of votes(i.e %d Votes)\n", max->vote);
    }
}

//main()

int main()
{
    int pos;
    int ch, ch1, ch2;
    do
    {
        printf("\n");

        printf("-------------------------------------------------------------------------------------------\n\n");
        printf("                                    \t1.ADMIN\n");

        printf("                                    \t2.VOTE ENTRY\n");

        printf("                                    \t3.WINNER\n");

        printf("                                    \t4.EXIT\n");

        printf("-------------------------------------------------------------------------------------------\n\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);
        printf("-------------------------------------------------------------------------------------------\n\n");
        switch (ch)
        {

        case 1:

            if (checkadmin())
            {
                do
                {
                    system("cls");

                    printf("-------------------------------------------------------------------------------------------\n\n");
                    printf("                                    \t1.ADD/EDIT VOTERS \n");
                    printf("                                    \t2.ADD/EDIT CANDIDATES\n");
                    printf("                                    \t3.ADD/EDIT ADMIN\n");
                    printf("                                    \t4.EXIT\n");
                    printf("-------------------------------------------------------------------------------------------\n\n");
                    printf("Enter your choice: ");
                    scanf("%d", &ch1);
                    printf("-------------------------------------------------------------------------------------------\n\n");
                    system("cls");
                    switch (ch1)
                    {
                        system("cls");
                    case 1:

                        do
                        {

                            printf("-------------------------------------------------------------------------------------------\n\n");
                            printf("\t\t\t\t\t1.Add a new voter\n\t\t\t\t\t2.Delete the voter\n\t\t\t\t\t3.Displaying the voters list\n\t\t\t\t\t4.Edit Details\n\t\t\t\t\t5.Exit\n");
                            printf("-------------------------------------------------------------------------------------------\n\n");
                            printf("\nEnter your choice: ");
                            scanf("%d", &ch2);
                            printf("-------------------------------------------------------------------------------------------\n\n");
                            switch (ch2)
                            {
                            case 1:
                                insert_voters();
                                break;
                            case 2:
                                delete_voters();
                                break;
                            case 3:
                                display_voters();
                                break;
                            case 4:
                                voterupdate();
                                break;
                            case 5:
                                break;
                            default:
                                printf("Invalid choice\n");
                            }
                        } while (ch2 != 5);
                        break;
                    case 2:
                        do
                        {

                            printf("-------------------------------------------------------------------------------------------\n\n");

                            printf("\n\n\t\t\t\t\t1.Add a new candidate\n\t\t\t\t\t2.Delete a candidate\n\t\t\t\t\t3.Displaying the candidates information\n\t\t\t\t\t4.Update Candidate Details\n\t\t\t\t\t5.Exit\n\n");

                            printf("-------------------------------------------------------------------------------------------\n\n");

                            printf("\nEnter your choice: ");
                            scanf("%d", &ch);
                            printf("-------------------------------------------------------------------------------------------\n\n");

                            switch (ch)
                            {
                            case 1:
                                insert_candidates();
                                break;
                            case 2:
                                delete_candidates();
                                break;
                            case 3:
                                display_candidates();
                                break;
                            case 4:
                                candidateupdate();
                                break;
                            case 5:
                                break;
                            default:
                                printf("Invalid choice\n");
                            }
                        } while (ch != 5);
                        break;
                    case 3:

                        do
                        {

                            printf("-------------------------------------------------------------------------------------------\n\n");
                            printf("\t\t\t\t\t1.Add a new Admin\n\t\t\t\t\t2..Display the existing Admins\n\t\t\t\t\t3.Stop the Polling Process\n\t\t\t\t\t4.Start the Polling Process\n\t\t\t\t\t5.Exit\n");
                            printf("-------------------------------------------------------------------------------------------\n\n");
                            printf("\nEnter your choice: ");
                            scanf("%d", &ch2);
                            printf("-------------------------------------------------------------------------------------------\n\n");
                            switch (ch2)
                            {
                            case 1:
                                admin();
                                break;
                            case 2:
                                admindisplay();
                                break;
                            case 3:
                                stop();
                                break;
                            case 4:
                                startprocess();
                                break;
                            case 5:
                                break;
                            default:
                                printf("Invalid choice\n");
                            }
                        } while (ch2 != 5);
                        break;
                    case 4:
                        break;
                    default:
                        printf("Invalid choice\n");
                    }
                    system("cls");
                } while (ch1 != 4);
            }
            else
            {
                printf("Name and Password Doesn't match with the Present Record");
                break;
            }
            break;
        case 2:
                check();
                break;
        case 3:
            winning();
            break;
        case 4:
            printf("Thanks For Using This Voting Portal");
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    } while (ch != 4);
}