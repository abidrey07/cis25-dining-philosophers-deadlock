## Part 1: Observe the Deadlock (5 points)

1. Run the dining philosophers demo: `./philosophers`
2. Each philosopher needs to eat 5 bites. If successful, you'll see "SUCCESS! All philosophers finished eating!"
3. Watch for deadlock (program stops producing output but doesn't exit)
4. You may need to run it several times - deadlock doesn't always happen immediately
5. Press Ctrl+C to kill the program when it deadlocks

**Question:** What was the last output you saw before the program froze? (Copy the last few lines)

```
Philosopher 0 picked up left chopstick (C0)
Philosopher 2 picked up left chopstick (C2)
Philosopher 3 picked up left chopstick (C3)
Philosopher 1 picked up left chopstick (C1)
Philosopher 4 picked up left chopstick (C4)
```
Program froze here.