#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Card {
    string rank;
    int value;
    char suit;
};

list<Card> initializeDeck() {
    list<Card> deck;
    string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    char suits[] = { 'H', 'D', 'S', 'C' };
    int values[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

    for (const char& s : suits) {
        for (int i = 0; i < 13; i++) {
            Card card;
            card.rank = ranks[i];
            card.value = values[i];
            card.suit = s;
            deck.push_back(card);
        }
    }

    return deck;
}

void shuffleDeck(list<Card>& deck) {
    srand(time(0));
    for (int i = 0; i < deck.size(); i++) {
        auto it1 = deck.begin();
        advance(it1, i);
        int ridx = rand() % deck.size();
        auto it2 = deck.begin();
        advance(it2, ridx);
        swap(*it1, *it2);
    }
}

Card deal(list<Card>& deck) {
    Card c = deck.back();
    deck.pop_back();
    return c;
}

int calHandValue(const list<Card>& hand) {
    int total = 0;
    for (const auto& card : hand) {
        total += card.value;
    }
    return total;
}

bool isBust(const list<Card>& hand) {
    return calHandValue(hand) > 21;
}

int main() {
    while (true) {
        list<Card> deck = initializeDeck();
        shuffleDeck(deck);
        list<Card> playerHand, dealerHand;
        playerHand.push_back(deal(deck));
        dealerHand.push_back(deal(deck));
        playerHand.push_back(deal(deck)); // Player gets two face up  cards
        dealerHand.push_back(deal(deck)); // Dealer gets one face up card and one hole card
        cout << "*********************************************************************************************************************\n\n";
        cout << "\t\t\t\t\t\t BlackJack\n\n";
        cout << "*********************************************************************************************************************\n\n";
        cout << "\n\n\n";
        cout << "Player's Hand: " << playerHand.begin()->rank << " of " << playerHand.begin()->suit << ", " << next(playerHand.begin(), 1)->rank << " of " << next(playerHand.begin(), 1)->suit << endl;
        cout << "\n";
        cout << "Dealer's Hand: " << dealerHand.begin()->rank << " of " << dealerHand.begin()->suit << endl;

        // Player's turn
        while (true) {
            char choice;
            cout << "Do you want to hit (h) or stand (s)? ";
            cin >> choice;
            if (choice == 'h') {
                playerHand.push_back(deal(deck));
                cout << "Player's Hand: ";
                for (const auto& card : playerHand) {
                    cout << card.rank << " of " << card.suit << ", ";
                }
                cout << endl;
                if (isBust(playerHand)) {
                    cout << "Bust! Dealer wins.\n";
                    break;
                }
            }
            else if (choice == 's') {
                break; // Player stands
            }
            else {
                cout << "Invalid choice. Please enter 'h' or 's'.\n";
            }
        }
        // Dealer's turn
        while (calHandValue(dealerHand) < 17 && !isBust(playerHand)) {
            dealerHand.push_back(deal(deck));
        }
        cout << "Dealer's Hand: ";
        for (const auto& card : dealerHand) {
            cout << card.rank << " of " << card.suit << ", ";
        }
        cout << endl;
        if (isBust(dealerHand) || calHandValue(playerHand) > calHandValue(dealerHand)) {
            cout << "Player wins!\n";
        }
        else if (calHandValue(playerHand) < calHandValue(dealerHand)) {
            cout << "Dealer wins!\n";
        }
        else {
            cout << "It's a tie!\n";
        }

        char playAgain;
        cout << "Do you want to play again? (y/n) ";
        cin >> playAgain;
        if (playAgain != 'y') {
            break;
        }
    }

    return 0;
}

