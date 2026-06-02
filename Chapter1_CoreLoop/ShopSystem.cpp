#include "ShopSystem.h"
#include "joker_variation/FlatChipJoker.h"
#include "joker_variation/PairJoker.h"
#include "joker_variation/MultiplierJoker.h"
#include "joker_variation/ScaryFaceJoker.h"
#include "joker_variation/AbstractJoker.h"
#include "joker_variation/AceBoosterJoker.h"
#include "joker_variation/LustyJoker.h"
#include "joker_variation/WrathfulJoker.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

struct JokerEntry {
    int id;
    std::string name;
    std::string desc;
};

static const std::vector<JokerEntry> JOKER_POOL = {
    {0, "Flat Chip Joker",  "+20 Chips each hand"},
    {1, "Pair Joker",       "+4 Mult if hand = Pair"},
    {2, "Multiplier Joker", "+2 Mult always active"},
    {3, "Scary Face",       "+30 Mult if J/Q/K is played"},
    {4, "Abstract Joker",   "+3 Mult for each Joker owned"},
    {5, "Ace Booster",      "+15 Chips for each Ace played"},
    {6, "Lusty Joker",      "+30 Chips if Heart is played"},
    {7, "Wrathful Joker",   "+30 Chips if Spade is played"},
};

static std::unique_ptr<Joker> makeJoker(int id) {
    switch (id) {
        case 0: return std::make_unique<FlatChipJoker>();
        case 1: return std::make_unique<PairJoker>();
        case 2: return std::make_unique<MultiplierJoker>();
        case 3: return std::make_unique<ScaryFaceJoker>();
        case 4: return std::make_unique<AbstractJoker>();
        case 5: return std::make_unique<AceBoosterJoker>();
        case 6: return std::make_unique<LustyJoker>();
        case 7: return std::make_unique<WrathfulJoker>();
        default: return nullptr;
    }
}

void ShopSystem::openShop(SessionState& session, ScoringRule& scoringRule) {
    std::cout << "\n=================================\n";
    std::cout << "       WELCOME TO THE SHOP       \n";
    std::cout << "=================================\n";

    // Ambil 3 joker acak dari pool yang BELUM dimiliki (tanpa duplikat)
    static std::mt19937 g(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> poolIds;
    for (auto& e : JOKER_POOL) {
        if (!scoringRule.hasJoker(e.name)) {
            poolIds.push_back(e.id);
        }
    }
    std::shuffle(poolIds.begin(), poolIds.end(), g);

    // Slot shop: 3 joker (jika sisa joker < 3, slot akan -1)
    std::vector<int> shopSlots = {-1, -1, -1};
    for (size_t i = 0; i < 3 && i < poolIds.size(); ++i) {
        shopSlots[i] = poolIds[i];
    }

    while (true) {
        int currentJokers = scoringRule.getJokerCount();
        
        std::cout << "\nYour Money : $" << session.money << "\n";
        std::cout << "Joker Slots: " << currentJokers << " / 5\n";
        if (currentJokers >= 5) {
            std::cout << "[WARNING] Slots full! Buying a new Joker will REPLACE: " << scoringRule.getOldestJokerName() << "\n";
        }
        std::cout << "Available Jokers (Cost $4 each):\n";
        std::cout << "-------------------------------------------\n";

        for (int i = 0; i < 3; ++i) {
            if (shopSlots[i] == -1) {
                std::cout << "  " << i << ". [SOLD OUT]\n";
                continue;
            }
            const JokerEntry& e = JOKER_POOL[shopSlots[i]];
            std::cout << "  " << i << ". " << e.name << "  ->  " << e.desc << "\n";
        }
        std::cout << "-------------------------------------------\n";
        std::cout << "  3. Leave Shop\n";
        std::cout << "Choose (0-3): ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 3) {
            std::cout << "Leaving shop...\n";
            break;
        }

        if (choice >= 0 && choice < 3) {
            if (shopSlots[choice] == -1) {
                std::cout << "Slot is already sold out!\n";
            } else if (session.money >= 4) {
                session.money -= 4;
                auto newJoker = makeJoker(shopSlots[choice]);
                if (newJoker) {
                    std::cout << "Purchased " << newJoker->getName() << "! Immediately active.\n";
                    scoringRule.addJoker(std::move(newJoker));
                }
                shopSlots[choice] = -1;
            } else {
                std::cout << "Not enough money! (Requires $4)\n";
            }
        }
    }
}
