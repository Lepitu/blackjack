#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOTAL_CARDS 52
#define CARD_VALUES 13
#define MAX_HAND 10

char *values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};

struct card {
    char *value;
    char *suit;
    int numericValue;
};

struct card deck[TOTAL_CARDS];
struct card playerHand[MAX_HAND];
int numPlayerCards = 0;
int playerSum = 0;
char choice;

void initializeDeck() {
    for (int i = 0; i < TOTAL_CARDS; i++) {
        deck[i].value = values[i % CARD_VALUES];
        deck[i].suit = suits[i / CARD_VALUES];

        if (strcmp(deck[i].value, "A") == 0) {
            deck[i].numericValue = 11;
        } else if (strcmp(deck[i].value, "J") == 0 || strcmp(deck[i].value, "Q") == 0 || strcmp(deck[i].value, "K") == 0) {
            deck[i].numericValue = 10;
        } else {
            deck[i].numericValue = atoi(deck[i].value);
        }
    }
}

void shuffleDeck() {
    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARDS; i++) {
        int j = rand() % TOTAL_CARDS;
        struct card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void showCard(struct card c) {
    printf("  %s of %s\n", c.value, c.suit);
}

int sumHand(struct card hand[], int numCards) {
    int sum = 0;
    for (int i = 0; i < numCards; i++) {
        sum += hand[i].numericValue;
    }
    return sum;
}

int main() {
    initializeDeck();
    shuffleDeck();

    printf("Welcome to Blackjack!\n");

    playerHand[numPlayerCards++] = deck[0];
    playerHand[numPlayerCards++] = deck[1];
    playerSum = sumHand(playerHand, numPlayerCards);

    printf("Your cards:\n");
    showCard(playerHand[0]);
    showCard(playerHand[1]);
    printf("Total sum: %d\n", playerSum);

    while (playerSum < 21) {
        printf("Do you want another card? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            if (numPlayerCards < TOTAL_CARDS) {
                playerHand[numPlayerCards] = deck[numPlayerCards + 2];
                playerSum = sumHand(playerHand, ++numPlayerCards);

                for (int i = 0; i < numPlayerCards; i++) {
                    if (playerHand[i].numericValue == 11 && playerSum > 21) {
                        playerHand[i].numericValue = 1;
                        playerSum -= 10;
                    }
                }

                printf("New card:\n");
                showCard(playerHand[numPlayerCards - 1]);
                printf("Total sum: %d\n", playerSum);
            } else {
                printf("No more cards left in the deck!\n");
                break;
            }
        } else {
            break;
        }
    }

    if (playerSum == 21) {
        printf("Blackjack! You won.\n");
    } else if (playerSum > 21) {
        printf("You busted. Game over.\n");
    } else {
        printf("You stand with %d. Game over.\n", playerSum);
    }

    return 0;
}
