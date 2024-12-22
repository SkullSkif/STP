#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <unordered_map>

const int NUM_DICE = 5;
const int MIN_VALUE = 1;
const int MAX_VALUE = 6;

void calculateScores(const std::array<int, NUM_DICE>& dice) {
    std::unordered_map<int, int> counts;
    std::array<int, MAX_VALUE> sum = {0, 0, 0, 0, 0, 0};
    for (int die : dice) {
        counts[die]++;
        sum[die-1] += die;
    }
    
    // Calculate scores for each category
    // int ones = counts[1] * 1;
    // int twos = counts[2] * 2;
    // int threes = counts[3] * 3;
            
    // int fours = counts[4] * 4;
    // int fives = counts[5] * 5;
    // int sixes = counts[6] * 6;


    int threeOfAKind = 0;
    int fourOfAKind = 0;
    bool fullHouse = false;
    bool smallStraight = false;
    bool largeStraight = false;
    bool yahtzee = false;
    int chance = 0;
std::cout << counts.size() << "  ";
    for (const auto& [value, count] : counts) {
        chance += value * count;
        if (count >= 3) {
            threeOfAKind = chance; // Score for Three of a Kind
        }
        if (count >= 4) {
            fourOfAKind = chance; // Score for Four of a Kind
        }

        if (counts.size() == 2) {
            for (const auto& [value, count] : counts) {
                if (count == 2) {
                    fullHouse = true; // Если есть пара
        }
        if (count == 3) {
            fullHouse = true; // Если есть тройка
        }
    }
}
        if (count == 1) {
            smallStraight = (counts.count(1) && counts.count(2) && counts.count(3) && counts.count(4)) ||
                (counts.count(2) && counts.count(3) && counts.count(4) && counts.count(5)) ||
                (counts.count(3) && counts.count(4) && counts.count(5) && counts.count(6));
            largeStraight = (counts.count(1) && counts.count(2) && counts.count(3) && counts.count(4) && counts.count(5)) ||
                (counts.count(2) && counts.count(3) && counts.count(4) && counts.count(5) && counts.count(6));
        }
        if (count == 5) {
            yahtzee = true; // Yahtzee
        }
    }

    // Output scores
    std::cout << "Ones:             " << sum[0] << std::endl;
    std::cout << "Twos:             " << sum[1] << std::endl;
    std::cout << "Threes:           " << sum[2] << std::endl;
    std::cout << "Fours:            " << sum[3] << std::endl;
    std::cout << "Fives:            " << sum[4] << std::endl;
    std::cout << "Sixes:            " << sum[5] << std::endl;
    std::cout << "Three Of A Kind:  " << threeOfAKind << std::endl;
    std::cout << "Four Of A Kind:   " << fourOfAKind << std::endl;
    std::cout << "Full House:       " << (fullHouse ? 25 : 0) << std::endl;
    std::cout << "Small Straight:    " << (smallStraight ? 30 : 0) << std::endl;
    std::cout << "Large Straight:    " << (largeStraight ? 40 : 0) << std::endl;
    std::cout << "Yahtzee:         " << (yahtzee ? 50 : 0) << std::endl;
    std::cout << "Chance:           " << chance << std::endl;
}

int main() {
    std::array<int, NUM_DICE> dice;
    std::cout << "Enter five dice values (1-6): ";
    
    for (int i = 0; i < NUM_DICE; ++i) {
        std::cin >> dice[i];
        if (dice[i] < MIN_VALUE || dice[i] > MAX_VALUE) {
            std::cerr << "Error: invalid dice value" << std::endl;
            return 1; // Exit with non-zero code
        }
    }

    calculateScores(dice);
    return 0; // Exit with zero code
}