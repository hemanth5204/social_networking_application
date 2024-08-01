#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char username[20];
    struct user *next;
    struct friend_node *friends;
    struct post *posts;
};

struct friend_node {
    struct user *friend;
    struct friend_node *next;
};

struct post {
    char username[20];
    char post[100];
    struct post *next;
};

struct user *head = NULL;

void display_error(const char *message) {
    printf("Error: %s\n", message);
}
void add_user(char username[20]) {
    
    struct user *temp = (struct user *)malloc(sizeof(struct user));
    struct user *check_user = head;
    while (check_user != NULL) {
        if (strcmp(check_user->username, username) == 0) {
            display_error("User already exists");
            free(temp); // Free the allocated memory for temp
            return;
        }
        check_user = check_user->next;
    }
    strcpy(temp->username, username);
    temp->next = NULL;
    temp->friends = NULL;
    temp->posts = NULL;

    if (head == NULL) {
        head = temp;
    } else {
        struct user *ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}

void add_friend(char username1[20], char username2[20]) {
     struct user *ptr1 = head;
    struct user *ptr2 = head;
    int user1_found = 0, user2_found = 0;

    // Finding user1
    while (ptr1 != NULL && strcmp(ptr1->username, username1) != 0) {
        ptr1 = ptr1->next;
    }
    if (ptr1 != NULL) {
        user1_found = 1;
    }

    // Finding user2
    while (ptr2 != NULL && strcmp(ptr2->username, username2) != 0) {
        ptr2 = ptr2->next;
    }
    if (ptr2 != NULL) {
        user2_found = 1;
    }

    // Error handling if either user doesn't exist
    if (!user1_found || !user2_found) {
        if (!user1_found && !user2_found) {
            printf("Both users don't exist. Please re-enter.\n");
        } else if (!user1_found) {
            printf("User '%s' doesn't exist. Please re-enter.\n", username1);
        } else {
            printf("User '%s' doesn't exist. Please re-enter.\n", username2);
        }
        return; // Ask for the task again
    }


    struct friend_node *temp1 = (struct friend_node *)malloc(sizeof(struct friend_node));
    temp1->friend = ptr2;
    temp1->next = ptr1->friends;
    ptr1->friends = temp1;

    struct friend_node *temp2 = (struct friend_node *)malloc(sizeof(struct friend_node));
    temp2->friend = ptr1;
    temp2->next = ptr2->friends;
    ptr2->friends = temp2;
}

void remove_friend(char username1[20], char username2[20]) {
    struct user *ptr1 = head;
    struct user *ptr2 = head;

    while (strcmp(ptr1->username, username1) != 0) {
        ptr1 = ptr1->next;
    }

    while (strcmp(ptr2->username, username2) != 0) {
        ptr2 = ptr2->next;
    }
      
      if (!username1 || !username2) {
        if (!username1 && !username2) {
            printf("Both users don't exist. Please re-enter.\n");
        } else if (!username1) {
            printf("User '%s' doesn't exist. Please re-enter.\n", username1);
        } else {
            printf("User '%s' doesn't exist. Please re-enter.\n", username2);
        }
        return; // Ask for the task again
    }


    struct friend_node *temp1 = ptr1->friends;
    struct friend_node *prev1 = NULL;

    while (temp1 != NULL && strcmp(temp1->friend->username, username2) != 0) {
        prev1 = temp1;
        temp1 = temp1->next;
    }

    if (temp1 != NULL) {
        if (prev1 == NULL) {
            ptr1->friends = temp1->next;
        } else {
            prev1->next = temp1->next;
        }
        free(temp1);
    }

    struct friend_node *temp2 = ptr2->friends;
    struct friend_node *prev2 = NULL;

    while (temp2 != NULL && strcmp(temp2->friend->username, username1) != 0) {
        prev2 = temp2;
        temp2 = temp2->next;
    }

    if (temp2 != NULL) {
        if (prev2 == NULL) {
            ptr2->friends = temp2->next;
        } else {
            prev2->next = temp2->next;
        }
        free(temp2);
    }
}

void add_post(char username[20], char post[100]) {
    struct user *ptr = head;

    while (ptr != NULL && strcmp(ptr->username, username) != 0) {
        ptr = ptr->next;
    }

    if (ptr != NULL) {
        struct post *temp = (struct post *)malloc(sizeof(struct post));
        strcpy(temp->username, username);
        strcpy(temp->post, post);
        temp->next = ptr->posts;
        ptr->posts = temp;
    } else {
        printf("User not found.\n");
    }
}


void show_posts(char username[20]) {
    struct user *ptr = head;

    while (ptr != NULL && strcmp(ptr->username, username) != 0) {
        ptr = ptr->next;
    }

    if (ptr != NULL) {
        struct post *ptr1 = ptr->posts;

        while (ptr1 != NULL) {
            printf("%s: %s\n", ptr1->username, ptr1->post);
            ptr1 = ptr1->next;
        }
    } else {
        printf("User not found.\n");
    }
}

void show_friends(char username[20]) {
    struct user *ptr = head;

    while (ptr != NULL && strcmp(ptr->username, username) != 0) {
        ptr = ptr->next;
    }

    if (ptr != NULL) {
        struct friend_node *ptr1 = ptr->friends;

        printf("Friends of %s:\n", ptr->username);

        while (ptr1 != NULL) {
            printf("%s\n", ptr1->friend->username);
            ptr1 = ptr1->next;
        }
    } else {
        printf("User not found.\n");
    }
}

void show_mutuals(char username1[20], char username2[20]) {
    struct user *ptr1 = head;
    struct user *ptr2 = head;

    while (strcmp(ptr1->username, username1) != 0) {
        ptr1 = ptr1->next;
    }

    while (strcmp(ptr2->username, username2) != 0) {
        ptr2 = ptr2->next;
    }

    struct friend_node *ptr = ptr1->friends;

    printf("Mutual friends of %s and %s:\n", ptr1->username, ptr2->username);

    while (ptr != NULL) {
        struct friend_node *ptr3 = ptr2->friends;
        while (ptr3 != NULL) {
            if (strcmp(ptr->friend->username, ptr3->friend->username) == 0) {
                printf("%s\n", ptr->friend->username);
            }
            ptr3 = ptr3->next;
        }
        ptr = ptr->next;
    }
}

void search_posts(char keyword[100]) {
    struct user *ptr = head;

    while (ptr != NULL) {
        struct post *ptr1 = ptr->posts;

        while (ptr1 != NULL) {
            if (strstr(ptr1->post, keyword) != NULL) {
                printf("%s: %s\n", ptr1->username, ptr1->post);
            }

            ptr1 = ptr1->next;
        }

        ptr = ptr->next;
    }
}

void save_to_csv() {
    FILE *file = fopen("posts.csv", "w");

    if (file == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }

    struct user *user_ptr = head;
    while (user_ptr != NULL) {
        fprintf(file, "user,%s\n", user_ptr->username);

        struct friend_node *friend_ptr = user_ptr->friends;
        while (friend_ptr != NULL) {
            fprintf(file, "friend,%s,%s\n", user_ptr->username, friend_ptr->friend->username);
            friend_ptr = friend_ptr->next;
        }

        struct post *post_ptr = user_ptr->posts;
        while (post_ptr != NULL) {
            fprintf(file, "post,%s,%s\n", post_ptr->username, post_ptr->post);
            post_ptr = post_ptr->next;
        }

        user_ptr = user_ptr->next;
    }

    fclose(file);
}

void load_from_csv() {
    FILE *file = fopen("posts.csv", "r");

    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    char type[20];
    char username[20];
    char data1[20];
    char data2[20];
    char post_text[100];

    while (fscanf(file, "%19[^,],", type) == 1) {
        if (strcmp(type, "user") == 0) {
            fscanf(file, "%19[^\n]\n", username);
            add_user(username);
        } else if (strcmp(type, "friend") == 0) {
            fscanf(file, "%19[^,],%19[^\n]\n", data1, data2);
            add_friend(data1, data2);
        } else if (strcmp(type, "post") == 0) {
            fscanf(file, "%19[^,],%99[^\n]\n", data1, post_text);
            add_post(data1, post_text);
        }
    }

    fclose(file);
}



int main(void) {
    load_from_csv();  
    printf("Welcome to the Network\n");
    int choice;
    char username1[20], username2[20], post[100], keyword[100];
    while (1) {
        printf("What will you do?\n");
        printf("1. Add user\n2. Add friend\n3. Remove friend\n4. Add post\n5. Show posts\n6. Show friends\n7. Show mutual\n8. Search for a post\n9. Save to CSV\n10. Exit\nEnter your task ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the username: ");
                scanf("%19s", username1);
                add_user(username1);
                break;
            case 2:
                printf("Enter the username of user 1: ");
                scanf("%19s", username1);
                printf("Enter the username of user 2: ");
                scanf("%19s", username2);
                add_friend(username1, username2);
                break;
            case 3:
                printf("Enter the username of user 1: ");
                scanf("%19s", username1);
                printf("Enter the username of user 2: ");
                scanf("%19s", username2);
                remove_friend(username1, username2);
                break;
            case 4:
                printf("Enter the username: ");
                scanf("%19s", username1);
                printf("Enter the post: ");
                scanf(" %[^\n]", post);
                add_post(username1, post);
                break;
            case 5:
                printf("Enter the username: ");
                scanf("%19s", username1);
                show_posts(username1);
                break;
            case 6:
                printf("Enter the username: ");
                scanf("%19s", username1);
                show_friends(username1);
                break;
            case 7:
                printf("Enter the username of user 1: ");
                scanf("%19s", username1);
                printf("Enter the username of user 2: ");
                scanf("%19s", username2);
                show_mutuals(username1, username2);
                break;
            case 8:
                printf("Enter the keyword to search for: ");
                scanf("%99s", keyword);
                search_posts(keyword);
                break;
            case 9:
                save_to_csv();  
                printf("Data saved to posts.csv\n");
                break;
            case 10:
                save_to_csv();  
                exit(0);
        }
    }
}