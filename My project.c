#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


#define MAX_BOOKINGS 30
#define FILENAME "CiNSUHUB.txt"

struct Booking{
    int booking_id;
    char customer_name[50];
    char phone[15];
    char movie_name[50];
    char showtime[20];
    char seat_class[20];
    int num_tickets;
    float price_per_ticket;
    float total_price;
};

struct Booking bookings[MAX_BOOKINGS];
int num_bookings=0;



int login()
{
    char id[20], pass[20];
    char correct_id[]= "admin";
    char correct_pass[]="1234";

    printf("\n************* MOVIE TICKET BOOKING SYSTEM *************\n");
    printf("Enter User ID : ");
    scanf("%s", id);
    printf("Enter Password : ");
    scanf("%s", pass);

    if (strcmp(id, correct_id) == 0 && strcmp(pass,correct_pass) == 0)
    {
        printf("\nLogin successful! Welcome to CiNSUHUB><");
        return 1;
    }
    else
    {
        printf("\nLogin failed! Try again.\n");
        return 0;
    }
}



void saveToFile()
{
    if (num_bookings == 0)
    {
        printf("Oops...You haven't booked anything yet!\n");
        return;
    }

    FILE *fptr;
    fptr=fopen(FILENAME, "w");

    if (fptr==NULL)
    {
        printf("Sorry! Could not open file.\n");
        return;
    }
    for (int i=0;i<num_bookings;i++)
    {
        fprintf(fptr, "%d|%s|%s|%s|%s|%s|%d|%.2f|%.2f\n",
              bookings[i].booking_id,
              bookings[i].customer_name,
              bookings[i].phone,
              bookings[i].movie_name,
              bookings[i].showtime,
              bookings[i].seat_class,
              bookings[i].num_tickets,
              bookings[i].price_per_ticket,
              bookings[i].total_price);
    }
    fclose(fptr);
    printf("Nice! File saved successfully.\n");
}



void loadFromFile()
{
    FILE *fptr;
    fptr = fopen(FILENAME, "r");
    if (fptr==NULL)
    {
        return;
    }
    num_bookings=0;
    while (num_bookings<MAX_BOOKINGS && fscanf(fptr,"%d|%49[^|]|%14[^|]|%49[^|]|%19[^|]|%19[^|]|%d|%f|%f\n",
            &bookings[num_bookings].booking_id,
            bookings[num_bookings].customer_name,
            bookings[num_bookings].phone,
            bookings[num_bookings].movie_name,
            bookings[num_bookings].showtime,
            bookings[num_bookings].seat_class,
            &bookings[num_bookings].num_tickets,
            &bookings[num_bookings].price_per_ticket,
            &bookings[num_bookings].total_price) == 9)
    {
        num_bookings++;
    }
    fclose(fptr);

    for (int i = 0; i < num_bookings; i++)
        bookings[i].booking_id = i + 1;
    printf("Congrats! Loaded %d booking(s) successfully.\n", num_bookings);
}



void deleteBooking()
{
    if (num_bookings == 0)
    {
        printf("No bookings found.\n");
        return;
    }


    printf("\n--- All Bookings ---\n");
    printf("Occupied slots : 1 to %d\n", num_bookings);
    printf("Free slots     : %d to %d\n\n", num_bookings + 1, MAX_BOOKINGS);
    for (int i = 0; i < num_bookings; i++)
    {
        printf("[%d] ID: %d | Name: %s | Movie: %s | Showtime: %s\n",
               i + 1,
               bookings[i].booking_id,
               bookings[i].customer_name,
               bookings[i].movie_name,
               bookings[i].showtime);
    }


    int choice;
    printf("\nEnter record number to delete (1-%d): ", num_bookings);
    scanf("%d", &choice);

    if (choice < 1 || choice > num_bookings)
    {
        printf("Invalid choice.\n");
        return;
    }

    int idx = choice - 1;

    char confirm;
    printf("Delete booking ID %d for %s? (y/n): ", bookings[idx].booking_id, bookings[idx].customer_name);
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("Deletion canceled.\n");
        return;
    }


    int freed_id = bookings[idx].booking_id;

    for (int i = idx; i < num_bookings - 1; i++)
        bookings[i] = bookings[i + 1];
    num_bookings--;


    for (int i = 0; i < num_bookings; i++)
        bookings[i].booking_id = i + 1;

    saveToFile();
    printf("Record #%d deleted. Records renumbered 1 to %d.\n", freed_id, num_bookings);
}



void edit()
{
    char key[50];
    int i;

    printf("\n========== EDIT BOOKING ==========\n");
    printf("Enter customer name to search: ");

    getchar();
    fgets(key, 50, stdin);
    strtok(key, "\n");

    int matches[MAX_BOOKINGS];
    int match_count = 0;

    printf("\nMatching Records:\n");

    for (i = 0; i < num_bookings; i++)
    {
        if (strstr(bookings[i].customer_name, key) != NULL)
        {
            printf("[%d] ID: %d | Name: %s | Movie: %s | Showtime: %s\n",
                   match_count + 1,
                   bookings[i].booking_id,
                   bookings[i].customer_name,
                   bookings[i].movie_name,
                   bookings[i].showtime);

            matches[match_count] = i;
            match_count++;
        }
    }

    if (match_count == 0)
    {
        printf("No matching records found.\n");
        return;
    }

    printf("\nSelect record to edit (1-%d): ", match_count);

    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > match_count)
    {
        printf("Invalid choice.\n");
        return;
    }

    int idx = matches[choice - 1];

    printf("\n********** EDITING RECORD **********\n");
    printf("Press ENTER to keep current value.\n\n");

    char temp[50];
    int sel;


    printf("Customer name [%s]: ", bookings[idx].customer_name);
    fgets(temp, 50, stdin);
    if (temp[0] != '\n' && temp[0] != '\0')
    {
        strtok(temp, "\n");
        strcpy(bookings[idx].customer_name, temp);
    }


    while (1)
    {
        printf("Phone [%s] (11 digits, ENTER to keep): ", bookings[idx].phone);
        fgets(temp, 50, stdin);
        if (temp[0] == '\n' || temp[0] == '\0')
            break;
        strtok(temp, "\n");
        int len = (int)strlen(temp);
        int valid = 1;
        if (len != 11)
            valid = 0;
        else
            for (int k = 0; k < len; k++)
                if (!isdigit((unsigned char)temp[k])) { valid = 0; break; }
        if (valid)
        {
            strcpy(bookings[idx].phone, temp);
            break;
        }
        printf("Invalid! Phone must be exactly 11 digits with no letters or spaces.\n");
    }


    printf("Movie [%s]:\n", bookings[idx].movie_name);
    printf("  0. Keep current\n");
    printf("  1. Dune\n  2. Inception\n  3. The Conjuring\n");
    printf("  4. Shutter Island\n  5. Parasite\n  6. The Devil Wears Prada\n");
    printf("  7. Get Out\n  8. Howl's Moving Castle\n  9. Interstellar\n");
    printf(" 10. Murder on the Orient Express\n  Choice: ");
    scanf("%d", &sel);
    switch (sel)
    {
        case 1:  strcpy(bookings[idx].movie_name, "Dune");                         break;
        case 2:  strcpy(bookings[idx].movie_name, "Inception");                    break;
        case 3:  strcpy(bookings[idx].movie_name, "The Conjuring");                break;
        case 4:  strcpy(bookings[idx].movie_name, "Shutter Island");               break;
        case 5:  strcpy(bookings[idx].movie_name, "Parasite");                     break;
        case 6:  strcpy(bookings[idx].movie_name, "The Devil Wears Prada");        break;
        case 7:  strcpy(bookings[idx].movie_name, "Get Out");                      break;
        case 8:  strcpy(bookings[idx].movie_name, "Howl's Moving Castle");         break;
        case 9:  strcpy(bookings[idx].movie_name, "Interstellar");                 break;
        case 10: strcpy(bookings[idx].movie_name, "Murder on the Orient Express"); break;
        default: break;
    }


    printf("Showtime [%s]:\n", bookings[idx].showtime);
    printf("  0. Keep current\n");
    printf("  1. 10:00 AM\n");
    printf("  2. 03:00 PM\n");
    printf("  3. 08:00 PM\n");
    printf("  Choice: ");
    scanf("%d", &sel);
    switch (sel)
    {
        case 1: strcpy(bookings[idx].showtime, "10:00 AM"); break;
        case 2: strcpy(bookings[idx].showtime, "03:00 PM"); break;
        case 3: strcpy(bookings[idx].showtime, "08:00 PM"); break;
        default: break;
    }


    printf("Seat Class [%s]:\n", bookings[idx].seat_class);
    printf("  0. Keep current\n");
    printf("  1. Front\n");
    printf("  2. Rear\n");
    printf("  Choice: ");
    scanf("%d", &sel);
    switch (sel)
    {
        case 1: strcpy(bookings[idx].seat_class, "Front"); break;
        case 2: strcpy(bookings[idx].seat_class, "Rear");  break;
        default: break;
    }


    printf("Number of tickets [%d]:\n", bookings[idx].num_tickets);
    printf("  0. Keep current\n");
    printf("  1.  1 ticket\n");
    printf("  2.  2 tickets\n");
    printf("  3.  3 tickets\n");
    printf("  4.  4 tickets\n");
    printf("  5.  5 tickets\n");
    printf("  6.  6 tickets\n");
    printf("  7.  7 tickets\n");
    printf("  8.  8 tickets\n");
    printf("  9.  9 tickets\n");
    printf(" 10. 10 tickets\n");
    printf("  Choice: ");
    scanf("%d", &sel);
    if (sel >= 1 && sel <= 10)
        bookings[idx].num_tickets = sel;
    getchar();


    bookings[idx].total_price =
        bookings[idx].num_tickets * bookings[idx].price_per_ticket;

    saveToFile();

    printf("\nBooking updated successfully!\n");
    printf("Updated Total Price: %.2f BDT\n", bookings[idx].total_price);
}



void generateTicket(int idx)
{
    printf("\n");
    printf("+================================================+\n");
    printf("|           CiNSUHUB MOVIE TICKET               |\n");
    printf("+================================================+\n");
    printf("| %-14s: %-31d|\n", "Booking ID",   bookings[idx].booking_id);
    printf("| %-14s: %-31s|\n", "Name",         bookings[idx].customer_name);
    printf("| %-14s: %-31s|\n", "Phone",        bookings[idx].phone);
    printf("| %-14s: %-31s|\n", "Movie",        bookings[idx].movie_name);
    printf("| %-14s: %-31s|\n", "Showtime",     bookings[idx].showtime);
    printf("| %-14s: %-31s|\n", "Seat Class",   bookings[idx].seat_class);
    printf("| %-14s: %-31d|\n", "Tickets",      bookings[idx].num_tickets);
    printf("| %-14s: BDT %-27.2f|\n", "Price/Ticket", bookings[idx].price_per_ticket);
    printf("| %-14s: BDT %-27.2f|\n", "Total Price",  bookings[idx].total_price);
    printf("+================================================+\n");
    printf("|                  [ QR CODE ]                  |\n");
    printf("|                                                |\n");

    for (int i = 0; i < 5; i++)
    {
        printf("|        ");
        for (int j = 0; j < 16; j++)
            printf("%s", (rand() % 2) ? "##" : "  ");
        printf("        |\n");
    }

    printf("|                                                |\n");
    printf("|  ID: #%04d       Thank you for booking!       |\n", bookings[idx].booking_id);
    printf("+================================================+\n");
}


void view()
{
    if(num_bookings == 0)
    {
        printf("No bookings found.\n");
        return;
    }

    int i;
    printf("\n");
    printf("%-4s  %-20s  %-13s  %-15s  %-10s  %-6s  %-7s  %-12s  %-10s\n",
           "ID", "Name", "Phone", "Movie", "Showtime", "Seat", "Tickets", "Price/Ticket", "Total(BDT)");
    printf("%-4s  %-20s  %-13s  %-15s  %-10s  %-6s  %-7s  %-12s  %-10s\n",
           "----", "--------------------", "-------------", "---------------",
           "----------", "------", "-------", "------------", "----------");

    for(i = 0; i < num_bookings; i++)
    {
        printf("%-4d  %-20s  %-13s  %-15s  %-10s  %-6s  %-7d  %-12.2f  %-10.2f\n",
               bookings[i].booking_id,
               bookings[i].customer_name,
               bookings[i].phone,
               bookings[i].movie_name,
               bookings[i].showtime,
               bookings[i].seat_class,
               bookings[i].num_tickets,
               bookings[i].price_per_ticket,
               bookings[i].total_price);
    }
    printf("\nTotal bookings: %d\n", num_bookings);
}


void add()
{
    if (num_bookings >= MAX_BOOKINGS)
    {
        printf("Sorry! The reservation is full. Try again next time.\n");
        return;
    }
    int idx = num_bookings;
    int movie_choice, time_choice, seat_choice;

    printf("\n***** Add New Booking *****\n");

    bookings[idx].booking_id = num_bookings + 1;

    getchar();

    printf("Customer Name: \n");
    fgets(bookings[idx].customer_name, 50, stdin);
    strtok(bookings[idx].customer_name, "\n");

    printf("Phone Number: \n");
    while (1)
    {
        fgets(bookings[idx].phone, 15, stdin);
        strtok(bookings[idx].phone, "\n");
        int len = (int)strlen(bookings[idx].phone);
        int valid = 1;
        if (len != 11)
            valid = 0;
        else
            for (int k = 0; k < len; k++)
                if (!isdigit((unsigned char)bookings[idx].phone[k])) { valid = 0; break; }
        if (valid) break;
        printf("Invalid! Phone must be exactly 11 digits. Try again: \n");
    }

    printf("\nSelect Movie:\n");
    printf("  1. Dune\n  2. Inception\n  3. The Conjuring\n");
    printf("  4. Shutter Island\n  5. Parasite\n  6. The Devil Wears Prada\n");
    printf("  7. Get Out\n  8. Howl's Moving Castle\n  9. Interstellar\n");
    printf(" 10. Murder on the Orient Express\n Choice: ");
    scanf("%d", &movie_choice);

    switch(movie_choice)
    {
        case 1:  strcpy(bookings[idx].movie_name, "Dune");                         break;
        case 2:  strcpy(bookings[idx].movie_name, "Inception");                    break;
        case 3:  strcpy(bookings[idx].movie_name, "The Conjuring");                break;
        case 4:  strcpy(bookings[idx].movie_name, "Shutter Island");               break;
        case 5:  strcpy(bookings[idx].movie_name, "Parasite");                     break;
        case 6:  strcpy(bookings[idx].movie_name, "The Devil Wears Prada");        break;
        case 7:  strcpy(bookings[idx].movie_name, "Get Out");                      break;
        case 8:  strcpy(bookings[idx].movie_name, "Howl's Moving Castle");         break;
        case 9:  strcpy(bookings[idx].movie_name, "Interstellar");                 break;
        case 10: strcpy(bookings[idx].movie_name, "Murder on the Orient Express"); break;
        default: strcpy(bookings[idx].movie_name, "Unknown Movie");
    }

    printf("\nSelect Time:\n 1. 10 AM\n 2. 3 PM\n 3. 8 PM\n Choice: ");
    scanf("%d", &time_choice);

    switch(time_choice)
    {
        case 1:
            strcpy(bookings[idx].showtime, "10:00 AM");
            break;
        case 2:
            strcpy(bookings[idx].showtime, "03:00 PM");
            break;
        case 3:
            strcpy(bookings[idx].showtime, "08:00 PM");
            break;
        default:
            strcpy(bookings[idx].showtime, "Not Set");
    }

    printf("\nSelect Seat Class:\n 1. Front Row\n 2. Rear Row\n Choice: ");
    scanf("%d", &seat_choice);

    switch(seat_choice)
    {
        case 1:
            strcpy(bookings[idx].seat_class, "Front");
            break;
        case 2:
            strcpy(bookings[idx].seat_class, "Rear");
            break;
        default:
            strcpy(bookings[idx].seat_class, "Class not available");
    }

    bookings[idx].price_per_ticket = 500.00;
    printf("\nFixed Price: %.2f BDT per ticket ---\n", bookings[idx].price_per_ticket);

    do {
        printf("Enter Number of Tickets (must be 1 or more): ");
        scanf("%d", &bookings[idx].num_tickets);
        if (bookings[idx].num_tickets <= 0)
            printf("Invalid! Number of tickets cannot be zero or negative.\n");
    } while (bookings[idx].num_tickets <= 0);

    bookings[idx].total_price = bookings[idx].num_tickets * bookings[idx].price_per_ticket;

    num_bookings++;
    generateTicket(idx);
    saveToFile();

    printf("Booking saved successfully!\n");
    printf("Total Payable: %.2f BDT\n", bookings[idx].total_price);

   }



void search()
{
    char key[50];
    int found = 0;

    printf("\nEnter customer name to search :");
    getchar();
    fgets(key, 50, stdin);
    strtok(key,"\n");

    for(int i = 0; key[i]; i++)
        key[i] = tolower(key[i]);

    printf("\n--- Search Results ---\n");

    for(int i = 0; i < num_bookings; i++)
    {
        char name_copy[50];
        strcpy(name_copy, bookings[i].customer_name);

        for(int j = 0; name_copy[j]; j++)
            name_copy[j] = tolower(name_copy[j]);

        if(strstr(name_copy, key) != NULL)
        {
            printf("ID: %d | Name: %s | Movie_Name: %s | Showtime: %s | Seat_class: %s | Tickets: %d | Total: %.2f BDT\n",
                  bookings[i].booking_id,
                  bookings[i].customer_name,
                  bookings[i].movie_name,
                  bookings[i].showtime,
                  bookings[i].seat_class,
                  bookings[i].num_tickets,
                  bookings[i].num_tickets * bookings[i].price_per_ticket);
            found=1;
        }
    }

    if(found!=1)
    {
    printf("No matching records found.\n");
    }
}



void generateBill()
{
    int id;
    printf("\nEnter Booking ID to generate bill: ");
    scanf("%d", &id);

    int foundIndex = -1;


    for (int i=0; i<num_bookings; i++)
    {
        if (bookings[i].booking_id == id)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("Error! Booking ID not found.\n");
        return;
    }

    int type;
    printf("Select Customer Type (1.Regular, 2.Student): ");
    scanf("%d", &type);

    float subtotal = bookings[foundIndex].total_price;
    float discountRate = 0.0;

    if (type == 2)
    {
        discountRate = 0.15;
        printf("Student discount applied!\n");
    }
    else if (bookings[foundIndex].num_tickets >= 5)
    {
        discountRate = 0.10;
        printf("Bulk booking discount applied!\n");
    }

    float discountAmount = subtotal * discountRate;
    float finalTotal = subtotal - discountAmount;

    printf("\n==============================");
    printf("\n       MOVIE TICKET BILL      ");
    printf("\n==============================");
    printf("\nBooking ID       : %d", bookings[foundIndex].booking_id);
    printf("\nCustomer         : %s", bookings[foundIndex].customer_name);
    printf("\nPhone            : %s", bookings[foundIndex].phone);
    printf("\nMovie            : %s", bookings[foundIndex].movie_name);
    printf("\nShowtime         : %s", bookings[foundIndex].showtime);
    printf("\nTickets          : %d", bookings[foundIndex].num_tickets);
    printf("\nPrice per ticket : %.2f BDT", bookings[foundIndex].price_per_ticket);

    printf("\n------------------------------");
    printf("\nSubtotal         : %.2f BDT", subtotal);

    if (discountAmount>0)
    {
        printf("\nDiscount         : -%.2f BDT", discountAmount);
    }

    printf("\nTOTAL PRICE      : %.2f BDT", finalTotal);
    printf("\n==============================\n");
}



int main()
{
    if(!login())
    return 0;
    loadFromFile();

    int choice;
    do
    {
        printf("\n********* MAIN MENU *********\n");
        printf("1. View All Bookings\n");
        printf("2. Add New Booking\n");
        printf("3. Search Booking\n");
        printf("4. Edit Booking\n");
        printf("5. Delete Booking\n");
        printf("6. Generate Bill / Invoice\n");
        printf("7. Print Ticket\n");
        printf("0. Exit\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                view();
                break;
            case 2:
                add();
                break;
            case 3:
                search();
                break;
            case 4:
                edit();
                break;
            case 5:
                deleteBooking();
                break;
            case 6:
                generateBill();
                break;
            case 7:
            {
                printf("Enter booking ID to print ticket: ");
                int id;
                scanf("%d", &id);
                int found = 0;
                for(int i = 0; i < num_bookings; i++)
                {
                    if(bookings[i].booking_id == id)
                    {
                        generateTicket(i);
                        found = 1;
                        break;
                    }
                }
                if(!found)
                {
                    printf("Booking ID not found.\n");
                }
                break;
            }
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Try again!\n");

        }
    }while(choice!=0);
    return 0;
}
