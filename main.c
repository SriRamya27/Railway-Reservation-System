#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

typedef struct LOGIN
{char userid[20];
char pwd[10];
}login;

typedef struct STATION
{char stn1[20];
char stn2[20];
}station;

typedef struct PNR
{int pnrid;
int berths;
char train_no[50];
char  date[15];
char train_class[20];
int train_no_pos;
int date_pos;
int active;
}pnr;

typedef struct USER_BOOKING // consists of all relevant variables which take data from user
{int ch;
char train_no[5];
char train_class[2];
char  date[6]; // user should enter in ddmmyy
int pnr_array_2A[100][17][36][2];//1st dim: 100 pnr numbers; 2nd dim: 17 dates, 3rd dim: 36 trains; 4th dim: to store rand_pnr and no_berths booked;
int pnr_array_3A[100][17][36][2];
int pnr_array_SL[100][17][36][2];
int pnr_array_row_SL,pnr_array_row_2A,pnr_array_row_3A;
char first_name[15][6],last_name[15][6];
int person_age;
}user_booking;

typedef struct BOOKING_DATABASE //consists of predefined number of berths in a train etc....
{int berth_2A[17][36],berth_3A[17][36],berth_SL[17][36];
//1st dimension in each variable for date of travel
//2nd dimension for a specific train
// user should enter date in ddmmyy format
char *train[36];
char *date_of_travel[17];
}booking_database;

int bound_rand(int min, int max)
{int distance, anyRandom, x;
srand ( (unsigned)time(NULL));
rand();
rand();
rand();
distance = max-min;
anyRandom=rand();
x=anyRandom%distance;
return(x+min);
}

int main()
{
int book_again=1;
int pnrcounter=0;
int train_no_pos=0, date_pos=0;
booking_database berthdetails; // Initialising berthdetails, k represents date of travel
user_booking tkt;
pnr allpnrs[10];
tkt.pnr_array_row_SL=0;tkt.pnr_array_row_2A=0;tkt.pnr_array_row_3A=0;
int rand_pnr=bound_rand(1000000,9999999);
int flag_org_dest_same = 0;

for(int k=0;k<17;k++) // outer for loop for dates
    {for(int l=0;l<36;l++){ // inner for loop for trains
        berthdetails.berth_2A[k][l]=5;
        berthdetails.berth_3A[k][l]=8;
        berthdetails.berth_SL[k][l]=1;}}
login idpwd;
int flag_login=0, not_exit=1;

do
{
    book_again=1;

    while(book_again==1)

    {
    FILE *fp = fopen("/Users/Sreedhar/Desktop/RAMYA/2nd sem/RailwayReservation/RailwayReservation/backup/backup/usercredentials.csv","a"); // if we use w+ it will erase the old content and write the new content. a+ will just append the new data at the end of file.

    if (!fp)
    {printf("Can't open file\n");return 0;}

    char buf[10000];
    int row_count = 0;
    int column_count = 0;
        flag_login=0;
    int new_reg=0;
    char new_username[20],new_pwd[10];
        
        printf("Enter 0 if you are an existing user; Enter 1 to sign up as a new user:  ");
            scanf("%d",&new_reg);
            
        if(new_reg==1)
            {column_count=0;
                printf("Choose username (Max 20 characters):  ");
                scanf("%s",new_username);
                fputs("\n",fp); //this is the first fputs to go to new line
                fputs(new_username, fp);
                fputs(",",fp);
                column_count=1;
                printf("Choose password(Max 10 characters):  ");
                scanf("%s",new_pwd);
                fputs(new_pwd, fp);
                fputs(",",fp);
                fputs("0",fp);}
            fclose(fp);
            
        fp = fopen("/Users/Sreedhar/Desktop/RAMYA/2nd sem/RailwayReservation/RailwayReservation/backup/backup/usercredentials.csv","r");
        
            if(new_reg==0)
            {
                printf("Enter Userid:  ");
                scanf("%s",idpwd.userid);
                printf("Enter Password:  ");
                scanf("%s",idpwd.pwd);
                //to count the rows
                int rows_in_file = 0;
                for (int c = getc(fp); c != EOF; c = getc(fp))
                {if (c == '\n') // Increment count if this character is newline
                    rows_in_file++;}
                rows_in_file++; //add one more row to get correct number
                // printf("Rows in userdata file = %d\n",rows_in_file);
                fseek(fp,0,SEEK_SET);

                while (fgets(buf, 10000, fp))
                {
                    char *field = strtok(buf, ",");

                    column_count = 0;

                    row_count++;

                    if (row_count == 1) {continue;}

                    

                    

                    while (row_count<=rows_in_file && field)

                    {if (column_count == 0)

                    {if(strcmp(idpwd.userid,field)!=0)

                    {break;}}

                        if (column_count == 1)

                        {if(strcmp(idpwd.pwd,field)==0)

                        {flag_login =1; book_again=0;printf("\t\t\t\tUserid & Password matched!  ");

                            break;}}

                        field = strtok(NULL, ",");

                        column_count++;

                    }

                    if(row_count==rows_in_file && flag_login==0){;book_again=1;printf("Either username or password is wrong!\n"); break;}

                    

                    

                    if (flag_login==1){book_again=0;printf("Successfully logged in!\n"); break;}

                }// closing of while(fgets...

            }//closing bracket of if(new reg==0)

            fclose(fp);

        }// closing bracket of while(book_again==1)

        

        

        

        

        printf("Enter 0 to book tickets and 1 to cancel tickets:  ");

        scanf("%d",&tkt.ch);

        if (flag_login==1&&book_again==0&&tkt.ch==0)

        {

            station info;

            do {

                printf("Enter source station:  ");

                scanf("%s",info.stn1);

                printf("Enter destination station:  ");

                scanf("%s",info.stn2);

                if(strcmp(info.stn1, info.stn2)!=0) {flag_org_dest_same=0;}

                if(strcmp(info.stn1, info.stn2)==0)

                {printf("Origin and Destination cannot be the same\n"); flag_org_dest_same = 1;}

                

                

            } while(flag_org_dest_same==1);

            

            

            

            FILE *fp_train = fopen("/Users/Sreedhar/Desktop/RAMYA/2nd sem/RailwayReservation/RailwayReservation/backup/backup/train_details.csv","r");

            

            

            int row_count_source=0,column_count_source=0,row_count_dest=0,column_count_dest=0,

            row_count_field=0, column_count_field=0;

            

            

            char buf1[10000];

            

            

            //to count the rows

            int rows_in_file = 0;

            for (int c = getc(fp_train); c != EOF; c = getc(fp_train))

            {if (c == '\n') // Increment count if this character is newline

                rows_in_file++;}

            rows_in_file++; //add one more row to get correct number

            //printf("Rows in train file = %d\n",rows_in_file);

            fseek(fp_train,0,SEEK_SET);

            

            

            //to count the columns

            int cols_in_file = 0;

            for (int c = getc(fp_train); c != '\n'; c = getc(fp_train))

            {if (c == ',') // Increment count if this character is newline

                cols_in_file++;}

            cols_in_file++; //add one more column to get correct number

            //printf("Cols in train file = %d\n",cols_in_file);

            fseek(fp_train,0,SEEK_SET);

            

            while (fgets(buf1, 10000 , fp_train))

            {

                char *field = strtok(buf1,",");

                if(strcmp(info.stn1,field)==0){break;}

                row_count_source++;

                

                

                /*while(field && column_count_source<=cols_in_file)

                 {

                 column_count_source++;

                 field = strtok(NULL, ",");

                 }*/

            }

            row_count_source++;//add one more row to get correct number

            //printf("Row count source = %d\n",row_count_source);

            

            

            

            

            fseek(fp_train,0,SEEK_SET);

            int flag_dest_stn = 0;

            row_count_field = 0;

            column_count_dest = 0;

            while (fgets(buf1, 10000, fp_train))

            {

                char *field = strtok(buf1, ",");

                column_count_field = 0;

                row_count_field++;

                

                

                while (row_count_field<=1 && field)

                {

                    

                    

                    if (row_count_field == 1)

                    {

                        if(strcmp(info.stn2,field)==0)

                        {flag_dest_stn =1;

                            break;}

                    }

                    

                    field = strtok(NULL, ",");

                    column_count_dest++;

                }

                if(row_count_field==rows_in_file && flag_dest_stn==0){break;}

                

                

                if (flag_dest_stn==1){break;}

            }// closing of while(fgets...

            column_count_dest++;//add one more column to get correct number

            //printf("Column count dest = %d\n",column_count_dest);

            

            

            

            

            

            

            

            

            //Sagar idea

            fseek(fp_train,0,SEEK_SET);

            char *field = "";

            int cell_reqd = 0;

            int cnt = 1;

            int row_cnt = 1;

            int col_cnt = 1;

            int flag_got_info = 0;

            while ( fgets(buf1, 10000 , fp_train) && row_cnt<=rows_in_file)

            {//printf("333. I am here\n");

                field = strtok(buf1, ",");

                //printf("334. I am here\n");

                col_cnt = 0;

                while(field && col_cnt <= cols_in_file)

                { //printf("337. I am here\n");

                    cell_reqd = (row_count_source-1)*cols_in_file + column_count_dest;

                    //printf("Trains List:\n%s\n",field);

                    //printf("row_cnt = %d, cell_reqd = %d, cnt = %d\n",row_cnt,cell_reqd,cnt);

                    if(cell_reqd==cnt)

                    {flag_got_info = 1;

                        //printf("343. I am here\n");

                        break;}

                    cnt++;

                    col_cnt++;

                    //printf("346. I am here\n");

                    field = strtok(NULL, ",");

                    //printf("348. I am here\n");

                }

                //printf("350. I am here\n");

                if(flag_got_info == 1) {break;}

                row_cnt++;

            }

            if(flag_got_info == 0 || strcmp(field,"-")==0)  {printf("No direct trains between the selected stations\n\n");}

            else {printf("Trains between %s and %s: %s\n  ",info.stn1,info.stn2,field);}

            

            

        }

        

        

        

        

        

        

        

        

        if(tkt.ch==0)

        {

            printf("\t\t\t\t\tEnter the train number to be booked:  ");

            scanf("%s",tkt.train_no);

            printf("\t\t\t\tEnter date of travel in dd/mm/yy format:  ");

            scanf("%s",tkt.date);

            

            

            // FILE *fp_train = fopen("/Users/Sreedhar/Desktop/RAMYA/2nd sem/RailwayReservation/RailwayReservation/backup/backup/berths.csv","r");

            

            

            char *local_date_array[17]={"15/04/20","16/04/20","17/04/20","18/04/20","19/04/20","20/04/20","21/04/20","22/04/20","23/04/20","24/04/20","25/04/20","26/04/20","27/04/20","28/04/20","29/04/20","30/04/20","01/05/20"};

            

            

            for (int z=0;z<17;z++)

                berthdetails.date_of_travel[z]=local_date_array[z];

            

            

            char *local_train_array[36]={"13012","11213","17001","12017","17097","19098","13013","11214","14061","14613","17093","18405","14054","15932","14062","14614","41324","91312","17002","12018","17094","18406","41325","91313","14880","15512","17098","19099","14055","15933","12216","19707","14881","15513","12217","19708"};

            

            

            for(int y=0;y<36;y++)

                berthdetails.train[y]=local_train_array[y];

            

            

            

            //atta .. sagar here train position and date position of the index always stays at zero if you didn't find the

            //train or date, so always end up giving first date and first train that is what happened when I entered 14/4/20..

            

            

            for (train_no_pos=0;train_no_pos<36;train_no_pos++)

            {if (strcmp(berthdetails.train[train_no_pos],tkt.train_no)==0)

                break;} // compares the entered train number with the one in the array to capture its position

            

            

            for (date_pos=0;date_pos<17;date_pos++)

            {if (strcmp(berthdetails.date_of_travel[date_pos],tkt.date)==0)

                break;} //compares the entered date with the one in the array to capture its position

            

          

            

            printf("Berths available in train %s for date %s in 2nd AC:%d\t, 3rd AC:%d\t, Sleeper:%d\n",tkt.train_no,tkt.date, berthdetails.berth_2A[date_pos][train_no_pos],berthdetails.berth_3A[date_pos][train_no_pos],berthdetails.berth_SL[date_pos][train_no_pos]);//Print number of berths available for the date and train number entered by the user

            

            

            printf("Enter the class(2A for 2nd AC, 3A for 3rd AC, SL for Sleeper:  ");

            scanf("%s",tkt.train_class);

            

            

            printf("Enter the number of berths:  ");

            int no_berths; char name[6][15]; char age[6][2]; char gender[6][6];

            scanf("%d",&no_berths);

            

            

            if(no_berths>6)

            {

                printf("\nOnly 6 passengers can be booked in one session. For the remaining passengers you need to login again and book them\n");

            }

            

            

            

            

            for(int p=0;p<fmin(no_berths,6);p++)

                

                

            {printf("Enter Name:  ");

                scanf("%s",name[p]);

                printf("Enter Age:  ");

                scanf("%s",age[p]);

                printf("Enter Gender (Male/Female):  ");

                scanf("%s",gender[p]);

                

                

            }

            

            

            for(int k=0;k<6;k++)

                gender[no_berths+1][k]='\0';

            

            

            

            

            int temp_berth_type=0;

            

            

            if(strcmp(tkt.train_class,"SL")==0)

                temp_berth_type=berthdetails.berth_SL[date_pos][train_no_pos];

            

            

            if(strcmp(tkt.train_class,"3A")==0)

                temp_berth_type=berthdetails.berth_3A[date_pos][train_no_pos];

            

            

            if(strcmp(tkt.train_class,"2A")==0)

                temp_berth_type=berthdetails.berth_2A[date_pos][train_no_pos];

            //atta you have to call it every time.. otherwise same pnr is assigned to every ticket.

            rand_pnr=bound_rand(1000000,9999999);

            if (no_berths<=temp_berth_type)

                

                

            {   printf("Amount has been deducted from your account.    \tTicket succesfully booked!!\n\n********************TICKET**************************\n\nPNR %d\tDate: %s\tTrain: %s\tClass: %s\n\nNAME\t\t    GENDER\tAGE\tSTATUS\n",rand_pnr,local_date_array[date_pos],local_train_array[train_no_pos],tkt.train_class);

                

                

                for(int q=0;q<fmin(no_berths,6);q++)

                {

                    printf("%s\t\t\t",name[q]);

                    

                    

                    for(int w=0;w<1;w++)

                    {printf("%c",gender[q][w]);}

                    

                    

                    printf("\t");

                    

                    

                    for (int e=0;e<2;e++)

                    {printf("%c",age[q][e]);}

                    

                    

                    printf("\tCONFIRMED\n");

                }

                

                

                printf("\n");

                printf("****************************************************\n");

                temp_berth_type-=no_berths;

                printf("\nRemaining berths in this train and date is %d\n",temp_berth_type);

                //Atta --

                //Once berths are decudted and PNR is confirmed, add this to allpnrs

                pnrcounter++;

                allpnrs[pnrcounter].pnrid = rand_pnr;

                printf("\nAdding.....%d",allpnrs[pnrcounter].pnrid);

                allpnrs[pnrcounter].active = 1;

                strcpy(allpnrs[pnrcounter].train_no,tkt.train_no);

                strcpy(allpnrs[pnrcounter].date,tkt.date);

                strcpy(allpnrs[pnrcounter].train_class,tkt.train_class);

                allpnrs[pnrcounter].train_no_pos = train_no_pos;

                allpnrs[pnrcounter].date_pos=date_pos;

                allpnrs[pnrcounter].berths= fmin(no_berths,6);

                

                printf("\nAdded %d PNR to PNR ID %d database:",pnrcounter, allpnrs[pnrcounter].pnrid);

                

                

                

                if(strcmp(tkt.train_class,"SL")==0)

                    berthdetails.berth_SL[date_pos][train_no_pos]=temp_berth_type;

                

                

                if(strcmp(tkt.train_class,"3A")==0)

                    berthdetails.berth_3A[date_pos][train_no_pos]=temp_berth_type;

                

                

                if(strcmp(tkt.train_class,"2A")==0)

                    berthdetails.berth_2A[date_pos][train_no_pos]=temp_berth_type;

                

                

                

                

                if(strcmp(tkt.train_class,"SL")==0)

                {

                    tkt.pnr_array_SL[tkt.pnr_array_row_SL][date_pos][train_no_pos][0]=rand_pnr;

                    tkt.pnr_array_SL[tkt.pnr_array_row_SL][date_pos][train_no_pos][1]=no_berths;

                    printf("\nPrinting pnr_array %d %d\n",tkt.pnr_array_SL[tkt.pnr_array_row_SL][date_pos][train_no_pos][0],tkt.pnr_array_SL[tkt.pnr_array_row_SL][date_pos][train_no_pos][1]);

                    tkt.pnr_array_row_SL++;

                    

                    

                }

                

                

                if(strcmp(tkt.train_class,"3A")==0)

                {

                    tkt.pnr_array_3A[tkt.pnr_array_row_3A][date_pos][train_no_pos][0]=rand_pnr;

                    tkt.pnr_array_3A[tkt.pnr_array_row_3A][date_pos][train_no_pos][1]=no_berths;

                    printf("\nPrinting pnr_array %d %d\n",tkt.pnr_array_3A[tkt.pnr_array_row_3A][date_pos][train_no_pos][0],tkt.pnr_array_3A[tkt.pnr_array_row_3A][date_pos][train_no_pos][1]);

                    tkt.pnr_array_row_3A++;

                    

                    

                }

                

                

                if(strcmp(tkt.train_class,"2A")==0)

                {

                    tkt.pnr_array_2A[tkt.pnr_array_row_2A][date_pos][train_no_pos][0]=rand_pnr;

                    tkt.pnr_array_2A[tkt.pnr_array_row_2A][date_pos][train_no_pos][1]=no_berths;

                    printf("\nPrinting pnr_array %d %d\n",tkt.pnr_array_2A[tkt.pnr_array_row_2A][date_pos][train_no_pos][0],tkt.pnr_array_2A[tkt.pnr_array_row_2A][date_pos][train_no_pos][1]);

                    tkt.pnr_array_row_2A++;

                    

                    

                }

                

                

                

                

            }

            else

            {

                printf("Amount has been deducted from your account.    \tTicket succesfully booked!!\n\n********************TICKET**************************\n\nPNR %d\tDate: %s\tTrain: %s\tClass: %s\n\nNAME\t\t    GENDER\tAGE\tSTATUS\n",rand_pnr,local_date_array[date_pos],local_train_array[train_no_pos],tkt.train_class);

                int q1=0;

                for( q1=0;q1<temp_berth_type;q1++)

                {printf("%s\t\t\t",name[q1]);

                    

                    

                    for(int w1=0;w1<6;w1++)

                    {printf("%c",gender[q1][w1]);}

                    

                    

                    printf("\t");

                    

                    

                    for (int e1=0;e1<2;e1++)

                    {printf("%c",age[q1][e1]);}

                    

                    

                    printf("\tCONFIRMED\n");

                }

                

                

                for(int q2=q1;q2<no_berths;q2++) /// this for loop in else loop which will be entered only when berths needed by user are more than the available berths

                    

                    

                {

                    printf("%s\t\t\t",name[q2]);

                    

                    

                    for(int w2=0;w2<6;w2++)

                    {printf("%c",gender[q2][w2]);}

                    

                    

                    printf("\t");

                    

                    

                    for (int e2=0;e2<2;e2++)

                    {printf("%c",age[q2][e2]);}

                    

                    

                    printf("\tWaiting List %d\n",temp_berth_type+q2-1);

                }

                printf("\n");

                printf("****************************************************\n");

                temp_berth_type-=no_berths;

                

                printf("\nRemaining ... berths in this train and date is %d\n",temp_berth_type);

                

                

                //Once berths are decudted and PNR is confirmed, add this to allpnrs

                pnrcounter++;

                //printf("Adding............. not printing this ?????");

                allpnrs[pnrcounter].pnrid = rand_pnr;

                //printf("\nAdding.....%d",rand_pnr);

                printf("\nAdding.....%d",allpnrs[pnrcounter].pnrid);

                allpnrs[pnrcounter].active = 1;

                strcpy(allpnrs[pnrcounter].train_no,tkt.train_no);

                strcpy(allpnrs[pnrcounter].date,tkt.date);

                strcpy(allpnrs[pnrcounter].train_class,tkt.train_class);

                allpnrs[pnrcounter].train_no_pos = train_no_pos;

                allpnrs[pnrcounter].date_pos=date_pos;

                allpnrs[pnrcounter].berths= fmin(no_berths,6);

                

                printf("\nAdded %d PNR to PNR ID %d database:",pnrcounter, allpnrs[pnrcounter].pnrid);

                

                if(strcmp(tkt.train_class,"SL")==0)

                    berthdetails.berth_SL[date_pos][train_no_pos]=temp_berth_type;

                

                

                if(strcmp(tkt.train_class,"3A")==0)

                    berthdetails.berth_3A[date_pos][train_no_pos]=temp_berth_type;

                

                

                if(strcmp(tkt.train_class,"2A")==0)

                    berthdetails.berth_2A[date_pos][train_no_pos]=temp_berth_type;

                

                

                if(strcmp(tkt.train_class,"SL")==0)

                {

                    tkt.pnr_array_SL[tkt.pnr_array_row_SL][date_pos][train_no_pos][0]=rand_pnr;

                    tkt.pnr_array_SL[tkt.pnr_array_row_SL][date_pos][train_no_pos][1]=no_berths;

                    printf("\nPrinting pnr_array %d %d\n",tkt.pnr_array_SL[tkt.pnr_array_row_SL][date_pos][train_no_pos][0],tkt.pnr_array_SL[tkt.pnr_array_row_SL][date_pos][train_no_pos][1]);

                    tkt.pnr_array_row_SL++;

                    

                    

                }

                

                

                if(strcmp(tkt.train_class,"3A")==0)

                {

                    tkt.pnr_array_3A[tkt.pnr_array_row_3A][date_pos][train_no_pos][0]=rand_pnr;

                    tkt.pnr_array_3A[tkt.pnr_array_row_3A][date_pos][train_no_pos][1]=no_berths;

                    printf("\nPrinting pnr_array %d %d\n",tkt.pnr_array_3A[tkt.pnr_array_row_3A][date_pos][train_no_pos][0],tkt.pnr_array_3A[tkt.pnr_array_row_3A][date_pos][train_no_pos][1]);

                    tkt.pnr_array_row_3A++;

                    

                    

                }

                

                

                if(strcmp(tkt.train_class,"2A")==0)

                {

                    tkt.pnr_array_2A[tkt.pnr_array_row_2A][date_pos][train_no_pos][0]=rand_pnr;

                    tkt.pnr_array_2A[tkt.pnr_array_row_2A][date_pos][train_no_pos][1]=no_berths;

                    printf("\nPrinting pnr_array %d %d\n",tkt.pnr_array_2A[tkt.pnr_array_row_2A][date_pos][train_no_pos][0],tkt.pnr_array_2A[tkt.pnr_array_row_2A][date_pos][train_no_pos][1]);

                    tkt.pnr_array_row_2A++;

                }

                

                

            }

            

            

        }

        if(tkt.ch==1)//entering cancellation module

        {

            int pnr_entered=0;

            printf("Enter the PNR number to cancel:  ");

            scanf("%d",&pnr_entered);

            int foundpnr = 0;

            for(int i=0;i<=pnrcounter;i++){

                if(allpnrs[i].pnrid==pnr_entered&&allpnrs[i].active==1){

                    foundpnr=1;
                    allpnrs[i].active=0;
                    if(strcmp(allpnrs[i].train_class,"SL")==0){

                        int temp =   berthdetails.berth_SL[allpnrs[i].date_pos][allpnrs[i].train_no_pos];

                        printf("\nEarlier Available SL Berths for train and Date were: %d\n",berthdetails.berth_SL[allpnrs[i].date_pos][allpnrs[i].train_no_pos]);

                        

                        berthdetails.berth_SL[allpnrs[i].date_pos][allpnrs[i].train_no_pos]=temp+allpnrs[i].berths;

                        printf("\nNow Available SL Berths for train and Date are: %d\n\n",berthdetails.berth_SL[allpnrs[i].date_pos][allpnrs[i].train_no_pos]);

                        

                    }
                    
                    
                    else if(strcmp(allpnrs[i].train_class,"2A")==0){

                        int temp =   berthdetails.berth_2A[allpnrs[i].date_pos][allpnrs[i].train_no_pos];

                        printf("\nEarlier Available 2A Berths for train and Date were: %d\n",berthdetails.berth_2A[allpnrs[i].date_pos][allpnrs[i].train_no_pos]);

                        

                        berthdetails.berth_2A[allpnrs[i].date_pos][allpnrs[i].train_no_pos]=temp+allpnrs[i].berths;

                        printf("\nNow Available 2A Berths for train and Date are: %d\n\n",berthdetails.berth_2A[allpnrs[i].date_pos][allpnrs[i].train_no_pos]);

                        

                    }

                    else if(strcmp(allpnrs[i].train_class,"3A")==0){

                        int temp =   berthdetails.berth_3A[allpnrs[i].date_pos][allpnrs[i].train_no_pos];

                        printf("\nEarlier Available 3A Berths for train and Date were: %d\n",berthdetails.berth_3A[allpnrs[i].date_pos][allpnrs[i].train_no_pos]);

                        

                        berthdetails.berth_3A[allpnrs[i].date_pos][allpnrs[i].train_no_pos]=temp+allpnrs[i].berths;

                        printf("\nNow Available 3A Berths for train and Date are: %d\n\n",berthdetails.berth_3A[allpnrs[i].date_pos][allpnrs[i].train_no_pos]);

                        

                    }

                    

                    
                    

                }

            }
            if (foundpnr==0) printf("Entered pnr is not there in database \n");

            

        }

        

        

        //    else printf("Password does not match.\n\n");

        

        

        

        

        

        //else printf("This userid does not exist.\n\n");

        

        

        

        

    }while(not_exit==1);

    fflush(stdin);

    fflush(stdout);

}// main closing bracket

















//}


