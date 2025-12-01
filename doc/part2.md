## Part 2: Explain the Deadlock (5 points)

**Question:** In your own words, explain why deadlock occurs. What is each philosopher waiting for, and why can't any of them proceed?
Deadlock occurs because all functions await on occupied resources. In this case, the philosophers are waiting
for the chopstick on their right, which is occupied by other philosophers as they picked up their left chopstick. 
None of them can proceed because the condition for the philosophers to eat is that they must possess both chopsticks, 
which they do not because of the deadlock. 