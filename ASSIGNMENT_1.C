#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WebPage {
    int identifier;
    char address[100];
    struct WebPage* next_page;
    struct WebPage* previous_page;
} WebPage;

typedef struct NavigationSystem {
    WebPage* active_page;
    int id_tracker;
} NavigationSystem;

NavigationSystem* initializeNavigation() {
    NavigationSystem* nav = (NavigationSystem*)malloc(sizeof(NavigationSystem));
    nav->active_page = NULL;
    nav->id_tracker = 0;
    return nav;
}

void launchWebpage(const char* web_address) {
    char system_command[102];
    snprintf(system_command, sizeof(system_command), "start \"\" \"%s\"", web_address);
    system(system_command);
}

void addNewWebpage(NavigationSystem* nav) {
    char web_address[100];
    printf("Enter URL (include https:// or http://): ");
    scanf("%s", web_address);

    WebPage* new_webpage = (WebPage*)malloc(sizeof(WebPage));
    new_webpage->identifier = ++(nav->id_tracker);
    strcpy(new_webpage->address, web_address);
    new_webpage->next_page = NULL;
    new_webpage->previous_page = NULL;

    if (nav->active_page != NULL) {
        nav->active_page->next_page = new_webpage;
        new_webpage->previous_page = nav->active_page;
    }

    nav->active_page = new_webpage;

    printf("Visited: %s (Page ID: %d)\n", new_webpage->address, new_webpage->identifier);
    launchWebpage(new_webpage->address);
}

void navigateBackward(NavigationSystem* nav) {
    if (nav->active_page == NULL || nav->active_page->previous_page == NULL) {
        printf("No previous tab.\n");
        return;
    }
    nav->active_page = nav->active_page->previous_page;
    printf("Moved back to: %s (Page ID: %d)\n", nav->active_page->address, nav->active_page->identifier);
    launchWebpage(nav->active_page->address);
}

void navigateForward(NavigationSystem* nav) {
    if (nav->active_page == NULL || nav->active_page->next_page == NULL) {
        printf("No next tab.\n");
        return;
    }
    nav->active_page = nav->active_page->next_page;
    printf("Moved forward to: %s (Page ID: %d)\n", nav->active_page->address, nav->active_page->identifier);
    launchWebpage(nav->active_page->address);
}

void displayCurrentPage(NavigationSystem* nav) {
    if (nav->active_page == NULL) {
        printf("No current tab.\n");
    } else {
        printf("Current Tab -> Page ID: %d, URL: %s\n", nav->active_page->identifier, nav->active_page->address);
        launchWebpage(nav->active_page->address);
    }
}

void showNavigationHistory(NavigationSystem* nav) {
    WebPage* navigation_ptr = nav->active_page;
    
    while (navigation_ptr && navigation_ptr->previous_page != NULL) {
        navigation_ptr = navigation_ptr->previous_page;
    }
    
    printf("\nBrowser History:\n");
    while (navigation_ptr != NULL) {
        printf("Page ID: %d, URL: %s%s\n", navigation_ptr->identifier, navigation_ptr->address,
               (navigation_ptr == nav->active_page) ? " <-- Current Tab" : "");
        navigation_ptr = navigation_ptr->next_page;
    }
}

void removeCurrentPage(NavigationSystem* nav) {
    if (nav->active_page == NULL) {
        printf("No tab to close.\n");
        return;
    }
    
    WebPage* page_to_remove = nav->active_page;
    
    if (page_to_remove->previous_page) {
        page_to_remove->previous_page->next_page = page_to_remove->next_page;
    }
    if (page_to_remove->next_page) {
        page_to_remove->next_page->previous_page = page_to_remove->previous_page;
    }
    
    if (page_to_remove->next_page) {
        nav->active_page = page_to_remove->next_page;
    } else if (page_to_remove->previous_page) {
        nav->active_page = page_to_remove->previous_page;
    } else {
        nav->active_page = NULL;
    }
    
    printf("Closed Tab -> Page ID: %d, URL: %s\n", page_to_remove->identifier, page_to_remove->address);
    free(page_to_remove);
}

void cleanupNavigation(NavigationSystem* nav) {
    WebPage* navigation_ptr = nav->active_page;
    
    while (navigation_ptr && navigation_ptr->previous_page != NULL) {
        navigation_ptr = navigation_ptr->previous_page;
    }
    
    while (navigation_ptr != NULL) {
        WebPage* page_to_delete = navigation_ptr;
        navigation_ptr = navigation_ptr->next_page;
        free(page_to_delete);
    }
    
    free(nav);
}

int main() {
    NavigationSystem* nav_system = initializeNavigation();
    int user_choice;

    do {
        printf("\n===== Browser Menu =====\n");
        printf("1. Visit a New Page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Show Current Tab\n");
        printf("5. Close Current Tab\n");
        printf("6. Show History\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &user_choice);

        switch (user_choice) {
            case 1: addNewWebpage(nav_system); break;
            case 2: navigateBackward(nav_system); break;
            case 3: navigateForward(nav_system); break;
            case 4: displayCurrentPage(nav_system); break;
            case 5: removeCurrentPage(nav_system); break;
            case 6: showNavigationHistory(nav_system); break;
            case 7: printf("Exiting browser...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (user_choice != 7);

    cleanupNavigation(nav_system);
    return 0;
}
