// Dining Philosophers - Naive Implementation (DEADLOCKS!)
//
// This program demonstrates the classic deadlock scenario.
// Each philosopher tries to eat 5 times. If the program completes, there's no deadlock.
// If it freezes, deadlock has occurred!
//
// The deadlock happens because:
// 1. Each philosopher picks up their LEFT chopstick first
// 2. Then tries to pick up their RIGHT chopstick
// 3. If all 5 do this simultaneously, each has their left but needs their right
// 4. Each right chopstick is someone else's left - circular wait!

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex chopsticks[5];
std::mutex coutMutex;  // Protect console output

const int BITES_PER_PHILOSOPHER = 5;

void philosopher(int id) {
    int left = id;
    int right = (id + 1) % 5;

    for (int bite = 1; bite <= BITES_PER_PHILOSOPHER; bite++) {
        // Think
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Philosopher " << id << " thinking\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Get hungry, pick up LEFT chopstick first
        if (id == 4) {
            chopsticks[right].lock();
            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "Philosopher " << id << " picked up right chopstick (C" << right << ")\n";
            }

            // Small delay makes deadlock more likely to occur
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            // Try to pick up RIGHT chopstick - THIS IS WHERE WE GET STUCK
            chopsticks[left].lock();
            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "Philosopher " << id << " picked up left chopstick (C" << left << ")\n";
            }
        } else {
            chopsticks[left].lock();
            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "Philosopher " << id << " picked up left chopstick (C" << left << ")\n";
            }

            // Small delay makes deadlock more likely to occur
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            // Try to pick up RIGHT chopstick - THIS IS WHERE WE GET STUCK
            chopsticks[right].lock();
            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "Philosopher " << id << " picked up right chopstick (C" << right << ")\n";
            }
        }

        // Eat
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Philosopher " << id << " eating (bite " << bite << "/" << BITES_PER_PHILOSOPHER << ")\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Put down chopsticks
        chopsticks[right].unlock();
        chopsticks[left].unlock();
    }

    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "Philosopher " << id << " finished all " << BITES_PER_PHILOSOPHER << " bites!\n";
}

int main() {
    std::cout << "=== Dining Philosophers (Deadlock Demo) ===\n";
    std::cout << "Each philosopher needs to eat " << BITES_PER_PHILOSOPHER << " times.\n";
    std::cout << "If the program completes, no deadlock occurred.\n";
    std::cout << "If it freezes, deadlock has occurred!\n\n";

    std::thread philosophers[5];

    // Start all philosophers
    for (int i = 0; i < 5; i++) {
        philosophers[i] = std::thread(philosopher, i);
    }

    // Wait for all to finish
    for (int i = 0; i < 5; i++) {
        philosophers[i].join();
    }

    std::cout << "\n=== SUCCESS! All philosophers finished eating! ===\n";
    std::cout << "No deadlock occurred.\n";

    return 0;
}
