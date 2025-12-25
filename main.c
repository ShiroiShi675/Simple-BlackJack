// Things to add: split, double down, betting system
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define DIM_STRING 30
#define NUM_CARDS 52
#define NUM_SUIT_CARDS 13
#define BLACKJACK 21
#define DEALER_MAX 16
#define ACE_UNDER_BLACKJACK 11
#define ACE 1

typedef enum {STAND, HIT, SPLIT, DOUBLE_DOWN} Game_Choice;
typedef enum {EXIT, PLAY} Menu_Choice;
typedef enum {CLUBS, SPADES, DIAMONDS, HEARTS} Suit;

typedef struct {
    int value;
    Suit suit;
} Card;

void print_menu();
Card* deal_card(Card* hand, int* num_cards_hand);
Card* initial_hand(Card* hand, int* num_cards_hand);
Card* initial_dealer_hand(Card* dealer_hand, int* num_cards_dealer_hand);
void print_hands(Card* hand, Card* dealer_hand, int num_cards_hand, int hand_value);
int calculate_sum(Card* hand, int num_cards_hand);
void print_final_hands(Card* hand, Card* dealer_hand, int num_cards_hand, int num_cards_dealer_hand, int hand_sum, int dealer_hand_sum);
bool compare_scores(int hand_sum, int dealer_hand_sum, Card** dealer_hand, int* num_cards_dealer_hand);
void print_banner();

void print_menu() {
    printf("1) Start game");
    printf("\n0) Exit");
    printf("\nChoice: ");
}
Card* initial_hand(Card* hand, int* num_cards_hand) {
    hand = (Card*) malloc(2 * sizeof(Card));
    if (hand == NULL) {
        exit(EXIT_FAILURE);
    }
    *num_cards_hand = 2;
    hand[0].value = 1 * rand() % (10) + 1;
    hand[0].suit = rand() % (4);
    hand[1].value = 1 * rand() % (10) + 1;
    hand[1].suit = rand() % (4);
    return hand;
}
Card* initial_dealer_hand(Card* dealer_hand, int* num_cards_dealer_hand) {
    dealer_hand = (Card*) malloc(2 * sizeof(Card));
    if (dealer_hand == NULL) {
        exit(EXIT_FAILURE);
    }
    *num_cards_dealer_hand = 2;
    dealer_hand[0].value = 1 * rand() % (10) + 1;
    dealer_hand[0].suit = 1 * rand() % (4);
    dealer_hand[1].value = 1 * rand() % (10) + 1;
    dealer_hand[1].suit = 1 * rand() % (4);
    return dealer_hand;
}
void print_hands(Card* hand, Card* dealer_hand, int num_cards_hand, int hand_value) {
    printf("\n-------HANDS-------");
    switch (dealer_hand[0].suit) {
        case CLUBS:
            printf("\nDealer: %d CLUBS | ??? |", dealer_hand[0].value);
            break;
        case HEARTS:
            printf("\nDealer: %d HEARTS | ??? |", dealer_hand[0].value);
            break;
        case DIAMONDS:
            printf("\nDealer: %d DIAMONDS | ??? |", dealer_hand[0].value);
            break;
        case SPADES:
            printf("\nDealer: %d SPADES | ??? |", dealer_hand[0].value);
            break;
    }
    int i = 0;
    printf("\nValue: ???");
    printf("\nYour Hand: ");
    for (i = 0; i < num_cards_hand; i++) {
        switch (hand[i].suit) {
            case CLUBS:
                printf("%d CLUBS | ", hand[i].value);
                break;
            case HEARTS:
                printf("%d HEARTS | ", hand[i].value);
                break;
            case DIAMONDS:
                printf("%d DIAMONDS | ", hand[i].value);
                break;
            case SPADES:
                printf("%d SPADES | ", hand[i].value);
                break;
        }
    }
    printf("\nValue: %d", hand_value);
    printf("\n-------HANDS-------");
    printf("\n");
}
Card* deal_card(Card* hand, int* num_cards_hand) {
    hand = (Card*) realloc(hand, ((*num_cards_hand) + 1) * sizeof(Card));
    hand[*num_cards_hand].value = 1 * rand() % (10) + 1;
    hand[*num_cards_hand].suit = 1 * rand() % (4);
    (*num_cards_hand)++;
    return hand;
}
int calculate_sum(Card* hand, int num_cards_hand) {
    int sum = 0;
    int i;
    for (i = 0; i < num_cards_hand; i++) {
        if (hand[i].value == ACE) {
            sum += ACE_UNDER_BLACKJACK;
        } else {
            sum += hand[i].value;
        }
    }
    for (i = 0; i < num_cards_hand; i++) {
        if (hand[i].value == ACE && sum > BLACKJACK) {
            sum -= 10;
        }
    }
    return sum;
}
void print_final_hands(Card* hand, Card* dealer_hand, int num_cards_hand, int num_cards_dealer_hand, int hand_sum, int dealer_hand_sum) {
    printf("\n-------HANDS-------");
    printf("\nDealer Hand: ");
    int i = 0;
    for (i = 0; i < num_cards_dealer_hand; i++) {
        switch (dealer_hand[i].suit) {
            case CLUBS:
                printf("%d CLUBS | ", dealer_hand[i].value);
                break;
            case HEARTS:
                printf("%d HEARTS | ", dealer_hand[i].value);
                break;
            case DIAMONDS:
                printf("%d DIAMONDS | ", dealer_hand[i].value);
                break;
            case SPADES:
                printf("%d SPADES | ", dealer_hand[i].value);
                break;
        }
    }
    printf("\nValue: %d", dealer_hand_sum);
    printf("\nYour Hand: ");
    for (i = 0; i < num_cards_hand; i++) {
        switch (hand[i].suit) {
            case CLUBS:
                printf("%d CLUBS | ", hand[i].value);
                break;
            case HEARTS:
                printf("%d HEARTS | ", hand[i].value);
                break;
            case DIAMONDS:
                printf("%d DIAMONDS | ", hand[i].value);
                break;
            case SPADES:
                printf("%d SPADES | ", hand[i].value);
                break;
        }
    }
    printf("\nValue: %d", hand_sum);
    printf("\n-------HANDS-------");
    printf("\n");
}
bool compare_scores(int hand_sum, int dealer_hand_sum, Card** dealer_hand, int* num_cards_dealer_hand) {
    while (dealer_hand_sum < DEALER_MAX) {
        *dealer_hand = deal_card(*dealer_hand, num_cards_dealer_hand);
        dealer_hand_sum = calculate_sum(*dealer_hand, *num_cards_dealer_hand);
    }
    if (dealer_hand_sum > BLACKJACK) {
        return true;
    }
    if (hand_sum >= dealer_hand_sum) {
        return true;
    }
    return false;
}
void print_banner() {
    printf(
        "\n"
        "██████╗ ██╗      █████╗  ██████╗██╗  ██╗     ██╗ █████╗  ██████╗██╗  ██╗\n"
        "██╔══██╗██║     ██╔══██╗██╔════╝██║ ██╔╝     ██║██╔══██╗██╔════╝██║ ██╔╝\n"
        "██████╔╝██║     ███████║██║     █████╔╝      ██║███████║██║     █████╔╝ \n"
        "██╔══██╗██║     ██╔══██║██║     ██╔═██╗ ██   ██║██╔══██║██║     ██╔═██╗ \n"
        "██████╔╝███████╗██║  ██║╚██████╗██║  ██╗╚█████╔╝██║  ██║╚██████╗██║  ██╗\n"
        "╚═════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝ ╚════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝\n"
        "\n"
        "                        Simple Blackjack in C\n"
        "                           by ShiroiShi\n"
        "\n"
    );
}


int main(void) {
    srand(time(NULL));
    print_banner();
    Menu_Choice menu_choice = 0;
    Card* hand = NULL;
    Card* dealer_hand = NULL;
    int num_cards_hand = 0;
    int num_cards_dealer_hand = 0;
    Game_Choice game_choice = 0;
    int hand_value = 0;
    int dealer_hand_value = 0;
    bool outcome;
    bool busted = false;
    bool freed = false;

    do {
        if (!freed) {
            free(hand);
            free(dealer_hand);
        }
        num_cards_hand = 0;
        num_cards_dealer_hand = 0;
        print_menu();
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case EXIT:
                printf("Bye!");
                break;
            case PLAY:
                hand = initial_hand(hand, &num_cards_hand);
                dealer_hand = initial_dealer_hand(dealer_hand, &num_cards_dealer_hand);
                hand_value = calculate_sum(hand, num_cards_hand);
                dealer_hand_value = calculate_sum(dealer_hand, num_cards_dealer_hand);
                compare_scores(hand_value, dealer_hand_value, &dealer_hand, &num_cards_dealer_hand);

                do {
                    hand_value = calculate_sum(hand, num_cards_hand);
                    dealer_hand_value = calculate_sum(dealer_hand, num_cards_dealer_hand);
                    if (hand_value > BLACKJACK) {
                        print_final_hands(hand, dealer_hand, num_cards_hand, num_cards_dealer_hand, hand_value, dealer_hand_value);
                        if (dealer_hand_value > BLACKJACK) {
                            printf("DRAW!\n\n");
                        } else {
                            printf("LOSS!\n\n");
                        }
                        game_choice = STAND;
                        busted = true;
                    } else {
                        print_hands(hand, dealer_hand, num_cards_hand, hand_value);
                        printf("\nWhat do you want to do?\n");
                        printf("0) STAND\n");
                        printf("1) HIT\n");
                        printf("Choice: ");
                        scanf("%d", &game_choice);
                    }
                    switch (game_choice) {
                        case STAND:
                            if (!busted) {
                                dealer_hand_value = calculate_sum(dealer_hand, num_cards_dealer_hand);
                                outcome = compare_scores(hand_value, dealer_hand_value, &dealer_hand, &num_cards_dealer_hand);
                                print_final_hands(hand, dealer_hand, num_cards_hand, num_cards_dealer_hand, hand_value, dealer_hand_value);
                                if (outcome) {
                                    if (hand_value == dealer_hand_value) {
                                        printf("DRAW!\n\n");
                                    } else if (hand_value == BLACKJACK) {
                                        printf("BLACKJACK!\n\n");
                                    } else {
                                        printf("WIN!\n\n");
                                    }
                                } else {
                                    printf("LOSS!\n\n");
                                }
                            }
                            break;
                        case HIT:
                            hand = deal_card(hand, &num_cards_hand);
                            break;
                        default:
                            printf("Enter a valid choice!\n");
                            break;
                    }
                } while (game_choice != STAND);
                break;
            default:
                printf("Enter a valid choice!\n");
                break;
        }
        busted = false;
        freed = false;
    } while (menu_choice != EXIT);

    exit(EXIT_SUCCESS);
}
